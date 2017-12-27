module.exports = {
  /**
   * Convert all vocals into lower case
   *
   * @param string string which will be converted
   * @return converted string
   */
  lowerVocal: function(string) {
    return String(string)
        .replace('A', 'a')
        .replace('E', 'e')
        .replace('I', 'i')
        .replace('O', 'o')
        .replace('U', 'u');
  }
};