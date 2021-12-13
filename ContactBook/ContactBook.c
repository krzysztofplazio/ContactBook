#include <stdio.h>
#include <stdlib.h>

void logging()
{
	char login[32], pass[32];
	printf("Your personal phone book!\n");
	printf("Login: ");
	scanf_s("%s", &login);
	printf("Password: ");
	scanf_s("%s", &pass);
	printf("Checking input...\n");
	// look for good password
	printf("Logging succesfull!\n");
	system("cls");
}

int main(void)
{
	logging();
}