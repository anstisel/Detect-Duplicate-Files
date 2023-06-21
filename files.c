#include "duplicates.h"
#define HASHTABLE_SIZE 8192

fileData *fill_fileData( char *fullpath, long int fsize) {
	char *hash;
	numfiles++;
	fileData *dir = malloc(sizeof(fileData));
	dir->fsize = fsize; //save abspath and filsize in structure fileData
	dir->abspath = strdup(fullpath);

	totalfsize += dir->fsize; //accumulates sizes of files
	min_totalsize = totalfsize;
	hash = strSHA2(dir->abspath); 
	dir-> hashvalue =strdup(hash); //fileData holds all necessary items for a file
	
	if (hashtable_find(hashtble, dir)) {
		numduplicates++;
		min_totalsize = totalfsize- fsize; //do not include the file sizes of duplicates
	}
	return dir;
}

long int getsize(const char *abspath) {
	long int size = 0;
	
	if (stat(abspath, &statinfo) != 0) {
		perror("Cannot get file size error\n");
		size = -1;
	}
	else {
		size = statinfo.st_size;
	}
	return size;
}


//THIS PROGRAM LOOKS THROUGH FILES WITHIN A DIRECTORY
int printfiles(char *basepath, bool include_hidden) {
	//open and read each directory, print filenames, search directories recursively
	if (hashtble == NULL) {
		hashtble = hashtable_new();
	}
	int currentdup = numduplicates;
	DIR *directory = opendir(basepath);
	
	int ret = 0;
	
	long int fsize = 0;
    //printf("Checking directory: %s\n", basepath); // print the directory path being checked
    
	if(directory == NULL){
		printf("Open Directory Error\n");
		perror("Open Directory Error\n");
		return -1;
	}

	while (directory != NULL) {
		
			dpointer = readdir(directory); //reads current dir, positions stream to next directory
			if(dpointer == NULL) { 
				break; //reached end of directory stream
			}
	
			char *filename = dpointer->d_name;
			char *fullpath = strcat(realpath(basepath, NULL), "/"); //absolute path includes /rootfile
			fullpath = strcat( fullpath, filename); 
	
			ret = stat(fullpath, &statinfo); //get file status
			if(ret < 0){
				perror("Read stat fail\n"); 
				return -1;
			}

			if (S_ISDIR(statinfo.st_mode)) { //if file is a directory 
				if(0 == strcmp("..", filename) || 0 == strcmp(".", filename)){
				//ignore the current directory and its parent directory
					continue;
				}
				printfiles(fullpath, include_hidden); //recursively process all files within 
			}
			else { 
				//encountered a file
				//printf("Checking file: %s\n", fullpath); // print the file path being checked				
				fsize = getsize(fullpath);
				fileData *filepointer = fill_fileData(fullpath, fsize);
				if (include_hidden && filename[0] == '.') { 
					insertFiles(hashtble, filepointer);
				}
				else {	
					if (filename[0] != '.') {
						insertFiles(hashtble, filepointer);
					}
				}
			}	
				
	}	
		numfiles--;
        closedir(directory);
        return numduplicates- currentdup;
}


