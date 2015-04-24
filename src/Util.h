/*
 * Util.h
 *
 *  Created on: Apr 17, 2015
 *      Author: jonno
 */

#ifndef SRC_UTIL_H_
#define SRC_UTIL_H_

#include <string>
#include <vector>

namespace Util {

	/**
	 * Converts string of hexidecimal values to a string
	 * where two characters indicate one value.
	 */
	std::string hexToString(const std::string& hex);

	/**
	 * Converts string that are in hexidecimal format, e.g.: "0512"
	 * into a string of hexidecimal values, e.g.: ")x05 0x12"
	 */
	std::string stringToHex(const std::string& str);
	
	std::vector<std::string> split(std::string string, char c);


} /* namespace Util */

#endif /* SRC_UTIL_H_ */
