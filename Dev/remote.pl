#! /usr/bin/perl
#
#-----------------------------------#
# PROGRAM: SSH/SFTP Profile Manager #
# AUTHOR:  Sydney Ann Mason         #
# VERSION: 20181126                 #
#-----------------------------------#

#---------#
# Pragmas #
#---------#
use strict;
use warnings;
use IO::File;
use File::HomeDir;
use Path::Tiny;

#--------------------------------------#
# Subroutine: Main                     #
#                                      #
# Description                          #
# Determines what action will be taken #
#--------------------------------------#
sub main{
    my @args = @ARGV; #CLI arguments

    #Conditionals that determine what action will be taken
    if($args[0] eq 'ssh' || $args[0] eq 'sftp'){
        remote_action(@args);
    }
    elsif($args[0] eq 'save'){
        profile_maint(@args);
    }
    elsif($args[0] eq 'print-profiles'){
        print_profiles(@args);
    }
    elsif($args[0] eq 'help'){
        help_menu(@args);
    }
    elsif($args[0] eq 'remove'){
        remove(@args);
    }
    else{
        println("$args[0] is an invalid command.\n",
                "Run `remote help` for assistance in finding the right command");
    }
}

#-----------------------------------------#
# Subroutine: remote_action               #
#                                         #
# Description:                            #
# Executes [SSH|SFTP] protocol on profile #
#-----------------------------------------#
sub remote_action{
    my @args = @_; #parameters array
    my @file_contents; #contents of the file
    my $args_num = scalar @args; #number of received parameters
    my $file = 'remote_profiles'; #file that is the profile is written into 
    my $profiles_dir; #holds path to directory of profiles
    my $file_ptr; #var to hole file reference
    my $url_details = ''; #connection url for remote action

    #checks if the correct nunmber of arguments have been given
    if($args_num > 2){
        println('Invalid number of arguements given. ',
                "Expected 2, was given $args_num.\n",
                "Proper format is: remote $args[0] [remote server profile]");
        return 1;
    }

    #checks to make sure that the profiles directory exists
    $profiles_dir = File::HomeDir->my_home . '/.remote_profiles';

    #creates remote_profiles directory if is doesn't exist
    unless(-d $profiles_dir){
        mkdir $profiles_dir;
    }

    #opens file to be read in line by line
    $file_ptr = path("$profiles_dir/$file")->openr_utf8;

    #reads file line by line and puts it into an array
    while(my $row = $file_ptr->getline()){
        chomp($row);
        push(@file_contents, $row);
    }

    #reads through file contents
    for(my $ind = 0; $ind < @file_contents; $ind += 1){
        #grabs index of the correct profile and breaks loop
        if($args[1] eq substr($file_contents[$ind], 0, index($file_contents[$ind], ' '))){
            $url_details = substr($file_contents[$ind], index($file_contents[$ind], ' ') + 1);
            last;
        }
    }

    #makes sure that the [SSH|SFTP] action to be executed is valid and executes it
    if($url_details eq '' && index($args[1], '@') >= 0){
        exec("$args[0] $args[1]");
    }
    elsif($url_details ne ''){
        exec("$args[0] $url_details");
    }
    else{
        println("Error: $args[1] is not a valid profile nor connection,\nplease check input");
        return 1;
    }
}

#--------------------------------------------#
# Subroutine: profile_maint                  #
#                                            #
# Description:                               #
# Updates [SSH|SFTP] list with a new profile #
#--------------------------------------------#
sub profile_maint{
    my @args = @_; #parameters
    my $args_num = scalar @args; #number of parameters received
    my $save_file; #file that is the profile is written into 
    my $profiles_dir; #holds path to directory of profiles
    my $file_ptr; #var to hole file reference

    #checks if the correct number of arguments have been given
    unless($args_num == 3){
        println('Invalid number of arguements given. ',
                "Expected 3, given $args_num.\n",
                'Proper format is: remote save user@server profile-name',
                "\n",
                'Example: remote save-ssh foo@bar foobar');

        return 1;
    }

    #path to .remote_profiles directory
    $profiles_dir = File::HomeDir->my_home . '/.remote_profiles';

    #checks to make sure that the profiles directory exists
    unless(-d $profiles_dir){
        mkdir $profiles_dir;
    }

    #path to remote_profiles
    $save_file = "$profiles_dir/remote_profiles";

    #checks if remote_profiles exists before opening to read
    unless(-e $save_file){
        $file_ptr = path("$save_file")->openw_utf8;
    }

    #opens file to be read in line by line
    $file_ptr = path("$save_file")->openr_utf8;

    #reads file line by line and checks is received profile name already exists
    while(my $row = $file_ptr->getline()){
        chomp($row);
        #prints error statement if profile name already exists in file
        if($args[2] eq substr($row, 0, index($row, ' '))){
            println("Profile name $args[2] already exists");
            return 1;
        }
    }

    #write profile to remote_profiles
    $file_ptr = path("$save_file")->opena_utf8;
    $file_ptr->print("$args[2] $args[1]\n");

    return 0;
}

#----------------------------------------#
# Subroutine: print_profiles             #
#                                        #
# Description:                           #
# Prints known [SSH|SFTP] list to screen #
#----------------------------------------#
sub print_profiles{
    my $args_num = scalar @_; #number of arguments in args
    my $profiles_file = 'remote_profiles';; #file that is the profile is written into 
    my $profiles_dir; #holds path to directory of profiles
    my $file_ptr; #var to hole file reference

    #checks if the number of received arguments is correct
    if($args_num > 1 || $args_num < 1){
        println('Invalid number of arguments given. ',
                "Expected 1, given $args_num.\n",
                "Proper format is: remote print-profiles");

        return 1;
    }

    #checks to make sure that the profiles directory exists
    $profiles_dir = File::HomeDir->my_home . '/.remote_profiles';

    unless(-d $profiles_dir){
        println('No profiles have been saved');
        return 1;
    }

    #opens file to be read in line by line
    $file_ptr = path("$profiles_dir/$profiles_file")->openr_utf8;

    #reads file line by line and prints it out
    while(my $row = $file_ptr->getline()){
        print($row);
    }

    return 0;
}

#-----------------------------------------#
# Subroutine: help_menu                   #
#                                         #
# Description:                            #
# Prints executable actions to the screen #
#-----------------------------------------#
sub help_menu{
    my @args = @_; #paramter array
    #hash table holding actions (keys) and descriptions (values)
    my %options = ('ssh' => 'executes SSH protocol on profile',
                   'sftp' => 'executes sftp protocol on profile',
                   'save' => 'writes new profile to file',
                   'print-profiles' => 'dsiplays all currently saved profiles',
                   'help' => 'displays all executable actions available');
    my $args_num = scalar @args; #number of arguments in args
    my $count = 1; #counter for the list of actions
    my ($key, $value); #variables that hold the keys and values of options

    #checks if the correct number of arguments have been passed in
    if($args_num > 1 || $args_num < 1){
        println('Invalid number of argument given. ',
                "Expected 1, was given $args_num.",
                'Proper format is: remote help');

        return 1;
    }

    #help menu header
    println("#-----------#\n",
            "# Help Menu #\n",
            "#-----------#");

    #prints out the keys and values of options
    while(($key, $value) = each(%options)){
        print("$count) $key\n\t$value\n");
        $count += 1;
    }

    return 0;
}

#--------------------------------------#
# Subroutine: remove                   #
#                                      #
# Description:                         #
# Removes profile from remote_profiles #
#--------------------------------------#
sub remove{
    my @args = @_; #parameter array
    my @file_contents; #array of file contents
    my $args_num = scalar @args; #number of parameters received
    my $save_file = 'remote_profiles'; #file that is to be edited 
    my $profiles_dir; #holds path to directory of profiles
    my $file_ptr; #var to hole file reference
    my $index = -1; #array indexing integer

    #checks if the correct number of arguments were passed
    if($args_num != 2){
        println('Invalid number of argument given. ',
                "Expected 2, was given $args_num.",
                'Proper format is: remote remove [profile]');

        return 1;
    }

    #checks to make sure that the profiles directory exists
    $profiles_dir = File::HomeDir->my_home . '/.remote_profiles';

    unless(-d $profiles_dir){
        println('No profiles have been written');
    }

    #opens file to be read in line by line
    $file_ptr = path("$profiles_dir/$save_file")->openr_utf8;

    #reads file line by line
    while(my $row = $file_ptr->getline()){
        chomp($row);
        push(@file_contents, $row);
    }

    #finds the profile in the content array
    for(my $ind = 0; $ind < @file_contents; $ind += 1){
        if($args[1] eq substr($file_contents[$ind], 0, index($file_contents[$ind], ' '))){
            $index = $ind;
            last;
        }
    }

    #if profile was not found, run this
    if($index == -1){
        println("$args[0] not found");
        return 1;
    }

    splice(@file_contents, $index, 1); #removes profile from content array

    #opens file to be rewritten
    $file_ptr = path("$profiles_dir/$save_file")->openw_utf8;

    #rewrites file
    foreach my $profile (@file_contents){
        $file_ptr->print("$profile\n");
    }

    return 0;
}

#-------------------------------------#
# Subroutine: println                 #
#                                     #
# Description:                        #
# Appends newline to print statements #
#-------------------------------------#
sub println{
    my @args = @_; #parameters array
    my $statement = shift @args; #variable that holds the printed statement
    my $elem; #elements of the parameters array

    #loop that builds the print statement
    foreach $elem (@args){
        $statement .= $elem;
    }
    
    print($statement . "\n"); #appends newline print statement

    return 0;
}

#--------------------------#
# Executes main subroutine #
#--------------------------#
main();
