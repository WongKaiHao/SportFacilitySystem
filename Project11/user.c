#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning (disable:4996)
int menuUser();
int addUser(int current, struct User b[20]);
void displayUser(int current, struct User b[20]);
void searchUser(int current, struct User b[20]);
void deleteUser(int current, struct User b[20]);
void modifyUser(struct User b[20]);

struct User
{
	char addId[10], addName[30], gender, choose[10], ic[30], contact[20], cont, comfirm;

};

int mainUser()
{

	struct User b[20];
	FILE* y;
	int choice, current = 0;
	int i = 0;
	do
	{
		choice = menuUser();
		if (choice == 1)
			current = addUser(current, b);
		else if (choice == 2)
			displayUser(current, b);
		else if (choice == 3)
			modifyUser(b);
		else if (choice == 4)
			searchUser(current, b);
		else if (choice == 5)
			deleteUser(current, b);
		else if (choice != 0)
			printf("error choice.please try again");
	} while (choice != 0);
	system("pause");
	y = fopen("user.txt", "r");

	if (y == NULL)
	{
		printf("Unable to open the user.txt file");
		exit(-1);
	}
	else
	{
		while (fscanf(y, "%s %s %[^\:]:%c %s %s\n", b[i].choose, b[i].addId, b[i].addName, &b[i].gender, b[i].ic, b[i].contact) != EOF)
		{
			printf(" %-10s \t%-10s \t%-10s \t%-10c%-10s \t%-10s\n", b[i].choose, b[i].addId, b[i].addName, b[i].gender, b[i].ic, b[i].contact);
			current++;
			i++;
		}
	}
}

//The screen will display a menu for the user to select which function to use in the main page
int menuUser()
{
	int choice;
	printf("***************************************\n");
	printf("*  Welcome to sport facilities system *\n");
	printf("*  ================================== *\n");
	printf("*  (1)register the user account       *\n");
	printf("*  (2)display the user account        *\n");
	printf("*  (3)modify the user account         *\n");
	printf("*  (4)search the user account         *\n");
	printf("*  (5)delete the user account         *\n");
	printf("*  (0)exit                            *\n");
	printf("***************************************\n");
	printf("Enter your choice :");
	scanf("%d", &choice);
	rewind(stdin);
	system("CLS");
	return choice;

}
//if the user choose the add function the system will directly ask the user all the user detail to let the user key in
int addUser(int current, struct User b[20])
{
	FILE* add;
	struct User user[20];

	add = fopen("user.txt", "a");

	if (add == NULL)
	{
		printf("Unable to open the user.txt file");
		exit(-1);
	}
	else
	{

		do
		{

			printf("Welcome to register your new user account\n");
			printf("=========================================\n");
			printf("Do you staff or student:");
			rewind(stdin);
			scanf(" %s", user[current].choose);

			printf("Enter your ID:");
			rewind(stdin);
			scanf(" %s", user[current].addId);


			printf("Enter your name:");
			rewind(stdin);
			scanf(" %[^\n]", user[current].addName);
			/*just can input the F and M*/
			do
			{
				printf("Enter your gender(M/F):");
				rewind(stdin);
				scanf(" %c", &user[current].gender);

			} while (user[current].gender != 'M' && user[current].gender != 'F');
			printf("Enter your Ic:");
			rewind(stdin);
			scanf("%s", user[current].ic);

			printf("Enter your contact number:");
			rewind(stdin);
			scanf("%s", user[current].contact);

			fprintf(add, "%s %s %s:%c %s %s\n", user[current].choose, user[current].addId, user[current].addName, user[current].gender, user[current].ic, user[current].contact);
			/*	if Y it will continue add ,if N it will return to the menu*/
			do
			{
				printf("do you want continue register(Y/N):");
				rewind(stdin);
				scanf(" %c", &user[current].cont);
				if (user[current].cont != 'N' && user[current].cont != 'Y')
				{
					printf("choice error.Please try again\n");
				}
			} while (user[current].cont != 'N' && user[current].cont != 'Y');
		} while (user[current].cont == 'Y');
	}
	printf("done\n");
	fclose(add);
	system("pause");
	system("CLS");
	return current;


}
//if the user chooses the display function the system will read from the fileand display all the user information
void displayUser(int current, struct User b[20])
{
	FILE* p;
	int i = 0;

	p = fopen("user.txt", "r");

	if (p == NULL)
	{
		printf("Unable to open the user.txt file");
		exit(-1);
	}
	else
	{
		int i = 0;

		printf("Type\t\t Id\t\tName\t\tGender\t  Ic\t\tContact\n");
		printf("===================================================================================\n");

		while (fscanf(p, "%s %s %[^\:]: %c %s %s\n", b[i].choose, b[i].addId, b[i].addName, &b[i].gender, b[i].ic, b[i].contact) != EOF)
		{

			printf(" %-10s \t%-10s \t%-10s \t%-10c%-10s \t%-10s\n", b[i].choose, b[i].addId, b[i].addName, b[i].gender, b[i].ic, b[i].contact);

		}
		printf("===================================================================================\n");
		printf("\n");

		fclose(p);
	}
	system("pause");
	system("CLS");
}
//if the user choose the search function the user will be required to key in the user id that they want to search.The system will find from the file and display the specific user data.
void searchUser(int current, struct User b[20])
{
	FILE* search;
	int i = 0;
	search = fopen("user.txt", "r");
	if (search == NULL)
	{
		printf("Unable to open the user.txt file");
		exit(-1);
	}
	else
	{
		char searchId[6], found;
		printf("please enter your ID:");
		rewind(stdin);
		scanf("%s", searchId);
		printf("Type\t\t Id\t\tName\t\tGender\t  Ic\t\tContact\n");
		printf("===================================================================================\n");
		while (fscanf(search, " %s %s %[^\:]:%c %s %s\n", b[i].choose, b[i].addId, b[i].addName, &b[i].gender, &b[i].ic, &b[i].contact) != EOF)
		{
			if (strcmp(searchId, b[current].addId) == 0)
			{
				printf(" %-10s \t%-10s \t%-10s \t%-10c%-10s \t%-10s\n", b[i].choose, b[i].addId, b[i].addName, b[i].gender, b[i].ic, b[i].contact);
				found = 'Y';
				break;
			}
			else
				found = 'N';
		}
		printf("===================================================================================\n");
		printf("\n");
		if (found == 'N')
		{
			printf("not in file\n");
		}
		fclose(search);
	}
	fclose(search);
	system("pause");
	system("CLS");
}
/*The function for this part is to allow the staff to delete the unwanted user*/
void deleteUser(int current, struct User b[20])
{

	FILE* delete;
	int i;
	delete = fopen("user.txt", "r");
	if (delete == NULL)
	{
		printf("Unable to open the user.txt file");
		exit(-1);
	}
	else
	{
		i = 0;
		printf("Type\t\t Id\t\tName\t\tGender\t  Ic\t\tContact\n");
		printf("===================================================================================\n");
		while (fscanf(delete, "%s %s %[^\:]:%c %s %s\n", b[i].choose, b[i].addId, b[i].addName, &b[i].gender, &b[i].ic, &b[i].contact) != EOF)
		{
			printf(" %-10s \t%-10s \t%-10s \t%-10c%-10s \t%-10s\n", b[i].choose, b[i].addId, b[i].addName, b[i].gender, b[i].ic, b[i].contact);
			current++;
			i++;
		}
		printf("===================================================================================\n");
		printf("\n");
		fclose(delete);
	}
	char deleteId[6];
	delete = fopen("user.txt", "w");
	if (delete == NULL)
	{
		printf("Unable to open the user.txt file");
		exit(-1);
	}
	else
	{
		printf("please enter the id you want to delete:");
		scanf(" %s", deleteId);
		rewind(stdin);
		for (i = 0; i < current; i++)
		{
			if (strcmp(deleteId, b[i].addId) == 0)
			{
				for (; i < current; i++)
					b[i] = b[i + 1];
				printf("delete sucessfull\n");
			}

		}
		current--;
	}
	for (int i = 0; i < current; i++)
	{
		fprintf(delete, "%s %s %s:%c %s %s\n", b[i].choose, b[i].addId, b[i].addName, b[i].gender, b[i].ic, b[i].contact);
	}
	fclose(delete);
	system("pause");
	system("CLS");
}
//allow staff to modify the user information.Staff can modify the user information such as, name, gender, icand contact
void modifyUser(struct User b[20])
{
	FILE* sptr, *msptr;
	int i = 0, a, modify;
	char modifyID[6], found = 'F', confirm, newId[10], newName[30], newGender, newIc[30], newContact[30];
	sptr = fopen("user.txt", "r");
	if (sptr == NULL)
	{
		printf("Unable to open the user.txt file");
		exit(-1);
	}
	else
	{
		printf("Type\t\t Id\t\tName\t\tGender\t  Ic\t\tContact\n");
		printf("===================================================================================\n");
		while (fscanf(sptr, "%s %s %[^\:]:%c %s %s\n", b[i].choose, b[i].addId, b[i].addName, &b[i].gender, b[i].ic, b[i].contact) != EOF)
		{
			printf(" %-10s \t%-10s \t%-10s \t%-10c%-10s \t%-10s\n", b[i].choose, b[i].addId, b[i].addName, b[i].gender, b[i].ic, b[i].contact);
			i++;
		}
		printf("===================================================================================\n");
		printf("Enter the staff ID that needed to modify:");
		rewind(stdin);
		scanf("%s", modifyID);
		printf("**************\n");
		printf("*  modify    *\n");
		printf("**************\n");
		printf("* (1)name    *\n");
		printf("* (2)gender  *\n");
		printf("* (3)ic      *\n");
		printf("* (4)contact *\n");
		printf("**************\n");
		for (a = 0; a < i; a++)
		{
			if (strcmp(modifyID, b[a].addId) == 0)
			{
				found = 'Y';
				break;
			}
			else
				found = 'N';
		}
		if (found == 'N')
		{
			printf("error found file\n");
		}
		else
		{
			printf("enter your choice:");
			scanf("%d", &modify);

			if (modify == 1)
			{
				printf("Name      : %s\n", b[a].addName);
				printf("enter new name: ");
				rewind(stdin);
				scanf("%[^\n]", newName);
				strcpy(b[a].addName, newName);
			}
			else if (modify == 2)
			{
				printf("gender  : %c\n", b[a].gender);
				printf("enter the new gender:");
				rewind(stdin);
				scanf(" %c", &newGender);
				b[a].gender = newGender;
			}
			else if (modify == 3)
			{
				printf("ic : %s\n", b[a].ic);
				printf("enter the ic:");
				rewind(stdin);
				scanf("%s", newIc);
				strcpy(b[a].ic, newIc);
			}
			else if (modify == 4)
			{
				printf("contact  : %s\n\n", b[a].contact);
				printf("enter the new contact:");
				rewind(stdin);
				scanf("%s", newContact);
				strcpy(b[a].contact, newContact);
			}
			else
				printf("modify error\n");

		}
		fclose(sptr);
	}
	{
		msptr = fopen("user.txt", "w");
		if (msptr == NULL)
		{

			printf("Unable to open the user.txt file");
			exit(-1);
		}
		else
		{
			for (a = 0; a < i; a++)
			{
				fprintf(msptr, " %s %s %s:%c %s %s\n", b[a].choose, b[a].addId, b[a].addName, b[a].gender, b[a].ic, b[a].contact);

			}
			if (found == 'Y')
			{
				printf("modify sucessfully\n");
			}
		}
		fclose(msptr);
	}
	system("pause");
	system("CLS");
}
