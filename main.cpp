#include <iostream>
#include "database.h"

int main() {
	database users("test");

	std::unordered_map<std::string, std::string> testRecords;
	testRecords["Username"] = "Wiktor";
	testRecords["Password"] = "Password";

	users.addRecord(testRecords);
}