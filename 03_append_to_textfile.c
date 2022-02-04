#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TEST_FILE "database2.txt"

char *escape(char *buffer);

int main(void)
{
	char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

	char *weeks[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

	time_t timestamp = time(NULL);
	struct tm *now = localtime(&timestamp);

	FILE *fh = NULL;

	char *message = NULL;
	int llen = 0;

	char *p = NULL;

	char *escmsg = NULL;

	printf("Enter message: ");
	getline(&message, &llen, stdin);

	p = strchr(message, '\n');
	if (p != NULL)
		*p = '\0';

	escmsg = escape(message);

	if ((fh = fopen(TEST_FILE, "at")) != NULL)
	{
		printf("Opening file '%s' successful.\n", TEST_FILE);
	}
	else
	{
		fprintf(stderr, "Error: Cannot open file '%s'.\n");
		return 1;
	}

	if (fprintf(fh, "\"%s.,%s.%d,%d-%2d:%02d:%02d\",\"%s\"\n",
				weeks[now->tm_wday],
				months[now->tm_mon],
				now->tm_mday,
				now->tm_year + 1900,
				now->tm_hour,
				now->tm_min,
				now->tm_sec,
				escmsg) >= 0)
	{
		printf("Appending to file '%s' successful.\n", TEST_FILE);
	}
	else
	{
		fprintf(stderr, "Error: Cannot append to file '%s'.\n", TEST_FILE);
		return 1;
	}

	free(escmsg);
	escmsg = NULL;

	fclose(fh);

	return 0;
}

char *escape(char *buffer)
{
	int i, j;
	int l = strlen(buffer) + 1;
	char esc_char[] = {'\a', '\b', '\f', '\n', '\r', '\t', '\v', '\\', '"'};
	char esc_str[] = {'a', 'b', 'f', 'n', 'r', 't', 'v', '\\', '"'};
	char *dest = (char *)calloc(l * 2, sizeof(char));
	char *ptr = dest;
	for (i = 0; i < l; i++)
	{
		for (j = 0; j < 9; j++)
		{
			if (buffer[i] == esc_char[j])
			{
				*ptr++ = '\\';
				*ptr++ = esc_str[j];
				break;
			}
		}
		if (j == 9)
			*ptr++ = buffer[i];
	}
	*ptr = '\0';
	return dest;
}
