//Implementation of the class for CSR Matrices
#include "csrMatrix.h"
#include <iostream>
using namespace std;


//Default constructor sets everything to NULL or 0
matrix::matrix()
{
	NNZ = 0;
	rows = 0;
	columns = 0;
	data = NULL;
	columnInd = NULL;
	rowPtr = NULL;
}


//Constructor used to initialize the data
//INPUT: Data array of non-nonzeros, column indices for the data, row ptrs for where the rows start
//How many rows, columns and non-zero entries
//OUTPUT: An initialized CSR matrix
matrix::matrix(const float * dataToCopy, const int * indToCopy, const int * rowPtrToCopy, const int & rowCount, const int & columnCount, const int & NNZs)
{
	NNZ = NNZs;
	data = new float[NNZ];
	columnInd = new int[NNZ];
	rowPtr = new int[rowCount + 1];
	rows = rowCount;
	columns = columnCount;
	for(int i = 0; i < NNZ; ++i)
	{
		data[i] = dataToCopy[i];
		columnInd[i] = indToCopy[i];
	}
	for(int i = 0; i < rows + 1; ++i)
	{
		rowPtr[i] = rowPtrToCopy[i];
	}

}


//Copy Constructor
//This will copy all data from a matrix into the new matrix  
//INPUT: Complete CSR matrix
//OUTPUT: Complete copy of the inputted matrix
matrix::matrix(matrix & A)
{
	data = new float[A.NNZ];
	columnInd = new int[A.NNZ];
	rowPtr = new int[A.rows + 1];
	for(int i = 0; i < NNZ; ++i)
	{
		data[i] = A.data[i];
		columnInd[i] = A.columnInd[i];
	}
	for(int i = 0; i < A.rows; ++i)
	{
		rowPtr[i] = A.rowPtr[i];
	}
}


//Turn a dense square matrix form into CSR
//INPUT: Matrix A, number of rows/columns
//OUTPUT: Initialized matrix in CSR format
matrix::matrix(float ** A, int n)
{
	NNZ = 0;
	rows = n;
	columns = n;
	rowPtr = new int[n+1];
	rowPtr[0] = 0;

	//First loop through we find how many nonzero entries there are
	for(int i = 0; i < n; ++i)
	{
		rowPtr[i+1] = rowPtr[i];
		for(int j = 0; j < n; ++j)
		{
			//How many nonzeros are there, also set rowPtr
			if(A[i][j] != 0)
			{
				++NNZ;
				++rowPtr[i+1];
			}
		}	
	}	

	//Now the data arrays can be set
	data = new float[NNZ];
	columnInd = new int[NNZ];

	int index = 0;
	for(int i = 0; i < n; ++i)
	{
		for(int j = 0; j < n; ++j)
		{
			if(A[i][j] != 0)
			{
				data[index] = A[i][j];
				columnInd[index] = j;
				++index;
			}
		}
	}
}




//Destructor for the class
matrix::~matrix()
{
	delete data;
	delete columnInd;
	delete rowPtr;
}


//CSR Matrix times a vector
//INPUT: Vector class to multiply by, answer vector to save the data into
//Output: Ax=b (a vector)
void matrix::times(const vector & X, vector & answer)
{
	delete answer.data; //Just in case the data was the wrong length
	answer.data = new float[rows];

	//CSR matrix times a vector
	for(int i = 0; i < rows; ++i)
	{
		answer.data[i] = 0;
		for(int k = rowPtr[i]; k < rowPtr[i+1]; ++k)
		{
			int j = columnInd[k];
			answer.data[i] += data[k]*X.data[j];
		}
	}
	answer.length = rows;
}


//Display matrix in non-sparse format (for debugging)
void matrix::display()
{
	//Display the matrix in CSR format
	cout << '\n' << "Data: ";
	for(int i = 0; i < NNZ; ++i)
	{
		cout << data[i] << " ";
	}

	cout << '\n' << "Column Indices: ";
	for(int i = 0; i < NNZ; ++i)
	{
		cout << columnInd[i] << " ";
	}

	cout << '\n' << "Row Pointer: ";
	for(int i = 0; i < rows + 1; ++i)
	{
		cout << rowPtr[i] << " ";
	}


	//Display the matrix in dense format
	cout << "The matrix in dense form: " << '\n';	
	int index = 0;
	for(int i = 0; i < rows; ++i) {
	cout << '\n';
		for(int j = 0; j < columns; ++j)
		{
			if(j == columnInd[index] && rowPtr[i] < rowPtr[i+1])
			{
				cout << data[index] << " ";
				++index;
			}
			else
			{
				cout << "0 ";
			}
		}
	}
	cout << '\n';
}
