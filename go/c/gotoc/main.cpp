#include <iostream>

#include <cstring>

#include "libgotoc.h"

using namespace std;

GoString ToGoString(const char* s) {
	GoString go_string;
	go_string.p = s;
	go_string.n= strlen(s);
	return go_string;
}

int main(int argc, char** argv) {
	SayHello(ToGoString("Sweety"));

	return 0;
}
