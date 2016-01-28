//Author: Jason Du

#include "definitions.h"
#include "system_utilities.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

void printError(int err){
	if (err == BAD_BLOCK_NUMBER){
		cout << "Allocate error: invalid block number.\n";
		cout << "***ERROR. Bad block encountered.\n";
	}
}