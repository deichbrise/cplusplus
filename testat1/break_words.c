#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int c;

	while((c = getchar()) != EOF)
	{
		if(c == ' ')
		{
			putchar('\n');
		}
		else
		{
			putchar(c);
		}
	}

	return 0;
}
