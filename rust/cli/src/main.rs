use std::env;
use std::process;
use std::string::String;

fn print_help() {
    println!("Usage:
--help: Showing the help
--version: Showing the version
--name=<NAME>: Printing name"
);
}

fn show_version() {
    println!("v0.1.0");
}

fn main() {
    println!("hello_friend");
    let args: Vec<String> = env::args().collect();

    if args.len() <= 1 {
        println!("Not enough arguments. Try --help");
        process::exit(1);
    }

    let arg = &args[1];
    if arg == "--help" || arg == "-h" {
        print_help();
        process::exit(0);
    } else if arg == "--version" {
        show_version();
    } else if arg.contains("--name") {
        let parts:Vec<&str> = arg.split("=").collect();
        if parts.len() < 2 {
            println!("Invalid arguments");
            process::exit(1);
        }
        let name = parts[1];
        println!("We do the name {}", name);
    } else {
        println!("Unknown argument");
    }
}
