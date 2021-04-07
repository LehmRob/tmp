use std::io::BufReader;
use std::io::BufRead;
use std::fs::File;
use std::env;
use std::process;

fn print_help(name: &String) {
    println!("Usage {}:
    --help: Show help", name);
}

fn analyze(filename: &str) {
    let file = File::open(filename).unwrap();
    let file_reader = BufReader::new(&file);

    let mut counter: u32 = 1;
    for _ in file_reader.lines() {
        counter += 1;
    }

    println!("Counted {} in {} lines", counter, filename);
}

fn main() {
    let args: Vec<String> = env::args().collect();

    match args.len() {
        1 => {
            println!("Not enough arguments. Try --help");
            process::exit(0);
        },
        2 => {
            match args[1].as_str() {
                "--help" => {
                    print_help(&args[0]);
                    process::exit(0);
                },
                path => {
                    analyze(path);
                }
            }
        },
        _ => {
            println!("Not enough arguments. Try --help");
            process::exit(0);
        }
    }

}
