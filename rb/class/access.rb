#!/usr/bin/env ruby

class Boogyman
	def scare(who)
		puts "I just scare the crap out of #{who}"
	end
end

class Boogyman
	protected
	def are_you_a_monster?(whoisasking)
		puts "Yes, #{whoisasking}, I am a monster"
		return true
	end
end

class Boogyman
	private
	def phone_me(message)
		puts message
	end
	public
	def scare(who)
		if(are_you_a_monster?("My Mother"))
			phone_me("I just scared the living poop out of #{who}")
		else
			puts "There will nothing happens"
		end
	end
end

b = Boogyman.new

b.scare("Me")
