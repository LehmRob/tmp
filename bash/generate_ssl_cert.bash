#!/bin/bash

# the script shows the steps for generating a self signed certificate
openssl req -newkey rsa:2048 -nodes -keyout private.key \
    -x509 -days 365 -out cert.crt

# finding more information on https://www.digitalocean.com/community/tutorials/openssl-essentials-working-with-ssl-certificates-private-keys-and-csrs
# although find information for single steps on
# https://www.akadia.com/services/ssh_test_certificate.html
