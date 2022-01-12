#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

void searchContactsByName(char* name)
{
	system("cls");
	MYSQL_ROW rows;
	char* query[150];
	bool isExists = false;
	int lastId = 0;
	int rowCounter = 0;
	sprintf(query, "SELECT Id, Name, SName, PhoneNumber, Address, Email FROM Contacts_%s WHERE Name = \"%s\";", login, name);

	if (mysql_query(conn, query))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	MYSQL_RES* response = mysql_use_result(conn);
	int numFields = mysql_num_fields(response);
	printf("Here's your contacts with name %s:\n", name);
	while ((rows = mysql_fetch_row(response)) != NULL)
	{
		if (numFields > 0)
		{
			lastId = atoi(rows[0]);
			printf("%s. \nName: \t\t%s \nSurname: \t%s \nPhoneNumber: \t%s \nAddress: \t%s \n\n", rows[0], rows[1], rows[2], rows[3], rows[4]);
			rowCounter++;
		}
	}
	if (rowCounter == 0)
	{
		printf("There's no constacts with name %s :(", name);
	}
	if (rowCounter > 1)
	{
		isContactExist(lastId, "ByName", searchContactsByName);
	}
	mysql_free_result(response);
	printf("Press \'q\' to go to main menu... ");
	char option;
	while (true)
	{
		option = _getch();
		if (option == 81 || option == 113)
		{
			mainMenu();
			break;
		}
	}
}

void searchContactsById(int id)
{
	system("cls");
	MYSQL_ROW rows;
	char* query[150];
	sprintf(query, "SELECT Id, Name, SName, PhoneNumber, Address, Email FROM Contacts_%s WHERE Id = %d", login, id);

	if (mysql_query(conn, query))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	printf("Here's your contact with %d ID:\n", id);
	MYSQL_RES* response = mysql_use_result(conn);
	int num_fields = mysql_num_fields(response);
	while ((rows = mysql_fetch_row(response)) != NULL)
	{
		if (num_fields > 0)
		{
			printf("%s. \nName: \t\t%s \nSurname: \t%s \nPhoneNumber: \t%s \nAddress: \t%s \n\n", rows[0], rows[1], rows[2], rows[3], rows[4]);
		}
	}
	mysql_free_result(response);
	printf("Press \'q\' to go to main menu... ");
	char option;
	while (true)
	{
		option = _getch();
		if (option == 81 || option == 113)
		{
			mainMenu();
			break;
		}
	}
}

void showAllContacts(char* temp)
{
	system("cls");
	MYSQL_ROW rows;
	char query[150];
	int lastId = 0;
	sprintf(query, "SELECT Id, Name, SName, PhoneNumber, Address, Email FROM Contacts_%s", login);
	bool isExists = false;
	if (mysql_query(conn, query))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	printf("Here's yours all contacts:\n");
	MYSQL_RES* response = mysql_use_result(conn);
	int num_fields = mysql_num_fields(response);
	while ((rows = mysql_fetch_row(response)) != NULL)
	{
		if (num_fields > 0)
		{
			lastId = atoi(rows[0]);
			printf("%s. \nName: \t\t%s \nSurname: \t%s \nPhoneNumber: \t%s \nAddress: \t%s \n\n", rows[0], rows[1], rows[2], rows[3], rows[4]);
			isExists = true;
		}
		else
		{
			printf("You haven't any contacts.");
			isExists = false;
		}
	}
	mysql_free_result(response);
	if (isExists)
	{
		isContactExist(lastId, "AllContacts", showAllContacts);
	}
	else
	{
		printf("Press \'q\' to go to main menu... ");
		char option;
		while (true)
		{
			option = _getch();
			if (option == 81 || option == 113)
			{
				mainMenu();
				break;
			}
		}
	}
}