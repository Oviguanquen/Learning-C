#pragma once

/*************************************/
			/* Libraries */
/*************************************/
/*	Used for:
	Constants:
	- STDOUT_FILENO:	Standard Output
	- STDERR_FILENO:	Standard Error

	Functions:
	- write()			Write bytes to file descriptor
*/
#include <unistd.h>

/*************************************/
		/*	Functions */
/*************************************/
/*	Print a char[] to STDOUT
*/
void f_print(const char* input);

/*	Print a char[] to STDERR
*/
void f_printError(const char* input);

/*	Copy input char[] to output char[]
	Return 0 on success, -1 if input is larger than output
	outputSize must include '\0'
*/
int f_strCpy(const char* input, char* output, unsigned int outputSize);

/*	Return the length of a char[] excluding '\0'
*/
unsigned int f_strLen(const char* input);