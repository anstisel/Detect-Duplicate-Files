#Makefile to build our 'duplicates' project
PROJECT = duplicates
HEADERS = $(PROJECT).h
OBJ = duplicates.o files.o hashAllocate.o hashing.o strSHA2.o 

C11 = cc -std=c11
CFLAGS = -Wall -Werror -pedantic

$(PROJECT): $(OBJ)
	$(C11) $(CFLAGS) -o $(PROJECT) $(OBJ) 

%.o: %.c $(HEADERS) 
	$(C11) $(CFLAGS) -c $<  

clean:
	rm -f $(PROJECT) $(OBJ)
	rm *.o $(PROJECT) $(OBJ)
