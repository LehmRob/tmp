#!/usr/bin/env ruby

# Simple panda example
myproc = Proc.new do |animal|
	puts "I love #{animal}!"
end

myproc.call("Panda")

# Show example
def make_show_name(show)
	Proc.new{|host| show + " mit " + host}
end

show1 = make_show_name("Wetten das")
show2 = make_show_name("Schlag den Raab")

puts show1.call("Thomas Gottschalk")
puts show1.call("Jörg Pilawa")
puts show2.call("Stefan Raab")

# Using the lambda operator
myproc2 = lambda do |x| 
	puts "Argument " + x
end

myproc2.call("deine")
myproc2.call("Mutter")

# difference between lambda and procs

lproc = lambda {|a,b| puts "#{a+b} <- sum"}
nproc = Proc.new {|a,b| puts "#{a+b} <- sum"}

nproc.call(1, 2, 3)
# Will throw an ArgumentError
#lproc.call(1, 2, 3)

def procnew
	newproc = Proc.new{return "I got here"}
	newproc.call

	return "Procnew returns"
end

def lambdaproc
	newproc = lambda{return "You got there"}
	newproc.call

	return "Lambdaproc returns"
end

puts procnew
puts lambdaproc
