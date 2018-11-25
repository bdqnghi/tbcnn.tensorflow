
class Mat {

	
	public: 
		
		Mat( int n, int m ); 
 		
		Mat( int n, int m, double* input_array ); 
 		
		Mat( int n, int m, double value ); 
		
		Mat( const Mat& input_matrix ); 
		
		~Mat(); 
		
		Mat zeros( int n, int m );
		
		Mat eye( int n );
		
		Mat row( int i );
		
		Mat col( int j );
		
		double operator()( int i, int j );
		
		Mat operator=( Mat B );
		
		bool operator==( Mat B );
        
        Mat mul( const Mat& B );
        
        Mat add( const Mat& B );
		
		void show();
		
		
		
		


	
	private:
		int rows; 
		int cols; 
		int num_elements; 
		double* data; 

};



# include "Matrix.cpp"
