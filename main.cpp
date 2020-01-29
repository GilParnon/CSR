//Gil Parnon, MTH 399, General implementation of things like matrix times a vector in CSR
#include "csrMatrix.h"
#include <iostream>
using namespace std;

int main()
{
	//Temp storage for matrix
	int SIZE = 25;
	float ** A = readIn(SIZE,159);
	float ** L = new float*[SIZE];
	float ** U = new float*[SIZE];

	cout << "The matrix 'A' is:" << endl;
	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			cout << A[i][j] << " ";
		}
		cout << '\n';
	}

	//Create a copy of the matrix
	float ** A2 = new float*[SIZE];

	//And initialize the L,U matrices
	for(int i = 0; i < SIZE; ++i)
	{
		U[i] = new float[SIZE];
		L[i] = new float[SIZE];
		A2[i] = new float[SIZE];
	}
	//Set the data for the matrix copy
	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			A2[i][j] = A[i][j];
			U[i][j] = 0;
			L[i][j] = 0;
		}
	}

	//This will do LU decomposition on A into an L and U.
	LU_Factor(A2,SIZE,L,U);

	for(int i = 0; i < SIZE; ++i)
	{
		
		for(int j = 0; j < SIZE; ++j)
		{
			A[i][j] = 0;
			for(int k = 0; k < SIZE; ++k)
			{
				A[i][j] += L[i][k]*U[k][j];
			}
		}
	}
	//Multiply L*U to check the answer
	cout << "The resutlting matrix is: " << endl;
	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			cout << A[i][j] << " ";
		}
		cout << '\n';
	}

	/*
	cout << "The matrix 'L' is:" << endl;
	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			cout << L[i][j] << " ";
		}
		cout << '\n';
	}

	cout << "The matrix 'U' is:" << '\n';
	for(int i = 0; i < SIZE; ++i)
	{
		for(int j = 0; j < SIZE; ++j)
		{
			cout << U[i][j] << " ";
		}

		cout << '\n';
	}
*/

	delete *A;
	delete *A2;
	delete A;
	delete A2;


	return 0;

}

