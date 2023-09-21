#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>}

// TODO: Loading database files and operating on them, custom and comprehensive errorHandling,
// Schema validation

// database.cpp functions initialization
std::unordered_map<std::string, std::string> extractFromLine(std::string& line);

class Database
{
private:
	std::fstream file;
	int recordsNum = 0;

public:
	std::string dbName;
	std::vector<std::string> dbSchema;
	std::string filename;
	
	// Database class constructor, set name to default or provided value
	Database() {};


	bool init(std::vector<std::string>& schema) {
		if (!schema.size()) return false;
		dbSchema = schema;
		std::cout << "Provide name for database file. (Default: defaultDB.txt)" << std::endl;
		std::getline(std::cin, dbName);
		filename = dbName.size() ? dbName + ".txt" : "defaultDB.txt";
		std::string operation;
		file.open(filename, std::ios::in);
		if (file.is_open()) {
			std::cout << "File " + dbName + " currently exist, do you want to erase it's content? (Y/N)" << std::endl;
			std::getline(std::cin, operation);
			file.close();
			if (operation == "Y" || operation == "y") {
				file.open(filename, std::ios::out | std::ios::trunc);
				file.close();
				return true;
			}
			return false;
		}
		else {
			file.open(filename, std::ios::app);
			file.close();
			return true;
		}
	}


	/// <summary>
	/// Add records with specified key value pairs to the database file only if
	/// the specified record does not exist
	/// </summary>
	/// <param name="keyValue">key-value pairs that are going to be put inside database</param>
	/// <param name="checkField">field of the database by which availability is checked eg. is username taken</param>
	/// <returns>returns true - success, false - failure</returns>
	bool addRecord(std::unordered_map<std::string, std::string>& keyValue, std::string checkField = "") {
		// Check if there's no record with provided value by checkField eg. is username free
		if (checkField.size()) {
			auto result = findByField(checkField, keyValue[checkField]);
			if (!result.empty()) {
				std::cout << "Item already exists" << std::endl;
				return false;
			}
		}
		// Open the file with control at the end of the file
		file.open(filename, std::ios::app);

		// Insert id + key-value pairs separated by semicolon and 
		// increment count of records in database to know next ID
		keyValue["id"] = std::to_string(recordsNum);
		for (auto& key : dbSchema) {
			file << key + ": " + keyValue[key] + ";";
		}
		recordsNum++;
		file << std::endl;
		// divide from the next record by endl and close the file
		file.close();
		return true;
	}

	bool editRecord(std::string id, std::unordered_map<std::string, std::string>& newData) {
		// Function variables
		std::string line;
		int lineCount = 0, lineID = stoi(newData["id"]);
		// Need char* to remove/rename file
		char* originalFile = filename.data();
		// create and open temp file
		std::fstream temp;
		file.open(filename, std::ios::in);
		temp.open("temp.txt", std::ios::app);
		// Write every line of db file except the one with ID to edit
		// Put edited on its place
		while (getline(file, line)) {
			if (lineCount != lineID) {
				temp << line << std::endl;
			}
			else {
				for (auto& key : dbSchema) {
					temp << key + ": " + newData[key] + ";";
				}
				temp << std::endl;
			}
			lineCount++;
		}

		temp.close();
		file.close();
		// Remove original db, rename temp to original DB file and
		// check for errors
		if (std::remove(originalFile) == -1) {
			std::cout << "Edit failed because of file deletion failure" << std::endl;
			return false;
		}
		if (std::rename("temp.txt", originalFile) == -1) {
			std::cout << "Edit failed because of file rename failure" << std::endl;
			return false;
		}

		return true;

	}


	/// <summary>
	/// Remove record from database with specified field value
	/// </summary>
	/// <param name="field">Record field name to match and remove</param>
	/// <param name="value">Record field value to match and remove</param>
	/// <returns>returns true-success, false-failure</returns>
	bool removeRecord(std::string field, std::string value) {
		// Function variables
		std::string line;
		int lineCount = 0, lineID = stoi(findByField(field, value)["id"]);
		// Need char* to remove/rename file
		char* originalFile = filename.data();
		// create and open temp file
		std::fstream temp;
		file.open(filename, std::ios::in);
		temp.open("temp.txt", std::ios::app);
		// Write every line of db file except the one with ID to remove and
		// put DELETED USER: ID on deleted record line
		while (getline(file, line)) {
			if (lineCount != lineID) {
				temp << line << std::endl;
			}
			else {
				temp << "#DELETED USER:" << lineID << std::endl;
			}
			lineCount++;
		}

		temp.close();
		file.close();
		// Remove original db, rename temp to original DB file and
		// check for errors
		if (std::remove(originalFile) == -1) {
			std::cout << "Removal failed because of file deletion failure" << std::endl;
			return false;
		}
		if (std::rename("temp.txt", originalFile) == -1) {
			std::cout << "Removal failed because of file rename failure" << std::endl;
			return false;
		}

		return true;
	}

	/// <summary>
	/// Find record with provided field value
	/// </summary>
	/// <param name="field">Record field to return</param>
	/// <param name="value">Record value to return</param>
	/// <returns>Unordered map of key value pairs of the found record or
	///  empty map when record do not exist</returns>
	std::unordered_map<std::string, std::string> findByField(std::string field, std::string value) {
		// Function variables
		std::string line, result;
		std::string searchTerm = field + ": " + value + ";";
		// Open file in read mode
		file.open(filename, std::ios::in);
		while (getline(file, line)) {
			if (line.find(searchTerm) != std::string::npos) {
				result = line;
				break;
			}
		}
		file.close();
		// Check if the record exist and return
		if (!result.size()) return {};
		return extractFromLine(result);
	}
};
