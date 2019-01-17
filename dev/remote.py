#!/usr/bin/python

#-----------------------------------#
# PROGRAM: SSH/SFTP Profile Manager #
# AUTHOR:  Sydney Ann Mason         #
# VERSION  20180111                 #
#-----------------------------------#

#---------#
# IMPORTS #
#---------#
import sys
import collections
import os

#---------------------------------------#
# FUNC: remote_action                   #
# DESC: Executes the specified SSH/SFTP #
#       protocol on the profile         #
# VARS:                                 #
#---------------------------------------#
def remote_action(cmd, prof):
    command = cmd + ' ' + prof
    os.system(command)

#--------------------------------------#
# FUNC: profile_maint                  #
# DESC: Adds a new profile to the list #
#       to the list of new profiles    #
# VARS:                                #
#--------------------------------------#
def profile_maint(url, prof):
    print(prof + ' = ' + url)

#------------------------------------#
# FUNC: print_profiles               #
# DESC: Prints the list of all saved #
#       profiles                     #
# VARS:                              #
#------------------------------------#
def print_profiles():
    print('Printing coming soon')

#---------------------------------#
# FUNC: help_menu                 #
# DESC: Prints executable actions #
# VARS:                           #
#   action_list, ordered dict of  #
#                actions          #
#---------------------------------#
def help_menu():
    action_list = collections.OrderedDict()

    action_list['ssh'] = 'executes SSH protocol on profile'
    action_list['sftp'] = 'executes SFTP protocol on profile'
    action_list['save'] = 'writes new profile to profile list'
    action_list['print'] = 'displays all currently saved profiles'
    action_list['help'] = 'displays all executable actions'

    print("#-----------#\n" +
          "# Help Menu #\n" +
          "#-----------#")

    for key, val in action_list.items():
        print(key + '\n\t' + val)

#----------------------------------#
# FUNC: remove                     #
# DESC: Deletes profile from the   #
#       list of the known profiles #
# VARS:                            #
#----------------------------------#
def remove(prof):
    print(prof)

#-------------------------------------#
# FUNC: main                          #
# DESC: Main function, takes CLI args #
#       and passes them to the        #
#       appropriate function          #
# VARS:                               #
#-------------------------------------#
def main(argv):
    try:
        if argv[0] == 'ssh' or argv[0] == 'sftp':
            remote_action(argv[0], argv[1])
        elif argv[0] == 'save':
            profile_maint(argv[1], argv[2])
        elif argv[0] == 'print':
            print_profiles()
        elif argv[0] == 'help':
            help_menu()
        elif argv[0] == 'remove':
            remove(prof)
    except Exception as e:
        print(e)

#--------------#
# CALL: main() #
#--------------#
if __name__ == "__main__":
    main(sys.argv[1:])
