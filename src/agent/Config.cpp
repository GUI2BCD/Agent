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

}

Config::~Config() {
	// TODO Auto-generated destructor stub
}

/**
 * This loads the configuration file from disk to memory
 * @return bool of status whether config is valid or not
 */
bool Config::loadConfig() {

	// File object handle
	std::ifstream config;
	// Parsing variables
	std::string token, tmp;

	// Open file
	config.open("/etc/llragent.cfg");

	// File doesn't exist
	if (!config.is_open()) {
		config.close();
		// Set defaults
		setUrl(defaultURL);

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
				setMode(PASSIVE);
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
		// URL
		else if (tmp == "url:") {
			lineParser >> tmp;

			// Nothing set
			if (tmp.empty()) {
				std::cout << "Error: No url set." << std::endl;
				setUrl(defaultURL);
			}
			// Username
			else {
				setUrl(tmp);
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
		// Password
		else if (tmp == "password:") {
			lineParser >> tmp;

			// Nothing set
			if (tmp.empty()) {
				std::cout << "Error: No password set." << std::endl;
				return false;
			}
			// Userid
			else {
				setPassword(tmp);
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
/**
 * Saves the configuration from memory to the disk
 * @return bool whether save was successful
 */
bool Config::saveConfig() {

	std::ofstream config;

	// Open config file and write each key
	config.open("/etc/llragent.cfg");

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

	// URL
	if (!getUrl().empty()) {
		config << "url: " << getUrl() << std::endl;
	}
	// Nothing set
	else {
		config << "url: http://morrisherd.com/LastResortRecovery/agent.php"
				<< std::endl;
	}

	// Username
	if (!getUserName().empty()) {
		config << "username: " << getUserName() << std::endl;
	}
	// Nothing set
	else {
		config << "username: " << std::endl;
	}

	// Password
	if (!getPassword().empty()) {
		config << "password: " << getPassword() << std::endl;
	}
	// Nothing set
	else {
		config << "password: " << std::endl;
	}

	// Deviceid
	if (!getDeviceId().empty()) {
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

/**
 * Creates a string representation of the configuration
 * @return string representation
 */
std::string Config::toString() {

	std::stringstream tmp;

	tmp << "mode: " << getMode() << std::endl << "username: " << getUserName()
			<< std::endl << "password: " << getPassword() << std::endl
			<< "deviceid: " << getDeviceId() << std::endl;

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

const std::string& Config::getPassword() const {
	return password;
}

void Config::setPassword(const std::string& password) {
	this->password = password;
}

const std::string& Config::getUserName() const {
	return userName;
}

void Config::setUserName(const std::string& userName) {
	this->userName = userName;
}

int Config::getPollInterval() const {
	return pollInterval;
}

void Config::setPollInterval(int pollInterval) {
	this->pollInterval = pollInterval;
}

const std::string& Config::getUrl() const {
	return url;
}

void Config::setUrl(const std::string& url) {
	this->url = url;
}
