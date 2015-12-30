module.exports = function(array, count, options) {
  array = array.slice(0, -count);
  var result = '';
  for (var item in array) {
    result += options.fn(array[item]);
  }
  return result;
};