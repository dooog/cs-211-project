#include "intarray.h"
#include <stdlib.h>
#include <string.h>



intarray::intarray() {

	//this->intarray(10);
	number_of_elements = 10;
	data = (int *)malloc(sizeof(int)*10);
}


intarray::intarray(int sz) {

	// Check for sz being ok.  If not, arbitrarily pick the default value.
	if(sz<=0) sz = 10;
	
	number_of_elements = sz;
	data = (int *)malloc(sizeof(int)*sz);
}

intarray::intarray(const intarray &oldArray) {
	number_of_elements = oldArray.number_of_elements;
	data = (int *)malloc(number_of_elements*sizeof(int));
	memcpy(data, oldArray.data, number_of_elements*sizeof(int));
}


intarray::~intarray(void) {

	free( (void *)data);
}

void intarray::setElement(int subscript, int value) {
	// Store the value into the array at position subscript.

	if(subscriptOK(subscript)) 
		data[subscript] = value;
	return;
}

int  intarray::getElement(int subscript) {
	// Retrieve the value stored in the array at 
	// position subscript.

	if(subscriptOK(subscript)) return data[subscript];
	else                       return 0;
}


// Here are two versions of subscript ok.  The first simply checks
// if the subscript is in bounds.  The second extends the array
// upper limit if the subscript is beyond the existing length.
// The intarray class should have one or the other of these.  I
// have included them both here for illustration, but one would
// always be commented out.

/*
int intarray::subscriptOK(int sb) {
	// Return TRUE (1) if sb is a valid subscript, 
	// FALSE (0) otherwise.

	if ( (sb>=0) && (sb<number_of_elements) ) return 1;
	else                                      return 0;
}
*/


int intarray::subscriptOK(int sb) {
	// Return FALSE (0) if sb is negative.  Otherwise
	// check if sb is in range.  If not, extend the array
	// by enough new elements.  In either of these cases,
	// return TRUE (1).

	if(sb<0)                   return 0; 
	if(sb<number_of_elements)  return 1;

	// Here if need to extend array.
	int j, *newarray;

	// sb will be the new largest subscript, so the number
	// of elements must be sb+1.
	newarray = (int *)malloc(sizeof(int)*(sb+1));

	// Now we have to copy all the existing elements and zero out
	// all the new ones.
	for(j=0; j<number_of_elements; j++) newarray[j] = data[j];
	for(j=number_of_elements; j<=sb; j++) newarray[j] = 0;

	// Now free the old array and set data and number_of_elements
	// to their new values.
	free( (void *) data);
	data = newarray;
	number_of_elements = sb+1;

	return 1;
}
