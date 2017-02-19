package main

import (
	"flag"
	"log"
	"net"

	proto "github.com/huin/mqtt"
	"github.com/jeffallen/mqtt"
)

var (
	port = flag.String("port", ":8888", "Port to mqtt broker")
	host = flag.String("host", "localhost", "Host to mqtt broker")
)

func main() {
	flag.Parse()

	conn, err := net.Dial("tcp", *host+*port)
	if err != nil {
		log.Fatalf("Can't connect to server, %s\n", err)
	}
	defer conn.Close()

	cc := mqtt.NewClientConn(conn)

	err = cc.Connect("user", "pass")
	if err != nil {
		log.Fatalf("Can't connect %s\n", err)
	}
	defer cc.Disconnect()

	for i := 0; i < 3; i++ {
		cc.Publish(&proto.Publish{
			Header:    proto.Header{Retain: false},
			TopicName: "MyTopic",
			Payload:   proto.BytesPayload([]byte("Hello_friend")),
		})
	}

	<-make(chan bool)
}
