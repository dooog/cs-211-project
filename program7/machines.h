//Author: Jason Du

#ifndef MACHINES_H
#define MACHINES_H

#include "disk_drive.h"
#include <string.h>

class computer{

public:
	computer(char name[], int driveSize);
	//~computer();
	virtual void print();
	int isThisMyName(char *n);
	int maximum_number_of_files;
	void printDirectory();
	int createFile(char *n, int len);
	

protected:
	char computerName[20];
	diskDrive *newDisk;
	int findFreeFileDescriptor();
	void getFileDescriptor(int n, fileDescriptor *fd);
	void putFileDescriptor(int n, fileDescriptor *fd);

};

class PC: public computer{
public:
	PC(char name[], int driveSize, char oName[]);
	void print();
private:
	char ownerName[32];
};

class server: public computer{
public:
	server(char name[], int driveSize, char loc[]);
	void print();
private:
	char serverLocation[16];
};

class printer: public computer{
public:
	printer(char name[], int driveSize, int num);
	void print();
private:
	int numPrinters;
};

#endif