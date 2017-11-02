#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

/*
 * @brief determine if the char is in range 0 until 9 hence a valid digit
 * @param c the char to be checked
 * @return 1 if is valid digit, else 0
 */
int isDigit(char c)
{
	return c >= '0' && c <= '9';
}

/*
 * @brief determine if char is whitespace or not
 * @param c the char to be checked
 */
int isWhitespace(char c)
{
	return c == ' ';
}

void postprocessBuffer(char buffer[])
{
	buffer[strlen(buffer) - 1] = '\0';
}

void resetBuffer(char buffer[])
{
	memset(buffer, 0, sizeof(&buffer));
}

void logResult(char line[], int sum, int numbers)
{
	float avg = sum / (float) numbers;
	printf("Line: %s, Average: %f \n", line, avg);
}

int processLine(char line[])
{
	char number_buffer[BUFFER_SIZE];
	int k = 0;
	int sum = 0;
	int numbers = 0;

	for (int i = 0; i < strlen(line); i++)
	{
		char c = line[i];

		if (isDigit(c) == 1) {
			number_buffer[k] = c;
			k++;
		}
		/*
		 * If char is not digit, nor whitespace nor last char the char is not valid
		 * hence the average is not computable.
		 * */
		else if (isWhitespace(c) != 1)
		{
			return 1;
		}

		if (isWhitespace(c) == 1 || i == strlen(line) - 1)
		{
			sum = sum + atoi(number_buffer);
			numbers++;
			k = 0;
			resetBuffer(number_buffer);
		}

	}

	logResult(line, sum, numbers);

	return 0;
}

void assertArgs(int args, char* argv[])
{
	if (args != 2)
	{
		printf("Usage: line_mean filename");
		exit(1);
	}
}

void execute(int args, char* argv[])
{
	FILE* file = NULL;
	char buffer[BUFFER_SIZE];

	file = fopen(argv[1], "r");

	if (file == NULL)
	{
		printf("Cannot read file");
		exit(1);
	}

	while (fgets(buffer, sizeof(buffer), file) != NULL)
	{
		postprocessBuffer(buffer);

		/* If return value equals 1, line does not contains only numbers. */
		if(processLine(buffer) == 1)
		{
			printf("Cannot calculate average of line %s \n", buffer);
		}
	}

	fclose(file);
}

int main(int args, char* argv[])
{
	assertArgs(args, argv);
	execute(args, argv);
	return 0;
}
