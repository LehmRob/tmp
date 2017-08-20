package main

import (
	"fmt"
	"syscall"
	"time"
	"unsafe"
)

type winsize struct {
	Row    uint16
	Col    uint16
	Xpixel uint16
	Ypixel uint16
}

func getCurrentTermWidth() int {
	ws := &winsize{}
	retCode, _, errno := syscall.Syscall(syscall.SYS_IOCTL,
		uintptr(syscall.Stdin),
		uintptr(syscall.TIOCGWINSZ),
		uintptr(unsafe.Pointer(ws)))

	if int(retCode) == -1 {
		panic(errno)
	}
	return int(ws.Col)
}

func deleteCurLine() {
	fmt.Printf("\r")
	for i := 0; i < getCurrentTermWidth(); i++ {
		fmt.Printf(" ")
	}
}

func main() {
	fmt.Println("Hello World")
	output := []string{"hello", "hi", "du", "da", "mein", "koch", "schweinegeil"}

	for _, out := range output {
		deleteCurLine()
		fmt.Printf("\r%s", out)
		time.Sleep(2 * time.Second)
	}
	fmt.Printf("\n")
}
