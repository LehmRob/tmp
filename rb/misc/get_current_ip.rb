#!/usr/bin/env ruby

require 'net/http'

class MyIp
  IP_URI = URI('http://www.wieistmeineip.de/')
  
  private
  def self.searchForIp(response)
    pattern_found = false
    response.each_line do |line|
      if /ipv4/.match(line)
        pattern_found = true
      end
      if pattern_found && /\d+\.\d+\.\d+\.\d+/.match(line)
        line = line.delete('<div class="title"><strong>').delete('/')
        puts line
      end
    end
  end

  public
  def self.getIp
    response = Net::HTTP.get(IP_URI)
    searchForIp(response)
  end
end

MyIp.getIp
