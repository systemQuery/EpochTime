#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdbool.h>

void to_conversion(char *);

unsigned int to_date(int date)
{
	if (date >= 1 && date <= 31)
	{
		unsigned int date_to_seconds = date * 86400;
		return date_to_seconds;
	}
	else
	{
		printf("Invalid date");
	}
}

unsigned int to_month(int month, bool leap)
{
	unsigned int month_to_seconds=0;
	for (int i = month; i >= 1; i--)
	{
		if (i == 01 || i == 03 || i == 05 || i == 07 || i == 10 || i == 12 || i == 8)
		{
			month_to_seconds = month_to_seconds + to_date(31);
		}
		else if (i == 04 || i == 06 || i == 9 || i == 11)
		{
			month_to_seconds = month_to_seconds + to_date(30);	
		}
		else if (i == 02 && leap==false)
		{
			month_to_seconds = month_to_seconds + to_date(28);
		}
		else if (i == 2 && leap == true)
		{
			month_to_seconds = month_to_seconds + to_date(29);
		}
		else
		{
			printf("Invalid Month");
			return;
		}
	}
	return month_to_seconds;
}

bool leapYear(int year)
{
	if (year % 100 == 0)
	{
		if (year % 400 == 0)
		{
			return true;
		}
		else
			return false;
	}
	else
	{
		if (year % 4 == 0)
			return true;
		else
			return false;
	}
}

unsigned int convert_into_seconds(int years,int months, int dates)
{
	unsigned int total = 0;
	bool checkLeap, lastYearBool, nonLeap;
	int countLeap = 0, notLeap=0;
	unsigned int remain_month = 0;
	nonLeap = leapYear(years);

		if(((months == 01 || months == 03 || months == 05 || months == 07 || months == 10 || months == 12 || months == 8) && (dates<=31)) || ((months == 04 || months == 06 || months == 9 || months == 11) && (dates<=30)) ||(months==2 && dates<=29) )
		{
			for (int i = 1970; i < years; i++)
			{
				checkLeap = leapYear(i);
				if (checkLeap)
				{
					countLeap++;
				}
				else
				{
					notLeap++;
				}
			}

			unsigned int totalNotLeapSec = per_year_to_seconds(notLeap);
			
			unsigned int totalLeapSec = per_year_to_seconds(countLeap) + countLeap * 86400;

			lastYearBool = leapYear(years);
			if (lastYearBool)
			{
				remain_month = to_month(months-1, lastYearBool); 
				remain_month += to_date(dates);
			}
			else
			{
				remain_month = to_month(months-1, lastYearBool);
				remain_month += to_date(dates);
			}

			total = totalNotLeapSec + totalLeapSec + remain_month;
			printf("\nTIME AFTER CONVERTING THE DATE INTO EPOCH TIME IS %d SECONDS\n", total-1);
		}
		else
		{
			printf("Invalid date entered OR Invalid date format\n");
		}
	
	return total;
}

unsigned int per_year_to_seconds(int notLeap)
{
	unsigned int noLeap = 18748800 + 10368000 + 2419200;
	unsigned int totalSec = noLeap * notLeap;
	return totalSec;
}

void to_conversion(char *dateArray)
{
	char date_array[2]="";
	char mon_array[2]=""; 
	char year_array[4]="";
	int j=0;
	bool checkBool;

	unsigned int sum = 0;
	unsigned int onlyOneYear;

	int int_date = 0;
	int int_mon = 0;
	int int_year = 0;

	bool leap_or_not = false;

		if (dateArray[2] == '/' && dateArray[5]=='/' || dateArray[2] == '-' && dateArray[5] == '-' || dateArray[2] == '.' && dateArray[5] == '.')
		{
			
			for (int i = 0,j=0; i < 2; i++,j++)
			{
				date_array[j] = dateArray[i];
			}
			int_date = atoi(date_array);
			
			for (int k = 3,j=0; k < 5; k++,j++)
			{
				mon_array[j] = dateArray[k];
			}
			int_mon = atoi(mon_array);

			for (int a = 6,j=0; a < 10; a++,j++)
			{
				year_array[j] = dateArray[a];
			}
			int_year = atoi(year_array); 

		}

		checkBool = leapYear(int_year);

		if (int_year == 1970)
		{
			onlyOneYear = to_month(int_mon-1, false);
			onlyOneYear += to_date(int_date);
		}
		else if (int_year > 1970 && int_year < 2038)
		{
			if (!checkBool && int_mon == 2 && int_date == 29)
			{
				printf(" %d year is not Leap year",int_year);
			}
			else
			{
				sum = convert_into_seconds(int_year, int_mon, int_date);
			}
		}
		else {
			printf("Invalid Data OR Epoch time starts from 1970 and it will last only till 2037");
		}
}

int main()
{
	printf("\t\t=======THESE ARE THE GIVEN DATE FORMATS FOR CONVERTING A PARTICULAR DATE TO EPOCH TIME========\n");
	printf("\n1. dd/mm/yyyy\n2. dd-mm-yyyy\n3. dd.mm.yyyy\n\n");

	char epochDate[11];

	printf("Enter the date from 1 January 1970 onwards to :\n");
	scanf("%s", epochDate);

	to_conversion(epochDate);
	//free(epochDate);

	return 0;
}