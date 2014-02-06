/*
 * Agent.hpp
 *
 *  Created on: Jan 26, 2014
 *      Author: cameron
 */

#ifndef AGENT_HPP_
#define AGENT_HPP_

class Agent {
public:

	Agent();
	virtual ~Agent();

	// Will prompt the user to enter their details and initialize this agent
	void firstRunSetup();

	void run();
	void registerDevice();
	void getStatus();
	

};

#endif /* AGENT_HPP_ */
