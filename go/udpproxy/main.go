// Copyright (c) 2017 Robert Lehmann <lehmrob@gmail.com>
// This software is licensed under BSD Clause 2 License
// Look into the LICENSE file for more information

package main

import (
	"flag"
	"log"
	"net"
)

var (
	port1 = flag.String("port1", ":8000", "First port for proxy connection")
	port2 = flag.String("port2", ":8001", "Second port for proxy connection")
)

func main() {
	flag.Parse()

	addr1, err := net.ResolveUDPAddr("udp", "0.0.0.0"+*port1)
	if err != nil {
		log.Fatal(err)
	}

	conn1, err := net.ListenUDP("udp", addr1)
	if err != nil {
		log.Fatal(err)
	}
	defer conn1.Close()

	buf := make([]byte, 1024)

	_, remoteAddr, err := conn1.ReadFrom(buf)
	if err != nil {
		log.Fatal(err)
	}

	log.Println(remoteAddr)
}
