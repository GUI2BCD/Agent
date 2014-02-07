/*
 * Agent.hpp
 *
 *  Created on: Jan 26, 2014
 *      Author: cameron
 */

#ifndef AGENT_HPP_
#define AGENT_HPP_
#include "Config.hpp"
#include "PassiveConnection.hpp"

class Agent {
public:

	Agent();
	virtual ~Agent();

	// Main loop of agent
	void run();

	// Will prompt the user to enter their details and initialize this agent
	void firstRunSetup();
	void registerDevice();
	void getStatus();
	
	static void sigShutdown( int n );


private:

	void setSignals();

	Config config;
	PassiveConnection connection;

	static bool running;


};

#endif /* AGENT_HPP_ */
