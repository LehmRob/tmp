#!/bin/bash

# -D Port for SOCKS proxy on local host
# -f going into background
# -C use compression
# -q be quiet
# -N no command is following
# remember to set a manual SOCKS proxy for firefox browser
ssh -D 1337 -f -C -q -N root@92.222.161.228

