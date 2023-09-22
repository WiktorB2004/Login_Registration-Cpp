#include "database.h"
#include <iostream>
#include <string>

/// <summary>
/// Extract data from data string and put it into unordered_map.
/// Data must be provided in key: value;key: value (...) format.
/// </summary>
/// <param name="line">string with data in correct format</param>
/// <returns>unordered map with key value pairs from data string</returns>
std::unordered_map<std::string, std::string> extractFromLine(std::string& line) {
	std::string curr, key = "id";
	std::unordered_map<std::string, std::string> res;
	for (char c : line) {
		if (c == ':') { 
			key = curr;
			curr = "";
		}
		else if (c == ';') {			
			if (curr[0] == ' ') curr = curr.substr(1);
			res[key] = curr;
			curr = "";
			
		}
		else {
			curr += c;
		}
		
	}
	return res;
}


bool validData(const std::vector<std::string>& schema, const std::unordered_map<std::string, std::string>& data) {
	if (schema.size() != data.size()) return false;
	for (auto& pair : data) {
		if (std::find(schema.begin(), schema.end(), pair.first) == schema.end()) return false;
	}
	return true;
}
