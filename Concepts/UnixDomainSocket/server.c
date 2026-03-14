/*
	I'm using info from
	man 7 unix
	man 0p sys_un.h
	man 3type sockaddr_un
*/

#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>

#include "my_functions.h"

#define UDS_DIR "/tmp/my_uds"
#define UDS_PATH "/tmp/my_uds/uds0"

int main()
{
	/* Create FileDescriptor
	*/
	int socketFileDescriptor;
	socketFileDescriptor = socket(AF_UNIX, SOCK_DGRAM, 0);

	/* Check FileDescriptor
	*/
	if (-1 == socketFileDescriptor)
	{
		f_printError("Create");
		return -1;
	}

	/* Create UDS
	*/
	struct sockaddr_un unixDomainSocket;

	/* Initialize memory
	*/
	memset(&unixDomainSocket, 0, sizeof(struct sockaddr_un));

	/* Configure UDS
	*/
	unixDomainSocket.sun_family = AF_UNIX;
	(void)f_strCpy(UDS_PATH, unixDomainSocket.sun_path, sizeof(unixDomainSocket.sun_path) - 1);

	/* Create directory and purge previous file
	*/
	(void)mkdir(UDS_DIR, 0777);
	unlink(UDS_PATH);

	if(bind(socketFileDescriptor, (struct sockaddr *) &unixDomainSocket, sizeof(unixDomainSocket)) == -1)
	{
		f_printError("Bind");
		return -1;
	}

	while(1)
	{
		f_print("Hello");
	}
	
	return 0;
}