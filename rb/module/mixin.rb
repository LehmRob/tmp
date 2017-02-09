#!/usr/bin/env ruby

module Movement
	def run
		puts "Run Forest! RUN!"
	end
	
	def walk
		puts "Walk away"
	end
	
	def crawl
		puts "I'm so sloooooow!"
	end
end

class Man
	include Movement
	def jump
		puts "Jump in the air"
	end
end

man = Man.new
man.jump
man.run
