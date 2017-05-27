use std::str;
use std::thread;
use std::net::UdpSocket;

fn main() {
    let sock = match UdpSocket::bind("0.0.0.0:10032") {
        Ok(s)=>s,
        Err(e)=>panic!("could not bind socket: {}", e),
    };

    let mut buf = [0; 2048];

    loop {
        match sock.recv_from(&mut buf) {
            Ok((amt, src))=> {
                thread::spawn(move || {
                    println!("amt: {}", amt);
                    println!("{}", str::from_utf8(&buf).unwrap_or(""));
                });
            }
            Err(e) => {
                println!("{}", e);
            }
        };
    }
}
