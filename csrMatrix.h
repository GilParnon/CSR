//Vector class containing data and an integer for the length
class vector
{
	public:
		 
		vector(); //Default constructor sets everything to NULL
       		vector(vector & X);//Copies all data from a different vector X into a new vector
		vector(float * newData, int & len); //Generate a new vector from an array of floats and the specified length
		vector(int & len); //Generate the 0 vector for a given length
		~vector(); //Deletes the vector and the data inside it

		vector operator /(const float & a); //Divide a vector by a constant
		vector operator *(const float & a); //Multiply a vector by a constant
		vector operator -(const vector & X); //Subtract 2 vectors componentwise
		float& operator [](int & i); //Access a piece of data from the vector for a given index i

		float innerProd(const vector & X); //Inner Product of two vectors
		void normalize(); //Normalize a vector
		void display(); //Display a vector vertically

	//DATA
		int length;
		float * data;
};

//CSR Matrix class
class matrix
{
	public:
		//Default Constructor just sets everything to NULL or 0
		matrix();

		//Copies all data from a matrix A into the new matrix
		matrix(matrix & A);

		//Initialize a CSR matrix from the data, column indices, the row ptrs, number of rows, columns and non-zeroes.
		matrix(const float * dataToCopy, const int * indToCopy, const int * rowPtrToCopy, const int & rowCount, const int & columnCount, const int & NNZs);

		//Initialize a CSR matrix from a non-CSR matrix stored as a 2D-array of floats
		matrix(float ** A, int );

		//Deletes a matrix and all the data inside it.
		~matrix();
	
		//Multiply a matrix times a vector. Returns a matrix.
		void times(const vector & X, vector & answer);

		//For debugging purposes this will display the matrix in both CSR form and dense form
		void display();



	//DATA 
		int NNZ;
		int rows;
		int columns;
		float * data;
		int * columnInd;
		int * rowPtr;

};

//EXTRA FUNCTIONS

//LU Functions (given the LU matrix already known)
void forward(vector & x, vector & b, matrix & L);
void backward(vector & x, vector & b, matrix & U);

//LU Decomposition
//INPUT:Matrix to be decomposed, number of rows/columns, two empty (nxn) matrices to be filled
//OUTPUT: Lower triangular matrix L, upper triangular matrix U such that L*U = A
void LU_Factor(float ** A, int n, float **L, float **U);

//Reads in from a text file
//INPUT: Number of rows/columns, Number of nonzero entries
//OUTPUT: Dense matrix
float ** readIn(int dim, int NNZ);
