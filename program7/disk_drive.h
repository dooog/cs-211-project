//Author: Jason Du

#ifndef DISK_DRIVE_H
#define DISK_DRIVE_H

class diskDrive {

public:
	diskDrive(int bytes);
	//~diskDrive();
	void print();
	int allocateBlock(int blockNum);
	int freeBlock(int blockNum);
	int isBlockFree(int blockNum);
	int storeBlock(char *d, int blk);
	int retrieveBlock(char *d, int blk);
	void formatDrive(int maxFiles);

private:
	int numBlocks;
	char *bitmap;
	char *storageBlocks;

};

#endif