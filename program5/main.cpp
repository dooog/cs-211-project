//Author: Jason Du

#include "definitions.h"
#include "system_utilities.h"
#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

int main(){

	ifstream input;
	char line[MAX_CMD_LINE_LENGTH];
	char *myTokens[MAX_TOKENS_ON_A_LINE];
	int numTokens;

	input.open("p5input.txt", ios::in);
	if(input.fail()) {
		cout << "Failure to open file";
		return 0;
	}

	fillCommandList();
	memset(line, '\0', MAX_CMD_LINE_LENGTH);
	input.getline(line, MAX_CMD_LINE_LENGTH);
	numTokens = parseCommandLine(line, myTokens);
	while (getCommandNumber(myTokens[0]) != HALT){
		switch(getCommandNumber(myTokens[0])) {
		case SYSTEM_STATUS: cout << "The command was system_status."; break;
		case HALT: cout << "The command was halt."; break;
		case ADD_NETWORK_NODE: cout << "The command was add_network_node."; break;
		case DELETE_NETWORK_NODE: cout << "The command was delete_network_node."; break;
		case CREATE_FILE: cout << "The command was create_file."; break;
		case LS: cout << "The command was ls."; break;
		case DELETE_FILES: cout << "The command was delete_files."; break;
		case PRINT_FILES: cout << "The command was print_files."; break;
		case TRANSFER_FILE: cout << "The command was transfer_file."; break;
		default: cout << "There was not a recognized command."; break;
		}
		cout << "\nHere are the tokens from your line:\n";
		for (int i = 0; i < numTokens; i++){
			cout << myTokens[i] << "\n";
		}
		cout << "\n";
		memset(line, '\0', MAX_CMD_LINE_LENGTH);
		for (int j = 0; j < numTokens; j++) free ((void *)myTokens[j]);
		input.getline(line, MAX_CMD_LINE_LENGTH);
		numTokens = parseCommandLine(line, myTokens);
	}
	for (int j = 0; j < numTokens; j++) free ((void *)myTokens[j]);
	cout << "You have chosen to halt.";
	cin >> numTokens;

	return 0;

}