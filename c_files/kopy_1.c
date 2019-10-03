/******************************************************************
kopy.c
An example Unix-like shell copy command/utility.
Copies the first file to the second. Options to be defined.
D.Heffernan
1/April/2007  last update: 27/Sep/11
ver 0.1.1
*****************************************************************/                   

//ID 16160703
//Name Lorcan Williamson 

#include <stdio.h>  
#include <stdlib.h>
#include <fcntl.h>
#include <sys/time.h>
#include <ctype.h>

int close(int a);
int read(int a, char b[], int c);
int write(int a, char b[], int c);

int main (int argc, char *argv[])   {
    int i, j;
    int fileArg = 0; // Count for files on command line
    int infd, outfd; // File descriptor for input and output file
    int num_read, num_write;  // Numbers of characters returned by a file access
    char buff [4096]; // Buffer for use in file access
    char* fileName[2] = {} ;  // Point to file names

    // flags for the command line options
    short upperOption = 0;
    short sizeOption = 0;
    short rateOption = 0;
    // Parse the command line arguments
    for (i = 1 ; i < argc; i++ ) {
        if (argv[i][0] == '-') { // Check for a command option
            switch (argv[i][1]) {
	        case 'u':
		    upperOption = 1;
		    break;
		case 's':
	            sizeOption = 1;
		    break;
		case 'r':
	            rateOption = 1;
		    break;
	    }
	}
        else {
	    fileName[fileArg++] = argv[i];
	}
    }

    // Open the first file for reading
    infd = open (fileName[0], O_RDONLY);
    if (infd == -1) { 
        printf ("Failed to open first file %s\n", fileName[0]);
	return 1;
    }
    // Open/create the second file for writing
    outfd = open (fileName[1], O_CREAT | O_WRONLY, 0600 );
    if (outfd == -1) {
        printf ("Failed to open second file %s\n", fileName[1]);
	close (infd);
	return 1;
    }

    // used to time the copy rate for the -r option
    struct timeval startTime;
    struct timeval endTime;
    // used to count the size
    int size = 0;
    // sets tv_sec and tv_usec of startTime to current time
    gettimeofday(&startTime, NULL);
    // Now copy the contents of the first file to the second file
    while ((num_read = read (infd, buff, sizeof (buff))) > 0) {
        // if upper buffer is set then convert the buffer to uppercase
	if (upperOption) {
            for (i = 1; i < num_read; i++ ) {
                buff[i] = islower(buff[i]) ? toupper(buff[i]) : buff[i];
	    }
	}
	size++;
  	num_write = write (outfd, buff, num_read);
        // Check for basic failure
	if (num_write != num_read) {
            printf ("Problem -mismatch between write size and read size!\n");
        }
    }
    // sets tv_sec and tv_usec of endTime to current time
    gettimeofday(&endTime, NULL);

    double start = startTime.tv_sec * 1000000 + startTime.tv_usec; // gets start in usec
    double end = endTime.tv_sec * 1000000 + endTime.tv_usec; //gets end in usec
    unsigned long deltaTime = (unsigned long)(end - start); // gets difference
    double rate = size*1000000.0/deltaTime; // gets rate in KB/s
    if (rateOption) { // if rate option is set then display the rate
	printf("File copied at %fKB/s\n", rate);
    }

    if (sizeOption) { // if size option is set then display the size
        printf("%s is %dkB\n", fileName[0], size);
    }
    // Remember to close all open files before exit           
    close (outfd);
    close (infd);
    return 0 ;
}
