var assert = require('assert');
var ownmod = require('../index');

describe('#lowerVocal()', function() {
  it('should convert upper A to lower a',
     function() { assert.equal(ownmod.lowerVocal("A"), 'a') });
  it('should convert upper E to lower e',
     function() { assert.equal(ownmod.lowerVocal("E"), 'e') });
  it('should convert upper I to lower i',
     function() { assert.equal(ownmod.lowerVocal("I"), 'i') });
  it('should convert upper O to lower o',
     function() { assert.equal(ownmod.lowerVocal("O"), 'o') });
  it('should convert upper U to lower u',
     function() { assert.equal(ownmod.lowerVocal("U"), 'u') });
  it('should convert HALLO to HaLLo',
     function() { assert.equal(ownmod.lowerVocal("HALLO"), 'HaLLo') });
});