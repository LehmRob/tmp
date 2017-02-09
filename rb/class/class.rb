#!/usr/bin/env ruby

class Bogyman
	def initialize(name, location)
		puts "I am the Boogyman"
		@name = name
		@location = location
	end

	def get_name
		return @name
	end

	def get_location
		return @location
	end
end

bogyman = Bogyman.new("Earl", "New York")
puts "My name is #{bogyman.get_name}"
puts "I am living at #{bogyman.get_location}"

# Add an methode to the class String

class String
	def write_size
		puts self.size
	end
end

size_writer = "Tell me baby"
size_writer.write_size
