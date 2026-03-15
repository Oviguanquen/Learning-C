#pragma once

/*************************************/
			/* Libraries */
/*************************************/
/*	Used for:
	Constants:
	- F_SETFL		Set file status flags
	- O_NONBLOCK	Never block on execution

	Functions:
	- fcntl()		Perform indicated operations on file.
*/
#include <fcntl.h>

/*	Used for:
	Constants:
	- SIGPIPE		Write on a pipe with no one to read it
	- SIG_IGN		Ignore signal

	Functions:
	- signal()		Modify indicated signal properties.
*/
#include <signal.h>

/*	Used for:
	Constants:
	- AF_UNIX			UNIX domain sockets
	- SOCK_SEQPACKET	Sequenced-Packet

	Functions:
	- socket()			Create socket File Descriptor
	- bind()			Assign socket File Descriptor to address
	- listen()			Set number of connections
*/
#include <sys/socket.h>

/*	Used for:
	Structure:
	- sockaddr_un		UDS socket address
*/
#include <sys/un.h>

/*	Used for:
	Function:
	- mkdir()			Create a directory with permissions
*/
#include <sys/stat.h>

/*	Used for:
	Functions:
	- unlink()			Remove file
	- close()			Deallocate File Descriptor
	- write()			Write bytes to File Descriptor
*/
#include <unistd.h>

/*	Used for:
	Functions:
	- f_printError()	Prints to STDERR
	- f_strCpy()		Copy one char[] to another
	- f_strLen()		Returns length of char[]
*/
#include "myFunctions.h"

/*************************************/
		/*	Functions */
/*************************************/
/*	Creates the UDS socket with the params from udsServer.h
	Return FileDescriptor in success, -1 on error
*/
int f_createUDS(char* dirPath, char* filePath, int maxClients);

/*	Accepts new clients that subscribe to the UDS
	Return the number of actual clients
*/
int f_acceptClient(int socketFileDescriptor, int* clientsFileDescriptors, int actualClients, int maxClients);

/*	Publishes the msg to all Clients and updates if any client disconnected
	Return the number of actual clients
*/
int f_publishMessage(int* clientsFileDescriptors, int actualClients, char* msg);

/* Ignore the signal SIGPIPE(Write on pipe with no one to read it)
*/
void f_ignoreDisconnections(void);