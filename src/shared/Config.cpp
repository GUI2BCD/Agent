/*
 * Config.cpp
 *
 *  Created on: Jan 25, 2014
 *      Author: cameron
 */

#include "Config.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
Config::Config() {

	setMode(FIRSTRUN);
	// Check if setup is required
	init();

}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

bool Config::init() {

	// Check if the config exists and is valid
	if (!loadConfig()) {
		// Prompt user
		std::cout << "First time setup required." << std::endl;
		return false;
	}

	return true;

}

bool Config::loadConfig() {

	// File object handle
	std::ifstream config;
	// Parsing variables
	std::string token, tmp;

	// Open file
	config.open("agent.cfg");

	// File doesn't exist
	if( !config.is_open() ) {
		config.close();
		return false;
	}

	// Read through file line by line
	while (config.is_open() && std::getline(config, token)) {

		std::stringstream lineParser(token);
		lineParser >> tmp;

		// Handle each key here

		// Mode
		if (tmp == "mode:") {
			lineParser >> tmp;

			// Nothing set
			if (tmp.empty()) {
				std::cout << "Error: No mode set." << std::endl;
				return false;
			}
			// Passive mode
			else if (tmp == "passive") {
				setMode(PASSIVE);
			}
			// Active mode
			else if (tmp == "active") {
				setMode(ACTIVE);
			}
			// Bad option
			else {
				std::cout << "Mode invalid option: " << tmp;
				setMode(PASSIVE);
			}
		}
		// Username
		else if (tmp == "username:") {
			lineParser >> tmp;

			// Nothing set
			if (tmp.empty()) {
				std::cout << "Error: No username set." << std::endl;
				return false;
			}
			// Username
			else {
				setUserName(tmp);
			}

		}
		// Userid
		else if (tmp == "userid:") {
			lineParser >> tmp;

			// Nothing set
			if (tmp.empty()) {
				std::cout << "Error: No userid set." << std::endl;
				return false;
			}
			// Userid
			else {
				setUserId(tmp);
			}

		}

		// Deviceid
		else if (tmp == "deviceid:") {
			lineParser >> tmp;

			// Nothing set
			if (tmp.empty()) {
				std::cout << "Error: No deviceid set." << std::endl;
				return false;
			}
			// Username
			else {
				setDeviceId(tmp);
			}

		}
		// Bad key
		else {
			std::cout << "Invalid key: " << tmp << std::endl;
		}

	}

	config.close();
	return true;
}

bool Config::saveConfig() {

	std::ofstream config;

	// Open config file and write each key
	config.open("agent.cfg");

	// Passive mode
	if (getMode() == PASSIVE) {
		config << "mode: passive" << std::endl;
	}
	// Active mode
	else if (getMode() == ACTIVE) {
		config << "mode: active" << std::endl;
	}
	// Nothing set
	else {
		config << "mode: passive" << std::endl;
	}

	// Username
	if (!getUserName().empty()) {
		config << "username: " << getUserName() << std::endl;
	}
	// Nothing set
	else {
		config << "username: " << std::endl;
	}

	// Userid
	if (!getUserName().empty()) {
		config << "userid: " << getUserId() << std::endl;
	}
	// Nothing set
	else {
		config << "userid: " << std::endl;
	}

	// Deviceid
	if (!getUserName().empty()) {
		config << "deviceid: " << getDeviceId() << std::endl;
	}
	// Nothing set
	else {
		config << "deviceid: " << std::endl;
	}

	// Close file
	config.close();

	return true;

}

std::string Config::toString() {

	 std::stringstream tmp;

	 tmp << "mode: " << getMode() << std::endl <<
			"username: " << getUserName() << std::endl <<
			"userid: " << getUserId() << std::endl <<
			"deviceid: " << getDeviceId() << std::endl;


	 return tmp.str();

}

const std::string& Config::getDeviceId() const {
	return deviceID;
}

void Config::setDeviceId(const std::string& deviceId) {
	deviceID = deviceId;
}

AgentMode Config::getMode() const {
	return mode;
}

void Config::setMode(AgentMode mode) {
	this->mode = mode;
}

const std::string& Config::getUserId() const {
	return userID;
}

void Config::setUserId(const std::string& userId) {
	userID = userId;
}

const std::string& Config::getUserName() const {
	return userName;
}

void Config::setUserName(const std::string& userName) {
	this->userName = userName;
}
