#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <windows.h>
#include <string.h>
#include <locale.h>

char login[32], pass[32];
MYSQL* conn;

char* server = "http://mysql.mastero.cloud/";
char* user = login;
char* password = pass;
char* database = "PhoneBook";

void mainMenu();

void backToMenu()
{
	printf("0. Back to main menu");
}

void getContactById()
{
	system("cls");
}

void searchContacts()
{
	system("cls");
}

void showAllContacts()
{
	system("cls");
	MYSQL_ROW rows;
	char query[] = "SELECT Id, Name, SName, PhoneNumber, Address, Email FROM Contacts_";
	int lastId = 0;
	strcat(query, login);
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
			lastId = rows[0];
			printf("%s. Name: %s Surname: %s PhoneNumber: %s Address: %s \n", rows[0], rows[1], rows[2], rows[3], rows[4]);
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
		char quit[1];
		printf("Exit? [y/N]: ");
		scanf("%s", &quit[0]);

		putchar('\n');
		switch (quit[0])
		{
		case 121:
		{
			mainMenu();
		}
		break;
		case 78:
		{
			int conNum;
			printf("Pick your contact number: ");
			scanf("%d", &conNum);
			if (conNum > lastId || lastId == 0)
			{
				printf("There's not contact with id %d", conNum);
			}
			else
			{
				getContactById(conNum);
			}
		}
		break;
		default:
		{
			printf("Pick a correct one: ");
		}
		break;
		}
	}
}

void mainMenu()
{
	system("cls");
	int choose;
	printf("Welcome in your personal Contact Book %s!\nWhat do you want to do now?\n", login);
	printf("1. Show my all contacts.\n");
	printf("2. Search contact.\n");
	printf("3. Add new contact.\n");
	printf("4. Edit existed contact.\n");
	printf("Pick a number: ");
	scanf("%d", &choose);
	switch (choose)
	{
	case 1:
	{
		showAllContacts();
	}
	break;
	case 2:
	{
		searchContacts();
	}
	break;
	default:
		printf("Pick number from menu.\n");
		break;
	}
}

bool goodLogin()
{
	bool isLogged = true;

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) 
		isLogged = false;

	return isLogged;
}

void logging()
{
	char c = ' ';
	int i = 0;
	printf("Your personal phone book!\n");
	printf("Login: ");
	scanf("%s", &login);
	printf("Password: ");
	scanf("%s", &pass);
	bool isLogged = goodLogin();
	if (isLogged)
	{
		printf("Logging succesfull!");
		mainMenu();
		Sleep(1000);
	}
	else
	{
		printf("Bad password or login. Try again.");
	}
	//system("cls");
}

int main(void)
{
	logging();
	mysql_close(conn);
}
