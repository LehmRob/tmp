use std::net::UdpSocket;

fn main() {
    let sock = UdpSocket::bind("127.0.0.1:10033").expect("Couldn't bind address");

    sock.send_to("Hello World".as_bytes(), "127.0.0.1:10032").expect("Couldn't send data");
}
