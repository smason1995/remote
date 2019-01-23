/*******************************************
 * Remote, SSH/SFTP remote profile manager *
 * author: Sydney Ann Mason                *
 * version: 20190123                       *
 *******************************************/

/***********
 * Imports *
 ***********/
#include<stdio.h>
#include<string.h>
#include<unistd.h>

/**************************
 * Signature Declarations *
 **************************/
int main(int, char**);
int remote_action(char*, char*);
int add_profile(char*, char*);
int remove_profile(char*);
void print_profiles();
void help();

/******************
 * Function: Main *
 ******************/
int main(int argc, char* argv[]){
    //Checks first argument to determine next course of action
    if(strcmp(argv[1], "ssh") == 0 || strcmp(argv[1], "sftp") == 0){
        remote_action(argv[1], argv[2]);
    }
    else if(strcmp(argv[1], "print") == 0){
        print_profiles();
    }
    else if(strcmp(argv[1], "save") == 0){
        add_profile(argv[2], argv[3]);
    }
    else if(strcmp(argv[1], "remove") == 0){
        remove_profile(argv[2]);
    }
    else if(strcmp(argv[1], "help") == 0){
        help();
    }
    else{
        printf("Command:\n\t%s\nis an invalid command\n", argv[0]);
    }

    //Default return value on successful run
    return 0;
}

int remote_action(char* cmd, char* profile){
    return 0;
}

int add_profile(char* profileName, char* profileURL){
    return 0;
}

int remove_profile(char* profileName){
    return 0;
}

void print_profiles(){}

void help(){
    printf("Help Menu:\n");
    printf("ssh\n\texecutes SSH protocol on given profile\n");
    printf("sftp\n\texecutes SFTP protocol on given prifle\n");
    printf("print\n\tprints all currently saved profiles\n");
    printf("save\n\twrites new profiles to the list of currently known profiles\n");
    printf("remove\n\tremoves specified profile from the list of known ones\n");
    printf(" help\n\tdisplays help menu\n");
}
