//Author: Jason Du

#include "definitions.h"
#include "system_utilities.h"
#include "machines.h"
#include <stdlib.h>
#include <iostream>
#include <string.h>
using namespace std;

void printError(int err){
	if (err == BAD_BLOCK_NUMBER){
		cout << "Allocate error: invalid block number.\n";
		cout << "***ERROR. Bad block encountered.\n";
	}
	if (err == NETWORK_FULL){
		cout << "***ERROR. The network is full.\n";
	}
	if (err == COMPUTER_NOT_FOUND){
		cout << "***ERROR. The computer was not found.\n";
	}
	if (err == INVALID_COMPUTER_TYPE){
		cout << "***ERROR. This is not a valid computer type.\n";
	}
	if (err == FILE_SYSTEM_FULL){
		cout << "***ERROR. The file system is full.";
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

computer *computerNetwork[MAX_NETWORK_NODES];

void systemStatus(){
	cout << "\nHere are the computers currently in the network:\n";
	int c = 0;
	while (computerNetwork[c] != NULL) {
		computerNetwork[c]->print();
		c++;
	}
}

int addNetworkNode(char *toks[], int numberToks){
	if (numberToks == 10) return NETWORK_FULL;
	int dsize = stringToInt(toks[3]);
	if (strcmp(toks[1], "PC") == 0) {
		computerNetwork[numberToks] = new PC(toks[2], dsize, toks[4]);
		return 0;
	} else if (strcmp(toks[1], "server") == 0) {
		computerNetwork[numberToks] = new server(toks[2], dsize, toks[4]);
		return 0;
	} else if (strcmp(toks[1], "printer") == 0) {
		int conv = stringToInt(toks[4]);
		computerNetwork[numberToks] = new printer(toks[2], dsize, conv);
		return 0;
	}
	return INVALID_COMPUTER_TYPE;
}

int deleteNetworkNode(char *toks[], int numberToks){
	int pos = findNode(toks[1]);
	if (pos == -1) return COMPUTER_NOT_FOUND;
	for (int i = pos; i < numberToks; i++) computerNetwork[i] = computerNetwork[i+1];
	computerNetwork[numberToks] = NULL;
	return 0;
}

int findNode(char *n){
	for (int i = 0; i < MAX_NETWORK_NODES; i++){
		if (computerNetwork[i] != NULL) {
			if (computerNetwork[i]->isThisMyName(n) == 1) return i;
		}
	}
	return -1;
}

computer getComputer(int numNode){
	return *computerNetwork[numNode];
}

int stringToInt(char *s){
	int convertedString = 0;
	int count = 0;
	int temp = 0;
	while (s[count] != 00){
		temp = s[count];
		temp = temp - 48;
		convertedString = 10*convertedString + temp;
		count++;
	}
	return convertedString;
}