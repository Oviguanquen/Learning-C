#include "../include/udsServer.h"

int f_createUDS(char* dirPath, char* filePath, int maxClients)
{
	/* Used Variables */
	struct sockaddr_un	unixDomainSocket		= {0};
	int					socketFileDescriptor	= 0;

	/*---------------------------------------------------*/

	/* Create directory and purge previous file
	*/
	(void)mkdir(dirPath, 0700);
	(void)unlink(filePath);

	/* Create socket FileDescriptor
	*/
	socketFileDescriptor = socket(AF_UNIX, SOCK_SEQPACKET, 0);

	if (socketFileDescriptor == -1)
	{
		f_printError("Create - Error");
		return -1;
	}

	/* Configure UDS
	*/
	unixDomainSocket.sun_family = AF_UNIX;
	(void)f_strCpy(filePath, unixDomainSocket.sun_path, sizeof(unixDomainSocket.sun_path) - 1);

	/* Assign socket address
	*/
	if (bind(socketFileDescriptor, (struct sockaddr *) &unixDomainSocket, sizeof(unixDomainSocket)) == -1)
	{
		f_printError("Bind - Error");
		(void)close(socketFileDescriptor);
		return -1;
	}

	/* Start listening
	*/
	if (listen(socketFileDescriptor, maxClients) == -1)
	{
		f_printError("Listen - Error");
		(void)close(socketFileDescriptor);
		return -1;
	}

	/* Don't wait when accepting connection
	*/
	(void)fcntl(socketFileDescriptor, F_SETFL, O_NONBLOCK);

	return socketFileDescriptor;
}

int f_acceptClient(int socketFileDescriptor, int* clientsFileDescriptors, int actualClients, int maxClients)
{
	/* Used Variables */
	int	clientFileDescriptor	= 0;

	/*---------------------------------------------------*/

	/* Try to accept new client
	*/
	clientFileDescriptor = accept(socketFileDescriptor, NULL, NULL);

	/* If there is a new client check actualClients
	*/
	if (clientFileDescriptor != -1)
	{
		if (actualClients < maxClients)
		{
			clientsFileDescriptors[actualClients] = clientFileDescriptor;
			actualClients++;
		}
		else
			close(clientFileDescriptor);
	}

	return actualClients;
}

int f_publishMessage(int* clientsFileDescriptors, int actualClients, char* msg)
{
	/* Send the msg to each client
	*/
	for (int i = 0; i < actualClients; i++)
	{
		/* The client is disconnected
		*/
		if (write(clientsFileDescriptors[i], msg, f_strLen(msg)) == -1)
		{
			(void)close(clientsFileDescriptors[i]);
			actualClients--;
			clientsFileDescriptors[i] = clientsFileDescriptors[actualClients];
			i--;
		}
	}

	return actualClients;
}

void f_ignoreDisconnections()
{
	/* Ignore the signal SIGPIPE(Write on pipe with no one to read it)
	*/
	signal(SIGPIPE, SIG_IGN);
}