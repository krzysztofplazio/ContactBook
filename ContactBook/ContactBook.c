#include <stdio.h>
#include <stdlib.h>
#include <mysql.h>
#include <windows.h>
#include <string.h>
#include <locale.h>
#include <conio.h>

#define PASS_LENGTH 32
#define LOG_LENGTH 32

char login[LOG_LENGTH], pass[PASS_LENGTH];
MYSQL* conn;

char* server = "185.226.98.6";
unsigned int port = 33306;
char* user = login;
char* password = pass;
char* database = "PhoneBook";

void mainMenu();
void searchContactsById();
void showAllContacts();

void passHider()
{
	char c;
	int charPos = 0;
	while (true)
	{
		c = _getch();
		switch (c)
		{
		case 13:
		{
			goto exit_loop;
			break;
		}
			break;
		case 8:
		{
			if (charPos > 0)
			{
				charPos--;
				pass[charPos] = '\0';
				printf("\b \b");
			}
			break;
		}
		case 32:
		case 9:
			continue;
			break;
		default:
			if (charPos < PASS_LENGTH)
			{
				pass[charPos] = c;
				charPos++;
				printf("*");
			}
			else
			{
				printf("\nYour password is too long.");
				goto exit_loop;
			}
			break;
		}
	}
	exit_loop: ;	
	pass[charPos] = '\0';
	printf("\n");
}

void isContactExist(bool isExists, int lastId)
{
	if (isExists)
	{
		char quit;
		printf("Exit? [y/N]: ");
		quit = _getch();
		putchar('\n');
		switch (quit)
		{
		case 121:
		{
			mainMenu();
		}
		break;
		case 110:
		case 78:
		{
			int conNum;
			while (true)
			{
				printf("Pick your contact number: ");
				scanf("%d", &conNum);
				if (conNum > lastId || lastId == 0)
				{
					printf("There's not contact with id %d\n\n", conNum);
				}
				else
				{
					searchContactsById(conNum);
					break;
				}
			}
		}
		break;
		default:
		{
			showAllContacts();
		}
		break;
		}
	}
}

void searchContactsByName(char* name)
{
	system("cls");
	MYSQL_ROW rows;
	char* query[150];
	bool isExists = false;
	int lastId = 0;
	sprintf(query, "SELECT Id, Name, SName, PhoneNumber, Address, Email FROM Contacts_%s WHERE Name = \"%s\";", login, name);

	if (mysql_query(conn, query))
	{
		fprintf(stderr, "%s\n", mysql_error(conn));
		exit(1);
	}
	printf("Here's your contacts with name %s:\n", name);
	MYSQL_RES* response = mysql_use_result(conn);
	int numFields = mysql_num_fields(response);
	while ((rows = mysql_fetch_row(response)) != NULL)
	{
		if (numFields > 0)
		{
			lastId = atoi(rows[0]);
			printf("%s. \nName: \t\t%s \nSurname: \t%s \nPhoneNumber: \t%s \nAddress: \t%s \n\n", rows[0], rows[1], rows[2], rows[3], rows[4]);
		}
	}
	if (numFields == 0)
	{
		printf("There's no contacts with name %s :(.\n", name);
	}
	else if (numFields > 1)
	{
		isContactExist(true, lastId);
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

void showAllContacts()
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
	isContactExist(isExists, lastId);
}

void mainMenu()
{
	system("cls");
	char choose;
	printf("Welcome in your personal Contact Book %s!\nWhat do you want to do now?\n", login);
	printf("1. Show my all contacts.\n");
	printf("2. Search contact.\n");
	printf("3. Add new contact.\n");
	printf("4. Edit existed contact.\n");
	printf("5. Exit program.\n");
	printf("\nPick a number: ");
	//scanf("%d", &choose);
	choose = _getch();
	switch (choose)
	{
	case '1':
	{
		showAllContacts();
	}
	break;
	case '2':
	{
		system("cls");
		char name[100];
		printf("First name: ");
		scanf("%s", &name);
		searchContactsByName(name);
	}
	break;
	case '5':
	{
		printf("\nBye! See you soon!");
	}
	break;
	default:
		mainMenu();
		break;
	}
}

bool goodLogin()
{
	bool isLogged = true;

	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, server, user, password, database, port, 0, NULL, 0)) 
		isLogged = false;

	return isLogged;
}

void logging()
{
	int i = 0;
	printf("Your personal phone book!\n");
	printf("Login: ");
	scanf("%s", &login);
	printf("Password: ");
	passHider();
	bool isLogged = goodLogin();
	if (isLogged)
	{
		printf("Logging succesfull!");
		mainMenu();
		Sleep(1000);
	}
	else
	{
		printf("Bad password or login. Try again.\n\n");
		logging();
	}
	//system("cls");
}

int main(void)
{
	logging();
	mysql_close(conn);
}
