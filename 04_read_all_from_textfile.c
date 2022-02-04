#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define TEST_FILE "database2.txt"

int main(void)
{
	time_t timestamp = time(NULL);
	struct tm *now = localtime(&timestamp);

	FILE *fh = NULL;

	char *line = NULL;
	int llen = 0;
	int rlen = 0;

	int line_num = 0;

	if ((fh = fopen(TEST_FILE, "rt")) != NULL)
	{
		printf("Opening file '%s' successful.\n", TEST_FILE);
	}
	else
	{
		fprintf(stderr, "Error: Cannot Open file '%s': %s.\n", TEST_FILE, strerror(errno));
		return 1;
	}

	printf("Reading from file '%s'.\n", TEST_FILE);
	while ((rlen = getline(&line, &llen, fh)) != -1)
	{
		if (line_num == 0)
		{
			printf("Line#  Message\n");
		}

		line_num++;
		printf("%04d: %s", line_num, line);
	}

	if (errno != 0)
	{
		if (line_num == 0)
		{
			printf("File '%s' is empty.\n", TEST_FILE);
		}
		else
		{
			printf("Finished reading.\n");
		}
	}
	else
	{
		fprintf("Error: Cannot read from file '%s': %s\n", strerror(errno));
		return 2;
	}

	fclose(fh);

	return 0;
}
