#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
bool goodLogin()
{
	MYSQL mysql;
	return false;
}

void logging()
{
	char login[32], pass[32];
	printf("Your personal phone book!\n");
	printf("Login: ");
	scanf("%s", &login);
	printf("Password: ");
	scanf("%s", &pass);
	printf("Checking input...\n");
	
	printf("Logging succesfull!\n");
	system("cls");
}

int main(void)
{
	logging();
}