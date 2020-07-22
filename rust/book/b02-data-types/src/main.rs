fn main() {
    println!("Hello, world!");

    // use type annotations to make the datatype clear for the compiler
    // otherwise the compiler will throw an error because the function parse()
    // can return many types.
    let guess: u32 = "42".parse().expect("Not a number!");
    println!("Guess {}", guess);

    println!("==some numeric operations");
    let sum = 5 + 10;
    let diff = 95.5 - 3.2;
    let prod = 2.0 * 1.26;
    let quot = 3.0 / 2.0;
    let remain = 43 % 5;
    println!("{}", sum);
    println!("{}", diff);
    println!("{}", prod);
    println!("{}", quot);
    println!("{}", remain);

    println!("==character types");
    let c = 'z';
    let z = 'ℤ';
    let heart_eyed_cat = '😻';
    println!("{}", c);
    println!("{}", z);
    println!("{}", heart_eyed_cat);

    println!("==tuple types");
    let tup = (500, 2.2, true);
    let (x, y, z) = tup;
    println!("{}", x);
    println!("{}", y);
    println!("{}", z);
    println!("{}", tup.0);
    println!("{}", tup.2);
    println!("{}", tup.1);

    println!("==array types");
    let a = [1,  2, 3, 4, 5];
    for n in &a {
        print!("{} ", n);
    }
    println!("");

    let months = ["Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Okt", "Nov", "Dez"]; 
    for m in &months {
        print!("{} ", m);
    }
    println!("");

    let a: [i32; 5] = [-1, 0, 1, 2, 3];
    for n in &a {
        print!("{} ", n);
    }
    println!("");
}
