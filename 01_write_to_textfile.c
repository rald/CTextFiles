#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define TEST_FILE "database.txt"



int main(void) {

	FILE *fh=NULL;
	
	char *message=NULL;
	int llen=0;
	
	char *p=NULL;
	
	printf("Enter message: ");
	getline(&message,&llen,stdin); 
	
	p=strchr(message,'\n');
	if(p) *p='\0';

	if((fh=fopen(TEST_FILE,"wt"))!=NULL) {
		printf("Opening file '%s' successful.\n",TEST_FILE);
	} else {
		fprintf(stderr,"Error: Opening file '%s'.\n");
		return 1;
	}
		
	if(fprintf(fh,"%s\n",message)>=0) {
		printf("Writing to file '%s' successful.\n",TEST_FILE);
	} else {
		fprintf(stderr,"Error: Cannot write to file '%s': %s.\n",TEST_FILE,strerror(errno));
		return 2;	
	}
	
	fclose(fh);

	return 0;	
}
