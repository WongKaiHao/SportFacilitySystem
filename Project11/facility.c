#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#pragma warning(disable: 4996)
void lLine();
void sLine();
void addFaci();
void searchFaci();
void modifyFaci();
void displayFaci();
void deleteFaci();
int menuFaci();
int modifyMenuFaci();

struct ID {
	char wID;
	int nID;
};
typedef struct {
	char Type[20], Description[22], Venue[20];
	int maxUser;
	struct ID iD;
}Facility;

Facility faci;
//return value into the main when user choose what action to be done
int menuFaci()
{
	int choice;
	sLine();
	printf("\n1.add\n2.display\n3.search\n4.modify\n5.delete\n0.Exit\n");
	sLine();
	printf("\nPlease Enter your choice: ");
	rewind(stdin);
	scanf("%d", &choice);

	return choice;
}
//return value into the modify section when user choose what action to be done
int modifyMenuFaci()
{
	int choice;
	sLine();
	printf("\n1. ID\n2. Type\n3. Description\n4. Venue\n5. Maximum User Allow\n");
	sLine();
	printf("What do you want to modified for this facility: ");
	rewind(stdin);
	scanf("%d", &choice);

	return choice;
}
//receive value from menu and carry out action
int mainFaci()
{
	char subOption;
	int choice;
	SYSTEMTIME t;

	GetLocalTime(&t);

	printf("Today's Date: %d-%d-%d\n", t.wDay, t.wMonth, t.wYear);
	printf("%d : %d : %d\n", t.wHour, t.wMinute, t.wSecond);

	do
	{
		printf("\nSport Facility Menu\n");
		choice = menuFaci();
		if (choice == 1)
			addFaci();
		else if (choice == 2)
			displayFaci();
		else if (choice == 3)
			do
			{
				searchFaci();
				printf("Do you want to search again?('Y' = yes) > ");
				rewind(stdin);
				scanf("%c", &subOption);
			} while (toupper(subOption) == 'Y');

		else if (choice == 4)
			modifyFaci();
		else if (choice == 5)
			deleteFaci();
		else if (choice == 0)
		{
			printf("Thank You!!!\n");
			printf("exited.\n");
			exit(-1);
		}
		else
		{
			printf("No such things.\n");
			printf("Please enter again!!!\n");
			system("pause");
			system("cls");
		}
	} while ((choice >= 0 && choice <= 5) || (choice < 0 || choice > 5));

}


//Tools
void sLine()
{
	for (int i = 0; i <= 50; i++)
	{
		printf("*");
	}
	printf("\n");
}
void lLine()
{
	for (int i = 0; i <= 120; i++)
	{
		printf("+");
	}
	printf("\n");
}

//Add new information of facility into the file
void addFaci()
{
	FILE* fptr;

	char answer;
	fptr = fopen("facility.dat", "ab");
	if (fptr == NULL)
	{
		printf("Error occur to open facility.dat.\n");
		exit(-1);
	}
	else
	{
		printf("Any facilities details to be added?(Y = yes): ");
		rewind(stdin);
		scanf("%c", &answer);
		if (toupper(answer) == 'Y')
		{
			do
			{
				printf("Facility ID: ");
				rewind(stdin);
				scanf("%c%d", &faci.iD.wID, &faci.iD.nID);
				faci.iD.wID = toupper(faci.iD.wID);
				printf("Facility Type : ");
				rewind(stdin);
				scanf("%[^\n]", faci.Type);
				printf("Facility Descriptions : ");
				rewind(stdin);
				scanf("%[^\n]", faci.Description);
				printf("Facility Venue : ");
				rewind(stdin);
				scanf("%[^\n]", faci.Venue);

				faci.maxUser = 0;
				printf("Enter facility maximum user allowed: ");
				rewind(stdin);
				scanf("%d", &faci.maxUser);
				while (faci.maxUser <= 0 || faci.maxUser > 100)
				{
					printf("Invalid, please retype: ");
					rewind(stdin);
					scanf("%d", &faci.maxUser);
				}
				printf("Sure to add this facility?(Y = yes): ");
				rewind(stdin);
				scanf("%c", &answer);
				if (toupper(answer) == 'Y')
				{
					fwrite(&faci, sizeof(faci), 1, fptr);
					printf("Any more facilities details to be added?(Y = yes): ");
					rewind(stdin);
					scanf("%c", &answer);
				}

			} while (toupper(answer) == 'Y');
		}
	}
	fclose(fptr);
}
//Display the information that have been added by user in the file
void displayFaci()
{
	FILE* fptr;

	int count = 0;
	fptr = fopen("facility.dat", "rb");
	printf("%-20s %-20s %-30s %-20s %-20s\n", "Facility Id", "Facility Type", "Facility Description", "Facility Venue", "Maximum Userm Allowed");
	lLine();
	while (fread(&faci, sizeof(faci), 1, fptr) != 0)
	{

		printf("%c%-20.4d %-20s %-30s %-20s %-20d\n", faci.iD.wID, faci.iD.nID, faci.Type, faci.Description, faci.Venue, faci.maxUser);
		count++;
	}

	printf("<%d listed>\n", count);
	fclose(fptr);

}
//Allow the user to search info of facility 
void searchFaci()
{
	FILE* fptr;

	Facility f[20];
	char searchType[20];
	int validation = 0;
	fptr = fopen("facility.dat", "rb");
	if (fptr == NULL)
	{
		printf("error in opening facility.dat\n");
		exit(-1);
	}
	else
	{
		//User must enter more than 3 alphabet
		int i = 0;
		printf("Enter the facility type you are searching for(atleast 3 alphabet): ");
		rewind(stdin);
		scanf("%s", searchType);

		while (fread(&f[i], sizeof(Facility), 1, fptr) != 0)
		{
			if (strncmp(f[i].Type, searchType, 3) == 0)
			{
				printf("Facility Id: %c%d\n", f[i].iD.wID, f[i].iD.nID);
				printf("Facility Type: %s\n", f[i].Type);
				printf("Facility Description: %s\n", f[i].Description);
				printf("Facility Venue: %s\n", f[i].Venue);
				printf("Maximum User Allowed: %d\n", f[i].maxUser);

				validation = 1;

			}
			i++;
		}
		if (validation == 0)
		{
			printf("Fail to search!\n");
		}

		fclose(fptr);
	}
}
//Allow user to change the information for the facility
void modifyFaci()
{
	Facility mod[999];
	FILE* read;

	int part, i = 0, totalData = 0, num;
	char word, confirm, again;

	printf("Please enter the ID of the facility you want to modify > ");
	rewind(stdin);
	scanf("%c%d", &word, &num);
	word = toupper(word);

	read = fopen("facility.dat", "rb");
	if (read == NULL)
	{
		printf("error while opening facility.dat!\n");
		exit(-1);
	}
	else
	{
		while (fread(&mod[i], sizeof(Facility), 1, read) != 0)
		{
			i++;
			totalData++;
		}
		fclose(read);

		for (i = 0; i <= totalData; i++)
		{
			if (word == mod[i].iD.wID && num == mod[i].iD.nID)
			{


				printf("Old information\n");
				printf("Facility Id: %c%.4d\n", mod[i].iD.wID, mod[i].iD.nID);
				printf("Facility Type: %s\n", mod[i].Type);
				printf("Facility Description: %s\n", mod[i].Description);
				printf("Facility Venue: %s\n", mod[i].Venue);
				printf("Facility maximum user allowed: %d\n", mod[i].maxUser);
				do
				{
					part = modifyMenuFaci();

					if (part == 1)
					{
						printf("Please enter the new ID > ");
						rewind(stdin);
						scanf("%c%d", &mod[i].iD.wID, &mod[i].iD.nID);
						//if the user key in same id as stored information, the program will ask the user key in again
						while (mod[i].iD.wID == word && mod[i].iD.nID == num)
						{
							printf("Please try again: ");
							rewind(stdin);
							scanf("%c%d", &mod[i].iD.wID, &mod[i].iD.nID);
						}
					}
					else if (part == 2)
					{
						printf("Please enter the new type > ");
						rewind(stdin);
						scanf("%[^\n]", mod[i].Type);

					}
					else if (part == 3)
					{
						printf("Please enter the new description > ");
						rewind(stdin);
						scanf("%[^\n]", mod[i].Description);
					}
					else if (part == 4)
					{
						printf("Please enter new venue > ");
						rewind(stdin);
						scanf("%[^\n]", mod[i].Venue);
					}
					else if (part == 5)
					{
						mod[i].maxUser = 0;
						printf("Please enter new maximum user allow > ");
						rewind(stdin);
						scanf("%d", mod[i].maxUser);
						while (mod[i].maxUser <= 0 || mod[i].maxUser > 100)
						{
							printf("Invalid user allow, please enter again: ");
							rewind(stdin);
							scanf("%d", &mod[i].maxUser);
						}
					}
					else
					{
						printf("\n\nINVALID INPUT\n\n");
					}

					printf("\nDo you want to make a modification again > ");
					rewind(stdin);
					scanf("%c", &again);

				} while (part < 1 || part > 5 || toupper(again) == 'Y');
				break;
			}
		}

		do
		{
			printf("Confirm to do modification ( y = yes, n = no) > ");
			rewind(stdin);
			scanf("%c", &confirm);

			if (toupper(confirm) == 'Y')
			{
				printf("\nMODIFICATION HAS BEEN SUCCESS\n");

				read = fopen("facility.dat", "wb");
				fwrite(&mod, sizeof(Facility), totalData, read);
				fclose(read);

				printf("New Information\n");
				printf("New Facility Id: %c%d\n", mod[i].iD.wID, mod[i].iD.nID);
				printf("Facility Type: %s\n", mod[i].Type);
				printf("Facility Description: %s\n", mod[i].Description);
				printf("Facility Venue: %s\n", mod[i].Venue);
				printf("Facility maximum user allowed: %d\n", mod[i].maxUser);

			}
			else if (toupper(confirm) == 'N')
			{
				printf("\nMODIFICATION HAS BEEN CANCELLED\n");
			}
			else
			{
				printf("\nINVALID INPUT TRY AGAIN\n\n");
			}
		} while (toupper(confirm) != 'Y' && toupper(confirm) != 'N');

		system("pause");
	}

}
//Allow user to remove an information of facility in the file
void deleteFaci()
{
	FILE* fptr;

	Facility f[20];
	char fwCode, answer;
	int count = 0, i, j, fnCode, validation = 0;

	fptr = fopen("facility.dat", "rb");
	if (fptr == NULL)
	{
		printf("Error in opening facility.dat.\n");
		exit(-1);
	}
	else
	{
		i = 0;
		while (fread(&f[i], sizeof(Facility), 1, fptr) != 0)
		{
			count++;
			i++;
		}

		fclose(fptr);
	}
	fptr = fopen("facility.dat", "wb");
	if (fptr == NULL)
	{
		printf("Error in opening facility.dat.\n");
		exit(-1);
	}
	else
	{

		printf("Enter facility Id to delete: ");
		rewind(stdin);
		scanf("%c%d", &fwCode, &fnCode);
		fwCode = toupper(fwCode);
		printf("Do you want to delete?(Y = yes): ");
		rewind(stdin);
		scanf("%c", &answer);
		for (int i = 0; i < count; i++)
		{
			if (toupper(answer) == 'Y')
			{
				for (int i = 0; i < count; i++)
				{

					if (fwCode == f[i].iD.wID && fnCode == f[i].iD.nID)
					{
						for (int j = i; j < count - 1; j++)
						{
							f[j] = f[j + 1];
						}
						count--;
						validation = 1;
					}
				}
				break;
			}
			else
			{
				printf("\nRemove processs has stopped!\n");
				break;
			}


		}
		if (validation == 1)

			printf("delete has done!\n");
		else
			printf("The information you want to delete doesnt exist!\n");


		for (int i = 0; i < count; i++)
		{
			fwrite(&f[i], sizeof(f[i]), 1, fptr);
		}
	}
	fclose(fptr);
}
