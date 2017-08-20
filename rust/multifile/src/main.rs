mod cars;
mod train;

fn main() {
    println!("Hello, world!");
    cars::pkw::brum();
    cars::whoami();
    train::whoami();
}
