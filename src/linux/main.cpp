#include <iostream>
#include <signal.h>
#include "../agent/Agent.hpp"

int main(int argc, char *argv[]) {

	// Agent object
	Agent agent;

	agent.run();

	return 0;

}
