#!/usr/bin/env ruby

class Boogyman
	attr_writer :scare_factor, :hidding_place
	attr_reader :scare_factor, :hidding_place
	def info
		puts @scare_factor
		puts @hidding_place
	end
end

b = Boogyman.new

b.scare_factor="Scary"
b.hidding_place = "london"

b.info
