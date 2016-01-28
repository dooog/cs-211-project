
#ifndef INTARRAY_H
#define INTARRAY_H


class intarray {
public:
	intarray(int sz);
	intarray();
	~intarray(void);
	intarray(const intarray &oldArray);
	void setElement(int subscript, int value);
	int  getElement(int subscript);

private:
	int number_of_elements;
	int *data;

	int subscriptOK(int sb);
};

#endif
