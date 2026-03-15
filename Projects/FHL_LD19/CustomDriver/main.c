#include "include/fhl_ld19.h"
#include "include/udsServer.h"
#include "include/myFunctions.h"

#include <stdio.h>

#define MAX_CLIENTS	5
#define UDS_DIR		"/tmp/uds"
#define MAX_RAW		500
#define MSG_SIZE	(360 * 2 * 6)	// 360º, 2(data, intensity) 6(digits of precision)

typedef struct
{
	float		angle;
	uint16_t	distance;
	uint8_t		intensity;
} LidarPoint;

void f_addToRaw(int* currentRawPoints, LidarPoint* rawPoints, LiDARFrameTypeDef* frame);
void f_reduceTo360(LidarPoint* rawPoints, LidarPoint* convertedPoints);

int main(int argc , char* argv[])
{
	if (argc < 3)
	{
		f_printError("[ERROR] I need more arguments.");
		return -1;
	}

	char*	lidarPath;
	char*	udsPath;

	lidarPath	= argv[1];
	udsPath		= argv[2];

	/*	Socket Variables
	*/
	int	socketFileDescriptor;
	int	clientsFileDescriptors[2] = {0};
	int	actualClients;

	/*	Lidar Variables
	*/
	LidarPoint			rawPoints[MAX_RAW]		= {0};
	LidarPoint			convertedPoints[360]	= {0};

	LiDARFrameTypeDef 	frame;
	int					lidarFileDescriptor;
	int					currentRawPoints = 0;
	uint8_t 			b0, b1;

	f_ignoreDisconnections();

	socketFileDescriptor = f_createUDS(UDS_DIR, udsPath, MAX_CLIENTS);

	actualClients = 0;
	while(1)
	{
		actualClients = f_acceptClient(socketFileDescriptor, clientsFileDescriptors, actualClients, MAX_CLIENTS);
		lidarFileDescriptor = f_connectLidar(lidarPath);
		if (lidarFileDescriptor == -1)
		{
			usleep(250000);
			continue;
		}

		f_configPort(lidarFileDescriptor);

		char	msg[MSG_SIZE];
		int		offset;
		while(1)
		{
			actualClients = f_acceptClient(socketFileDescriptor, clientsFileDescriptors, actualClients, MAX_CLIENTS);
		
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

			f_addToRaw(&currentRawPoints, rawPoints, &frame);
			if (currentRawPoints >= MAX_RAW)
			{
				f_reduceTo360(rawPoints, convertedPoints);
				
				offset = 0;
				offset += sprintf(msg + offset, "[");
				for (int i = 0; i < 360; i++)
				{
					/* Distance */
					offset += sprintf(msg + offset, "%d", convertedPoints[i].distance);

					/* Distance and Intensity*/
					// offset += sprintf(msg + offset, "[%d, %d]", convertedPoints[i].distance, convertedPoints[i].intesity);

					if (i < 359)
						offset += sprintf(msg + offset, ",");
				}
				offset += sprintf(msg + offset, "]\n");
				msg[offset] = '\0';

				actualClients = f_publishMessage(clientsFileDescriptors, actualClients, msg);

				currentRawPoints = 0;
				memset(msg, 0, sizeof(MSG_SIZE));
				memset(convertedPoints, 0, sizeof(LidarPoint) * 360);
				memset(rawPoints, 0, sizeof(LidarPoint) * MAX_RAW);
			}
		}
	}

	return 0;
}

void f_addToRaw(int* currentRawPoints, LidarPoint* rawPoints, LiDARFrameTypeDef* frame)
{
	float startAngle;
	float endAngle;
	float angleIncrement;
	float angle;

	startAngle	= frame->startAngle / 100.0f;
	endAngle	= frame->endAngle / 100.0f;
	if (startAngle > endAngle)
		endAngle = endAngle + 360.0f;

	angleIncrement = (endAngle - startAngle) / (POINT_PER_PACK - 1);

	for (int i = 0; i < POINT_PER_PACK; i++)
	{
		if (*currentRawPoints >= MAX_RAW)
		{
			break;
		}

		if (frame->point[i].distance == 0)
			continue;

		angle = startAngle + (float)i * angleIncrement;
		if (angle >= 360.0f)
			angle -= 360.0f;

		rawPoints[*currentRawPoints].angle		= angle;
		rawPoints[*currentRawPoints].distance	= frame->point[i].distance;
		rawPoints[*currentRawPoints].intensity	= frame->point[i].intensity;

		(*currentRawPoints)++;
	}
}

void f_reduceTo360(LidarPoint* rawPoints, LidarPoint* convertedPoints)
{
	int point;

	for (int i = 0; i < MAX_RAW; i++)
	{
		if (rawPoints[i].distance == 0)
			continue;
		
		point = (int)(rawPoints[i].angle) % 360;

		if ((convertedPoints[point].distance == 0) || (rawPoints[i].distance < convertedPoints[point].distance))
			convertedPoints[point] = rawPoints[i];
	}
	for (int i = 0; i < 360; i++)
	{
		printf("Angle: %.2f\tDistance: %d\tIntensity: %d\n", (double)convertedPoints[i].angle, convertedPoints[i].distance, convertedPoints[i].intensity);
	}
}