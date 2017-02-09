package main

import (
    "golang.org/x/crypto/ssh"
    "io"
	"os"
)

func main() {
    sshConfig := &ssh.ClientConfig{
        User: "vmpadmin",
        Auth: []ssh.AuthMethod{
            ssh.Password("JtP8mQ9E"),
        },
    }

    conn, err := ssh.Dial("tcp", "vmp-clan.de:22", sshConfig)
    if err != nil {
        panic(err.Error())
    }
    defer conn.Close()

    session, err := conn.NewSession()
    if err != nil {
        panic(err.Error())
    }
    defer session.Close()

    modes := ssh.TerminalModes{
    	ssh.ECHO:          0,     // disable echoing
    	ssh.TTY_OP_ISPEED: 14400, // input speed = 14.4kbaud
    	ssh.TTY_OP_OSPEED: 14400, // output speed = 14.4kbaud
    }

    if err := session.RequestPty("xterm", 80, 40, modes); err != nil {
    	session.Close()
        panic(err.Error())
    }

    stdin, err := session.StdinPipe()
    if err != nil {
        panic(err.Error())
    }

    go io.Copy(stdin, os.Stdin)

    stdout, err := session.StdoutPipe()
    if err != nil {
        panic(err.Error())
    }

    go io.Copy(os.Stdout, stdout)

    stderr, err := session.StderrPipe()
    if err != nil {
        panic(err.Error())
    }

    go io.Copy(os.Stderr, stderr)

    err = session.Run("uptime")
    if err != nil {
        panic(err.Error())
    }
}
