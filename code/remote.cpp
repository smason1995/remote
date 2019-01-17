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
    vector<char*> arguments; //Vector holding CLI arguments

    //Reads argv into arguments
    for(int i = 0; i < argc; i++){
        arguments.push_back(argv[i]);
    }

    //Checks first argument to determine next course of action
    if(arguments.at(0) == "ssh" || arguments.at(0) == "sftp"){
        remote_action(arguments.at(0), arguments.at(1));
    }
    else if(arguments.at(0) == "print"){
        print_profiles();
    }
    else if(arguments.at(0) == "save"){
        add_profile(arguments.at(1), arguments.at(2));
    }
    else if(arguments.at(0) == "remove"){
        remove_profile(arguments.at(1));
    }
    else if(arguments.at(0) == "help"){
        help();
    }
    else{
        cout << "Command:\n\t" << arguments.at(0) 
             << endl << "is an invalid argument" 
             << endl;
    }

    //Default return value on successful run
    return 0;
}
