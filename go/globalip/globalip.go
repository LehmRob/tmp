package main

import (
	"fmt"
	"io"
	"io/ioutil"
	"log"
	"net/http"
	"regexp"
)

func readIp(bodyReader io.ReadCloser) (string, error) {
	body, err := ioutil.ReadAll(bodyReader)
	if err != nil {
		return "", err
	}

	content := string(body[:])
	re, err := regexp.Compile("(\\d{1,3}\\.){3}\\d{1,3}")
	if err != nil {
		return "", err
	}
	ips := re.FindString(content)

	return ips, nil
}

func main() {

	resp, err := http.Get("http://whatsmyip.com")
	if err != nil {
		log.Fatal("Page is not availible")
	}

	if resp.StatusCode != 200 {
		log.Fatal("Service is temporary not availible")
	}

	ip, err := readIp(resp.Body)
	if err != nil {
		log.Fatal(err)
	}

	fmt.Println(ip)
}
