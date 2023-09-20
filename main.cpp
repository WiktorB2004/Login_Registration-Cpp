#include <iostream>
#include <string>
#include <stdlib.h>
#include "database.h"

Database users("accountsDB");

void clean() { system("cls"); }

bool userLogin();
bool userRegister();
void loggedScreen(std::unordered_map<std::string, std::string>& data);
bool accountRemoval(std::unordered_map<std::string, std::string>& data);

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
		loggedScreen(userData);
	}
	else {
		main();
		return false;
	}
	return true; 
}


void loggedScreen(std::unordered_map<std::string, std::string>& data) {
	clean();
	std::string operation;
	std::cout << "Logged in successfuly" << "\n\n"
		<< "Your username: " << data["username"] << std::endl
		<< "Your password: " << data["password"] << "\n\n";

	std::cout << "Possible actions: " << std::endl
		<< "1. Change password" << std::endl
		<< "2. Remove you account" << std::endl
		<< "3. Logout" << std::endl;
	
	std::getline(std::cin, operation);

	if (operation == "1") {
		// add logic to change password
		std::cin.get();
	}
	else if (operation == "2") {
		accountRemoval(data);
	}
	else if (operation == "3") {
		main();
	}
};

bool accountRemoval(std::unordered_map<std::string, std::string>& data) {
	clean();
	std::string operation;
	std::cout << "If you want to delete your account enter your password: " << std::endl;
	std::getline(std::cin, operation);
	if (operation == data["password"]) {
		if (users.removeRecord("username", data["username"])) {
			std::cout << "Removal successful, push any button to go back to main screen" << std::endl;
			std::cin.get();
			main();
		}
		else {
			std::cout << "Error occured, push any button to go back to main screen" << std::endl;
			std::cin.get();
			main();
		}
	}


	return true;
}