/*$T \GzMatrix.h GC 1.150 2013-11-24 18:03:35 */


/*$6*/
#ifndef _GZMATRIX_H
#define _GZMATRIX_H
#include "Gz.h"
#include <iostream>
using namespace std;
#define degToRad(x) (x*3.14159/180) //Converts Degree to Radians
void setIdentityMatrix(GzMatrix m)
{
	for(int i = 0; i < 4; i=i+1)
		for(int j = 0; j < 4; j=j+1)
			if(i == j)
				m[i][j] = 1;
			else
				m[i][j] = 0;
}

int GzRotXMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along x axis
// Pass back the matrix using mat value
	setIdentityMatrix(mat);
	mat[0][0]=1;
	mat[3][3]=1;
	degree=degToRad(degree);
	mat[1][1]=cos(degree);
	mat[1][2]=-1*sin(degree);
	mat[2][1]=sin(degree);
	mat[2][2]=cos(degree);
	return GZ_SUCCESS;
}
int GzRotYMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along y axis
// Pass back the matrix using mat value
	setIdentityMatrix(mat);
	degree=degToRad(degree);
	mat[0][0]=cos(degree);
	mat[0][2]=sin(degree);
	mat[1][1]=1; mat[3][3]=1;
	mat[2][0]=-1*sin(degree);
	mat[2][2]=cos(degree);
	return GZ_SUCCESS;
}
int GzRotZMat(float degree, GzMatrix mat)
{
// Create rotate matrix : rotate along z axis
// Pass back the matrix using mat value
	setIdentityMatrix(mat);
	degree=degToRad(degree);
	mat[0][0]=cos(degree);
	mat[0][1]=-1*sin(degree);
	mat[1][0]=sin(degree);
	mat[1][1]=cos(degree);
	mat[2][2]=mat[3][3]=1;

	return GZ_SUCCESS;
}
bool isIdentityMatrix(GzMatrix m)
{
	for(int i = 0; i < 4; i=i+1)
		for(int j = 0; j < 4; j=j+1)
		{
			if(i == j && m[i][j] != 1)
				return false;
			else if(i!=j && m[i][j] != 0)
				return false;
		}

	return true;
}

/* */
void transformVertices(GzCoord c,GzMatrix m){
	if(isIdentityMatrix(m))
		return;
	float b[4];
	float a[4];a[0]=c[0];a[1]=c[1];a[2]=c[2];a[3]=1;
	for(int j=0;j<4;j=j+1)
	{
			b[j]=0;
			for(int k=0;k<4;k=k+1)
			{
				b[j]+=a[k]*m[j][k];
			}
			
	}
		
		c[0]=b[0];
		c[1]=b[1];
		c[2]=b[2];
}
void copyMatrices(GzMatrix m1, GzMatrix m2)
{
	for(int i = 0; i < 4; i=i+1)
		for(int j = 0; j < 4; j=j+1) 
			m1[i][j] = m2[i][j];
}

/* */
/* */
void matrixMultiplication(GzMatrix T, GzMatrix R, GzMatrix result)
{
	if(isIdentityMatrix(R))
	{
		copyMatrices(result, T);
		return;
	}

	if(isIdentityMatrix(T))
	{
		copyMatrices(result, R);
		return;
	}
	for(int i = 0; i < 4; i=i+1)
	{
		for(int j = 0; j < 4; j=j+1)
		{
			result[i][j] = 0;
			for(int k = 0; k < 4; k=k+1)
			{
				result[i][j] += T[i][k] * R[k][j];
			}
		}
	}
}

/* */
void matrixMultiplication(GzMatrix M, GzMatrix T, GzMatrix R, GzMatrix result)
{
	if(isIdentityMatrix(R))
	{
		matrixMultiplication(M, T, result);
		return;
	}
	if(isIdentityMatrix(T))
	{
		matrixMultiplication(M, R, result);
		return;
	}
	GzMatrix	temp;
	matrixMultiplication(M, T, temp);
	matrixMultiplication( temp,R, result);
}

/* */

/* */
void addTranslationMatrix(GzMatrix m, GzCoord c)
{
	m[0][3] += c[0];
	m[1][3] += c[1];
	m[2][3] += c[2];
}

/* */

/* */
void inverseTranslateCopyMatrix(GzMatrix m1, GzMatrix m2)
{
	for(int i = 0; i < 4; i=i+1)
		for(int j = 0; j < 4; j=j+1) m1[i][j] = m2[i][j];
	m1[0][3] *= -1;
	m1[1][3] *= -1;
	m1[2][3] *= -1;
}

/* */
void printMatrix(GzMatrix TM)
{
	cout << TM[0][0] << " " << TM[0][1] << " " << TM[0][2] << " " << TM[0][3] << endl;
	cout << TM[1][0] << " " << TM[1][1] << " " << TM[1][2] << " " << TM[1][3] << endl;
	cout << TM[2][0] << " " << TM[2][1] << " " << TM[2][2] << " " << TM[2][3] << endl;
	cout << TM[3][0] << " " << TM[3][1] << " " << TM[3][2] << " " << TM[3][3] << endl;
	cout << endl << endl;
}

/* */
void copyGzCoord(GzCoord c1, GzCoord c2)
{
	c1[0] = c2[0];
	c1[1] = c2[1];
	c1[2] = c2[2];
}

/* */
void initializeGzCoord(GzCoord n)
{
	n[0] = n[1] = n[2] = 0;
}

/* */
void addGzCoords(GzCoord c1, GzCoord c2)
{
	c1[0] += c2[0];
	c1[1] += c2[1];
	c1[2] += c2[2];
}

/* */
void scalarGzCoord(GzCoord n, float a)
{
	n[0] *= a;
	n[1] *= a;
	n[2] *= a;
}

/* */
void normalizeGzCoord(GzCoord n)
{
	float	d = sqrt(n[0] * n[0] + n[1] * n[1] + n[2] * n[2]);
	n[0] /= d;
	n[1] /= d;
	n[2] /= d;
}
#endif
