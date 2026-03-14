#pragma once

/*	Libraries*/
/*	Used to change File Descriptor properties
*/
#include <fcntl.h>

/*	Used if user wants to ignore SIGPIPE signal
*/
#include <signal.h>

/*	Used for managing sockets
*/
#include <sys/socket.h>

/*	Used to define de UDS socket
*/
#include <sys/un.h>

/*	Used to create directory if doesn't exist
*/
#include <sys/stat.h>

/*	Used for system calls: write, read...
*/
#include <unistd.h>

/*	Basic implementation of print, printError, strlen and strcpy
*/
#include "myFunctions.h"

/*	Configurable parameters */
#define MAX_CLIENTS	2
#define UDS_DIR		"/tmp/my_uds"
#define UDS_PATH	"/tmp/my_uds/uds0"

/*	Functions */
/*	Creates the UDS socket with the params from udsServer.h
	Return FileDescriptor in success, -1 on error
*/
int				f_createUDS(void);

/*	Accepts new clients that subscribe to the UDS
	Return the number of actual clients
*/
unsigned int	f_acceptClient(int socketFileDescriptor, int* clientsFileDescriptors, unsigned int actualClients);

/*	Publishes the msg to all Clients and updates if any client disconnected
	Return the number of actual clients
*/
unsigned int	f_publishMessage(int* clientsFileDescriptors, unsigned int actualClients, char* msg);

/* Ignore the signal SIGPIPE(Write on pipe with no one to read it)
*/
void			f_ignoreDisconnections(void);