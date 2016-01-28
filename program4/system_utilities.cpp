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

int parseCommandLine(char line[], char *tokens[]){
	int numTokens, count, tokenTerminator, tokenLength;
	count = 0;
	numTokens = 0;
	tokenLength = 0;
	while (line[count] != '\0'){
		while (line[count] == ' ') count++;
		tokenTerminator = count;
		if (line[count] == '\"'){
			count++;
			tokenTerminator++;
			while (line[tokenTerminator] != '\"'){
				tokenTerminator++;
			}
			tokenLength = tokenTerminator - count;
		} else {
			tokenTerminator++;
			while (line[tokenTerminator] != ' ' && line[tokenTerminator] != '\0'){
				tokenTerminator++;
			}
			tokenLength = tokenTerminator - count;
		}
		tokens[numTokens] = (char *)malloc(tokenLength + 1);
		for(int k = 0; k < tokenLength; k++) tokens[numTokens][k] = line[count+k];
		tokens[numTokens][tokenLength] = '\0';
		count = count + tokenLength + 1;
		numTokens++;
	}
	
	return numTokens;
}