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
    char* actarr[3] = {cmd, profile, NULL}; //command array to be passed into exec
    execvp(actarr[0], actarr);
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
    char line[256];
    FILE* profFile;
    int spaceIndex = -1;
    int exists = 0;
    Dllist* profList = dllist_create();

    /* reads list of profiles into doubly linked list*/
    profFile = fopen(path, "r");
    while(fgets(line, sizeof(line), profFile)){
        dllist_push_back(profList, line);
    }
    fclose(profFile);

    /* checks to make sure that the profile name or url to be written doesn't
     * already exist */
    for(int i = 0; i < profList->size; i++){
        strcpy(line, dllist_read_index(profList, i)); //grabs current name-url pair from list

        /* checks to make sure that name and url do not already exist */
        if(strstr(line, profileName) != NULL){
            printf("%s already exists\n", profileName);
            exists = 1;
            break;
        }
        else if(strstr(line, profileURL) != NULL){
            printf("%s already has a profile\n", profileURL);
            exists = 1;
            break;
        }
    }

    dllist_destroy(profList);

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

void list_profiles(){}

void help(){
    printf("Help Menu:\n");
    printf("ssh\n\texecutes SSH protocol on given profile\n");
    printf("sftp\n\texecutes SFTP protocol on given prifle\n");
    printf("list\n\tlists all currently saved profiles\n");
    printf("save\n\twrites new profiles to the list of currently known profiles\n");
    printf("remove\n\tremoves specified profile from the list of known ones\n");
    printf(" help\n\tdisplays help menu\n");
}
