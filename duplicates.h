#ifndef DUPLICATES_H
#define DUPLICATES_H //preventing the file from being included twice

//On Linux we need to prototype the (non-standard) strup() function
#if defined (__linux__) 
extern char *strdup(const char *string);
#endif

#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/param.h>


//helpful preprocessor macro to check if allocations are successful
#define CHECK_ALLOC(p) if (p == NULL) { perror(__func__); exit(EXIT_FAILURE); }
#define HASHTABLE_SIZE 8192
//Functions to be used
int printfiles(char *progname, bool aflag);
struct stat statinfo;
struct dirent *dpointer; //pointer for directory entry

int numduplicates;
int numfiles;
int totalfsize;
int min_totalsize;

typedef struct fileData {
        long int fsize;
        char *abspath;
        char *hashvalue; //strSHA2 string
} fileData;

//DEFINING A LIST OF DIRECTORIES
typedef struct _list {
	fileData *dir;
	struct _list *next; //pointer to another list (linked list)
} LIST;
extern LIST *list_new(void); //Create new empty list
extern LIST *list_add(LIST *list, fileData *dir); //add new pathname to list
extern bool list_find(LIST *list, fileData *wanted); //is pathname within list
extern void list_print(LIST *list);
extern LIST *list_new_item(fileData *dir);

//DEFINING A HASHTABLE TO MAP DIRECTORIES
typedef LIST *HASHTABLE; //creates an alias, typing HASHTABLE is equivalent to LIST*

extern void allocateHash(HASHTABLE *hashtble, fileData *dir);

 HASHTABLE *hashtble;
extern HASHTABLE *hashtable_new(void); //hashtable as new array of lists
extern void hashtable_add(HASHTABLE *hashbtle, fileData *dir); //add data (string)
extern bool hashtable_find(HASHTABLE *, fileData *dir); //determine whether file 
				//already exists within given hashtable 

extern void insertFiles(HASHTABLE *hashtble, fileData *dir);	
extern uint32_t hash_string(char *hashvalue);
extern char *strSHA2(char *pathname);
extern fileData *fill_fileData( char *abspath, long int fsize);

extern void print_statistics();
extern int find_duplicates(char *hash, bool displayf);
extern void print_duplicates();
extern void printrpath(char *abspath);



#endif 
