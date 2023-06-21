#include "duplicates.h"
#define HASHTABLE_SIZE	8192

LIST *list_new(void) { //create empty list (just a null-pointer)
	return NULL;
}

bool list_find(LIST *list, fileData *wanted) { //string = directory name
	while (list != NULL) {
		if (strcmp( list->dir->hashvalue, wanted->hashvalue) == 0) { //check if list *dir points to matching hash 
			return true;
		}
		list = list-> next; //not found so move to next list within hashtable
	}
	return false;
}


LIST *list_new_item (fileData *dir) {
	LIST *new = malloc(sizeof(LIST));
	CHECK_ALLOC(new);
	new->dir = dir;
	CHECK_ALLOC(new->dir);
	new->next = NULL;
	return new;
}

LIST *list_add(LIST *list, fileData *dir) {
	LIST *new = list_new_item(dir);
	new-> next = list;
	return new;
}

//  PRINT EACH ITEM (A STRING) IN A GIVEN LIST TO stdout
void list_print(LIST *list)
{
    if(list != NULL) {
        while(list != NULL) {
		//printf("ABSPATH: \t%s", list->dir->abspath); // Print the absolute path of the directory/file
	    if(list->next != NULL) {
			//printf(" -> \n");
            }
	    list	= list->next;
        }
    }
}

uint32_t hash_string(char *hashvalue) {
	uint32_t hash = 0;
	while (*hashvalue != '\0') {
		hash = hash*33 + *hashvalue; //allocate data in a fairly spread out manner
		++hashvalue;
	}
	return hash; //hash position where string exists is returned
}

HASHTABLE *hashtable_new(void) {
	HASHTABLE *new = malloc(HASHTABLE_SIZE * sizeof(LIST *)); //allocates space for new hashtable
	CHECK_ALLOC(new);
	return new;
}

void hashtable_add(HASHTABLE *hashtable, fileData *dir) {
	uint32_t h = hash_string(dir->hashvalue) % HASHTABLE_SIZE; //choose list
	hashtable[h] = list_add(hashtable[h], dir);
	//printf("\nAdding: hashtable[h] = %s\n", hashtable[h]->dir->abspath);
}

bool hashtable_find(HASHTABLE *hashtable, fileData *dir) {
	uint32_t h = hash_string(dir->hashvalue) % HASHTABLE_SIZE;
	return list_find(hashtable[h], dir);
}









