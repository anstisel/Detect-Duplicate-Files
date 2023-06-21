//Project 2
//Student 1: Elisha Anstiss 22241944
//Student 2: Yuying Mao 22772169

#include "duplicates.h"
#include <getopt.h>

void print_statistics(void) {
        printf("Number of files: %i\n", numfiles);
        printf("Total size: %i\n", totalfsize);
        printf("Number of duplicates: %i\n", numduplicates);
		printf("Minimum size: %i\n", min_totalsize);
}

void usage(char *progname) {
	fprintf(stderr, "To run: ./%s [options] dirname1\n", progname);
	fprintf(stderr, "Options are:\n");
	fprintf(stderr, "-a:\t\t checks and prints all files, including those beginning with '.'\n");
	fprintf(stderr, "-f:\t\t finds and prints all relative paths of the filename\n");
	fprintf(stderr, "-l:\t\t lists all file of duplicates found\n");
	fprintf(stderr, "-q:\t\t quietly tests if any duplicates exist, if so EXIT_SUCCESS else EXIT_FAILURE\n");
	fprintf(stderr, "For example: try ./duplicates -a testdir\n");
	exit(EXIT_FAILURE);
}

int main( int argc, char*argv[]) {
	char *progname = ( progname = strrchr(argv[0], '/')) ? progname+1 : argv[0]; //a?b:c --> b if a is true, else c
	int numduplicates =0;
#if defined(ADVANCED)
	if(argc < 1) {
		usage(progname);
	}
#else
	if (argc != 1) {
		//usage(progname); THIS WAS UNCOMMENTED, under assumption all your compiling would be done with one input
	}
	
#endif
	
	int opt;
	char OPTLIST[] = "af:lq"; 
	bool include_hidden = false;
	bool duplicatesPrinted = false; //Flag to track if -l (thus do not print usage)
	char *displayf = NULL;
	char *displayh = NULL;
	bool displayl = false;
	bool qexit = false;

	while ((opt = getopt(argc, argv, OPTLIST)) != -1) { //while options are available
		switch(opt) {
			case 'a' :
				//simulates Linux -ls
				include_hidden = true; //set aflag to true			
				break;
			case 'f':
				displayf = strdup(optarg); //optarg grabs next argument= filename
				CHECK_ALLOC(displayf);
				break;
			case 'l': 
				displayl = true;
				break;
			case 'q':
				qexit = true;
				break;
			default: 
				fprintf(stderr, "Usage: %s -%c is invalid\n", progname, opt);
				argc = -1;
				break;
		}

	}

	if ((argc-optind) < 1) {
		usage(progname);
	}
	struct stat statinfo;
	if (argc == 2) {
		numduplicates = printfiles(argv[1], include_hidden);
	}

	if (stat(argv[2], &statinfo) == 0 || S_ISDIR(statinfo.st_mode)) { //if input is acceptable directoryTHIS WAS PREVIOUSLY ARGV[0]
		numduplicates = printfiles(argv[2], include_hidden);
	}
	else {
		perror(argv[2]);
		exit(EXIT_FAILURE);
	}	

	if (displayf) { //find files with the same hash as the hash of the filename provided
		char *hash = strSHA2(displayf);
	//	int numduplicates = find_duplicates(hash, displayf);
		//Subsequent methods called by find_duplicates not working, thus numduplicates unused error
		free(hash);
		free(displayf);
		exit(numfiles > 0 ? EXIT_SUCCESS : EXIT_FAILURE); 
	}
	if (displayh) { //find files with same hash as hash given
		//int numduplicates = find_duplicates(displayh, "");
		//Subsequent methods called by find_duplicates not working, thus numduplicates unused error
	
		free(displayh);
		exit(numfiles > 0 ? EXIT_SUCCESS : EXIT_FAILURE);	
	}
	if (qexit) {
		exit(numduplicates == 0 ? EXIT_SUCCESS: EXIT_FAILURE);
	}
	if (displayl) {
		print_duplicates();
		duplicatesPrinted = true;
	}
	if (!duplicatesPrinted) {
		print_statistics();
	}
	return 0;
}
