extern crate serde_json;
#[macro_use]
extern crate serde_derive;

#[derive(Debug, Serialize, Deserialize)]
struct Person {
    first_name: String,
    last_name: String,
    age: u32,
    aliases: Vec<String>,
}

fn main() {
    println!("Hello, world!");

    let person = Person{
        first_name: String::from("Robert"),
        last_name: String::from("Lehm"),
        age: 29,
        aliases: vec![
            String::from("Rob"),
            String::from("Bob"),
        ],
    };

    let person_json = serde_json::to_string(&person);
    println!("JSON {}", person_json.unwrap());

    let data = r#"
        {
            "first_name": "Jo",
            "last_name": "Caste",
            "age": 42,
            "aliases": [
                "J",
                "JoJo",
                "Johnny"
            ]
        }"#;

    let parsed_person: Person = serde_json::from_str(data).unwrap();
    println!("Parsed person {:?}", parsed_person);
    println!("Age of parsed person {:?}", parsed_person.age);
}
