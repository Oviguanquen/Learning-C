#include "include/udsClient.h"

int main (int argc, char* argv[])
{
	char* 				path;
	char				buffer[4096];
	int					receiveStatus;
	int					socketFileDescriptor;

	if (argc < 2)
		path = "/tmp/uds/lidar";

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
			receiveStatus = f_receiveFromUDS(socketFileDescriptor, buffer, (int)sizeof(buffer));

			if (receiveStatus <= 0)
				break;

			printf("%s\n", buffer);
		}

		close(socketFileDescriptor);

	}while(1);
}