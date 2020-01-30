//Gil Parnon, MTH 399, General implementation of things like matrix times a vector in CSR
#include "csrMatrix.h"
#include <iostream>
using namespace std;

int main()
{

	//Temp storage
	int SIZE = 3;
	float temp[SIZE];
	float ** A = readIn(SIZE,9);
	float ** L = new float*[SIZE];
	float ** U = new float*[SIZE];

	//Create a copy of the matrix
	float ** A2 = new float*[SIZE];
	//Initialization of the matrices
	for(int i = 0; i < SIZE; ++i)
	{
		U[i] = new float[SIZE];
		L[i] = new float[SIZE];
		A2[i] = new float[SIZE];
		for(int j = 0; j < SIZE; ++j)
		{
			A2[i][j] = A[i][j];
			U[i][j] = 0;
			L[i][j] = 0;
		}
	}

	//This will do LU decomposition on A into an L and U.
	LU_Factor(A2,SIZE,L,U);
	matrix L_CSR(L,SIZE);
	L_CSR.display();
	matrix U_CSR(U,SIZE);
	U_CSR.display();
	cout << "What is x?" << '\n';
	for(int i =0; i < SIZE; ++i)
	{
		cout << "x" << i << ": ";
		cin >> temp[i];
		cin.ignore(100,'\n');
		cout << '\n';
	}
	vector x(temp,SIZE);
	vector b(SIZE);
	vector y(SIZE);
	vector ans(SIZE);
	matrix A_CSR(A,SIZE);

	//Multiply the inputted x to generate b, then retrieve it with LU
	A_CSR.times(x,b);

	cout << "b = " << '\n';
	b.display();

	//Run LU factorization
	forward(y,b,L_CSR);
	backward(ans,y,U_CSR);

	//Output the answer and what x was originally
	cout << '\n' <<"X = ";
	x.display();
	cout << '\n' << "You got = ";
	ans.display();


	for(int i = 0; i < SIZE; ++i)
	{
		delete A[i];
		delete A2[i];
		delete L[i];
		delete U[i];
	}
	delete [] A;
	delete [] A2;
	delete [] L;
	delete [] U;

	return 0;

}

