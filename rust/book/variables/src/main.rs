fn main() {
    let mut x = 5;
    println!("Current value {}", x);
    x = 6;
    println!("New value {}", x);

    // Shadowing

    let y = 1;
    println!("Current y {}", y);
    let y = y + 1;
    println!("Current y {}", y);
    let y = y * 2;
    println!("Current y {}", y);

    let spaces = "    ";
    let spaces = spaces.len();
    println!("Spaces {}", spaces);

    // Numbers
    //
    // Integers

    let my_num = 32;
    println!("My number is {}", my_num);

    // Some operations
    let sum = 5 + 10;
    let diff = sum - 3;
    println!("Diff {}", diff);

    let product = 3 * 10;
    println!("Product {}", product);
    
    let quot = 33.78 / 2.0;
    println!("Quot {}", quot);
}
