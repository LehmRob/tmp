package main

import (
	"flag"
	"fmt"
	"log"
	"net"
	"os"

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

	tq := []proto.TopicQos{
		{
			Topic: "MyTopic",
			Qos:   proto.QosAtMostOnce,
		},
	}
	cc.Subscribe(tq)

	for m := range cc.Incoming {
		fmt.Print(m.TopicName, "\t")
		m.Payload.WritePayload(os.Stdout)
		fmt.Println("\tr: ", m.Header.Retain)
	}
}
