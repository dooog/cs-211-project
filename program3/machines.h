//Author: Jason Du

#ifndef MACHINES_H
#define MACHINES_H

#include "disk_drive.h"

class computer{

public:
	computer(char name[], int driveSize);
	~computer();
	void print();

private:
	char computerName[20];
	diskDrive *newDisk;

};

#endif