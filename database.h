#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

class database
{
public:
	std::string dbName;

	// Initialization of database -> delete dafault value, add custom errorHandling
	database(std::string name) {
		// Throw database initialization error if name.size() == 0 or name is taken -> errorHandler
		
		// successful initialization, create the database file
		dbName = name;
		std::fstream file;
		file.open(dbName + ".txt", std::ios::in);
	}

	/// <summary>
	/// Add record with specified key value pairs to the database file
	/// </summary>
	/// <param name="keyValue">map of key value pairs that are going to be put inside database file</param>
	void addRecord(std::unordered_map<std::string, std::string> keyValue) {
		std::fstream file;
		file.open(dbName, std::ios::out);

		for (auto& [key, value] : keyValue) {
			file << key + ": " + value + ";";
		}
		file << std::endl;
		file.close();
	}
};

