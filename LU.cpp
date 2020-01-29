//Implementation of LU factorization
#include "csrMatrix.h"
using namespace std;


//First step of LU
//INPUT: Empty vector y, answer vector b, lower diagonal matrix L
//OUTPUT: Vector y such that Ly=b
void forward(vector & y, vector & b, matrix & L)
{
	y.data[0] = b.data[0]/L.data[0];
	for(int i = 1; i < L.rows; ++i)
	{
		y.data[i] = b.data[i];
		for(int k = L.rowPtr[i]; k < L.rowPtr[i+1]; ++k)
		{
			int j = L.columnInd[k];
			y[i] = y[i] - L.data[k]*y[j];
		}
		y.data[i] = y.data[i]/L.data[L.rowPtr[i+1]-1];
	}
}


//Second step of LU
//INPUT: Empty vector X, answer vector y, upper diagonal matrix U
//OUTPUT: Vector X such that Ux=y
void backward(vector & x, vector & y, matrix & U)
{
	x.data[U.rows-1] = y.data[U.rows-1]/U.data[U.NNZ];
	for(int i=U.rows-2; i > -1; --i)
	{
		x.data[i] = y.data[i];
		for(int k = U.rowPtr[i+1]; k > U.rowPtr[i-1]; --k)
		{
			int j = U.columnInd[k];
			x[i] = x[i] - U.data[k]*x[j];
		}
		x.data[i] = x.data[i]/U.data[U.rowPtr[i+1]-1];
	}
}


//LU by LD^{-1}L^T decomposition. U = D^{-1}L^T for A is SPD 
//INPUT: Matrix A (nxn), rows/column size of A, empty matrices L,U (nxn)
//OUTPUT: L,U will be stored such that LU=A 
void LU_Factor(float **A, int n, float **L, float **U)
{
	float D[n]; //Diagonal vector represents the diagonal entries of D
	for(int i = 0; i < n; ++i)
	{
		//Set the diagonals of both matrices
		L[i][i] = 1; D[i] = 1/A[i][i];
		

		//From here we only need the diagonals and the lower matrix
		//as from exploiting the symmetry of A, and since it is SPD
		//we can use LD^{-1}L^T decomposition
		for(int j = i+1; j < n;  ++j)
		{
			L[j][i] = A[j][i]*D[i];
		}

		//Update our copy of A
		for(int k = i+1; k < n; ++k)
		{
			for(int j = i+1; j < k;  ++j)
			{
				A[k][j] -= L[k][i]*A[j][i];
			}

		}
	}

	//Do the matrix multiplication to generate the upper
	//diagonal matrix, U = D^{-1}L^T 
	for(int i = 0; i < n; ++i)
	{
		for(int j = i; j < n; ++j)
		{
			U[i][j] = L[j][i]/D[i];
		}
	}
}
