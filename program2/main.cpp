/* 

	Processing Polynomials, EECS 211 Program 2
	Author: Jason Du

*/

#include <iostream>
#include <fstream>
using namespace std;

#define MAX_POWER 5
#define NUMBER_OF_COEFFICIENTS 6

ifstream inp("polydata.txt", ios::in);

int readPoly(float coeffs[]);
int dispPoly(int order, float coeffs[]);
int derivs(int order, float coeffs[], float derivCoeffs[]);
float compValue(int order, float coeffs[], float xvalue);

int main() {

	int input, power;
	float coeffs[NUMBER_OF_COEFFICIENTS];
	float derivCoeffs[NUMBER_OF_COEFFICIENTS - 1];

	for (int i = 0; i < 5; i++){
		cout << "\nEnter an integer to proceed to the next polynomial.";
		cin >> input;
		power = readPoly(coeffs);
		dispPoly(power, coeffs);
		derivs(power, coeffs, derivCoeffs);
		cout << "\nThe next polynomial displayed is the derivative of your original polynomial.";
		dispPoly(power - 1, derivCoeffs);
		cout << "\nx\t\tp(x)\t\tp'(x)";
		cout << "\n0.0\t\t", cout << compValue(power, coeffs, 0.0), cout << "\t\t", cout << compValue(power - 1, derivCoeffs, 0.0);
		cout << "\n0.2\t\t", cout << compValue(power, coeffs, 0.2), cout << "\t\t", cout << compValue(power - 1, derivCoeffs, 0.2);
		cout << "\n0.4\t\t", cout << compValue(power, coeffs, 0.4), cout << "\t\t", cout << compValue(power - 1, derivCoeffs, 0.4);
		cout << "\n0.6\t\t", cout << compValue(power, coeffs, 0.6), cout << "\t\t", cout << compValue(power - 1, derivCoeffs, 0.6);
		cout << "\n0.8\t\t", cout << compValue(power, coeffs, 0.8), cout << "\t\t", cout << compValue(power - 1, derivCoeffs, 0.8);
		cout << "\n1.0\t\t", cout << compValue(power, coeffs, 1.0), cout << "\t\t", cout << compValue(power - 1, derivCoeffs, 1.0), cout << "\n";
	}
	cout << "Enter an integer to exit.";
	cin >> input;
	return 0;
}


int readPoly(float coeffs[]){
	
	int order;
	inp >> order;
	for (int j = 0; j <= order; j = j + 1){
		inp >> coeffs[j];
	}
	if (order > 5){
		order = 5;
	}
	return order;

}
	

int dispPoly(int order, float coeffs[]){

	cout << "\nHere is your polynomial: ";
	cout << coeffs[0];
	for (int k = 1; k <= order; k = k + 1){
		cout << " + ";		
		cout << coeffs[k];
		for (int l = 0; l < k; l = l + 1){
			cout << "*x";
		}
	}
	return 0;

}


int derivs(int order, float coeffs[], float derivCoeffs[]){

	if (order == 0) {
		derivCoeffs[0] = 0;
	} else {
		for (int m = 1; m <= order; m = m + 1){
			derivCoeffs[m - 1] = coeffs[m] * m;
		}
	}
	return 0;

}


float compValue(int order, float coeffs[], float xvalue){

	float val = 0;
	float tempval = 0;

	for (int n = 0; n <= order; n = n + 1){
		tempval = coeffs[n];
		for (int p = 1; p <= n; p = p + 1){
			tempval = tempval * xvalue;
		}
		val = val + tempval;
	}
	return val;

}