//Author: Jason Du

#include "definitions.h"
#include "system_utilities.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>
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

class commandElement{	
public:
	commandElement(char *command, int commandNum);
	int amIThisCommand(char *command);
private:
	char *commandString;
	int numCommand;
};

commandElement *commandList[NUMBER_OF_COMMANDS];

commandElement::commandElement(char *command, int comNum){
	commandString = (char *)malloc(strlen(command)+1);
	memcpy(commandString, command, strlen(command)+1);
	numCommand = comNum;
}

int commandElement::amIThisCommand(char *command){
	if (strcmp(commandString, command) == 0) return numCommand;
	else return 0;
}

void fillCommandList(){
	commandList[0] = new commandElement("system_status", SYSTEM_STATUS);
	commandList[1] = new commandElement("halt", HALT);
	commandList[2] = new commandElement("add_network_node", ADD_NETWORK_NODE);
	commandList[3] = new commandElement("delete_network_node", DELETE_NETWORK_NODE);
	commandList[4] = new commandElement("create_file", CREATE_FILE);
	commandList[5] = new commandElement("ls", LS);
	commandList[6] = new commandElement("delete_files", DELETE_FILES);
	commandList[7] = new commandElement("print_files", PRINT_FILES);
	commandList[8] = new commandElement("transfer_file", TRANSFER_FILE);
}

int getCommandNumber(char *s){
	for (int i = 0; i < NUMBER_OF_COMMANDS; i++){
		if (commandList[i]->amIThisCommand(s) != 0) return commandList[i]->amIThisCommand(s);
	}
	return UNDEFINED_COMMAND;
}