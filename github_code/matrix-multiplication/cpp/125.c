// This is a declaration. This shows us what we want to implement and how it would work.
class Mat {

	// These are the public member functions for anyone using the library to call
	public: 
		// Create a matrix of dimension nxm
		Mat( int n, int m ); // CONSTRUCTOR
 		// Create an nxm matrix initialized to input_array
		Mat( int n, int m, double* input_array ); // CONSTRUCTOR
 		// Create an nxm matrix initialized to a certain value
		Mat( int n, int m, double value ); // CONSTRUCTOR
		// Create a copy of input matrix
		Mat( const Mat& input_matrix ); // COPY CONSTRUCTOR
		// Release the dynamically allocated memory
		~Mat(); // DESTRUCTOR
		// Create an nxm matrix initialized to all zeros
		Mat zeros( int n, int m );
		// Create an nxm identity matrix
		Mat eye( int n );
		// Extract row i from the matrix
		Mat row( int i );
		// Extract column j from the matrix
		Mat col( int j );
		// Overload the () operator for element extraction
		double operator()( int i, int j );
		// Overload the assignment operator
		Mat operator=( Mat B );
		// Overload the equivalency operatro
		bool operator==( Mat B );
        // This is the matrix multiplication routine
        Mat mul( const Mat& B );
        // This is the matrix addition routine
        Mat add( const Mat& B );
		// We will use this function to print out small matrices for testing purposes
		void show();
		// Can you guys think of more cool things we might want to do with a matrix?
		// We can basically implement ANYTHING!! Perhaps Matrix/Matrix multiplication?
		// Matrix/Vector multiplication? Matrix addition/subtraction?
		// I want to hear your ideas!


	// This is the private data only available to the member functions of the class
	private:
		int rows; // Store the number of rows of the matrix
		int cols; // Store the number of columns of the matrix
		int num_elements; // Store the number of elements in the matrix = rows*cols
		double* data; // This is a pointer to the actual data

};

// Here we include all the actual definitions for the member functions
// from the file 'Matrix.cpp'. Remember this is basically a copy and paste
# include "Matrix.cpp"
