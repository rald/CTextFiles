#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#define TEST_FILE "database2.txt"
#define TEMP_FILE "database3.txt"

int main(void)
{
	time_t timestamp = time(NULL);
	struct tm *now = localtime(&timestamp);

	FILE *fin = NULL;
	FILE *fout = NULL;

	char *line = NULL;
	int llen = 0;
	int rlen = 0;

	int line_rem = 0;
	int line_num = 0;
	bool removed = false;

	printf("Enter line number to remove: ");
	scanf("%d", &line_rem);

	if ((fin = fopen(TEST_FILE, "rt")) != NULL)
	{
		printf("Opening file '%s' successful.\n", TEST_FILE);
	}
	else
	{
		fprintf(stderr, "Error: Cannot open file '%s': %s\n", TEST_FILE, strerror(errno));
		return 1;
	}

	if ((fout = fopen(TEMP_FILE, "wt")) != NULL)
	{
		printf("Opening file '%s' successful.\n", TEMP_FILE);
	}
	else
	{
		fprintf(stderr, "Error: Cannot open file '%s': %s\n", TEMP_FILE, strerror(errno));
		return 2;
	}

	printf("Copying file '%s' to file '%s'.\n", TEST_FILE, TEMP_FILE);
	while ((rlen = getline(&line, &llen, fin)) != -1)
	{
		line_num++;
		if (line_rem != line_num)
		{
			fprintf(fout, "%s", line);
		}
		else
		{
			printf("Excluding line %d.\n", line_rem);
			removed = true;
		}
	}

	if (errno != 0)
	{
		printf("Finished copying.\n");
	}
	else
	{
		fprintf(stderr, "Error: Copying '%s' to '%s': %s\n", strerror(errno));
		return 3;
	}

	if (remove(TEST_FILE) == 0)
	{
		printf("File '%s' successfully deleted.\n", TEST_FILE);
	}
	else
	{
		fprintf(stderr, "Error: Cannot delete file '%s': %s\n", TEST_FILE, strerror(errno));
		return 4;
	}

	if (rename(TEMP_FILE, TEST_FILE) == 0)
	{
		printf("File '%s' successfully renamed to '%s'.\n", TEMP_FILE, TEST_FILE);
	}
	else
	{
		fprintf(stderr, "Error: Cannot rename file '%s' to '%s': %s\n", TEMP_FILE, TEST_FILE, strerror(errno));
		return 5;
	}

	if (removed)
	{
		printf("Line %d successfully removed from file '%s'.\n", line_rem, TEST_FILE);
	}
	else
	{
		printf("Error: Cannot removed line %d from file %s.\n", line_rem, TEST_FILE);
	}

	fclose(fout);
	fclose(fin);

	return 0;
}
