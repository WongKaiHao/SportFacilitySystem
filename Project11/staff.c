#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#pragma warning(disable:4996)
#define MAX_SIZE 20//Allow maximum 20 staff account
/*----------------------------------------------------------------------*/
/*Menu function to do decision*/
int menuStaff();
int searchStaffMenu();
int modifyStaffMenu();
/*--------------------------------------------------------------------------------*/
/*Structure for staff information*/
typedef struct
{
	char staffID[6], name[50], password[9], passwordRec[100];
}Account;
typedef struct
{
	Account account;
	char position[20];
	char telephone[13];
}Staff;
/*------------------------------------------------------------------------------------------------------------*/
/*Login function*/
void login(int nCurrent, Staff staff[MAX_SIZE])//pass in number of current record, array of structure,and 
{
	/*Local declaration*/
	char checkID[6], checkPassword[9];
	int log = 0, errorCount = 0;
	char forget, forgetId[6];

	do
	{
		printf("Login Staff Account\n");
		printf("-------------------\n");
		printf("Enter your staff ID:");
		scanf(" %s", checkID);//allow staff to enter id
		rewind(stdin);
		printf("Enter your password:");
		scanf(" %s", checkPassword);//allow staff to enter password
		rewind(stdin);
		for (int i = 0; i < nCurrent; i++)//loops to get the array of structure
		{
			if (strcmp(staff[i].account.staffID, checkID) == 0 && strcmp(staff[i].account.password, checkPassword) == 0)//check if the id and password are matche
				log = 1;//if the id and password are matched,it return true
		}
		if (!log)//if log return false,print the error message
		{
			printf("Invalid ID or Password ,please try again ! ! !\n");
			errorCount++;//accumulate the error counter
			if (errorCount > 3)
			{
				printf("Sorry, you already enter id or password incorrectly more than 3 times.\n");
				printf("Maybe you forget password?(Y=yes)");
				scanf(" %c", &forget);//Ask the staff if he/she forget password
				if (toupper(forget) == 'Y')
				{
					printf("Please enter your staff Id:");
					scanf("%s", forgetId);//Ask the staff to enter his/her id that forget password
					for (int i = 0; i < nCurrent; i++)
					{
						if (strcmp(staff[i].account.staffID, forgetId) == 0)//check staff id that entered by staff
							printf("Your password hint is %s\n", staff[i].account.passwordRec);//display the hintfor his/her password
					}
				}
				else if (toupper(forget) == 'N')
					printf("Please try again\n");
			}
			system("pause");
			system("cls");
		}
	} while (log != 1);//loop until the staff enter correct id and password
	if (log)
		printf("Welcome...Login successfully\n");//print the message
	system("pause");
	system("cls");
}
/*-------------------------------------------------------------------------------------------------------------*/
/*add function*/
int addStaff(int nCurrent, FILE *aptr, Staff staff[MAX_SIZE])//pass in the number of current record,address of file for appending and array of structure
{
	/*Local declaration and initialization*/
	char conpassword[9], yes;
	int count, i = 0, validation1 = 0, validation2 = 0, validation3 = 0;
	printf("Do you want to register?(Y=yes):");
	scanf(" %c", &yes);//Ask the Staff if he/she want to register an account
	while (yes == 'Y' || yes == 'y')
	{
		char j[6] = "S", ch[5];
		/*Autogenerated staff ID*/
		count = nCurrent + 1;
		printf("Staff ID : %s%04d\n", j, count);
		sprintf(ch, "%04d", count);
		strcat(j, ch);
		strcpy(staff[nCurrent].account.staffID, j);//copy the id into the array

		printf("Staff Name :");
		scanf(" %[^\n]", staff[nCurrent].account.name);//Ask for staff Name
		rewind(stdin);

		printf("Staff Position :");
		scanf(" %[^\n]", staff[nCurrent].position);//Ask for staff Position
		rewind(stdin);

		printf("Staff Telephone (Include Country Code):");
		scanf(" %s", staff[nCurrent].telephone);//Ask for staff Telephone
		rewind(stdin);

		printf("Staff Password(Maximum 8-character ):");
		scanf(" %s", staff[nCurrent].account.password);//Ask for staff password to login
		rewind(stdin);

		printf("Confirm Staff Password:");
		scanf(" %s", conpassword);//ensure the staff remember what is password that entered 
		rewind(stdin);

		printf("Hint to help you remember your password:");
		scanf(" %[^\n]", staff[nCurrent].account.passwordRec);//to give some hints to staff when he/she forget password during login
		rewind(stdin);

		if (strcmp(conpassword, staff[nCurrent].account.password) == 0)
		{
			fprintf(aptr, "S%04d:%s:%s:%s %s:%s\n", count, staff[nCurrent].account.name, staff[nCurrent].position, staff[nCurrent].telephone, staff[nCurrent].account.password, staff[nCurrent].account.passwordRec);//write into the file
			printf("Register done!\n");//print the message
			nCurrent++;//accumulate the number of current records
		}
		else
			printf("Register failed!\n");
		printf("Do you want to continue registration?(Y=yes):");
		scanf(" %c", &yes);
	}
	system("pause");
	system("CLS");
	return nCurrent;//return the number of current records
}
/*--------------------------------------------------------------------------------------------------------------------------------------------------------*/
/*search function based id*/
void searchId(int nCurrent, Staff staff[MAX_SIZE])//pass in number of current record nad array of structure
{
	/*Local declaration and initialization*/
	char searchID[6];
	int validation = 0;
	printf("Enter the staff ID that is searching for:");
	scanf(" %s", searchID);//Ask for staff id
	rewind(stdin);

	for (int i = 0; i < nCurrent;)
	{
		if (strcmp(searchID, staff[i].account.staffID) == 0)
		{
			printf("Staff ID     : %s\n", staff[i].account.staffID);
			printf("Name         : %s\n", staff[i].account.name);
			printf("Position     : %s\n", staff[i].position);
			printf("Telephone    : %s\n", staff[i].telephone);
			printf("Password     : %s\n", staff[i].account.password);
			printf("Password Hint: %s\n\n", staff[i].account.passwordRec);
			validation = 1;//if found the record,it return true
		}
		i++;
	}
	if (!validation)//if validation return false,print the error message
		printf("Sorry ,the record is not found.Please try again!\n");
	system("pause");
	system("CLS");
}
/*Search function based on staff name*/
void searchName(int nCurrent, Staff staff[MAX_SIZE])
{
	/*Local declaration and initialization*/
	char searchN[30];
	int validation = 0;
	printf("Enter the staff name to search:");
	scanf(" %[^\n]", searchN);//Ask for staff name
	rewind(stdin);

	for (int i = 0; i < nCurrent;)
	{
		if (strcmp(searchN, staff[i].account.name) == 0)
		{
			printf("Staff ID     : %s\n", staff[i].account.staffID);
			printf("Name         : %s\n", staff[i].account.name);
			printf("Position     : %s\n", staff[i].position);
			printf("Telephone    : %s\n", staff[i].telephone);
			printf("Password     : %s\n", staff[i].account.password);
			printf("Password Hint: %s\n\n", staff[i].account.passwordRec);
			validation = 1;//if found the record,it return true
		}
		i++;
	}
	if (!validation)//if validation return false,print the error message
		printf("Sorry ,the record is not found.Please try again!\n");
	system("pause");
	system("CLS");
}
/*Search function based on staff position*/
void searchPosi(int nCurrent, Staff staff[MAX_SIZE])
{
	/*Local declaration and initialization*/
	char searchP[30];
	int validation = 0;
	printf("Enter the staff position to search:");
	scanf(" %[^\n]", searchP);//Ask for staff position
	rewind(stdin);

	for (int i = 0; i < nCurrent;)
	{
		if (strcmp(searchP, staff[i].position) == 0)
		{
			printf("Staff ID     : %s\n", staff[i].account.staffID);
			printf("Name         : %s\n", staff[i].account.name);
			printf("Position     : %s\n", staff[i].position);
			printf("Telephone    : %s\n", staff[i].telephone);
			printf("Password     : %s\n", staff[i].account.password);
			printf("Password Hint: %s\n\n", staff[i].account.passwordRec);
			validation = 1;//if found the record,it return true
		}
		i++;
	}
	if (!validation)//if validation return false,print the error message
		printf("Sorry ,the record is not found.Please try again!\n");
	system("pause");
	system("CLS");
}
/*Search function based on staff telephone*/
void searchTele(int nCurrent, Staff staff[MAX_SIZE])
{
	/*Local declaration and initialization*/
	int validation = 0;
	char searchT[13];
	printf("Enter the staff ID that is searching for:");
	scanf(" %s", searchT);//Ask for staff telephone
	rewind(stdin);

	for (int i = 0; i < nCurrent;)
	{
		if (strcmp(searchT, staff[i].telephone) == 0)
		{
			printf("Staff ID     : %s\n", staff[i].account.staffID);
			printf("Name         : %s\n", staff[i].account.name);
			printf("Position     : %s\n", staff[i].position);
			printf("Telephone    : %s\n", staff[i].telephone);
			printf("Password     : %s\n", staff[i].account.password);
			printf("Password Hint: %s\n\n", staff[i].account.passwordRec);
			validation = 1;//if found the record,it return true
		}
		i++;
	}
	if (!validation)//if validation return false,print the error message
		printf("Sorry ,the record is not found.Please try again!\n");
	system("pause");
	system("CLS");
}
/*-------------------------------------------------------------------------------------------------------------------------*/
/*Modify staff name*/
void modifyName(int nCurrent, Staff staff[MAX_SIZE])
{
	/*Local declaration and initialization*/
	char modifyID[6], name[30];
	printf("Enter the staff ID that needed to modify:");
	scanf(" %s", modifyID);//Ask for staff id
	rewind(stdin);
	for (int i = 0; i < nCurrent;)
	{
		if (strcmp(modifyID, staff[i].account.staffID) == 0)
		{
			printf("OLD INFORMATION");
			printf("Staff ID       : %s\n", staff[i].account.staffID);
			printf("Name           : %s\n", staff[i].account.name);
			printf("Position       : %s\n", staff[i].position);
			printf("Telephone      : %s\n", staff[i].telephone);
			printf("Password       : %s\n", staff[i].account.password);
			printf("Password Hint  : %s\n\n", staff[i].account.passwordRec);
			printf("NEW INFORMATION\n");
			printf("Staff Name :");
			scanf(" %[^\n]", name);
			strcpy(staff[i].account.name, name);
			rewind(stdin);
			printf("Modify successfully\n");
		}
		i++;
	}
	system("pause");
	system("CLS");
}
/*Modify staff Position*/
void modifyPosi(int nCurrent, Staff staff[MAX_SIZE])
{
	/*Local declaration and initialization*/
	char modifyID[6];
	printf("Enter the staff ID that needed to modify:");
	scanf(" %s", modifyID);//Ask for staff id
	rewind(stdin);
	for (int i = 0; i < nCurrent;)
	{
		if (strcmp(modifyID, staff[i].account.staffID) == 0)
		{
			printf("OLD INFORMATION");
			printf("Staff ID       : %s\n", staff[i].account.staffID);
			printf("Name           : %s\n", staff[i].account.name);
			printf("Position       : %s\n", staff[i].position);
			printf("Telephone      : %s\n", staff[i].telephone);
			printf("Password       : %s\n", staff[i].account.password);
			printf("Password Hint  : %s\n\n", staff[i].account.passwordRec);
			printf("NEW INFORMATION\n");
			printf("Staff Position :");
			scanf(" %[^\n]", staff[i].position);
			rewind(stdin);
			printf("Modify successfully\n");
		}
		i++;
	}
	system("pause");
	system("CLS");
}
/*Modify staff telephone*/
void modifyTele(int nCurrent, Staff staff[MAX_SIZE])
{
	/*Local declaration and initialization*/
	char modifyID[6];
	printf("Enter the staff ID that needed to modify:");
	scanf(" %s", modifyID);//Ask for staff id
	rewind(stdin);
	for (int i = 0; i < nCurrent;)
	{
		if (strcmp(modifyID, staff[i].account.staffID) == 0)
		{
			printf("OLD INFORMATION");
			printf("Staff ID       : %s\n", staff[i].account.staffID);
			printf("Name           : %s\n", staff[i].account.name);
			printf("Position       : %s\n", staff[i].position);
			printf("Telephone      : %s\n", staff[i].telephone);
			printf("Password       : %s\n", staff[i].account.password);
			printf("Password Hint  : %s\n\n", staff[i].account.passwordRec);
			printf("NEW INFORMATION\n");
			printf("Staff Telephone :");
			scanf(" %s", &staff[i].telephone);//Modify Telephone
			printf("Modify successfully\n");
		}
		i++;
	}
	system("pause");
	system("CLS");
}
/*Modify staff password*/
void modifyPass(int nCurrent, Staff staff[MAX_SIZE])
{
	/*Local declaration and initialization*/
	char modifyID[6];
	printf("Enter the staff ID that needed to modify:");
	scanf(" %s", modifyID);//Ask for staff id
	rewind(stdin);
	for (int i = 0; i < nCurrent;)
	{
		if (strcmp(modifyID, staff[i].account.staffID) == 0)
		{
			printf("OLD INFORMATION");
			printf("Staff ID       : %s\n", staff[i].account.staffID);
			printf("Name           : %s\n", staff[i].account.name);
			printf("Position       : %s\n", staff[i].position);
			printf("Telephone      : %s\n", staff[i].telephone);
			printf("Password       : %s\n", staff[i].account.password);
			printf("Password Hint  : %s\n\n", staff[i].account.passwordRec);
			printf("NEW INFORMATION\n");
			printf("Staff Password :");
			scanf(" %[^\n]", staff[i].account.password);//Modify Password 
			rewind(stdin);
			printf("Modify successfully\n");
		}
		i++;
	}
	system("pause");
	system("CLS");
}
/*Modify staff password hints*/
void modifyPassRec(int nCurrent, Staff staff[MAX_SIZE])//pass in number of current record nad array of structure
{
	/*Local declaration and initialization*/
	char modifyID[6];
	printf("Enter the staff ID that needed to modify:");
	scanf(" %s", modifyID);//Ask for staff id
	rewind(stdin);
	for (int i = 0; i < nCurrent;)
	{
		if (strcmp(modifyID, staff[i].account.staffID) == 0)
		{
			printf("OLD INFORMATION");
			printf("Staff ID       : %s\n", staff[i].account.staffID);
			printf("Name           : %s\n", staff[i].account.name);
			printf("Position       : %s\n", staff[i].position);
			printf("Telephone      : %s\n", staff[i].telephone);
			printf("Password       : %s\n", staff[i].account.password);
			printf("Password Hint  : %s\n\n", staff[i].account.passwordRec);
			printf("NEW INFORMATION\n");
			printf("Staff Password :");
			scanf(" %[^\n]", staff[i].account.passwordRec);//Modify Password hint
			rewind(stdin);
			printf("Modify successfully\n");
		}
		i++;
	}
	system("pause");
	system("CLS");
}
/*-------------------------------------------------------------------------------------------------------------------------------------------*/
/*Display function*/
void displayStaff(int nCurrent, Staff staff[MAX_SIZE])//pass in number of current record nad array of structure
{
	/*Local declaration */
	int i;
	printf("\t \t \t STAFF INFORMATION\n");
	printf("-------------------------------------------------------------------------\n");
	printf("Staff ID \t Name        \t Position \t Telephone \t Password\n");
	printf("-------------------------------------------------------------------------\n");
	for (i = 0; i < nCurrent; i++)
	{
		printf(" %s       \t %s \t %s \t %s \t %s\n", staff[i].account.staffID, staff[i].account.name, staff[i].position, staff[i].telephone, staff[i].account.password);
	}
	printf("-------------------------------------------------------------------------\n");
	printf("%d records listed\n", nCurrent);//diaplay the number of current record
	system("pause");
	system("CLS");
}
/*--------------------------------------------------------------------------------------------------------------------------------------------*/
/* Delete function */
int deleteStaff(int nCurrent, Staff staff[MAX_SIZE])//pass in number of current record nad array of structure
{
	/*Local declaration and initialization*/
	FILE *sptr;
	char answer, checkId[6], answers;
	int i, validation = 0;
	sptr = fopen("staff.txt", "w");
	if (sptr == NULL)//check if the file can open or not
	{
		printf("Error in opening staff.txt.");
		exit(-1);
	}
	else
	{
		do
		{
			/*display the staff information record to staff for reference*/
			printf("\t \t \t STAFF INFORMATION\n");
			printf("-------------------------------------------------------------------------\n");
			printf("Staff ID \t Name        \t Position \t Telephone \t Password\n");
			printf("-------------------------------------------------------------------------\n");
			for (i = 0; i < nCurrent; i++)
			{
				printf(" %s       \t %s \t %s \t %s \t %s\n", staff[i].account.staffID, staff[i].account.name, staff[i].position, staff[i].telephone, staff[i].account.password);
			}
			printf("-------------------------------------------------------------------------\n");
			rewind(stdin);
			printf("Enter staff ID to delete:");
			scanf(" %s", checkId);//Ask for the staff id to delete
			rewind(stdin);
			printf("Do you confirm to delete?:");
			scanf(" %c", &answer);
			if (toupper(answer) == 'Y')
			{
				for (i = 0; i < nCurrent; i++)
				{
					if (strcmp(checkId, staff[i].account.staffID) == 0)
					{
						for (; i < nCurrent; i++)
							staff[i] = staff[i + 1];
						printf("Remove the Staff Account successfully!\n");
					}
				}
				nCurrent--;
			}
			else if (toupper(answer) != 'N')
				printf("Please retype your choice!");
			printf("Do you want to continue to delete record?:");
			scanf(" %c", &answers);
		} while (toupper(answers) != 'N');
		/*Write back the array into the file*/
		for (i = 0; i < nCurrent; i++)
			fprintf(sptr, "%s:%s:%s:%s %s:%s\n", staff[i].account.staffID, staff[i].account.name, staff[i].position, staff[i].telephone, staff[i].account.password, staff[i].account.passwordRec);
		fclose(sptr);
	}
	system("pause");
	system("CLS");
	return nCurrent;//Return the number of current record
}
/*-----------------------------------------------------------------------------------------------------------------------------------------------*/
/*The main page of Staff Information Module*/
int mainStaff()
{
	/*Local declaration and initialization*/
	Staff staff[MAX_SIZE];
	int i = 0, choice, nCurrent = 0, choiSearch, choiModify;
	FILE *rptr, *aptr;
	aptr = fopen("staff.txt", "a");
	if (aptr == NULL)//check if the file can open or not
	{
		printf("Unable to open the staff.txt file");
		exit(-1);
	}
	rptr = fopen("staff.txt", "r");
	if (rptr == NULL)//check if the file can open or not
	{
		printf("Unable to open the staff.txt file");
		exit(-1);
	}
	else
	{
		/*read the data in the file into the array*/
		while (fscanf(rptr, " %[^\:]:%[^\:]:%[^\:]:%s %[^\:]:%[^\n]", staff[i].account.staffID, staff[i].account.name, staff[i].position, &staff[i].telephone, staff[i].account.password, staff[i].account.passwordRec) != EOF)
		{
			nCurrent++;
			i++;
		}
		login(nCurrent, staff);//call the function
		do
		{
			choice = menuStaff();
			if (choice == 1)
				nCurrent = addStaff(nCurrent, aptr, staff);//call the function
			else if (choice == 2)
			{
				do
				{
					choiSearch = searchStaffMenu();//call the function
					if (choiSearch == 1)
						searchId(nCurrent, staff);//call the function
					else if (choiSearch == 2)
						searchName(nCurrent, staff);//call the function
					else if (choiSearch == 3)
						searchPosi(nCurrent, staff);//call the function
					else if (choiSearch == 4)
						searchTele(nCurrent, staff);//call the function
					else if (choiSearch != 5)
						printf("Invalid.Please try again!");
				} while (choiSearch != 5);
			}
			else if (choice == 3)
			{
				/*Local declaration */
				FILE *wptr;
				wptr = fopen("staff.txt", "w");
				if (wptr == NULL)
				{
					printf("Unable to open the staff.txt file");
					exit(-1);
				}
				do
				{
					choiModify = modifyStaffMenu();//call the function
					if (choiModify == 1)
						modifyName(nCurrent, staff);//call the function
					else if (choiModify == 2)
						modifyPosi(nCurrent, staff);//call the function
					else if (choiModify == 3)
						modifyTele(nCurrent, staff);//call the function
					else if (choiModify == 4)
						modifyPass(nCurrent, staff);//call the function
					else if (choiModify == 5)
						modifyPassRec(nCurrent, staff);//call the function
					else if (choiModify != 6)
						printf("Invalid.Please try again!");
				} while (choiModify != 6);//Loop until the staff want to exit 
				/*After the change is made inside the array, write back the array of structure into the file*/
				for (i = 0; i < nCurrent; i++)
					fprintf(wptr, " %s:%s:%s:%d %s:%s\n", staff[i].account.staffID, staff[i].account.name, staff[i].position, staff[i].telephone, staff[i].account.password, staff[i].account.passwordRec);
				fclose(wptr);//close the file
			}
			else if (choice == 4)
				displayStaff(nCurrent, staff);//call the function
			else if (choice == 5)
				nCurrent = deleteStaff(nCurrent, staff);//call the function
			else if (choice != 6)
				printf("Invalid choice ! Please choose again !");
		} while (choice != 6);//loop until exit
		if (choice == 6)
			printf("Exit Staff Module ! ! !");
		fclose(rptr);//close the file
		fclose(aptr);//close the file
		system("pause");
	}
}
/*---------------------------------------------------------------------------------------------------------------------------*/
/*Main Menu of Staff Information Module*/
int menuStaff()
{
	/*Local declaration */
	int choice;
	printf("\t \t \t STAFF INFORMATION\n");
	printf("-----------------------------------------------------------------\n");
	printf("1. Register the staff login account.\n");
	printf("2. Search for the staff information.\n");
	printf("3. Modify the staff information.\n");
	printf("4. Display all the staff login account and its information.\n");
	printf("5. Remove the staff login account.\n");
	printf("6. Exit\n");
	printf("-----------------------------------------------------------------\n\n");
	printf("Enter Your Choice :");
	scanf("%d", &choice);//
	system("pause");
	system("cls");
	return choice;//return choice to main
}
/*The menu of searching*/
int searchStaffMenu()
{
	/*Local declaration*/
	int choice1;
	printf("\t \t \t Searching Menu\n");
	printf("-----------------------------------------------------------------\n");
	printf("1. Search the staff information based on staff ID.\n");
	printf("2. Search the staff information based on name.\n");
	printf("3. Search the staff information based on position.\n");
	printf("4. Search the staff information based on telephone.\n");
	printf("5. Back to main page\n");
	printf("-----------------------------------------------------------------\n\n");
	printf("Enter Your Choice :");
	scanf("%d", &choice1);//Ask staff to make decision
	system("pause");
	system("cls");
	return choice1;//Return choice1 to main
}
/*The menu of modifiction*/
int modifyStaffMenu()
{
	/*Local declaration*/
	int choice2;
	printf("\t \t \t Modify Menu\n");
	printf("-----------------------------------------------------------------\n");
	printf("1. Modify staff Name.\n");
	printf("2. Modify staff position.\n");
	printf("3. Modify staff telephone.\n");
	printf("4. Modify staff password.\n");
	printf("5. Modify staff password hints.\n");
	printf("6. Back to main page\n");
	printf("-----------------------------------------------------------------\n");
	printf("*Remainder: Staff ID cannot be modified ! ! ! \n\n");
	printf("Enter Your Choice :");
	scanf("%d", &choice2);//Ask staff to make decision
	system("pause");
	system("cls");
	return choice2;//Return choice2 to main
}