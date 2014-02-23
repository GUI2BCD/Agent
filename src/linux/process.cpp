#include "process.hpp"
#include <stdio.h>

std::string runProgram( std::string program, std::string option ) {

	FILE *pipe;
	char buffer[80];

	std::string result = "";


	// Create pipe
	if(( pipe = popen( program.c_str(), option.c_str())) == NULL ) {

		perror("popen");
		return "";

	}

	// Read data
	while( fgets( buffer, 80, pipe ) ) {

		result+= buffer;

	}
	
	// Close pipes
	pclose(pipe);


	return buffer;


}
