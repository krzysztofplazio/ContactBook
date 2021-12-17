#include <stdio.h>

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
exit_loop:;
	pass[charPos] = '\0';
	printf("\n");
}