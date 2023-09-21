#include <iostream>
#include <string>
#include <stdlib.h>
#include "database.h"


std::vector<std::string> schema{ "id", "username", "password" };
// Database file must be clean (only at the moment - load functionality)
Database users("accountsDB", schema);

void clean() { system("cls"); }

bool userLogin();
bool userRegister();
bool loggedScreen(std::unordered_map<std::string, std::string>& data);
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
		userLogin();
	}
	else if (operation == "2") {
		userRegister();
	}
	else if (operation == "exit") {
		return 0;
	}
	else {
		std::string again;
		clean();
		std::cout << "Incorrect Input" << std::endl
			<< "try again? (Y/N)" << std::endl;
		std::getline(std::cin, again);
		if (again == "Y" || again == "y") {
			return main();
		}
	}
	return 0;
}


bool userRegister() {
	clean();
	std::string username, password;
	std::cout << "Create your account here, type exit to quit" << std::endl;

	std::cout << "Enter username: ";
	// TODO: Add verification - no spaces etc.
	std::getline(std::cin, username);
	if (username == "exit") return main();
	while (!users.findByField("username", username).empty()) {
		std::cout << "Username is taken or incorrect, try again or type exit: ";
		std::getline(std::cin, username);
		if (username == "exit") return main();
	}

	std::cout << "Enter password: ";
	std::getline(std::cin, password);
	if (password == "exit") return main();

	std::unordered_map<std::string, std::string> newUser;
	newUser["username"] = username;
	newUser["password"] = password;
	if (!users.addRecord(newUser)) {
		std::cout << "Got error while adding user to database" << std::endl;
		return main();
	}

	userLogin();

	return true;
}

bool userLogin() {
	clean();
	std::string username, password;
	std::cout << "Log in to your account here, type exit to quit" << std::endl;
	std::cout << "Enter username: ";
	std::getline(std::cin, username);
	if (username == "exit") return main();
	while (users.findByField("username", username).empty()) {
		if (username == "exit") return main();
		std::cout << "Username is taken or incorrect, try again or type exit: ";
		std::getline(std::cin, username);
		
	}
	auto userData = users.findByField("username", username);
	std::cout << "Enter password: ";
	std::getline(std::cin, password);

	int tries = 0;
	while (password != userData["password"] && tries < 3) {
		if (password == "exit") return main();
		std::cout << "Incorrect passowrd, try again (You have " << (3 - tries) << " left): ";
		std::getline(std::cin, password);
		tries++;
	}

	if (password == userData["password"]) {
		loggedScreen(userData);
	}
	else {
		return main();
	}
	return true; 
}


bool loggedScreen(std::unordered_map<std::string, std::string>& data) {
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
		std::string newPassword;
		std::cout << "Enter your new password or type exit: ";
		std::getline(std::cin, newPassword);
		if (newPassword == "exit") return loggedScreen(data);
		data["password"] = newPassword;
		if (!users.editRecord(data["id"], data)) {
			std::cout << "Edit failed, click any button to continue" << std::endl;
			std::cin.get();
		}
		return loggedScreen(data);
	}
	else if (operation == "2") {
		accountRemoval(data);
	}
	else if (operation == "3") {
		return main();
	}
	return true;
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
			return main();
		}
	}
	else {
		std::cout << "Error occured, push any button to go back to main screen" << std::endl;
		std::cin.get();
		return main();
	}

	return true;
}