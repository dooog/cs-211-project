/*

    Averaging program with input from a file or keyboard.
    Author:  Jason Du
             EECS 211, Winter 2013, Program 1
             
             
    File input is of the form:  N (number of scores in set) followed by
                                N numbers folowed by
                                -1 (there is another set) or -2 (end of data)
                                

*/

#include <iostream>
#include <fstream>
using namespace std;

// Set the following constant to 1 for input from the keyboard, 
// 0 for input from file.
#define DEBUG 0

int getOneNumber(int src);


// This is the input file for when DEBUG is 0.
ifstream inFile;

int main() {
	// Your variables go here.  Be sure to include an int called more.
	int more, sum, count, grade, sentinel, valid, invalid;
	int num = sum = valid = invalid = 0;
	
	if(DEBUG==0) {
		inFile.open("p1input.txt", ios::in);
		if(inFile.fail()) {
			cout << "Could not open input file.  Program terminating.\n\nEnter an integer to quit.";
			cin >> more;
			return 0;
		}
	}
	
	// The rest of your code goes here.
	count = sentinel = getOneNumber(DEBUG);
	while (sentinel != -2){
		num = 0;
		cout << "\nThe number of scores in this set is ";
		cout << count;
		while (num < count){
			grade = getOneNumber(DEBUG);
			if (grade >= 0 && grade <= 100){
				valid++;
				sum = sum + grade;
				num++;
			} else {
				invalid++;
				num++;
			}
		}
		if (valid == 0){
			cout << "\nThere are no valid scores for this data set.";
			cout << "\n";
		} else {
			cout << "\nThe average score of this data set is ";
			cout << (float) sum/(count-invalid);
			cout <<", and the number of invalid scores is ";
			cout << invalid;
			cout << "\n";
		}
		sum = valid = invalid = num = 0;
		sentinel = getOneNumber(DEBUG);
		count = getOneNumber(DEBUG);
	}

	cout << "\nEnd of data sets.  Enter an integer to quit.\nHave a nice day!";
	cin >> more;	
	
	return 0;
}

int getOneNumber(int src) {
	// Gets the next integer from the input.  If src is
	// 0, then read from the file opened in the main function, 
	// otherwise read from the keyboard.
	
	int val;
	
	if(src) {
		// Input from keyboard.
		cout << "Enter the next input: ";
		cin >> val;
	}
	else {
		// Input from file.
		inFile >> val;
	}
	
	return val;
	
}