#include <fstream>
#include <iostream>
#include "csrMatrix.h"
using namespace std;

//Reads in data from a text file
float ** readIn(int dim,int NNZ)
{
	ifstream fileIn;
	fileIn.open("matrix.txt");
	if(!fileIn)
	{
		cout << "No file to read from" << '\n';
		return 0;
	}

	//Create a dense matrix to store the data
	float ** A = new float*[dim];
	for(int i = 0; i < dim; ++i)
	{
		A[i] = new float[dim];
	}

	//Arrays to store the data
	int row[NNZ];
	int col[NNZ];
	float data[NNZ];

	//Read in all the data into a matrix
	for(int i = 0; i < NNZ; ++i)
	{
		fileIn >> row[i];
		fileIn.ignore();
		fileIn >> col[i];
		fileIn.ignore();
		fileIn >> data[i];
		fileIn.ignore();
	}
	
	//Store the data into the matrix 
	for(int i = 0; i < NNZ; ++i)
	{
		A[row[i]][col[i]] = data[i];
	}

	//Display the whole matrix
	/*
	for(int i = 0; i < dim; ++i)
	{
	cout << '\n';
		for(int k = 0; k < dim; ++k)
		{
			cout << A[i][k] << " ";
		}
	}
	*/
	fileIn.close();

	return A;
}
