fn main() {
    println!("Hello, friend!");
    
    // ARRAYS
    // ======
    // Declare arrays
    let a1 = [1, 2, 3]; // a1: [i32; 3]
    let a2 = [1, 2, 3, 4]; // a2: [i32; 4]
    let a3 = [0; 20]; // a3: [i32; 20] declare a array with 20 elements and all initilized with 0

    // Get the length of the array
    println!("Length of array a1 {}", a1.len());
    println!("Length of array a2 {}", a2.len());
    println!("Length of array a3 {}", a3.len());

    let names = ["max", "mike", "baxter"];
    // Access elements
    println!("Print second array {}", names[1]);

    // SLICES
    // ======

    let a4 = [1, 2, 3, 4, 5]; // normal array declaretion
    let s1 = &a4[..]; // slice over the hole section of the array
    let s2 = &a4[1..3]; // slice from index 1 to 3
    println!("Slice 1 length {}", s1.len());
    println!("Slice 2 length {}", s2.len());
}
