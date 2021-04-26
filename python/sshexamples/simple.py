import getpass
from paramiko import SSHClient

def main():
    username = input("username: ")
    password = getpass.getpass(prompt='password: ')
    passphrase = getpass.getpass(prompt='passphrase: ')
    client = SSHClient()
    client.load_system_host_keys()
    client.connect('localhost', username=username, password=password, passphrase=passphrase)
    resp = client.exec_command('uname -a')
    print(resp[1])


if __name__ == '__main__':
    main()
