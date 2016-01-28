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

int computer::isThisMyName(char *n){
	if (strcmp(computerName, n) == 0) return 1;
	return 0;
}

PC::PC(char name[], int driveSize, char oName[]) : computer (name, driveSize){
	memset(ownerName, '\0', 32);
	for (int i = 0; i < strlen(oName); i++) ownerName[i] = oName[i];
}

void PC::print(){
	cout << "This computer is a PC.\n";
	cout << "The owner of this PC is: ";
	for (int i = 0; i < strlen(ownerName); i++) cout << ownerName[i];
	cout << "\n";
	computer::print();

}

server::server(char name[], int driveSize, char loc[]) : computer (name, driveSize){
	memset(serverLocation, '\0', 16);
	for (int i = 0; i < strlen(loc); i++) serverLocation[i] = loc[i];
}

void server::print(){
	cout << "This computer is a server.\n";
	cout << "The location of this server is: ";
	for (int i = 0; i < strlen(serverLocation); i++) cout << serverLocation[i];
	cout << "\n";
	computer::print();
}

printer::printer(char name[], int driveSize, int num) : computer (name, driveSize){
	numPrinters = num;
}

void printer::print(){
	cout << "This computer has printers attached.\n";
	cout << "There are " << numPrinters << " printers attached to this computer.";
	computer::print();
}
