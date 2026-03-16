#pragma once

/*************************************/
			/* Libraries */
/*************************************/
/*	Used for:
	Constants
	- errno		Error codes
*/
#include <errno.h>

/*	Used for:
	Constants:
	- AF_UNIX			UNIX domain sockets
	- SOCK_SEQPACKET	Sequenced-Packet
	- MSG_DONTWAIT		Don't Block Execution

	Functions:
	- socket()			Create socket File Descriptor
	- connect()			Connect to designated socket
	- recv()			Receive data from socket
*/
#include <sys/socket.h>

/*	Used for:
	Structure:
	- sockaddr_un		UDS socket address

	Functions:
	- strerror()			Map the errno value to an error message
	- strcpy()			Copy one char[] into another char[]
*/
#include <sys/un.h>

/*	Used for:
	Functions:
	- printf()			Print on STDOUT formated char[]
*/
#include <stdio.h>

/*	Used for:
	Functions:
	- close()			Close file from File Descriptor
*/
#include <unistd.h>

/*************************************/
		/*	Functions */
/*************************************/
/*	Connects to UDS socket with path given
	Return File Descriptor in success, -1 in error
*/
int f_connectToUDS(const char* path);

/*	Receives data from socket and stores it in buffer
	Return Bytes received in success, -1 in error, 0 in Server Closed Conexion
*/
int f_receiveFromUDS(int socketFileDescriptor, char* buffer, int bufferSize);