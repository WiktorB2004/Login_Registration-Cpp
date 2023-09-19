#include <iostream>
#include "database.h"

int main() {
	Database users("test");
	std::string checkField = "username";

	std::unordered_map<std::string, std::string> wiktor;
	std::unordered_map<std::string, std::string> oliwier;
	std::unordered_map<std::string, std::string> wiktor2;
	wiktor["username"] = "Wiktor";
	wiktor["password"] = "Password";
	oliwier["username"] = "Oliwier";
	oliwier["password"] = "Password";
	wiktor2["username"] = "Wiktor2";
	wiktor2["password"] = "Password2";

	users.addRecord(wiktor, checkField);
	users.addRecord(oliwier, checkField);
	users.addRecord(wiktor2, checkField);
	users.findByField("password", "Password");
}