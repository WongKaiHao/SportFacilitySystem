#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#pragma warning (disable:4996)
void addBookingTime();
void searchBookingTime();
void modifyBookingTime();
void displayBookingTime();
void deleteBookingTime();
void bookingMenu(int s);
int validationOfTime(int a, int b, int c, int d, int maxHour, int minHour, int maxMin, int minMin);
int validationOfDate(int e, int f, int g);

struct Time {
	int bHr1, bMin1, bHr2, bMin2;
};

typedef struct {
	int bDay, bMonth, bYear;
}Date;

typedef struct {
	char id[6], userId[11], facilityId[6];
	Date date;
	struct Time time;
}Booking;

int mainBooking()
{
	int option;
	printf("\t\t\t\tMenu\n");
	printf("\t\t\t\t----\n");
	printf("\t\t\t1.Add Booking Time\n");
	printf("\t\t\t2.Search Booking Time\n");
	printf("\t\t\t3.Modify Booking Time\n");
	printf("\t\t\t4.Display Booking Time\n");
	printf("\t\t\t5.Delete Booking Time\n");
	printf("\t\t\t6.Exit\n");
	printf("\t\t\t---------------------------\n");
	printf("\t\t\tSelect your option : ");
	scanf("%d", &option);
	rewind(stdin);

	bookingMenu(option);
	system("pause");
}

void addBookingTime()
{
	SYSTEMTIME t;
	Booking book;
	printf("\n\n");
	printf("\n-----------------------------------------------------------------------------\n");
	printf("Addition of Booking Time :\n");
	FILE *ptr;
	ptr = fopen("booking.dat", "ab");      //open file for append

	if (ptr == NULL)
	{
		printf("Error in opening booking.dat file.");
		exit(-1);
	}
	else
	{
		char add, exit;
		printf("Any booking time to be added? (Y=Yes) > ");    //Ask the user for confirmation
		rewind(stdin);
		scanf("%c", &add);
		while (toupper(add) == 'Y')       //If yes, process to the adding of booking time
		{
			GetLocalTime(&t);
			printf("\nToday's date -- %d/%d/%d", t.wDay, t.wMonth, t.wYear);

			printf("\nBooking ID            : ");
			rewind(stdin);
			scanf("%s", book.id);

			printf("User ID               : ");
			scanf("%s", book.userId);

			printf("Facility Id           : ");
			scanf("%s", book.facilityId);

			do {
				printf("\nBooking date -> Year  : ");
				rewind(stdin);
				scanf("%d", &book.date.bYear);

				printf("Booking date -> Month : ");
				rewind(stdin);
				scanf("%d", &book.date.bMonth);

				printf("Reminder : Booking day must be one day in advance.");
				printf("\nBooking date -> Day   : ");
				rewind(stdin);
				scanf("%d", &book.date.bDay);

			} while (!validationOfDate(book.date.bDay, book.date.bMonth, book.date.bYear));    //For validation of booking date, if data wrong, user is needed to key in again.

			if (book.date.bYear == t.wYear && book.date.bMonth == t.wMonth)   //If same year and same month
			{
				if (book.date.bDay <= t.wDay)   // If same day or smaller than current day, print error message
				{
					printf("\nInvalid date.\n");
					printf("You must book the sport facility at least one day at advance!\n");
					printf("\nDo you want to exit the addition of booking time? (Y = yes) > ");       // Ask user want to exit or not
					rewind(stdin);
					scanf("%c", &exit);

					if (toupper(exit) == 'Y')
					{
						printf("\nExit to main menu..");
						break;
					}
				}
				else if (book.date.bDay > t.wDay)      //If bigger than current day
				{
					do {
						printf("\nBooking time for the year %d.", t.wYear);
						printf("\nBooking time -> From (eg.00 00) 24-hour format : ");
						scanf("%d %d", &book.time.bHr1, &book.time.bMin1);

						printf("Booking time -> To   (eg.00 00) 24-hour format : ");
						scanf("%d %d", &book.time.bHr2, &book.time.bMin2);
					} while (!validationOfTime(book.time.bHr1, book.time.bHr2, book.time.bMin1, book.time.bMin2, 24, 0, 60, 0));  // For validation fo booking time, if data wrong, user is needed to key in again.

					fwrite(&book, sizeof(Booking), 1, ptr);            //write into binary file
					printf("\nAny booking time to add (Y=Yes) > ");
					rewind(stdin);
					scanf("%c", &add);
				}
			}
			else if (book.date.bYear == t.wYear && book.date.bMonth >= t.wMonth)      //If same year, different month
			{
				do {
					printf("\nBooking time for the year %d.", t.wYear);
					printf("\nBooking time -> From (eg.00 00) 24-hour format : ");
					scanf("%d %d", &book.time.bHr1, &book.time.bMin1);

					printf("Booking time -> To   (eg.00 00) 24-hour format : ");
					scanf("%d %d", &book.time.bHr2, &book.time.bMin2);
				} while (!validationOfTime(book.time.bHr1, book.time.bHr2, book.time.bMin1, book.time.bMin2, 24, 0, 60, 0));  // For validation fo booking time, if data wrong, user is needed to key in again.

				fwrite(&book, sizeof(Booking), 1, ptr);            //write into binary file
				printf("\nAny booking time to add (Y=Yes) > ");
				rewind(stdin);
				scanf("%c", &add);
			}

			else if (book.date.bYear > t.wYear)           //If different month
			{
				do {
					printf("\nBooking time for the year %d.", book.date.bYear);
					printf("\nBooking time -> From (eg.00 00) 24-hour format : ");
					scanf("%d %d", &book.time.bHr1, &book.time.bMin1);

					printf("Booking time -> To   (eg.00 00) 24-hour format : ");
					scanf("%d %d", &book.time.bHr2, &book.time.bMin2);
				} while (!validationOfTime(book.time.bHr1, book.time.bHr2, book.time.bMin1, book.time.bMin2, 24, 0, 60, 0));    // For validation fo booking time, if data wrong, user is needed to key in again.


				fwrite(&book, sizeof(Booking), 1, ptr);           //write into binary file
				printf("\nAny booking time to add (Y=Yes) > ");
				rewind(stdin);
				scanf("%c", &add);
			}
		}
	}
	fclose(ptr);
	printf("\n-----------------------------------------------------------------------------\n\n");
}

void searchBookingTime()
{
	int day, month, year, option;
	char yesNo, fId[6];
	Booking s[40];
	int i = 0, count = 0, foundNo = 0;
	printf("\n\n");
	printf("\n-----------------------------------------------------------------------------\n");
	printf("Search of the booking time : \n");
	FILE *ptr;
	ptr = fopen("booking.dat", "rb");             //Open file for reading into a new array structure
	while (fread(&s[i], sizeof(Booking), 1, ptr) != 0)
	{
		i++;                    //For counting the number of set of data in array structure
		count++;
	}
	fclose(ptr);

	printf("Do you want to search for booking time? (y=Yes) > ");
	rewind(stdin);
	scanf("%c", &yesNo);

	while (toupper(yesNo) == 'Y')
	{
		printf("\n\n1.Facility ID\n");             //Give user 2 option for searching
		printf("2.Date\n");
		printf("Which one do you want to seach? > ");
		rewind(stdin);
		scanf("%d", &option);

		if (option == 1)
		{
			printf("\nWhich facility id do you want to search > ");
			scanf("%s", fId);

			printf("\nThe date and time that are already booked : \n");
			printf("\nFacility ID \tBooking date \tBooking time ");
			printf("\n----------- \t------------ \t------------\n ");

			for (i = 0; i < count; i++)
			{
				if (strcmp(fId, s[i].facilityId) == 0)        //If the facility ID correct print details
				{
					printf("%-10s \t%02d-%02d-%d \t%02d:%02d to %02d:%02d\n ", s[i].facilityId, s[i].date.bDay, s[i].date.bMonth, s[i].date.bYear, s[i].time.bHr1, s[i].time.bMin1, s[i].time.bHr2, s[i].time.bMin2);
					foundNo++;
				}
			}
			printf("\n----------- \t------------ \t------------\n ");
		}
		else if (option == 2)
		{
			do {
				printf("\nWhich date do you want to search e.g (DD MM YYYY) > ");
				rewind(stdin);
				scanf("%d %d %d", &day, &month, &year);
			} while (!validationOfDate(day, month, year));

			printf("\nThe time that are already booked at this date : \n");
			printf("\nFacility ID \tBooking date \tBooking time ");
			printf("\n----------- \t------------ \t------------\n ");

			for (i = 0; i < count; i++)
			{
				if (day == s[i].date.bDay && month == s[i].date.bMonth && year == s[i].date.bYear)      //If the day and time correct print details
				{
					printf("%-10s \t%02d-%02d-%d \t%02d:%02d to %02d:%02d\n ", s[i].facilityId, s[i].date.bDay, s[i].date.bMonth, s[i].date.bYear, s[i].time.bHr1, s[i].time.bMin1, s[i].time.bHr2, s[i].time.bMin2);
					foundNo++;
				}
			}
			printf("\n----------- \t------------ \t------------\n ");
		}
		else              //IF user printf other than 1 and 2
		{
			printf("Invalid option.\n");
			continue;
		}

		if (foundNo == 0)             // If no record found, print this
		{
			printf("\nRecord not found.\n\n");
		}
		else              //If have record ,print this
			printf("\n%d reocrds found.\n", foundNo);

		foundNo = 0;               //reset the foundNo tp 0 for another searching to avoid error
		printf("\nAny sport facility you want to search? > ");          //For continuing searching
		rewind(stdin);
		scanf("%c", &yesNo);
		system("cls");
	}
	printf("\n-----------------------------------------------------------------------------\n\n");
}

void modifyBookingTime()
{
	char yesNo, confirm, bId[16], uId[11];
	int i = 0, count = 0, numOfModify = 0;
	Booking m[40];
	printf("\n\n");
	displayBookingTime();
	printf("\n-----------------------------------------------------------------------------\n");
	printf("Modification of the booking time : \n");
	FILE *ptr;
	ptr = fopen("booking.dat", "rb");           //Open file for reading into a new array structure
	while (fread(&m[i], sizeof(Booking), 1, ptr) != 0)
	{
		i++;                       //For counting the number of set of data in array structure
		count++;
	}
	fclose(ptr);

	printf("\nDo you want to modify the booking time? (Y=Yes) > ");
	rewind(stdin);
	scanf("%c", &yesNo);

	while (toupper(yesNo) == 'Y')
	{
		printf("Please enter your User ID : ");
		scanf("%s", uId);

		printf("Please enter your Booking ID for modification : ");
		scanf("%s", bId);

		for (i = 0; i < count; i++)
		{
			if (strcmp(bId, m[i].id) == 0 && strcmp(uId, m[i].userId) == 0)            //If the User Id and Booking Id correct print this
			{
				printf("\nYour Booking ID  : %s\n", m[i].id);
				printf("Facility ID      : %s\n", m[i].facilityId);
				printf("Booking date     : %d-%d-%d\n", m[i].date.bDay, m[i].date.bMonth, m[i].date.bYear);
				printf("Booking time     : %02d:%02d to %02d:%02d\n", m[i].time.bHr1, m[i].time.bMin1, m[i].time.bHr2, m[i].time.bMin2);

				do {
					printf("\nModify to ... \n");
					printf("Booking date -> Day   : ");
					scanf("%d", &m[i].date.bDay);
					printf("Booking date -> Month : ");
					scanf("%d", &m[i].date.bMonth);
					printf("Booking date -> Year  : ");
					scanf("%d", &m[i].date.bYear);
				} while (!validationOfDate(m[i].date.bDay, m[i].date.bMonth, m[i].date.bYear));         //For validation of booking date, if data wrong, user is needed to key in again.

				do {
					printf("\nBooking time -> From : e.g (00 00) 24-hour format : ");
					scanf("%d %d", &m[i].time.bHr1, &m[i].time.bMin1);
					printf("             -> To   : e.g (00 00) 24-hour format : ");
					scanf("%d %d", &m[i].time.bHr2, &m[i].time.bMin2);
				} while (!validationOfTime(m[i].time.bHr1, m[i].time.bHr2, m[i].time.bMin1, m[i].time.bMin2, 24, 0, 60, 0));          // For validation fo booking time, if data wrong, user is needed to key in again.

				printf("\nSure to modify? (Y=Yes) > ");         //Ask user for confirmation
				rewind(stdin);
				scanf("%c", &confirm);

				if (toupper(confirm) == 'Y')           //If confirm to modify
				{
					printf("\nYour Booking ID           : %s\n", m[i].id);
					printf("Facility                  : %s\n", m[i].facilityId);
					printf("Booking date modified : %d-%d-%d\n", m[i].date.bDay, m[i].date.bMonth, m[i].date.bYear);
					printf("Booking time modified : %02d:%02d to %02d:%02d\n", m[i].time.bHr1, m[i].time.bMin1, m[i].time.bHr2, m[i].time.bMin2);
					numOfModify++;

					ptr = fopen("booking.dat", "wb");         //Open file for rewrite the data

					if (ptr == NULL)
					{
						printf("Unable to open file.\n");
					}
					else
					{
						for (i = 0; i < count; i++)
						{
							fwrite(&m[i], sizeof(Booking), 1, ptr);
						}
					}
					printf("\nModify done.\n");
					fclose(ptr);
				}
				else             //If dont want to modfy
				{
					ptr = fopen("booking.dat", "rb");           //read the original file for cancelling

					if (ptr == NULL)
					{
						printf("Unable to open file.\n");
					}
					else
					{
						for (i = 0; i < count; i++)
						{
							fread(&m[i], sizeof(Booking), 1, ptr);
						}
					}
					fclose(ptr);
					printf("\nModification Cancelled.\n");
					break;
				}
			}
		}
		printf("\nNumber of modified : %d\n", numOfModify);
		printf("\nDo you want to continue the modification of booking time? (Y=Yes) > ");      //Ask user for continue or not
		rewind(stdin);
		scanf("%c", &yesNo);
	}
	printf("\n-----------------------------------------------------------------------------\n\n");
}

void displayBookingTime()
{
	int totalNo = 0;
	SYSTEMTIME t;
	Booking book;
	GetLocalTime(&t);
	printf("\n\n");
	printf("\n-----------------------------------------------------------------------------\n");
	printf("List of the booking time : \n");
	GetLocalTime(&t);
	FILE *ptr;
	ptr = fopen("booking.dat", "rb");          //open the binary file for reading data
	printf("\nToday's date -- %d/%d/%d", t.wDay, t.wMonth, t.wYear);
	printf("\nBooking ID \t User ID \tFacility ID \tBooking date \tBooking time ");
	printf("\n---------- \t--------- \t----------- \t------------ \t------------\n ");
	while (fread(&book, sizeof(Booking), 1, ptr) != 0)            //display the data 
	{
		printf("%-10s \t%-10s \t%-10s \t%02d-%02d-%d \t%02d:%02d to %02d:%02d\n ", book.id, book.userId, book.facilityId, book.date.bDay, book.date.bMonth, book.date.bYear, book.time.bHr1, book.time.bMin1, book.time.bHr2, book.time.bMin2);
		totalNo++;
	}
	printf("\n---------- \t--------- \t----------- \t------------ \t------------\n ");
	printf("Total Number of Booking Times : %d \n", totalNo);             //display total number of data
	printf("\n-----------------------------------------------------------------------------\n\n");
	fclose(ptr);
}

void deleteBookingTime()
{
	char confirm, yesNo, bookId[16], userId[16];
	int i = 0, count = 0, numOfDelete = 0, foundNo = 0;
	Booking d[40];
	printf("\n\n");
	displayBookingTime();
	printf("\n-----------------------------------------------------------------------------\n");
	printf("Delete of the booking time : \n");
	FILE *ptr;
	ptr = fopen("booking.dat", "rb");           //Open file for reading into a new array structure
	while (fread(&d[i], sizeof(Booking), 1, ptr) != 0)
	{
		i++;                       //For counting the number of set of data in array structure
		count++;
	}
	fclose(ptr);

	printf("\nDo you want to delete the booking time? (y=Yes) : ");
	rewind(stdin);
	scanf("%c", &yesNo);

	while (toupper(yesNo) == 'Y')
	{
		printf("\nPlease enter your User ID : ");
		scanf("%s", userId);
		printf("Please enter your Booking ID : ");
		scanf("%s", bookId);

		for (i = 0; i < count; i++)
		{
			if (strcmp(bookId, d[i].id) == 0 && strcmp(userId, d[i].userId) == 0)         //If the booking id and user id is correct
			{
				printf("\nYour Booking ID  : %s\n", d[i].id);
				printf("Facility ID      : %s\n", d[i].facilityId);
				printf("Booking date     : %d-%d-%d\n", d[i].date.bDay, d[i].date.bMonth, d[i].date.bYear);
				printf("Booking time     : %02d:%02d to %02d:%02d\n", d[i].time.bHr1, d[i].time.bMin1, d[i].time.bHr2, d[i].time.bMin2);
				foundNo++;

				printf("\nAre you sure you want to delete this booking time? (y=Yes) : ");          //Ask user for confirmation
				rewind(stdin);
				scanf("%c", &confirm);

				if (toupper(confirm) == 'Y')        //If confirm
				{
					ptr = fopen("booking.dat", "wb");
					if (ptr == NULL)
					{
						printf("Unable to open file.\n");
					}
					else
					{
						for (int j = i; j < count - 1; j++)        //Deleting process
						{
							d[j] = d[j + 1];
						}
						count--;
					}

					for (i = 0; i < count; i++)           //open file for rewriting the new data
					{
						fwrite(&d[i], sizeof(Booking), 1, ptr);
					}
					fclose(ptr);
					numOfDelete++;
					printf("\nDelete complete.\n");
				}
				else
				{
					ptr = fopen("booking.dat", "rb");      //Open file for reading the original file for cancelling
					if (ptr == NULL)
					{
						printf("Unable to open file.\n");
					}
					else
					{
						for (i = 0; i < count; i++)
						{
							fread(&d[i], sizeof(Booking), 1, ptr);
						}
					}
					fclose(ptr);
					printf("\nDeleting Cancelled.\n");
					break;
				}
			}
		}

		if (foundNo == 0)
		{
			printf("\nNo records found.\n");
		}
		printf("Total number of deleting : %d", numOfDelete);
		printf("\nContinue to delete another booking time? (y=Yes) : ");      //Ask user for further deleting or not
		rewind(stdin);
		scanf("%c", &yesNo);
	}

}



int validationOfTime(int hour1, int hour2, int min1, int min2, int maxHour, int minHour, int maxMin, int minMin)   //Let user to key in the logic and correct data
{
	if (hour1 < minHour || hour1 > maxHour || min1 < minMin || min1 >= maxMin || hour1 == hour2)
	{
		printf("\nInvalid time.\n");     //If the data achieve these wrong statement, invalid message will be printed.
		return 0;
	}
	else if (hour2 < minHour || hour2 > maxHour || min2 < minMin || min2 >= maxMin || hour1 == hour2)
	{
		printf("\nInvalid time.\n");
		return 0;   //return 0 is for wrong statement.
	}
	else if (hour2 < hour1)
	{
		printf("\nInvalid time\n");
		return 0;
	}
	else
		return 1;   //return 1 is for true statement.
}

int validationOfDate(int day, int month, int year)             //Let user to key in the logic and correct data
{
	SYSTEMTIME t;
	GetLocalTime(&t);

	if (year < t.wYear)     //Validation for year
	{
		printf("Invalid year.\n");   //If the data achieve these wrong statement, invalid message will be printed.
		return 0;            //return 0 is for wrong statement.
	}

	if (month < 1 || month > 12)       //Validation for month
	{
		printf("Invalid month.\n");
		return 0;
	}

	if (month == 2)     //For month 2
	{
		if (year % 4 != 0)
		{
			if (day > 28 || day < 1)      //validation for day
			{
				printf("\nInvalid day based on the month and year.\n");
				return 0;
			}
			else return 1;         //return 1 is for true statement.

		}
		else if (year % 4 == 0)
		{
			if (day > 29 || day < 1)
			{
				{
					printf("\nInvalid day based on the month and year.\n");
					return 0;
				}
			}
			else
				return 1;
		}
	}

	if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)     //validation for day
	{
		if (day > 31 || day < 1)
		{
			printf("\nInvalid day based on the month.\n");
			return 0;
		}
		else
			return 1;

	}
	else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day > 30 || day < 1)
		{
			printf("\nInvalid day based on the month.\n");
			return 0;
		}
		else
			return 1;
	}
}

void bookingMenu(int selection)
{
	do {
		if (selection == 1)
		{
			system("cls");
			addBookingTime();
		}
		else if (selection == 2)
		{
			system("cls");
			searchBookingTime();
		}
		else if (selection == 3)
		{
			system("cls");
			modifyBookingTime();
		}
		else if (selection == 4)
		{
			system("cls");
			displayBookingTime();
		}
		else if (selection == 5)
		{
			system("cls");
			deleteBookingTime();
		}
		else if (selection == 6)
		{
			printf("Exit.\n");
			system("cls");
		}
		else
			printf("Invalid input.\n");

		printf("\n\n1.Add Booking Time\n");
		printf("2.Search Booking Time\n");
		printf("3.Modify Booking Time\n");
		printf("4.Display Booking Time\n");
		printf("5.Delete Booking Time\n");
		printf("6.Exit\n");
		printf("---------------------------\n");
		printf("Any further selection? > ");
		scanf("%d", &selection);
	} while (selection != 6);
}

