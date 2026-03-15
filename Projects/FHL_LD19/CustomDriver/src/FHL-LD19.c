#include "../include/FHL-LD19.h"

int	f_connectLidar(char* pathToLidar)
{
	int	lidarFileDescriptor;

	lidarFileDescriptor = open(pathToLidar, O_RDWR | O_NOCTTY);
	if (lidarFileDescriptor == -1)
		f_printError("Connect - Error");

	return lidarFileDescriptor;
}

void f_configPort(int lidarFileDescriptor)
{
	struct termios tty;

	/*	Get parameters from lidar File Descriptor terminal
	*/
	
	tcgetattr(lidarFileDescriptor, &tty);

	/*	Receive raw data
	*/
	cfmakeraw(&tty);

	/*	Configure tty
	*/
	tty.c_cc[VMIN]  = 1;	/* read wait for 1 byte */
    tty.c_cc[VTIME] = 0;	/* wait without timeout */

	/*	Configure I/O baudrate
	*/
    cfsetispeed(&tty, B230400);
    cfsetospeed(&tty, B230400);

	/* 	Set parameters from lidar File Descriptor terminal immediately
	*/
    tcsetattr(lidarFileDescriptor, TCSANOW, &tty);
}

int	f_searchFrame(int lidarFileDescriptor, uint8_t* b0, uint8_t* b1)
{
	while (1)
	{	
		if (read(lidarFileDescriptor, b0, 1) == -1)
		{
			f_printError("Search Frame Header - Error");
			return -1;
		}

		if (*b0 != HEADER)
			continue;

		if (read(lidarFileDescriptor, b1, 1) == -1)
		{
			f_printError("Search Frame VerLen - Error");
			return -1;
		}

		if (*b1 == VER_LEN)
			return 0;
	}
}

int f_readPort(int lidarFileDescriptor, LiDARFrameTypeDef* frame)
{
	uint8_t* 			p_frame;
	int					bytesRead;
	unsigned int		bytesRemaining;

	p_frame						= (uint8_t*) frame;
	p_frame 					= p_frame + 2;	/* We already know 2 bytes */
	bytesRemaining				= sizeof(LiDARFrameTypeDef) - 2;
	
	while (bytesRemaining > 0)
	{
		bytesRead	= read(lidarFileDescriptor, p_frame, bytesRemaining);
		
		if (bytesRead <= 0)
		{
			f_printError("Read - Error");
			return -1;
		}

		p_frame			= p_frame + bytesRead;
		bytesRemaining	= bytesRemaining - bytesRead;
	}

	return 0;
}

uint8_t f_calCRC8(uint8_t *p, uint8_t len)
{
	uint8_t		crc = 0;
	uint16_t	i;
	
	for (i = 0; i < len; i++)
	{
		crc = CrcTable[(crc ^ *p++) & 0xff];
	}

	return crc;
}

int f_validateData(LiDARFrameTypeDef* frame)
{
	float startAngle;
	float diff;
	float endAngle;

	/*	Angles arrives with *100
	*/
	startAngle	= frame->startAngle / 100.0f;
	endAngle	= frame->endAngle   / 100.0f;

	/*	End Angle should always be bigger than Start Angle
	*/
	if (endAngle < startAngle)
		endAngle += 360.0f;

	/*	Filter
	*/
	diff = endAngle - startAngle;
	if (diff < MIN_DELTA_ANGLE || diff > MAX_DELTA_ANGLE)
		return -1;

	return 0;
}
