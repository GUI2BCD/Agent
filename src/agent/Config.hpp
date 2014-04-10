/*
 * Config.hpp
 *
 *  Created on: Jan 25, 2014
 *      Author: cameron
 */

#ifndef CONFIG_HPP_
#define CONFIG_HPP_

#include <string>

// TODO put this in a default file somewhere
static std::string defaultURL = "http://morrisherd.com/LastResortRecovery/agent.php";

// Mode for the agent
enum AgentMode {

	FIRSTRUN, PASSIVE, ACTIVE
};


class Config {
public:
	// Initializes configuration file if necessary
	Config();
	// Cleans up config
	virtual ~Config();

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
	const std::string& getPassword() const;
	void setPassword(const std::string& password);
	const std::string& getUserName() const;
	void setUserName(const std::string& userName);
	int getPollInterval() const;
	void setPollInterval(int pollInterval);
	const std::string& getUrl() const;
	void setUrl(const std::string& url);
	const std::string& getPath() const;
	void setPath(const std::string& path);

private:
	// Get the local username
	std::string getUser();

	// Config path
	std::string path;

	// Username entered by user at first run
	std::string userName;
	// Encrypted password
	std::string password;
	// Device number generated by server
	std::string deviceID;
	// Current mode of the agent controlling actions
	AgentMode mode;
	// Poll interval of the agent
	int pollInterval;
	// URL of webhost
	std::string url;

};

#endif /* CONFIG_HPP_ */
