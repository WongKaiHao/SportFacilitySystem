#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#pragma warning(disable:4996)

void addFacilityUsage();
void searchFacilityUsage();
void displayFacilityUsage();
void modifyFacilityUsage();
//void deleteFacilityUsage();

typedef struct
{
	int days;
	int month;
	int year;

}date;
typedef struct
{
	int hour;
	int minutes;
}timed;

typedef struct
{
	char id[30];
	char fid[20], usagetype[20], purpose[30];
	date dated;
	timed time;
}user;

int mainFaciUsa()
{
	int option;
	do {
		system("CLS");
		printf("+++++++++++++++++++++ \n");
		printf("Facility Usage Module \n");
		printf("1.Add file\n");
		printf("2.Search file\n");
		printf("3.Modify file\n");
		printf("4.Display file\n");
		printf("5.Exit\n");
		printf("Choose your choice: ");
		scanf("%d", &option);
		rewind(stdin);

		if (option == 1)
		{
			addFacilityUsage();
		}
		else if (option == 2)
		{
			searchFacilityUsage();
		}
		else if (option == 3)
		{
			modifyFacilityUsage();
		}
		else if (option == 4)
		{
			displayFacilityUsage();
		}
		else if (option == 5)
		{
			exit(-1);
		}
		else
		{
			printf("Error input!\n");
			system("pause");
			main();
		}
		system("pause");
	} while (option != 5);
}

void addFacilityUsage()
{
	system("CLS");
	char confirm;
	int i = 0, recordCount = 0;
	FILE *fp;
	user b[20];
	char Next;
	fp = fopen("facilityUsage.txt", "a");

	if (fp == NULL)
	{
		printf("FIle not Found\n");
		system("pause");
		exit(-1);
	}

	do {
		user b[20];
		time_t t;
		time(&t);
		printf("\n(date and time): %s", ctime(&t));
		printf("Enter today's date(day /month/year):\n");
		rewind(stdin);
		scanf("%d %d %d", &b[i].dated.days, &b[i].dated.month, &b[i].dated.year);
		printf("Enter TODAYS TIME(hour-minutes-24hours):\n");
		rewind(stdin);
		scanf("%d %d", &b[i].time.hour, &b[i].time.minutes);
		printf("Enter User ID :\n");
		rewind(stdin);
		scanf("%[^\n]", &b[i].id);
		printf("Enter facility ID:\n");
		rewind(stdin);
		scanf("%[^\n]", &b[i].fid);
		rewind(stdin);
		printf("Enter Usage type:\n");
		rewind(stdin);
		scanf("%[^\n]", &b[i].usagetype);
		rewind(stdin);
		printf("Enter booking purpose:\n");
		scanf("%[^\n]", &b[i].purpose);
		fprintf(fp, "|%d|%d|%d|%d|%d|%s|%s|%s|%s|\n", b[i].dated.days, b[i].dated.month, b[i].dated.year, b[i].time.hour, b[i].time.minutes, b[i].id, &b[i].fid, b[i].usagetype, b[i].purpose);
		printf("Recorded sucessfully\n");
		printf("Next(Y/N)");
		rewind(stdin);
		scanf("%c", &Next);
	} while (toupper(Next) == 'Y');
	fclose(fp);
	return main();

}

void searchFacilityUsage()
{
	FILE*fptr;
	user f[20];
	char searchID[20];
	int i, n = 0, count = 0;
	fptr = fopen("facilityUsage.txt", "r");
	if (fptr == NULL)
	{
		printf("File error");
		exit(-1);
	}
	while (fscanf(fptr, "%[^|]|", f[n].fid) != EOF)
	{
		fscanf(fptr, "%s", f[n].id);
		fscanf(fptr, "%s", f[n].fid);
		fscanf(fptr, "%s", f[n].usagetype);
		fscanf(fptr, "%s", &f[n].purpose);
		n++;
	}
	fclose(fptr);

	printf("Enter your searchID :");
	rewind(stdin);
	scanf("%s", &searchID);


	for (i = 0; i < n; i++)
	{
		if (strcmp(searchID, f[i].fid) == 0)
		{
			printf("User ID                        :%s\n", f[i].id);
			printf("facility ID                    :%s\n", f[i].fid);
			printf("Usage type                     :%s\n", f[i].usagetype);
			printf("Booking purpose                :%s\n", f[i].purpose);
			count++;
		}
	}

	printf("         %d  Record found .\n", count);
	printf("-----------------------------------------------------------------------------------------\n");
	printf("\n");

	system("pause");

}



void displayFacilityUsage()
{
	FILE *display;
	FILE *display2;
	user b;
	char ch;
	int totalrecord = 0;
	display = fopen("facilityUsage.txt", "r");


	if (display == NULL)
	{
		printf("FIle not Found\n");
		system("pause");
		exit(-1);
	}
	while (fread(&b, sizeof(user), 1, display) != 0)
	{
		printf("Today's date(d-month-year)     :%d%d%d\n", b.dated.days, b.dated.month, b.dated.year);
		printf("TODAYS TIME(hour-minutes-am/pm):%d%d\n", b.time.hour, b.time.minutes);
		printf("User ID                        :%s\n", b.id);
		printf("facility ID                    :%s\n", b.fid);
		printf("Usage type                     :%s\n", b.usagetype);
		printf("Booking purpose                :%s\n", b.purpose);
		totalrecord++;
	}
	fclose(display);
	system("pause");
	system("cls");
	return main();
}

void modifyFacilityUsage()
{
	FILE *fp;
	int i = 0;
	int recordNum, countNo = 0;
	int choice, menuChoice;
	char facilityID[6];
	int countRecord = 0;
	user record[30];

	fp = fopen("facilityUsage.txt", "r");

	while (fscanf(fp, " %s|%s|%s|%s|\n", &record[i].fid, &record[i].id, &record[i].usagetype, &record[i].purpose) != EOF)
	{
		i++;
		countRecord++;
	}
	fclose(fp);

	system("CLS");
	printf("============================================\n");
	printf("%27s\n", "Modify Section");
	printf("============================================\n");
	printf("[1] Modify\n");
	printf("[2] back\n");
	printf("Selection >");
	scanf("%d", &menuChoice);

	while (menuChoice != 2)
	{
		system("CLS");
		printf("===========================\n");
		printf("Please enter facility ID:");
		scanf("%s", &facilityID);

		printf("Facility ID|  Student ID      |  Usage Type        | Purpose                 \n");
		printf("==============================================================================\n");

		for (i = 0; i < countRecord; i++)
		{
			if (strcmp(record[i].fid, facilityID) == 0)
			{

				printf("%-9s", record[i].fid);
				printf("%-18s", record[i].id);
				printf("%-25s", record[i].usagetype);
				printf("%-25s", record[i].purpose);
				countNo++;
			}


			printf("\n< %d record(s) listed > \n", countNo);
			printf("%30s", "==========================================");
			printf("\nPlease choose which record to change : \n");
			printf("[1] Facility ID\n");
			printf("[2] Student ID\n");
			printf("[3] Usage Type\n");
			printf("[4] Purpose\n");
			printf("[5] Exit\n");
			printf("%30s\n", "====================================================================");



			printf("==============\n");
			printf("Selection > ");
			scanf("%d", &choice);

			if (choice == 1)
			{
				printf("Please Enter A NEW Facility ID : ");
				scanf("%s", record[i].fid);
				printf("\nModify Success\n");
			}
			else if (choice == 2)
			{
				printf("Please Enter Your NEW Student ID : ");
				scanf("%s", record[i].id);
				printf("\nModify Success\n");
			}
			else if (choice == 3)
			{
				printf("Please Enter The NEW Usage Type : ");
				scanf("%s", record[i].usagetype);
				printf("\nModify Success\n");
			}
			else if (choice == 4)
			{
				printf("Please Enter The NEW Purpose : ");
				sscanf("%s", record[i].purpose);
				printf("\nModify Success\n");
			}
			else if (choice == 5)
			{
				printf("\nModify Cancelled\n");
				exit(-1);
			}
		}

		FILE*ptr;
		ptr = fopen("facility.txt", "w");

		if (ptr == NULL)
		{
			printf("File error");

			exit(-1);
		}
		for (i = 0; i < countRecord; i++) {
			fprintf(ptr, "%s|", record[i].fid);
			fprintf(ptr, "%s|", record[i].id);
			fprintf(ptr, "%s|", record[i].usagetype);
			fprintf(ptr, "%s|", record[i].purpose);

		}
		fclose(ptr);


	}
}


