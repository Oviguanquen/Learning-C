#include "include/FHL-LD19.h"

#include <unistd.h>

int main(void)
{
	LiDARFrameTypeDef 	frame;

	int					lidarFileDescriptor;

	uint8_t 			b0, b1;

	while (1)
	{
		/*	Connect to lidar, if can't connect delay of 250ms and retry
		*/
		lidarFileDescriptor = f_connectLidar("/dev/ttyUSB0");
		if (lidarFileDescriptor == -1)
		{
			usleep(250000);
			continue;
		}

		/*	Config lidar File Descriptor
		*/
		f_configPort(lidarFileDescriptor);
		
		while (1)
		{
			if (f_searchFrame(lidarFileDescriptor, &b0, &b1) == -1)
				break;

			frame.header				= b0;
			frame.packetType_nPoints	= b1;
			
			if (f_readPort(lidarFileDescriptor, &frame) == -1)
				break;

			if (f_calCRC8((uint8_t *)&frame, sizeof(LiDARFrameTypeDef) - 1) != frame.crc8)
				continue;

			if (f_validateData(&frame) == -1)
				continue;
		}
	}
}