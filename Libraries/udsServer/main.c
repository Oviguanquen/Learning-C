#include "include/udsServer.h"

int main()
{
	int				socketFileDescriptor;
	int				clientsFileDescriptors[MAX_CLIENTS] = {0};
	unsigned int	actualClients = 0;

	f_ignoreDisconnections();

	socketFileDescriptor = f_createUDS();
	
	while(1)
	{
		actualClients = f_acceptClient(socketFileDescriptor, clientsFileDescriptors, actualClients);

		actualClients = f_publishMessage(clientsFileDescriptors, actualClients, "Hey\n");

		// usleep(1000);	/* 1 ms */
	}
	
	return 0;
}