#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void calculateDateOfEastern(int year, char* buffer, int size)
{
    int goldenYear = (year % 19) + 1;
    int century = (year / 100) + 1;
    int skippedLeapYears = (3 * century / 4) - 12;
    int moonOrbitCorrectionFactor = ((8 * century + 5) / 25) - 5;
    int weekDay = (5 * year / 4) - skippedLeapYears - 10;
    int epact = (11 * goldenYear + 20 + moonOrbitCorrectionFactor - skippedLeapYears) % 30;
    if( (epact == 25 && goldenYear > 11) || epact == 24)
    {
        epact++;
    }

    int dayInTwoMonthPeriod = 44 - epact;
    if(dayInTwoMonthPeriod < 21)
    {
        dayInTwoMonthPeriod = dayInTwoMonthPeriod + 30;
    }
    dayInTwoMonthPeriod = dayInTwoMonthPeriod + 7 - ((weekDay + dayInTwoMonthPeriod) % 7);

    int finalDay = 0;
    char finalMonthBuffer[1024];
    if(dayInTwoMonthPeriod > 31)
    {
        finalDay = dayInTwoMonthPeriod - 31;
        strncpy(finalMonthBuffer, "April", sizeof(finalMonthBuffer));
    }
    else
    {
        finalDay = dayInTwoMonthPeriod;
        strncpy(finalMonthBuffer, "March", sizeof(finalMonthBuffer));
    }

    snprintf(buffer, size, "%s %d", finalMonthBuffer, finalDay);
    buffer[size - 1] = '\0';
}

void assertYear(int year, char* result)
{
    char buffer[1024];

    calculateDateOfEastern(year, buffer, sizeof(buffer));

    if(strcmp(buffer, result) != 0)
    {
        printf("Year: %d, Expected: %s, Actual: %s", year, result, buffer);
        exit(EXIT_FAILURE);
    }

}

void testCalculateDateOfEastern(void)
{

    assertYear(1994, "April 3");
    assertYear(1995, "April 16");
    assertYear(1998, "April 12");
}

int main(void)
{
    testCalculateDateOfEastern();

    char buffer[1024];
    while(scanf("%s", buffer) != EOF)
    {
        char resultBuffer[1024];
        int year = atoi(buffer);

        calculateDateOfEastern(year, resultBuffer, sizeof(resultBuffer));

        printf("%d - %s \n", year, resultBuffer);
    }
}

