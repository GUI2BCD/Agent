#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "process.hpp"
#include "../shared/Config.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

	Config agentConfig;

	std::cout << agentConfig.toString();

	return 0;

}
