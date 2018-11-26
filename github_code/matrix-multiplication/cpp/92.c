#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

vector<vector<double>> rx, ry, rz;


/*
* convert degree to radins.
*/
double convertDegreeToRadians(double degree){
	double rad = degree * M_PI / 180.0;//要用 PI, 除了要 include cmath，還要 define _USE_MATH_DEFINES
	return rad;
}

void InitialMatrix(vector<vector<double>>& m){
	m.clear();
	for (int i = 0; i < 3; i++){
		vector<double> v = { 0.0, 0.0, 0.0 };
		m.push_back(v);
	}
}
/*
* rotation matrix of axis
*/
void CalculateRotationAxis(double dx, double dy, double dz, bool rh){
	InitialMatrix(rx);
	InitialMatrix(ry);
	InitialMatrix(rz);
	double radx = convertDegreeToRadians(dx);
	double rady = convertDegreeToRadians(dy);
	double radz = convertDegreeToRadians(dz);
	if (!rh){
		radx = -radx;
		rady = -rady;
		radz = -radz;
	}
	//cout << radx << ", " << rady << ", " << radz << endl;
	/*
		| 1		0			0			|
		| 0		cos(radx)	-sin(radx)	|
		| 0		sin(radx)	cos(radx)	|
	*/
	rx[0][0] = 1;
	rx[1][1] = cos(radx);
	rx[1][2] = -sin(radx);
	rx[2][1] = sin(radx);
	rx[2][2] = cos(radx);
	/*
	| cos(rady)		0		sin(rady)	|
	| 0				1		0			|
	| -sin(rady)	0		cos(radx)	|
	*/
	ry[1][1] = 1;
	ry[0][0] = cos(rady);
	ry[0][2] = sin(rady);
	ry[2][0] = -sin(rady);
	ry[2][2] = cos(rady);
	/*
	| cos(radz)		-sin(radz)		0	|
	| sin(radz)		cos(radz)		0	|
	| 0					0			1	|
	*/
	rz[2][2] = 1;
	rz[0][0] = cos(radz);
	rz[0][1] = -sin(radz);
	rz[1][0] = sin(radz);
	rz[1][1] = cos(radz);

}

/*
* rotation matrix of 3 dimension 
*/
vector<vector<double>> MatrixMultiplication(vector<vector<double>> ma, vector<vector<double>> mb){
	int mar = ma.size();
	//ma[mar*mac]
	//mb[mbr*mbc]
	int mac = ma[0].size();
	int mbr = mb.size();
	int mbc = mb[0].size();
	vector<vector<double>> rmab(mar, vector<double>(mbc, 0));
	for (int i = 0; i < mar; i++){
		for (int j = 0; j < mbc; j++){
			for (int k = 0; k < mbr; k++){
				rmab[i][j] += ma[i][k] * mb[k][j];
			}
		}
	}

	return rmab;
}


/*
* Generate 4x4 Translation Matrix
*/
vector<vector<double>> GenerateTranslationMatrix(vector<vector<double>> rmatrix, vector<vector<double>> trans){
	vector<vector<double>> mcam = {
		{ 0, 0, 0, trans[0][0] },
		{ 0, 0, 0, trans[1][0] },
		{ 0, 0, 0, trans[2][0] },
		{ 0, 0, 0, 1 }
	};
	for (int i = 0; i < rmatrix.size(); i++){
		for (int j = 0; j < rmatrix[0].size(); j++){
			mcam[i][j] = rmatrix[i][j];
		}
	}
	return mcam;
}

int main(){
	vector<vector<double>> xyz = { { 0 }, { 0 }, { 0 }, { 1 } };
	cout << "x=";
	cin >> xyz[0][0];
	cout << "y=";
	cin >> xyz[1][0];
	cout << "z=";
	cin >> xyz[2][0];
	vector<vector<double>> trans = { { 0 }, { 8 }, { -12 } };
	double dx = 10;
	double dy = 7;
	double dz = 20;
	//Right-Hand Rule
	CalculateRotationAxis(dx, dy, dz, true);
	vector<vector<double>> rxyzRh = MatrixMultiplication(MatrixMultiplication(rz, ry), rx);
	vector<vector<double>> mcamR = GenerateTranslationMatrix(rxyzRh, trans);
	vector<vector<double>> resultR = MatrixMultiplication(mcamR, xyz);

	//Left-Hand Rule (Right-Hand's clockwise)
	CalculateRotationAxis(dx, dy, dz, false);
	vector<vector<double>> rxyzLh = MatrixMultiplication(MatrixMultiplication(rz, ry), rx);
	vector<vector<double>> mcamL = GenerateTranslationMatrix(rxyzLh, trans);
	vector<vector<double>> resultL = MatrixMultiplication(mcamL, xyz);

	/* for debug
	for (int i = 0; i < mcamL.size(); i++){
	for (int j = 0; j < mcamL[0].size(); j++){
	cout << mcamL[i][j] << ",";
	}
	cout << " " << endl;
	}
	*/
	cout << " " << endl;
	cout << "Left Hand" << endl;
	cout << "x=" << resultL[0][0] << ", y=" << resultL[1][0] << ", z=" << resultL[2][0] << endl;
	cout << " " << endl;
	cout << "Right Hand" << endl;
	cout << "x=" << resultR[0][0] << ", y=" << resultR[1][0] << ", z=" << resultR[2][0] << endl;
	cout << " " << endl;
	
	return 0;
}
