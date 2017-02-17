package main

import (
	"flag"
	"log"
	"net"

	"github.com/jeffallen/mqtt"
)

var (
	port = flag.String("port", ":8888", "Port for mqtt broker")
	host = flag.String("host", "localhost", "Host for mqtt broker")
)

func main() {
	flag.Parse()

	s, err := net.Listen("tcp", *host+*port)
	if err != nil {
		log.Fatalf("Can't create socket, %s\n", err)
	}

	broker := mqtt.NewServer(s)
	broker.Start()

	<-broker.Done
}
