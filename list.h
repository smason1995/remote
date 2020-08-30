#pragma once

#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<exception>

class List {
    public:
        List(); // Constructor
        ~List(); // Destructor
        int write (std::string); // Adds new profile to profiles.txt
        int remove (std::string); // Deletes existing profile from profiles.txt
        std::string get_profile (std::string); // Returns a specified profile from profiles.txt
        int get_size (); // Returns the number of profiles in profiles.txt
        int print (); // Displays all of the existing profiles the terminal
    private:
        std::string confdir = getenv("HOME") + std::string("/.config/remote/profiles.txt");
        std::vector<std::string> proflist;
        FILE *fp;
};
