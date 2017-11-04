#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 1024

void checkFile(FILE* file)
{
	if(file == NULL)
	{
		printf("cannot read file.");
		exit(1);
	}
}

void checkArgs(int args, char* argv[])
{
	if(args != 3)
	{
		printf("Usage: first_diff file1 file2");
		exit(1);
	}
}

void checkLine(char line1[], char line2[], int lineNumber)
{
	/* Simply replace the newline character */
	line1[strlen(line1) - 1] = '\0';
	line2[strlen(line2) - 1] = '\0';

	if(strcmp(line1, line2) != 0)
	{
		printf("Line %i is not equal: %s != %s \n", lineNumber, line1, line2);
	}
}

void execute(char path1[], char path2[])
{

	FILE* file1;
	FILE* file2;

	/*
	 * Maybe there is a better way of sizing the buffer because line greater than 1024 chars are truncated.
	 * For now it is sufficient for solving this task.
	 * */
	char buffer1[BUFFER_SIZE];
	char buffer2[BUFFER_SIZE];

	file1 = fopen(path1, "r");
	file2 = fopen(path2, "r");

	checkFile(file1);
	checkFile(file2);

	int lineCount = 1;


	while(fgets(buffer1, sizeof(buffer1), file1) != NULL && fgets(buffer2, sizeof(buffer2), file2) != NULL)
	{
		checkLine(buffer1, buffer2, lineCount);
		lineCount++;
	}

	/* Do not forget to close files. */
	fclose(file1);
	fclose(file2);
}

int main(int args, char* argv[])
{
	// Check args for validity
	checkArgs(args, argv);

	// Execute main process
	execute(argv[1], argv[2]);
	return 0;
}
