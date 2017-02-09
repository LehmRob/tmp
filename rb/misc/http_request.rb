#!/usr/bin/env ruby

require 'net/http'

response = Net::HTTP.get('google.de', '/index.html')

puts response
