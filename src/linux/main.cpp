#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "process.hpp"
#include "../shared/Config.hpp"
#include "../shared/PassiveConnection.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

	Config agentConfig;
	PassiveConnection test;

	std::cout << agentConfig.toString();

	test.setReportUrl("http://curl.haxx.se/libcurl/c/getinmemory.html");

	std::cout
			<< test.getStatus(agentConfig.getUserId(),
					agentConfig.getDeviceId());

	return 0;

}
