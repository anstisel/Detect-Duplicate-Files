#include "duplicates.h"

void insertFiles(HASHTABLE *hashtble, fileData *dir) {

        if (hashtable_find(hashtble, dir)) {
		uint32_t index = hash_string(dir->hashvalue) % HASHTABLE_SIZE; //choose list
		LIST *list = hashtble[index];
		while(list->next!= NULL){
			list = list->next;
		}
		list->next = list_new_item(dir);
		list_print(hashtble[index]);

        }
	else {
        	hashtable_add(hashtble, dir);
	}
}

int find_duplicates(char *hash, bool displayf) {
	uint32_t index = hash_string(hash) % HASHTABLE_SIZE;	
	LIST *list = hashtble[index];
	if(displayf) {
		if(list != NULL && strcmp(hash, list->dir->hashvalue) == 0) {
			printrpath(list->dir->abspath);
			printf("adding a duplicate");
			numduplicates++;
			list = list->next;
		}
	}
	else { //list relative pathnames of files who's hash matches indicated hash
		if ( list != NULL && strcmp(hash, list->dir->hashvalue) == 0) {
			numduplicates++;
			printrpath(list->dir->abspath);
			list = list-> next;
		}
	}
	return numduplicates;
}		

void printrpath(char *abspath) {
	//converts absolute pathname to relativepath and prints it
	char *cwd = getcwd(NULL, 0); // Get the current working directory
    if (cwd == NULL) {
        perror("Error getting current working directory");
        return;
    }
    if (strncmp(abspath, cwd, strlen(cwd)) == 0) {
        // The absolute path is within the current working directory
        char *relativepath = abspath + strlen(cwd) + 1; // Skip the common part of the paths
        printf("%s\n", relativepath);
    } else {
        // The absolute path is outside the current working directory
        printf("%s\n", abspath);
    }
    free(cwd); // Free the memory allocated by getcwd
}

void printfilename(char *abspath) {
	//converst absoluate path to filename
    char *filename = strrchr(abspath, '/'); // Find the last occurrence of '/' in the path
    if (filename != NULL) {
        filename++; // Move past the '/' character
        printf("Duplicate found!: %s\n", filename); // Print the file name
    }
}


void print_duplicates(void) {
    for (int i = 0; i < HASHTABLE_SIZE; i++) {
        LIST *list = hashtble[i]; // Get the linked list at index i
        while (list != NULL) {
            if (list->next != NULL) {
                printfilename(list->dir->abspath); // Print the name of the file
            }
            list = list->next;
        }
    }
}

