//Author: Jason Du

#include "definitions.h"
#include "disk_drive.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
using namespace std;

diskDrive::diskDrive(int bytes) {
	numBlocks = (bytes + 63) / 64;
	storageBlocks = (char *)malloc(sizeof(char)*numBlocks*64);
	bitmap = (char *)malloc((sizeof(char)*numBlocks+7)/8);
	for (int i = 0; i < (sizeof(char)*numBlocks+7)/8; i++) bitmap[i]=0;

}

/*diskDrive::~diskDrive() {
	free ((void *)storageBlocks);
	free ((void *)bitmap);
}*/

void diskDrive::print() {
	cout << "The disk size in bytes is: " << numBlocks*64 << "\n";
	cout << "The number of blocks on the drive is: " << numBlocks << "\n";
	cout << hex;
	cout << "Memory map: ";
	for (int j = 0; j < (sizeof(char)*numBlocks+7)/8; j++) {
		int k = bitmap[j];
		k = k & 0x000000ff;
		cout << k << " ";
	}
	cout << "\n\n";
	cout << dec;
}

int diskDrive::allocateBlock(int blockNum) {
	if (blockNum < 0 || blockNum > numBlocks - 1) return BAD_BLOCK_NUMBER;
	int bytePos = blockNum / 8;
	int bitPos = blockNum % 8;
	bitmap[bytePos] |= (1 << bitPos);
	return 0;
}

int diskDrive::freeBlock(int blockNum) {
	if (blockNum < 0 || blockNum > numBlocks - 1) return BAD_BLOCK_NUMBER;
	int bytePos = blockNum / 8;
	int bitPos = blockNum % 8;
	bitmap[bytePos] &= ~(1 << bitPos);
	return 0;
}

int diskDrive::isBlockFree(int blockNum) {
	if (blockNum < 0 || blockNum > numBlocks - 1) return BAD_BLOCK_NUMBER;
	int bytePos = blockNum / 8;
	int bitPos = blockNum % 8;
	int a = (bitmap[bytePos] & (1 << bitPos));
	a = a & 0x000000ff;
	if (a == 0) {
		return 1;} else return 0;
}

int diskDrive::storeBlock(char *d, int blk){
	if (blk > numBlocks) return BAD_BLOCK_NUMBER;
	memcpy(storageBlocks+blk*64, d, 64);
	allocateBlock(blk);
	return 0;
}

int diskDrive::retrieveBlock(char *d, int blk){
	if (blk >= numBlocks || blk < 0) return BAD_BLOCK_NUMBER;
	else memcpy(d, storageBlocks+blk*64, 64);
	return 0;
}

void diskDrive::formatDrive(int maxFiles){
	for (int i = 0; i < maxFiles; i++){
		fileDescriptor *fd = (fileDescriptor *)&storageBlocks[i * 16];
		memset(fd->fileName, 0, 8);
		fd->fileLength = -1;
		fd->firstBlockNum = 0;
	}
	for (int j = 0; j < maxFiles/4; j++) allocateBlock(j); 
}

int diskDrive::findNBlocks(int n, int start){
	int count = 0;
	for (int i = start; i < numBlocks - n + 1; i++){
		if (isBlockFree(i) == 1) count++;
		else count = 0;
		if (count >= n - 1) return i;
	}
	return -1;
}