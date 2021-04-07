use std::env;

fn print_help() {
    println!("Usage:
--help: Showing the help
--version: Showing the version");
}

fn show_version() {
    println!("v0.1.0");
}

fn main() {
    println!("hello_friend");
    let args: Vec<String> = env::args().collect();

    match args.len() {
        1 => {
            println!("Not enough arguments. Try --help");
        },
        2 => {
            let arg = &args[1];
            if arg == "--help" {
                print_help();
            } else if arg == "--version" {
                show_version();
            } else {
                println!("Unknown argument");
            }
        },
        _ => {
            print_help();
        }
    }
}
