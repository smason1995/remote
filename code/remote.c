/*******************************************
 * Remote, SSH/SFTP remote profile manager *
 * author: Sydney Ann Mason                *
 * version: 20190123                       *
 *******************************************/

/***********
 * Imports *
 ***********/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<errno.h>

#include "dll.h"

/**************************
 * Signature Declarations *
 **************************/
int main(int, char**);
int remote_action(char*, char*);
int add_profile(char*, char*);
int remove_profile(char*);
void list_profiles();
void help();

/**************************************
 * Function: Main                     *
 * Description:                       *
 *      Parses CLI args and calls the *
 *      appropriate function          *
 **************************************/
int main(int argc, char* argv[]){
    //Checks first argument to determine next course of action
    if(strcmp(argv[1], "ssh") == 0 || strcmp(argv[1], "sftp") == 0){
        if(argc != 3){
            printf("Incorrect number of args\n%s takes 1 arguement", argv[1]);
            return 1;
        }
        remote_action(argv[1], argv[2]);
    }
    else if(strcmp(argv[1], "list") == 0){
        if(argc != 2){
            printf("Incorrect number of args\n%s takes no arguement", argv[1]);
            return 1;
        }
        list_profiles();
    }
    else if(strcmp(argv[1], "save") == 0){
        if(argc != 4){
            printf("Incorrect number of args\n%s takes 2 arguements", argv[1]);
            return 1;
        }
        add_profile(argv[2], argv[3]);
    }
    else if(strcmp(argv[1], "remove") == 0){
        if(argc != 3){
            printf("Incorrect number of args\n%s takes 1 arguement", argv[1]);
            return 1;
        }
        remove_profile(argv[2]);
    }
    else if(strcmp(argv[1], "help") == 0){
        if(argc != 2){
            printf("Incorrect number of args\n%s takes no arguement", argv[1]);
            return 1;
        }
        help();
    }
    else{
        printf("Command:\n\t%s\nis an invalid command\n", argv[1]);
        return 1;
    }

    //Default return value on successful run
    return 0;
}

/***********************************
 * Function: Remote Action         *
 * Description:                    *
 *      executes ssh/sftp protocol *
 ***********************************/
int remote_action(char* cmd, char* profile){
    char* actarr[2]; //command array to be passed into exec

    actarr[0] = cmd; //adds cmd to first position of action array

    if(strchr(profile, '@') != NULL){
        /* puts profile into command array */
        actarr[1] = profile;
    }
    else{
        char* homeDir = getenv("HOME");
        char* path = strcat(homeDir, "/.config/remote/remote_profiles");
        char line[256], name[256], url[256];
        FILE* profFile;
        int exists = 0;

        /* reads list of profiles line by line */
        profFile = fopen(path, "r");
        while(fgets(line, sizeof(line), profFile)){
            /* splits line into tokens */
            strcpy(name, strtok(line, " "));
            strcpy(url, strtok(NULL, " "));

            /* Found profile */
            if(strcmp(name, profile) == 0){
                actarr[1] = url;
                exists = 1;
                break;
            }
        }
        fclose(profFile);

        /* exits because profile doesn't exist */
        if(exists == 0){
            printf("%s not a known profile", name);
            return 1;
        }
    }

    /* assembles args into a string */
    char call[256];
    strcpy(call, actarr[0]);
    strcat(call, " ");
    strcat(call, actarr[1]);

    /* executes call */
    system(call);

    return 0;
}

/************************************
 * Function: Add Profiles           *
 * Description:                     *
 *      Writes a new profile to the *
 *      list of profiles            *
 ************************************/
int add_profile(char* profileName, char* profileURL){
    char* homeDir = getenv("HOME");
    char* path = strcat(homeDir, "/.config/remote/remote_profiles");
    char line[256], name[256], url[256];
    FILE* profFile;
    int exists = 0;

    /* reads list of profiles line by line */
    profFile = fopen(path, "r");
    while(fgets(line, sizeof(line), profFile)){
        /* splits line into tokens */
        strcpy(name, strtok(line, " "));
        strcpy(url, strtok(NULL, " "));

        /* checks to make sure that name and url do not already exist */
        if(strstr(name, profileName) != NULL){
            printf("%s already exists\n", profileName);
            exists = 1;
            break;
        }
        else if(strstr(url, profileURL) != NULL){
            printf("%s already has a profile\n", profileURL);
            exists = 1;
            break;
        }
    }
    fclose(profFile);

    /* exits if profile already exists
     * otherwise, appends new line to file */
    if(exists == 1){
        printf("Failed to write %s\n", profileName);
        return 1;
    }
    else{
        /* assembles new profile pieces to be written */
        strcpy(line, profileName);
        strcat(line, " ");
        strcat(line, profileURL);
        strcat(line, "\n");

        /* appends new profile to the bottom of the list */
        profFile = fopen(path, "a");
        fprintf(profFile, line);
        fclose(profFile);
    }

    return 0;
}

int remove_profile(char* profileName){
    return 0;
}

void list_profiles(){
    char* homeDir = getenv("HOME");
    char* path = strcat(homeDir, "/.config/remote/remote_profiles");
    char line[256];
    FILE* profFile;

    /* reads list of profiles into doubly linked list*/
    profFile = fopen(path, "r");
    while(fgets(line, sizeof(line), profFile)){
        printf("%s", line);
    }
    fclose(profFile);
}

void help(){
    printf("Help Menu:\n");
    printf("ssh\n\texecutes SSH protocol on given profile\n");
    printf("sftp\n\texecutes SFTP protocol on given prifle\n");
    printf("list\n\tlists all currently saved profiles\n");
    printf("save\n\twrites new profiles to the list of currently known profiles\n");
    printf("remove\n\tremoves specified profile from the list of known ones\n");
    printf(" help\n\tdisplays help menu\n");
}
