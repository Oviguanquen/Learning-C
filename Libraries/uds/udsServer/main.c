#include "include/udsServer.h"

#define MAX_CLIENTS 5
#define UDS_DIR	"/tmp/uds"
#define UDS_PATH "/tmp/uds/uds0"

int main()
{
	int				socketFileDescriptor;
	int				clientsFileDescriptors[MAX_CLIENTS] = {0};
	int				actualClients = 0;
	char			msg[] = "Hey\n";

	f_ignoreDisconnections();

	socketFileDescriptor = f_createUDS(UDS_DIR, UDS_PATH, MAX_CLIENTS);
	
	while(1)
	{
		actualClients = f_acceptClient(socketFileDescriptor, clientsFileDescriptors, actualClients, MAX_CLIENTS);

		actualClients = f_publishMessage(clientsFileDescriptors, actualClients, msg, sizeof(msg) - 1);
	}
	
	return 0;
}