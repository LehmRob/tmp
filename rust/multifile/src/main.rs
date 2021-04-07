mod cars;
mod train;

fn main() {
    println!("Hello, world!");
    cars::pkw::brum();
    cars::pkw::whoami();
    cars::whoami();
    train::whoami();
}
