package main

import (
	"C"
	"fmt"
)

//export SayHello
func SayHello(name string) {
	fmt.Printf("Hello %s\n", name)
}

func main() {}
