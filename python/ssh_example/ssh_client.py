#!/usr/bin/env python

from paramiko import SSHClient

ssh = SSHClient()
ssh.connect('vmp-clan.de', username='vmpadmin', password='JtP8mQ9E')
