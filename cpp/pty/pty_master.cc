#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/select.h>

using namespace std;

int main(int argc, char **argv) {
	int fdm = posix_openpt(O_RDWR);
	if (fdm < 0) {
		cerr << "Can't create pty master" << endl;
		return 1;
	}

	int ret = grantpt(fdm);
	if (ret != 0) {
		cerr << "Error on granting rights" << endl;
		return 1;
	}

	ret = unlockpt(fdm);
	if (ret != 0) {
		cerr << "Error on unlocking pty" << endl;
		return 1;
	}

	cout << ptsname(fdm) << endl;

	fd_set fd_in;
	char input[150];

	for(;;) {
		FD_ZERO(&fd_in);
		FD_SET(fdm, &fd_in);

		ret = select(fdm + 1, &fd_in, NULL, NULL, NULL);
		if (ret < 0) {
			cerr << "Error in select loop" << endl;
			return 1;
		}

		if (FD_ISSET(fdm, &fd_in)) {
			ret = read(fdm, input, sizeof(input));
			if (ret > 0) {
				cout << "Recv data: " << input;
			}
		}
	}

	close(fdm);
	
	return 0;
}
