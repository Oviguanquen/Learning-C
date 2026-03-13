#include <stdio.h>
void			f_reverse(char* string);
void			f_print(char* string);
unsigned int	f_len(char* string);

void f_reverse(char* string)
{
	unsigned int 	len	= f_len(string);
	unsigned int	i	= 0;
	unsigned int	j	= len - 1;
	char			tmp;

	/* OLD VERSION
	char			auxString[len];
	for (i = 0; i < len; ++i)
	{
		auxString[i] = string[i];
	}

	for (i = 0; i < len; ++i)
	{
		string[i] = auxString[len - 1 - i];
	}
	*/

	while(i < j)
	{
		tmp			= string[i];
		string[i]	= string[j];
		string[j]	= tmp;
		i++;
		j--;
	}
}

void f_print(char* string)
{
	unsigned int len	= f_len(string);
	unsigned int i;

	for (i = 0; i < len; i++)
	{
		putchar(string[i]);
	}

	putchar('\n');
}

unsigned int f_len(char* string)
{
	unsigned int len	= 0;

	while(string[len] != '\0')
	{
		len++;
	}

	return len;
}

int main(void)
{
	char string [] = "test.qw";

	f_print(string);

	f_reverse(string);

	f_print(string);

	return 0;
}