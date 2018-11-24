#ifndef FLOYD_WARSHALL_CPP
#define FLOYD_WARSHALL_CPP

#include "Floyd-Warshall.hpp"

FloydWarshall::FloydWarshall(int n, string f)
{
	numberOfNodes = n;
	filename = f;
	for(int i=0; i<numberOfNodes; ++i)
	{
		vector < double > temp( numberOfNodes );
		allPairShortestPath.push_back( temp );
	}
}

FloydWarshall::FloydWarshall(int n)
{
	numberOfNodes = n;
	for(int i=0; i<numberOfNodes; ++i)
	{
		vector < double > temp( numberOfNodes );
		allPairShortestPath.push_back( temp );
	}
}

bool
fileExists(const char *filename)
{
  ifstream ifile(filename);
  return ifile;
}

char* substr(const char* str, int start, int end)
{
	char* a = new char[1+(end-start)]; 
	for(int i=start; i<end; i++) 
		a[i-start] = str[i]; 
	a[end-start] = '\0'; 
	return a;
}

double
atod(const char* a)
{
	double retVal = atoi(a);
	//cout<<"\ngangnam : "<<" ip= "<<a<<" retVal = "<<retVal;
	int start = 0;
	int end = 0;
	for(int i=0; a[i] != '\0'; i++){ 
		if(a[i] == '.' && start == 0){
			start = i+1; 
			end = i+1;
		}
		else if(start != 0)
			end = i+1;
			
/*		else if(start != 0 &&  (a[i] < '0' || a[i] > '9')){ 
			end = i; 
			break; 
		}*/
	}
	if(end > start){ 
		char* decimal = substr(a, start, end); 
		//cout<<" decimal  = "<<decimal;
		int dec = atoi(decimal); 
		int power = end-start; 
		retVal += ((double)dec)/(pow(10.0, (double)power)); 
	}
	//cout<<" op = "<<retVal;
	return retVal;
}

int
FloydWarshall::run( vector < vector < double > > tempMatrix ) // O(n^3) /SadFace
{
	cout<<"\n===>Entering run inside FloydWarshall";
	char *fileHash = getHashForFile((char*)filename.c_str());
	if( fileExists(fileHash) == true)
	{
		cout<<"\nFile Exists. Reading Shortest Path from it.\n";
		const string& delimiters = " ";
		ifstream input_file;
		// cout<<"c_str="<<fileName.c_str()<<"\n";
		input_file.open( fileHash );
		// cout<<"File opened\n";
		int64_t line_no = 0;
		while( input_file.good() )
		{
			// cout<<"watfq?!\n";
			string line;
			vector < double > tokens;
			getline( input_file, line );

			// Skip delimiters at beginning.
			string::size_type lastPos = line.find_first_not_of( delimiters, 0 );

			// Find first "non-delimiter".
			string::size_type pos = line.find_first_of( delimiters, lastPos );
			while( string::npos != pos || string::npos != lastPos )
			{
				// Found a token, add it to the vector.
				string temp = line.substr( lastPos, pos - lastPos );
				tokens.push_back( atod ( temp.c_str() ) );

				// Skip delimiters.  Note the "not_of"
				lastPos = line.find_first_not_of( delimiters, pos );

				// Find next "non-delimiter"
				pos = line.find_first_of( delimiters, lastPos );
			}
			// cout<<"tokens.size() = "<<tokens.size();
			cout<<"\n";
			if( tokens.size() == 0)
				continue;
			else
			{
				for(int i=0; i<tokens.size(); ++i)
					cout<<tokens[i]<<"\t";
			}
		}
		input_file.close();
		exit(0);
	}
	else
	{
		cout<<"\n====>File not found. Crapdoodle!";
		if(tempMatrix.size() != numberOfNodes)
		{
			cerr<< " FloydWarshall : I seem to have been created using the default constructor. I don't like that. Please initialize all my member variables and then we can talk!";
			exit( 0 );
		}
		allPairShortestPath = tempMatrix;
		int i = 0, j = 0, k = 0;
		for( k = 0; k<numberOfNodes; ++k)
			for( i = 0; i<numberOfNodes; ++i)
				for( j = 0; j<numberOfNodes; ++j)
					allPairShortestPath[ i ][ j ] = min( allPairShortestPath[ i ][ j ], allPairShortestPath[ i ][ k ] + allPairShortestPath[ k ][ j ] );
		for( i=0; i<numberOfNodes; ++i)
			allPairShortestPath[i][i] = 0;

		// Writing memoized shortest path into file
		ofstream out(fileHash);
		for(i=0; i<numberOfNodes; ++i)
		{
			for(j=0; j<numberOfNodes; ++j)
				out<<allPairShortestPath[i][j]<<"\t";
			out<<endl;
		}
	}
	cout<<"\n===>Exiting run inside FloydWarshall";
	return( 0 );
}

#endif
