#ifndef FLOYD_WARSHALL_CPP
#define FLOYD_WARSHALL_CPP

#include "Floyd-Warshall.hpp"

using namespace std;

FloydWarshall::FloydWarshall(string f)
{
	cout<<"\n[FWconstructor(filename)] - numberOfNodes="<<numberOfNodes;
	fflush(stdout);
	filename = f;
	for(int i=0; i<numberOfNodes; ++i)
	{
		ConnectivityMatrix temp;
		allPairShortestPath.push_back( temp );
	}
}

FloydWarshall::FloydWarshall(int n, string f)
{
	filename = f;
	numberOfNodes = n;
	cout<<"\n[FWconstructor(n, filename)] - numberOfNodes="<<numberOfNodes;
	fflush(stdout);
	for(int i=0; i<numberOfNodes; ++i)
	{
		ConnectivityMatrix temp;
		allPairShortestPath.push_back( temp );
	}
}

FloydWarshall::FloydWarshall(int n)
{
	numberOfNodes = n;
	for(int i=0; i<numberOfNodes; ++i)
	{
		ConnectivityMatrix temp( numberOfNodes );
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
//	cout<<"\ngangnam : "<<" ip= "<<a<<" retVal = "<<retVal;
	return retVal;
}

int
FloydWarshall::run( vector < ConnectivityMatrix > tempMatrix ) // O(n^3) /SadFace
{
	cout<<"\n===>Entering run inside FloydWarshall";
	string fileHash ( getHashForFile((char*)filename.c_str()) );
	fileHash += ".hash";
	if( fileExists(fileHash.c_str()) == true ) // Uncomment this to enable memoization
//	if( false == true )
	{
		cout<<"\nFile Exists. Reading Shortest Path from it.\n";
		const string& delimiters = ";";
		ifstream input_file;
		input_file.open( fileHash.c_str() );
//		  cout<<"File opened\n";
		int64_t line_no = 0;
		while( input_file.good() )
		{
			string line;
			vector < double > tokens;
			getline( input_file, line );
			string::size_type lastPos = line.find_first_not_of( delimiters, 0 );
			cout<<"a";
			fflush(stdout);

			string::size_type pos = line.find_first_of( delimiters, lastPos );
			while( string::npos != pos || string::npos != lastPos )
			{
				string temp = line.substr( lastPos, pos - lastPos );
				tokens.push_back( atod ( temp.c_str() ) );

				lastPos = line.find_first_not_of( delimiters, pos );

				pos = line.find_first_of( delimiters, lastPos );
			}
//			cout<<"tokens.size() = "<<tokens.size();
//			fflush(stdout);
			if( tokens.size() == 0)
				continue;
			else
			{
				for(int i=0; i<tokens.size(); ++i)
				{
					//cout<<"\n allPairShortestPath["<<i<<"].size=";
					//fflush(stdout);
					//cout<<allPairShortestPath[i].size();
					pair < int64_t, double > tempPair;
					tempPair.first = i;
					tempPair.second = tokens[i];
					allPairShortestPath[ line_no ].list.push_back(tempPair);
//					allPairShortestPath[ line_no ][ i ] = tokens[ i ];
//					cout<<"a";
				}
				++line_no;
			}
		}
//		fflush( stdout );
		input_file.close();
	}
	else
	{
		cout<<"\nHash file not found, hence computing all pair shortest path";
		if(tempMatrix.size() != numberOfNodes)
		{
			cerr<< " FloydWarshall : I seem to have been created using the default constructor. I don't like that. Please initialize all my member variables and then we can talk!";
			numberOfNodes = tempMatrix.size();
		}
		allPairShortestPath = tempMatrix;
		int i = 0, j = 0, k = 0;
		for( k = 0; k<numberOfNodes; ++k)
			for( i = 0; i<numberOfNodes; ++i)
				for( j = 0; j<numberOfNodes; ++j)
				{
					allPairShortestPath[ i ][ j ] = min( allPairShortestPath[ i ][ j ], allPairShortestPath[ i ][ k ] + allPairShortestPath[ k ][ j ] );
				}
		for( i=0; i<numberOfNodes; ++i)
		{
			allPairShortestPath[i][i] = 0;
		}

		// Writing memoized shortest path into file
		ofstream out(fileHash.c_str());
		out<<setprecision(8)<<fixed;
		for(i=0; i<numberOfNodes; ++i)
		{
			for(j=0; j<numberOfNodes; ++j)
				out<<allPairShortestPath[i][j]<<";";
			out<<endl;
		}
	}
	cout<<"\n===>Exiting run inside FloydWarshall";
	return( 0 );
}

#endif
