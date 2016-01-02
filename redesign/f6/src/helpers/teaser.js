module.exports = function(passedString) {
  var substring = passedString.substring(0, 150) + "...";
  return new Handlebars.SafeString(substring)
};