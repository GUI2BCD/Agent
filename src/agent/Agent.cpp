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

bool Agent::running = true;

Agent::Agent() {
	config.setPollInterval(10);

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
	}

	// Enter main daemon loop
	while (running) {

		// Get status of device
		//status = connection.getStatus(config.getUserName(),
		//		config.getPassword(), config.getDeviceId());

		std::cout << "Status: " << status << std::endl;
		if (status == "lost") {

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
	// Terminal blanking
	termios tty;

	// Print message about the setup
	std::cout << "****************************" << std::endl;
	std::cout << " Last Resort Recovery Setup " << std::endl;
	std::cout << "****************************" << std::endl;
	std::cout << "This process will connect this computer to your account"
			<< std::endl;
	std::cout << "Please enter your account details." << std::endl << std::endl;

	// Prompt for username
	std::cout << "Username: ";
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

	// TODO Encrypt password

	// TODO Check if credentials are valid

	// TODO Register this device
	config.setDeviceId("-1");

	// Store info
	config.setUserName(username);
	config.setPassword(password);

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
	int sigs[] = { SIGHUP, SIGINT, SIGQUIT, SIGBUS,
	SIGTERM, SIGSEGV, SIGFPE };

	int nsigs = sizeof(sigs) / sizeof(int);

	// Enable the handler for each handler
	for (int i = 0; i < nsigs; i++) {

		if (signal(sigs[i], Agent::sigShutdown) == SIG_ERR) {
			throw "Failed to set signals";
		}

	}

}
