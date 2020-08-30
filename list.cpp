#include "list.h"

using namespace std;

/*
 * Constructor for List object
 * Sets up profile list, proflist
 */
List::List(){
    ifstream ifile;
    string line = "";

    ifile.open(confdir);

    while(ifile){
        getline(ifile, line);
        proflist.push_back(line);
    }

    ifile.close();
}

/*
 * Destructor for List object
 */
List::~List(){}

/*
 * Appends new profile to the list
 * Returns 0 is successful
 * Returns 1 is failed
 */
int List::write(string profToAdd){
    ofstream ofile;
    try{
        proflist.push_back(profToAdd); // Appends profile to proflist

        ofile.open(confdir); // Opens profiles.txt

        /* Writes proflist to profiles.txt */
        for(int i = 0; i < proflist.size(); i++){
            ofile << proflist[i];
        }

        ofile.close(); // Closes profiles.txt
    }
    catch(exception& e){ // Catches exception
        cout << e.what() << '\n'; // Print thrown exception to console
        return 1; // Task failed
    }

    return 0; // Task succeeded
}

/*
 * Removes profiles from list
 * Returns 0 if successful
 * Returns 1 if failed
 */
int List::remove(string profToRemove){
    bool found = false;
    ofstream ofile;

    /* Finds the given profile to remove and erases it for proflist */
    for(int i = 0; i < proflist.size(); i++){
        string profile = proflist[i].substr(0, proflist[i].find(' '));
        if(profToRemove.compare(profile) == 0){
            found = true;
            proflist.erase(proflist.begin()+i);
            break;
        }
    }

    ofile.open(confdir); // Opens profiles.txt

    /* Writes proflist to profiles.txt */
    for(int i = 0; i < proflist.size(); i++){
        ofile << proflist[i];
    }

    ofile.close(); // Closes profiles.txt
    
    if(found){
        return 0; // Profile found and removed from list
    }
    return 1; // Profile not found and/or not removed from list
}

/*
 * Grabs a given profile from proflist and returns it
 */
string List::get_profile(string profToFind){    
    bool found = false;
    string ret_string = "";

    /* Loops through proflist to find given profile */
    for(int i = 0; i < proflist.size(); i++){
        string profile = proflist[i].substr(0, proflist[i].find(' ')); // Profile name at index
        if(profToFind.compare(profile) == 0){ // Profile found
            found = true;
            ret_string = proflist[i];
            break;
        }
    }

    if(found){
        return ret_string; // Profile was found
    }
    return "Profile not found"; // Profile was not found

}

/*
 * returns the number of profiles
 */
int List::get_size(){
    return proflist.size();
}

/*
 * Displays list profile list to the terminal
 */
int List::print(){
    if(proflist.empty() == false){
        for(int i = 0; i < proflist.size(); i++){
            cout << proflist.at(i) << endl;
        }
    }
    else{
        cout << "Profile list is empty" << endl;
    }

    return 0;
}
