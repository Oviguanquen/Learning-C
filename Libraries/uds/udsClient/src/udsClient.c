#include "../include/udsClient.h"
#include <stdio.h>
#include <sys/types.h>

int f_connectToUDS(const char* path)
{
	struct sockaddr_un	socketAddress;
	int					socketFileDescriptor;

	socketFileDescriptor = socket(AF_UNIX, SOCK_SEQPACKET, 0);
	if (socketFileDescriptor < 0)
	{
		printf("[ERROR] Socket Creation:\n%s\n", strerror(errno));
		return -1;
	}

	socketAddress.sun_family = AF_UNIX;
	strcpy(socketAddress.sun_path, path);

	if (connect(socketFileDescriptor, (struct sockaddr*) &socketAddress, sizeof(socketAddress)) < 0)
	{
		printf("[ERROR] Socket Connection:\n%s\n", strerror(errno));
		close(socketFileDescriptor);
		return -1;
	}

	return socketFileDescriptor;
}

ssize_t f_receiveFromUDS(int socketFileDescriptor, void* buffer, size_t bufferSize)
{
	ssize_t		receiveStatus;

	receiveStatus = recv(socketFileDescriptor, buffer, bufferSize, 0);

	if (receiveStatus < 0)
	{
		printf("[ERROR] Socket Reception:\n%s\n", strerror(errno));
		return -1;
	}

	if (receiveStatus == 0)
	{
		printf("[INFO] Server Closed Connection\n");
		return 0;
	}
	
	return receiveStatus;
}