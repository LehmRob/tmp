#include <iostream>
#include <string>

#include <libssh/libssh.h>

int show_remote_uptime(ssh_session s) {
	ssh_channel chan = ssh_channel_new(s);
	if (chan == NULL) {
		return SSH_ERROR;
	}

	auto ret = ssh_channel_open_session(chan);
	if (ret != SSH_OK) {
	  ssh_channel_free(chan);
	  return SSH_ERROR;
	}

	ret = ssh_channel_request_exec(chan, "uptime");
	if (ret != SSH_OK) {
	  ssh_channel_close(chan);
	  ssh_channel_free(chan);
	  return SSH_ERROR;
	}

	char buf[256];
	ret = ssh_channel_read(chan, buf, sizeof(buf), 0);
	if (ret != SSH_OK) {
	  ssh_channel_close(chan);
	  ssh_channel_free(chan);
	}

	return SSH_OK;
}

int main(int argc, char** argv) {
	std::cout << "Hello World" << std::endl;
	ssh_session my_session = ssh_new();
	if (my_session == NULL) {
		std::cerr << "Error occured" << std::endl;
		return 1;
	}

	ssh_options_set(my_session, SSH_OPTIONS_HOST, "vmp-clan.de");

	auto ret = ssh_connect(my_session);
	if (ret != SSH_OK) {
		std::cerr << "Can't connect to server" << std::endl;
		ssh_free(my_session);
		return 1;
	}

	std::string password;
	std::cout << "Enter password" << std::endl;
	std::cin >> password;
	
	auto err = ssh_userauth_password(my_session, "vmpadmin", password.c_str());
	if (err != SSH_AUTH_SUCCESS) {
		std::cerr << "Authentifcation failed" << std::endl;
		ssh_disconnect(my_session);
		ssh_free(my_session);
		return 1;
	}

	sho
	
	ssh_disconnect(my_session);
	ssh_free(my_session);

	return 0;
}
