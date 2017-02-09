#!/usr/bin/env ruby

module FighterValues
	BAMBOO_HEAD = { 'life' => 120, 'hit' => 90}
	DEATH = {'life' => 100, 'hit' => 3}
	CHUCK_NORRIS = {'life' => 1000000, 'hit' => 99999999}
end

module ConstantValues
	DEATH = -5
	EASY_HANDYCAP = 10
	MEDIUM_HANDYCAP = 20
	HARD_HANDYCAP = 30
end

puts FighterValues::DEATH

puts ConstantValues::DEATH
