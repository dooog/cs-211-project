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

/*computer::~computer(){
	delete newDisk;
}*/

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

void computer::printDirectory(){
	fileDescriptor *fd = new fileDescriptor;
	for (int i = 0; i < maximum_number_of_files; i++){
		getFileDescriptor(i, fd);
		cout << "\nFile entry " << i << " - ";	
		if (fd->fileLength == -1) cout << "not in use\n";
		else {
			cout << "File name: ";
			int namelength = strlen(fd->fileName);
			if (namelength > 8) namelength = namelength - 2;
			for (int i = 0; i < namelength; i++) {
				cout << fd->fileName[i];
			}
			cout << ", length: " << fd->fileLength << ", number of first block: " << fd->firstBlockNum << "\n";
		}
	}
}

int computer::createFile(char *n, int len){
	if (findFreeFileDescriptor() > maximum_number_of_files) return FILE_SYSTEM_FULL;
	fileDescriptor *tempFD = new fileDescriptor;
	memcpy(tempFD->fileName, n, 8);
	tempFD->fileLength = len;
	tempFD->firstBlockNum = 0;
	putFileDescriptor(findFreeFileDescriptor(), tempFD);
	delete tempFD;
	return 0;
}

int computer::findFreeFileDescriptor(){
	fileDescriptor *fd = new fileDescriptor;
	for (int i = 0; i < maximum_number_of_files; i++){
		getFileDescriptor(i, fd);
		if (fd->fileLength == -1) return i;
		}
	return FILE_SYSTEM_FULL;
}

void computer::getFileDescriptor(int n, fileDescriptor *fd){
	char *buf = (char *)malloc(64);
	newDisk->retrieveBlock(buf, n/4);
	memcpy(fd, buf + (n%4)*16, 16);
}

void computer::putFileDescriptor(int n, fileDescriptor *fd){
	char *buf = (char *)malloc(64);
	newDisk->retrieveBlock(buf, n/4);
	memcpy(buf+(n%4)*16, fd, 16);
	newDisk->storeBlock(buf, n/4);
	free( (void*)buf);
}

PC::PC(char name[], int driveSize, char oName[]) : computer (name, driveSize){
	memset(ownerName, '\0', 32);
	for (int i = 0; i < strlen(oName); i++) ownerName[i] = oName[i];
	maximum_number_of_files = 8;
	newDisk->formatDrive(maximum_number_of_files);
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
	maximum_number_of_files = 16;
	newDisk->formatDrive(maximum_number_of_files);
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
	maximum_number_of_files = 16;
	newDisk->formatDrive(maximum_number_of_files);
}

void printer::print(){
	cout << "This computer has printers attached.\n";
	cout << "There are " << numPrinters << " printers attached to this computer.";
	computer::print();
}
