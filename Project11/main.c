#include<stdio.h>//
#include<stdlib.h>
#pragma warning(disable: 4996)
int menu();
int main()
{
	int choice;
	do
	{
		choice = menu();
		if (choice == 1)
			mainStaff();
		else if (choice == 2)
			mainFaci();
		else if (choice == 3)
			mainUser();
		else if (choice == 4)
			mainBooking();
		else if (choice == 5)
			mainFaciUsa();
		else if (choice != 6)
			printf("Please try again!");
	} while (choice != 6);
	system("pause");
}
int menu()
{
	int choice;
	printf("\t\t        _________   _____       ______      ______     ___________     _________\n");
	printf("\t\t       /       ||   |  _ \\\\    /      \\\\   |    \\ \\   |          ||   /       ||\n");
	printf("\t\t      /    ____||   | / \\ \\\\  |   /\\   ||  | |\\  \\ \\  |___    ___||  /    ____||\n");
	printf("\t\t      \\       \\\\    | \\_/ //  |  |  |  ||  | |/  / /      |  ||      \\       \\\\\n");
	printf("\t\t       \\____   \\\\   |    //   |  |  |  ||  |    /_/       |  ||       \\____   \\\\\n");
	printf("\t\t       |       //   |   ||    |   \\/   ||  |  |\\ \\        |  ||       |       //\n");
	printf("\t\t       |______//    |___|/     \\______//   |__| \\_\\       |__|/       |______//\n");

	printf("\t __________      _____         ________      ___     ___          ___      __________    _____    _____\n");
	printf("\t/_________/|    / _ \\ \\       /_______/|    /__/|   /__/|        /__/|    /_________/|  /____/\\  /____/\n");
	printf("\t|    _____|/   / / \\ \\ \\     |   _____|/    |__|/   |  ||        |__|/    |___   ___|/   \\   \\ \\/   //\n");
	printf("\t|   /|____    / /_/_\\ \\ \\    |  /|          /__/|   |  ||        /__/|        | ||        \\   \\/   // \n");
	printf("\t|   |/___/|  /  _____  \\ \\   | | \\_____     |  ||   |  ||_____   |  ||        | ||         \\      // \n");
	printf("\t|   _____|/ /  / /   \\  \\ \\  |  \\_____/|    |  ||   |  |/____/|  |  ||        | ||          |    || \n");
	printf("\t|___|/     /__/_/     \\__\\/   \\_______|/    |__|/   |________|/  |__|/        |_|/          |____|/\n");

	printf("\t\t    _________  ___     ___   _________    ___________    _________     ___       ___\n");
	printf("\t\t   /       ||  \\ \\\\   / //  /        ||  |          ||  ||   ____||   |  \\\\     /  ||\n");
	printf("\t\t  /    ____||   \\ \\\\ / //  /     ____||  |___    ___||  || ||_____    |   \\\\   /   ||\n");
	printf("\t\t  \\       \\\\     \\ \\/ //   \\        \\\\       |  ||      ||       ||   |    \\\\ /    ||\n");
	printf("\t\t   \\____   \\\\     \\  //     \\____    \\\\      |  ||      ||   ____||   |  \\  \\/  /  ||\n");
	printf("\t\t   |       //     |  ||     |        //      |  ||      || ||_____    |  |\\    /|  ||\n");
	printf("\t\t   |______//      |__||     |_______//       |__|/      ||_______||   |__| \\__/ |__||\n");
	
	printf("\n\t\t\t\t  -=*=-=*=-=*=-=*=-=*= MENU =*=-=*=-=*=-=*=-=*=-\n");
	printf("\t\t\t\t\t  1. Staff Information Module\n");
	printf("\t\t\t\t\t  2. Facility Module\n");
	printf("\t\t\t\t\t  3. User Information Module\n");
	printf("\t\t\t\t\t  4. Booking Module\n");
	printf("\t\t\t\t\t  5. Facility Usage Module\n");
	printf("\t\t\t\t\t  6. Exit\n");
	printf("\t\t\t\t\t  Enter your choice:");
	scanf("%d",&choice);
	return choice;
}