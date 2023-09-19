#include "database.h"
#include <iostream>
#include <string>

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
