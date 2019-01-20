/*******************************************
 * Remote, SSH/SFTP remote profile manager *
 * author: Sydney Ann Mason                *
 * version:                                *
 *******************************************/

/***********
 * Imports *
 ***********/
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<string.h>
#include<unistd.h>

using namespace std;

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
    try{
        vector<char*> arguments; //Vector holding CLI arguments

        //Reads argv into arguments
        for(int i = 1; i < argc; i++){
            arguments.push_back(argv[i]);
        }

        //Checks first argument to determine next course of action
        if(strcmp(arguments.at(1), "ssh") == 0 || strcmp(arguments.at(1), "sftp") == 0){
            remote_action(arguments.at(1), arguments.at(2));
        }
        else if(strcmp(arguments.at(1), "print") == 0){
            print_profiles();
        }
        else if(strcmp(arguments.at(1), "save") == 0){
            add_profile(arguments.at(2), arguments.at(3));
        }
        else if(strcmp(arguments.at(1), "remove") == 0){
            remove_profile(arguments.at(2));
        }
        else if(strcmp(arguments.at(1), "help") == 0){
            help();
        }
        else{
            cout << "Command:\n\t" << arguments.at(0) 
                 << endl << "is an invalid argument" 
                 << endl;
        }
    }
    catch(int ex){
        cout << "An err has occurred. Exception number " << ex << endl;
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
    cout << "Help Menu:" << endl
         << "ssh\n\t" << "executes SSH protocol on given profile" << endl
         << "sftp\n\t" << "executes SFTP protocole on given profile" << endl
         << "print\n\t" << "prints all currently saved profiles" << endl
         << "save\n\t" << "writes new profile to the list of currently known profiles" << endl
         << "remove\n\t" << "removes specified profile from the list of known ones" << endl
         << "help\n\t" << "Displays help menu" << endl;
}
