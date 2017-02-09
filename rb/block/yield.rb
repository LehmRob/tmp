#!/usr/bin/env ruby

# Using yield to passing blocks to methodes

def yieldme
	puts "Execute 1. Block"
	yield
	puts "Execute 3. Block"
end

yieldme{puts "Execute 2. Block"}

def myeach(myarray)
	iter = 0
	while (iter < myarray.length)
		yield(myarray[iter])
		iter += 1
	end
end

testarray = ["eins", "zwo", "drei"]

myeach(testarray) do |item|
	puts "Arrayitem #{item}"
end

# Using ampersand 
def yieldme2(&block)
	block.call
	yield
end

yieldme2 {puts "I got it"}

