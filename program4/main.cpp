#include <iostream>
using namespace std;
#include <fstream>
#include "definitions.h"
#include "system_utilities.h"

//ifstream input;


int main(){

	ifstream input;
	int numTokens = 0;
	char line[MAX_CMD_LINE_LENGTH];
	char* myTokens[MAX_TOKENS_ON_A_LINE];

	//memset(line, '\0', MAX_CMD_LINE_LENGTH);
	
	input.open("p4input.txt", ios::in);
	if(input.fail()) {
		cout << "Failure to open file";
		return 0;
	}
	
	for (int i = 0; i < 4; i++){
		memset(line, '\0', MAX_CMD_LINE_LENGTH);
		input.getline(line, MAX_CMD_LINE_LENGTH);
		numTokens = parseCommandLine(line, myTokens);
		cout << "\nThere is/are " << numTokens << " token(s) on that line.\n";
		cout << "Here are the tokens:\n";
		for (int j = 0; j < numTokens; j++){
			cout << j + 1 << ". " << myTokens[j] << "\n";
		}
	}

	for (int j = 0; j < 4; j++) free((void *)myTokens[j]);
	cout << "Enter an integer to quit.";
	cin >> numTokens;
	return 0;
}