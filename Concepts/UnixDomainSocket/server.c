/*
	I'm using info from
	man 7 unix
	man 0p sys_un.h
	man 3type sockaddr_un
*/

#include <sys/socket.h>
#include <sys/un.h>

#include "my_functions.h"

#define UDS_PATH "/tmp/uds0"

int main()
{
	struct sockaddr_un uds;

	uds.sun_family = AF_UNIX;
	(void)f_strCpy(UDS_PATH, uds.sun_path, sizeof(uds.sun_path));
	f_print(uds.sun_path);

	return 0;
}