#include "include/udsClient.h"

#define UDS_PATH "/tmp/uds/uds0"

int main (int argc, char* argv[])
{
	char* 				path;
	char				buffer[4096];
	ssize_t				receiveLength;
	int					socketFileDescriptor;

	if (argc < 2)
		path = UDS_PATH;

	else
		path = argv[1];

	do
	{
		socketFileDescriptor = f_connectToUDS(path);

		if (socketFileDescriptor < 0)
		{
			usleep(250000);
			continue;
		}

		while (1)
		{
			memset(buffer, 0, sizeof(buffer));
			receiveLength = f_receiveFromUDS(socketFileDescriptor, buffer, sizeof(buffer) - 1);

			if (receiveLength <= 0)
				break;

			printf("%s\n", buffer);
		}

		close(socketFileDescriptor);

	}while(1);
}