use std::io::BufReader;
use std::io::BufRead;
use std::fs::File;
use std::env;

fn main() {
    println!("Hello, world!");

    let args: Vec<String> = env::args().collect();
    if args.len() <= 1 {
        panic!("Not enought arguments");
    }

    let filename = &args[1];
    println!("This is the file {}", filename);

    let file = File::open(filename).unwrap();
    let file_reader = BufReader::new(&file);

    let mut counter: u32 = 1;
    for line in file_reader.lines() {
        let l = line.unwrap();
        println!("Line {}, {}", counter, l);
        counter += 1;
    }
}
