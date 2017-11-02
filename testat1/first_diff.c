#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

int main(int args, char* argv[])
{

	if(args != 3)
	{
		printf("Usage: first_diff file1 file2");
		return 1;
	}

	FILE *file1;
	FILE *file2;

	/*
	 * Maybe there is a better way of sizing the buffer because line greater than 1024 chars are truncated.
	 * For now it is sufficient for solving this task.
	 * */
	char buffer1[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];

	file1 = fopen(argv[1], "r");
	file2 = fopen(argv[2], "r");

	if(file1 == NULL || file2 == NULL)
	{
		printf("Cannot read files.");
		return 1;
	}

	int lineCount = 1;

	while(fgets(buffer1, sizeof(buffer1), file1) != NULL && fgets(buffer2, sizeof(buffer2), file2) != NULL)
	{
		/* Simply replace the newline character */
		buffer1[strlen(buffer1) - 1] = '\0';
		buffer2[strlen(buffer2) - 1] = '\0';

        if(strcmp(buffer1, buffer2) != 0)
		{
			printf("Line %i are not equal: %s != %s \n", lineCount, buffer1, buffer2);
		}

		lineCount++;
	}

	/* Do not forget to close files. */
	fclose(file1);
	fclose(file2);

	return 0;
}
