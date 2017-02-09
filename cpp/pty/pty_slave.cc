#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char **argv) {
	int fd = open(argv[1], O_RDWR | O_NOCTTY);
	if (fd < 0) {
		cerr << "Can't open " << argv[1] << endl;
		return 1;
	}

	struct termios oldtio, newtio;
	tcgetattr(fd, &oldtio);
	newtio = oldtio;
	cfmakeraw(&newtio);

	char buf[] = "hello world\n";

	int ret = write(fd, buf, sizeof(buf));
	if (ret <= 0) {
		cerr << "Can't write" << endl;
		return 1;
	}

	close(fd);
	
	return 0;
}
