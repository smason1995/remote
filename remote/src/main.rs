/**
 * Remote, SSH/SFTP Profile Manager
 *
 * author: Sydney Mason
 * version: 20190304
 */

use std::io::Write;
use std::fs::{OpenOptions, read_to_string};
use std::env;
use std::process;

extern crate dirs;

fn main() {
    let argv: Vec<String> = env::args().collect();

    if argv.len() > 1 {
        match argv[1].trim() {
            "ssh" => {
                if argv.len() != 3 {
                    println!("{} expected 1 argument, but {} were given", argv[1].trim(), argv.len()-2);
                    process::exit(1);
                }
                remote_action(argv[1].trim().to_string(), argv[2].trim().to_string());
            },
            "sftp" => {
                if argv.len() != 3 {
                    println!("{} expected 1 argument, but {} were given", argv[1].trim(), argv.len()-2);
                    process::exit(1);
                }
                remote_action(argv[1].trim().to_string(), argv[2].trim().to_string());
            },
            "save" => {
                if argv.len() != 4 {
                    println!("save expected 2 arguments, but {} were given", argv.len()-2);
                    process::exit(1);
                }
                add_profile(argv[2].trim().to_string(), argv[3].trim().to_string());
            },
            "remove" => {
                if argv.len() != 3 {
                    println!("remove expected 1 argument, but {} were given", argv.len()-2);
                    process::exit(1);
                }
                remove_profile(argv[2].trim().to_string());
            },
            "list" => {
                if argv.len() != 2 {
                    println!("list expected 1 argument, but {} were given", argv.len()-2);
                    process::exit(1);
                }
                list_profiles();
            },
            "help" => {
                if argv.len() != 2 {
                    println!("help expected 1 argument, but {} were given", argv.len()-2);
                    process::exit(1);
                }
                help();
            },
            _ => {
                println!("Invalid command: {}", argv[1].trim());
            }
        }
    }
    else {
        println!("No arguments were given");
    }
}

fn remote_action(cmd: String, profile: String) -> i32 {
    println!("{} {}", cmd, profile);
    return 0;
}

fn add_profile(pname: String, purl: String) -> i32 {
    let mut fp: String;

    let profile = format!("{} {}", pname, purl);
    let profile = &*profile;

    match dirs::home_dir() {
        Some(path) => fp = path.display().to_string(),
        None => {
            println!("Failed to find home directory");
            return 1;
        }
    }

    fp = fp + "/.config/remote/remote_profiles";

    let contents = read_to_string(&fp).expect("Problem encountered while trying to read file");

    if !contents.is_empty() {
        let lines: Vec<&str> = contents.split("\n").collect();

        for line in lines {
            if line == profile {
                println!("Alias-URL pairing already exists in profile\n{}", profile);
                return 1;
            }
        }

        let mut append = OpenOptions::new().append(true).open(fp).unwrap();
        
        if let Err(e) = writeln!(append, "{}", profile) {
            eprintln!("Couldn't write {} to file", e);
            return 1;
        }
    }

    return 0;
}

fn remove_profile(pname: String) -> i32 {
    println!("{}", pname);
    return 0;
}

fn list_profiles() -> i32 {
    println!("list_profiles");
    return 0;
}

fn help(){
    println!("remote - SSH/SFTP profile manager");
    println!("---------------------------------");
    println!("ssh, connect via secure shell protocol into remote terminal\n\tusage: remote ssh [profile name or [user@host.ext/IP]]");
    println!("sftp, connect via secure file transfer protocol into remote file system\n\tusage: remote sftp [profile name or [user@host.ext/IP]]");
    println!("save, write a new profile to alias list for easy access\n\tusage: remote save [profile name] [user@[host.ext/IP]]");
    println!("remove, deletes a profile from alias list\n\tusage: remote remote remove [profile name]");
    println!("list, displays all profile and url to screen\n\tusage: remote list");
    println!("help, displays help menu to screen\n\tusage: remote help");
}
