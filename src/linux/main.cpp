#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "process.hpp"

int main( int argc, char *argv[] ) {

	char *program[1];
	program[0] = "iwlist";
	program[1] = "scan";

	runProgram(program);

	return 0;

}
