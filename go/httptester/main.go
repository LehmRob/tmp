package main

import (
	"fmt"
	"net/http"
	"time"
)

func main() {
	fmt.Println("Hello World")
	mux := http.NewServeMux()
	mux.HandleFunc("/", func(w http.ResponseWriter, req *http.Request) {
		fmt.Fprintf(w, "Hello World\n")
	})
	myServer := &http.Server{
		Addr:         ":8080",
		Handler:      mux,
		ReadTimeout:  10 * time.Second,
		WriteTimeout: 10 * time.Second,
	}
	myServer.ListenAndServe()
}
