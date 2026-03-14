#include "my_functions.h"

void f_print(char* input)
{
	write(STDOUT_FILENO, input, f_strLen(input));
	write(STDOUT_FILENO, "\n", 1);
}

void f_printError(char* input)
{
	write(STDERR_FILENO, input, f_strLen(input));
	write(STDERR_FILENO, "\n", 1);
}

int f_strCpy(char* input, char* output, unsigned int outputSize)
{
	if (f_strLen(input) > outputSize)
		return -1;

	unsigned int i;

	i = 0;
	while(input[i] != '\0')
	{
		output[i] = input[i];
		i++;
	}
	output[i] = '\0';
	return 0;
}

unsigned int f_strLen(char* input)
{
	unsigned int len;

	len = 0;
	while(input[len] != '\0')
	{
		len++;
	}

	return len;
}