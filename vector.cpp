//Implementation of the vector class
#include "csrMatrix.h"
#include <iostream>
#include <math.h>
using namespace std;


//Default constructor for a vector, initializes data to NULL
vector::vector()
{
	length = 0;
	data = NULL;
}


//Copies an array of data into a new vector
//INPUT: Array of data, length of the vector
//OUTPUT: Initialized vector
vector::vector(float * newData, int & len)
{
	data = new float[len];
	length = len;
	for(int i = 0; i < len; ++i)
	{
		data[i] = newData[i];
	}
}


//Initialiez the data vector, but don't fill it
//INPUT: integer length of the vector
//OUTPUT: 0 vector
vector::vector(int & len)
{
	data = new float[len];
	for(int i = 0; i < len; ++i)
	{
		data[i] = 0;
	}
	length = len;
}


//Copies an array of data into a new vector
//INPUT: Another vector
//OUTPUT: Exact copy of that vector
vector::vector(vector & X)
{
	data = new float[X.length];
	length = X.length;
	for(int i = 0; i < X.length; ++i)
	{
		data[i] = X[i];
	}
}


//Destructor for vector class
vector::~vector()
{
	delete data;
}


//Divide a vector by a constant
vector  vector::operator /(const float & a)
{
	for(int i = 0; i < this->length; ++i)
	{
		this->data[i]  = this->data[i]/a;
	}
	return *this;
}


//Multiply a vector by a constant
vector vector::operator *(const float & a)
{
	for(int i = 0; i < this->length; ++i)
	{
		this->data[i]  = this->data[i]*a;
	}
	return *this;
}


//Subtract vectors componentwise
vector vector::operator -(const vector & X)
{
	vector val(this->length);
	for(int i = 0; i < this->length; ++i)
	{
		val[i] = this->data[i] - X.data[i];	
	}
	return val;
}


//Access a vector using []
//INPUT: Integer
//OUTPUT: A float from the vector's data
float& vector::operator [](int & i)
{
	return this->data[i];
}

//Inner Product with another vector
//INPUT: Another vector
//OUTPUT: A scalar 
float vector::innerProd(const vector & X)
{
	float val = 0;
	if(length == X.length)
	{
		for(int i = 0; i < length; ++i)
		{
			val += data[i]*X.data[i];
		}
	}
}


//Normalize a vector
void vector::normalize()
{
	float a = sqrt(this->innerProd(*this));
	*this = *this/a;
}



//Displays the data entries of a vector
void vector::display()
{
	for(int i = 0; i < length; ++i)
	{
		cout << '\n' << data[i];
	}
}
