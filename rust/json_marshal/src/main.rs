extern crate serde_json;
#[macro_use]
extern crate serde_derive;

#[derive(Debug, Serialize, Deserialize)]
struct Person {
    first_name: String,
    last_name: String,
    aliases: Vec<String>,
}

fn main() {
    println!("Hello, world!");

    let person = Person{
        first_name: String::from("Robert"),
        last_name: String::from("Lehm"),
        aliases: vec![
            String::from("Rob"),
            String::from("Bob"),
        ],
    };

    let person_json = serde_json::to_string(&person);
    println!("JSON {}", person_json.unwrap());
}
