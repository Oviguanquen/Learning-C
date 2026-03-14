#pragma once

#include <unistd.h>

/*	Print a char[] to STDOUT
*/
void			f_print(char* input);

/*	Copy input char[] to output char[]
	Return 0 on success, -1 if input is larger than output
	outputSize must inclue '\0'
*/
int				f_strCpy(char* input, char* output, unsigned int outputSize);

/*	Return the length of a char[] excluding '\0'
*/
unsigned int	f_strLen(char* input);