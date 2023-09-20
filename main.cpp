#include <iostream>
#include <string>
#include <stdlib.h>
#include "database.h"

// Database file must be clean (only at the moment - load functionality)
Database users("accountsDB");

void clean() { system("cls"); }

bool userLogin();
bool userRegister();
void loggedScreen();

int main() {
	clean();
	std::string operation;

	std::cout << "Welcome to the portal" << std::endl
		<< "1. Login" << std::endl
		<< "2. Register" << std::endl
		<< "Select the action" << std::endl;

	std::getline(std::cin, operation);

	if (operation == "1") {
		clean();
		userLogin();
	}
	else if (operation == "2") {
		clean();
		userRegister();
	}
	else {
		std::string again;
		clean();
		std::cout << "Incorrect Input" << std::endl
			<< "try again? (Y/N)" << std::endl;
		std::getline(std::cin, again);
		if (again == "Y" || again == "y") {
			clean();
			main();
		}
		return 0;
	}
	return 0;
}


bool userRegister() {
	std::string username, password;

	std::cout << "Enter username: ";
	// TODO: Add verification - no spaces etc.
	std::getline(std::cin, username);
	std::cout << "Enter password: ";
	std::getline(std::cin, password);

	while (!users.findByField("username", username).empty()) {
		std::cout << "Username is taken, try again: ";
		std::getline(std::cin, username);
	}

	std::unordered_map<std::string, std::string> newUser;
	newUser["username"] = username;
	newUser["password"] = password;
	if (!users.addRecord(newUser)) {
		std::cout << "Got error while adding user to database" << std::endl;
		clean();
		main();
	}

	userLogin();

	return true;
}

bool userLogin() {
	clean();
	std::string username, password;
	std::cout << "Enter username: ";
	std::getline(std::cin, username);
	while (users.findByField("username", username).empty()) {
		clean();
		std::cout << "Incorrect username, try again: ";
		std::getline(std::cin, username);
	}

	auto userData = users.findByField("username", username);
	std::cout << "Enter password: ";
	std::getline(std::cin, password);

	int tries = 0;
	while (password != userData["password"] && tries < 3) {
		std::cout << "Incorrect passowrd, try again (You have " << (3 - tries) << " left): ";
		std::getline(std::cin, password);
		tries++;
	}

	if (password == userData["password"]) {
		loggedScreen();
	}
	else {
		main();
		return false;
	}
	return true; 
}


void loggedScreen() {
	clean();
	std::cout << "Logged in successfuly";
	std::cin.get();
};