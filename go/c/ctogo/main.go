package main

// #cgo LDFLAGS: -lcurl
// #include <stdlib.h>
// #include <curl/curl.h>
//
// static CURLcode curl_easy_setopt_string(CURL *handle, CURLoption option, char* parameter) {
//	return curl_easy_setopt(handle, option, parameter);
// }
//
// static CURLcode curl_easy_getinfo_string(CURL *handle, CURLoption option, char* data) {
//	return curl_easy_getinfo(handle, option, &data);
// }
import "C"
import (
	"log"
	"unsafe"
)

func main() {
	curl := C.curl_easy_init()
	defer C.free(unsafe.Pointer(curl))
	if curl == nil {
		log.Fatal("Could not initialize curl")
	}

	C.curl_easy_setopt_string(unsafe.Pointer(curl), C.CURLOPT_URL, C.CString("http://trackviewer.eu"))
	res := C.curl_easy_perform(unsafe.Pointer(curl))
	if C.CURLE_OK == res {
		ct := C.CString("")
		defer C.free(unsafe.Pointer(ct))
		res = C.curl_easy_getinfo_string(unsafe.Pointer(curl), C.CURLINFO_CONTENT_TYPE, ct)
		if C.CURLE_OK != res {
			log.Fatal("Can't get content type")
		}
	}
}
