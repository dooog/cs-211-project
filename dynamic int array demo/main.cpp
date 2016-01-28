#include <iostream>
using namespace std;

#include "intarray.h"

void dummy(intarray ia);

int main() {

	intarray a(10), b(5), c, d[5], *myClass;
	int x,i;

	for(i=0; i<10; i++) a.setElement(i,i*2);
	for(i=0; i<10; i++) cout << a.getElement(i) << "\n";

	for(i=0; i<5; i++) b.setElement(i,i*2);


	a.setElement(-1,100);
	a.setElement(20,100);
	x = a.getElement(-1);
	x = a.getElement(10);
	x = a.getElement(20);

	cout << &a << "   " << &b << "   " << &c << "\n\n";

	cout << "Enter the number of students in your class: ";

	cin >> x;
	myClass = new intarray(x);
	// process class average
	delete myClass;


	c = a;
	//c.intarray(&a);
	b = a;

	dummy(a);

	
	return 0;
}

void dummy(intarray ia) {
	intarray ib;

	cout << &ia << "   " << &ib << "\n\n";
	ib = ia;
}