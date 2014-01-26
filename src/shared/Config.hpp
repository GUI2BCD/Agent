/*
 * Config.hpp
 *
 *  Created on: Jan 25, 2014
 *      Author: cameron
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <string>

// Mode for the agent
enum AgentMode {

	FIRSTRUN,
	PASSIVE,
	ACTIVE
};


class Config {
public:
	// Initializes configuration file if necessary
	Config();
	// Cleans up config
	virtual ~Config();

	// Checks the status of the config and loads it if possible
	bool init();
	// Loads the options from the file into memory
	bool loadConfig();
	// Saves the options from memory to file
	bool saveConfig();

	// Converts object to string
	std::string toString();

	// Getters & Setters
	const std::string& getDeviceId() const;
	void setDeviceId(const std::string& deviceId);
	AgentMode getMode() const;
	void setMode(AgentMode mode);
	const std::string& getUserId() const;
	void setUserId(const std::string& userId);
	const std::string& getUserName() const;
	void setUserName(const std::string& userName);

private:
	// Username entered by user at first run
	std::string userName;
	// User number by generated by server
	std::string userID;
	// Device number generated by server
	std::string deviceID;
	// Current mode of the agent controlling actions
	AgentMode mode;
};

#endif /* CONFIG_HPP_ */