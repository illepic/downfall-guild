var _ = require('lodash');

/**
 * Return a value off an object in a collection by a simple lookup
 *
 * Example: Return the "avatar" value for Garreth in the data collection "users"
 * where the dynamic parameter we have is user.
 *
 *  {{lookup "users" "name" user "avatar"}}
 *
 * @param data Key of the data collection
 * @param lookupField Field on an object in that collection we'll search on
 * @param lookupValue Value of the key we're searching for
 * @param returnKey Return this actual value from the object
 * @param options Sent over automatically via Handlebars
 * @returns string
 */
module.exports = function(data, lookupField, lookupValue, returnKey, options) {

  // Return the value of the key from
  // the found object from the collection we asked for
  // using the _.matches syntax by _.set'ing a key/value to an empty object
  return _.result(_.find(_.result(options.data.root, data), _.set({}, lookupField, lookupValue)), returnKey);

};