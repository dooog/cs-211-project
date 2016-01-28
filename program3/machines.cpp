//Author: Jason Du

#include "definitions.h"
#include "machines.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

computer::computer(char name[], int driveSize){
	newDisk = new diskDrive(driveSize);
	memset(computerName, '\0', 20);
	for (int z = 0; z < strlen(name); z++) computerName[z] = name[z];
	//for (int n = 0; n < 20; n++) name[n] = '\0';
}

computer::~computer(){
	delete newDisk;
}

void computer::print(){
	cout << "The computer's name is: ";
	for (int y = 0; y < 20; y++) cout << computerName[y];
	cout << "\nHere is your new disk's information:\n";
	newDisk->print();
}