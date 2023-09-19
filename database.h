#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

std::unordered_map<std::string, std::string> extractFromLine(std::string& line);

class Database
{
private:
	std::fstream file;
	int recordsNum = 0;

public:
	const std::string dbName;
	const std::string filename = dbName + ".txt";
	
	// Database class constructor, set name to default or provided value
	Database(const std::string name = "defaultDB") : dbName(name) {}

	/// <summary>
	/// Add records with specified key value pairs to the database file only if
	/// the specified record does not exist
	/// </summary>
	/// <param name="keyValue">key-value pairs that are going to be put inside database</param>
	/// <param name="checkField">field of the database by which availability is checked eg. is username taken</param>
	bool addRecord(std::unordered_map<std::string, std::string>& keyValue, std::string checkField = "") {
		// TODO: CHECK IF USER ALREADY EXISTS -> print error message
		// Open the file with control at the end of the file
		if (checkField.size()) {
			auto result = findByField(checkField, keyValue[checkField]);
			if (!result.empty()) {
				std::cout << "Item already exists" << std::endl;
				return false;
			}
		}
		file.open(filename, std::ios::app);

		// Insert id + key-value pairs separated by semicolon and 
		// increment count of records in database to know next id
		file << recordsNum;
		for (auto& [key, value] : keyValue) {
			file << ";" + key + ": " + value;
		}
		recordsNum++;
		// divide from the next record by endl and close the file
		file << ";" << std::endl;
		file.close();
		return true;
	}


	std::unordered_map<std::string, std::string> findByField(std::string field, std::string value) {
		file.open(filename, std::ios::in);
		std::string line, result;
		std::string searchTerm = field + ": " + value + ";";
		while (getline(file, line)) {
			if (line.find(searchTerm) != std::string::npos) {
				result = line;
				break;
			}
		}
		file.close();
		if (result.empty()) {
			return {};
		}
		return extractFromLine(result);
	}
};
