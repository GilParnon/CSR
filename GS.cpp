//Implementation of Gram-Schmidt
#include "csrMatrix.h"
#include <iostream>
#include <math.h>
using namespace std;

//INPUT: A: array of vectors, n: How many vectors are contained in A
//OUTPUT: Orthonormal basis from the existing vectors
vector * gramSchmidt(vector * A, int n)
{
	vector * q = new vector[n];

	//Set all vectors equal to the initial vectors
	for(int i = 1; i < n; ++i)
	{
		q[i] = A[i];	
	}

	//Normalize the vector
	for(int i = 1; i < n; ++i)
	{
		q[i].normalize();
		
		//Orthoganalize the rest of the vectors to that one
		for(int j = i+1; j < n; ++j)
		{
			q[j] = q[j] - q[i]*q[i].innerProd(q[j]);
		}
	}
	return q;
}
