//Author: Jason Du

#ifndef MACHINES_H
#define MACHINES_H

#include "disk_drive.h"
#include <string.h>

class computer{

public:
	computer(char name[], int driveSize);
	~computer();
	virtual void print();
	int isThisMyName(char *n);

protected:
	char computerName[20];
	diskDrive *newDisk;

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