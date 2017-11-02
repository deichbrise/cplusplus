#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int args, char* argv[])
{

	if(args != 3)
	{
		printf("Usage: first_diff file1 file2");
		return 1;
	}

	FILE *file1;
	FILE *file2;

	char *line1 = NULL;
	size_t len1 = 0;
	ssize_t read1;

	char *line2 = NULL;
	size_t len2 = 0;
	ssize_t read2;

	file1 = fopen(argv[1], "r");
	file2 = fopen(argv[2], "r");

	if(file1 == NULL || file2 == NULL)
	{
		printf("Cannot read files.");
		return 1;
	}

	int lineCount = 1;

	while((read1 = getline(&line1, &len1, file1)) != -1 && (read2 = getline(&line2, &len2, file2)) != -1)
	{
        if(strcmp(line1, line2) != 0)
		{
			printf("Line %i are not equal: %s != %s \n", lineCount, line1, line2);
		}

		lineCount++;
	}

	fclose(file1);
	fclose(file2);

	return 0;
}
