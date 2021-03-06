/*
 * Agent.cpp
 *
 *  Created on: Jan 26, 2014
 *      Author: cameron
 */

#include "Agent.hpp"
#include <string>
#include <iostream>
#include <termios.h>
#include <unistd.h>
#include <signal.h>
#include <openssl/sha.h>
#include <stdio.h>
#include <string.h>
#include "Report.hpp"
bool Agent::running = true;


/**
 * Sets the default parameters for the agent
 */
Agent::Agent() {
	config.setPollInterval(30);
	config.setMode(PASSIVE);

}

Agent::~Agent() {
	// TODO Auto-generated destructor stub
}

/**
 * This function is the main loop of the agent. It handles the entire logic
 * of the agent.
 */
void Agent::run() {

	// Holds the current status of the device
	std::string status;

	// Setup signals
	setSignals();

	// Load configuration file
	if (!config.loadConfig()) {
		// Run first time setup
		firstRunSetup();
	} else {
		// Setup connection from config
		connection.setReportUrl(config.getUrl());
	}

	// Enter main daemon loop
	while (running) {

		// Get status of device
		status = connection.getStatus(config.getUserName(),
				config.getPassword(), config.getDeviceId());

		// Print current status
		std::cout << "Status: " << status << std::endl;
		if (status == "LOST") {

			// Generate report and submit
			runReport();

			// Wait for next poll
			sleep(config.getPollInterval());

		} else {
			// Wait for next poll
			sleep(config.getPollInterval());
		}

	}

}
/**
 * This will prompt the user to enter their details which will then validated
 * against the server. If valid it will store it in the config file. Otherwise
 * will continue prompting.
 */
void Agent::firstRunSetup() {

	// Temporary variables to hold user input
	std::string username;
	std::string password;
	std::string deviceName;
	std::string tmp;
	// Terminal blanking
	termios tty;
	// Setup connection
	connection.setReportUrl(config.getUrl());

	// Print message about the setup
	std::cout << "****************************" << std::endl;
	std::cout << " Last Resort Recovery Setup " << std::endl;
	std::cout << "****************************" << std::endl;
	std::cout << "This process will connect this computer to your account"
			<< std::endl;
	std::cout << "Please enter your account details." << std::endl << std::endl;

	do {
		// Prompt for username
		std::cout << "Email: ";
		std::cin >> username;

		// Prompt for password
		std::cout << "Password: ";

		// Blank input
		tcgetattr(STDIN_FILENO, &tty);
		tty.c_lflag &= ~ECHO;
		tcsetattr(STDIN_FILENO, TCSANOW, &tty);

		// Get user input
		std::cin >> password;

		// Unblank input
		tty.c_lflag |= ECHO;
		tcsetattr(STDIN_FILENO, TCSANOW, &tty);
		std::cout << std::endl;

		// Encrypt password
		password = encryptPassword(password);

	} while (connection.authenticate(username, password) != "Logged in");

	std::cout << "Logged in successfully." << std::endl;

	// Register this device
	do {
		std::cout << std::endl;
		std::cout << "Device name: ";
		std::cin >> deviceName;

		tmp = connection.registerDevice(username, password, deviceName);

	} while (tmp == "-1");

	config.setDeviceId(tmp);

	// Store info
	config.setUserName(username);
	config.setPassword(password);
	connection.setReportUrl(config.getUrl());

	// Save to configuration file
	config.saveConfig();

	// Done
	std::cout << std::endl;
	std::cout << "Your device is now registered. ";
	std::cout << "Please return to your dashboard." << std::endl;

}

/**
 * This function will set the agent to shutdown after catching a signal from OS
 * @param n
 */
void Agent::sigShutdown(int n) {
	std::cout << "Shutting down..." << std::endl;
	running = false;
}

/**
 * This function sets the OS signals to be handled by our signal handler
 */
void Agent::setSignals() {

	// Our signals we catch
	int sigs[] = { SIGHUP, SIGINT, SIGQUIT, SIGBUS, SIGTERM, SIGSEGV, SIGFPE };

	int nsigs = sizeof(sigs) / sizeof(int);

	// Enable the handler for each handler
	for (int i = 0; i < nsigs; i++) {

		if (signal(sigs[i], Agent::sigShutdown) == SIG_ERR) {
			throw "Failed to set signals";
		}

	}

}

/**
 * Runs the data collection process and submits it to the server
 */
void Agent::runReport() {

	Report r;
	std::string reportID;

	// Get effective username
	r.setUser(config.getUser());

	// Run data collection
	std::cout << "Collecting data..." << std::endl;
	r.collectData();
	// Submit to server
	std::cout << "Sending to server..." << std::endl;
	reportID = connection.sendReport(config.getUserName(), config.getPassword(),
			config.getDeviceId(), r.toPost());
	std::cout << "Submitting images..." << std::endl;
	connection.submitImages(reportID,r.getWebcam(),r.getScreenshot());

	std::cout << "Reporting complete." << std::endl;
}

/**
 * Encrypts password with the SHA512 algorithm
 * Source: http://www.askyb.com/cpp/openssl-sha512-hashing-example-in-cpp/
 *
 * @param p unhashed password
 * @return hashed password
 */
std::string Agent::encryptPassword(std::string p) {

	unsigned char digest[SHA512_DIGEST_LENGTH];

	SHA512((unsigned char*) p.c_str(), strlen(p.c_str()),
			(unsigned char*) &digest);

	char mdString[SHA512_DIGEST_LENGTH * 2 + 1];

	for (int i = 0; i < SHA512_DIGEST_LENGTH; i++)
		sprintf(&mdString[i * 2], "%02x", (unsigned int) digest[i]);

	return std::string(mdString);

}
