//Author: Jason Du

#ifndef SYSTEM_UTILITIES_H
#define SYSTEM_UTILITIES_H


void printError(int err);
int parseCommandLine(char line[], char *tokens[]);
void fillCommandList();
int getCommandNumber(char *s);
void systemStatus();
int addNetworkNode(char *toks[], int numberToks);
int deleteNetworkNode(char *toks[], int numberToks);
int findNode(char *n);
int stringToInt(char *s);

#endif