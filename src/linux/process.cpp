#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <cstdarg>

int runProgram( char *program[] ) {

	// Pipes for parent-child communication
	int child_in[2], child_out[2];
	// Counts number of characters read
	int bytes;
	// Holds child output
	char buffer[256];


	// Initialize pipes
	if( pipe(child_in) == -1 || pipe(child_out) == -1 ) {
		perror("pipe");
		exit(-1);
	}
	
	switch( fork() ) {

		// Failure
	case -1:
		printf("Failed to fork\n");
		exit(-1);
		break;

		// Child case
	case 0:
		
		// Repipe input
		if( close(0) == -1 ) {
			perror("pipe");
			exit(-1);
		}
		
		if( dup( child_in[0] ) != 0 ) {
			perror("dup");
			exit(-1);
		}

		// Repipe output
		if( close(1) == -1 ) {
			perror("pipe");
			exit(-1);
		}
		
		if( dup( child_out[1] ) != 1 ) {
			perror("dup");
			exit(-1);
		}

		// Close local/unused pipes
		if( close( child_in[0] ) == -1 || close( child_in[1] ) == -1 ||
				close( child_out[0] ) == -1 || close( child_out[1] ) == -1 ) {
			
			perror("close");
			exit(-1);
		}

		execvp( program[0], program );

		perror("execlp");
		
		exit(-1);

		break;

		// Parent case
	default: 
		
		// Close unused pipes
		if( close( child_in[0] ) == -1 || close( child_out[1] ) == -1 ) {
			perror("close");
			exit(-1);
		}
		
		// Close input
		if( close( child_in[1] ) == -1 ) {
			perror("close");
			exit(-1);
		}

		// Read child output
		while( ( bytes = read( child_out[0], buffer, sizeof(buffer))) != 0 ) {

			// Read error
			if( bytes == -1 ) {
				perror("read");
				exit(-1);
			}
			
			// Handle child output
			printf( buffer );

		}
		
		// Close pipe
		close(child_out[0]);
		
	}

	return 0;

}
