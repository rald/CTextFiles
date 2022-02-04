#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>

#define TEST_FILE "database.txt"
#define MESSAGE_MAX 256

int main(void)
{
	FILE *fh = NULL;

	char message[MESSAGE_MAX];

	if ((fh = fopen(TEST_FILE, "rt")) != NULL)
	{
		printf("Opening file '%s' successful.\n", TEST_FILE);
	}
	else
	{
		fprintf(stderr, "Error: Cannot open file '%s': %s\n", TEST_FILE, strerror(errno));
		return 1;
	}

	if (fscanf(fh, "%255[^\n]\n", message) == 1)
	{
		printf("Reading from file '%s' successful.\n", TEST_FILE);
		printf("Message: '%s'\n", message);
	}
	else
	{
		fprintf(stderr, "Error: Cannot read from file '%s': %s\n", TEST_FILE, strerror(errno));
		return 2;
	}

	fclose(fh);

	return 0;
}