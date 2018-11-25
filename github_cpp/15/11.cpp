
















#ifndef __MATRIX4X4_H_
#define __MATRIX4X4_H_

#include <memory.h>
#include "Vec3.h"

#define mPI 3.14159265358979323846

class Matrix4x4 {
private:
	float values[4][4];
	const static int _matrixSize;
	const static float _values_identity[];

public:
	Matrix4x4() {	
		identity();
	}
	
	
	friend bool operator==(const Matrix4x4& M1, const Matrix4x4& M2){
		bool retValue = true;		
		for (int y=0; y<4; y++) {
			for (int x=0; x<4; x++) {
				if (M1.values[y][x] != M2.values[y][x])
					retValue = false;
			}
		}
		return retValue;
	}

	
	inline float getElement(int row, int column) {
		return values[row][column];
	}

	
	inline void setElement(int row, int column, float value) {
		values[row][column] = value;
	}

	
	inline void multiply(Matrix4x4 &matrix)  {
		int y,x,i;
		Matrix4x4 tmpMatrix;

		for (y=0; y<4; y++)
			for (x=0; x<4; x++) {
				float result=0;
				for (i=0; i<4; i++) {
					result += values[y][i] * matrix.values[i][x];
				}
				tmpMatrix.setElement(y,x,result);
			}
		(*this) = tmpMatrix;
	}

	
	inline void scale(float value) {
		for (int y=0; y<4; y++)
			for (int x=0; x<4; x++) {
				values[y][x] *= value;
			}
	}

	
	

	friend Vec3
		operator*(const Matrix4x4& m,
		const Vec3& v) {
			float result[4] = { 0 };
			for (int i=0; i<4; i++) {
				for (int j=0; j<3; j++) {
					result[i] += m.values[i][j] * v.val[j];
				}
				result[i] += m.values[i][3];
			}
			
			return Vec3(result[0]/result[3], result[1]/result[3], result[2]/result[3]);
	}

	
	inline void clear() {
		memset(values, 0, _matrixSize);
	}

	
	inline void identity() {
		memcpy (values, _values_identity, _matrixSize);
	}

	
	inline Matrix4x4 & operator=(const Matrix4x4 &from) {
		memcpy(values, from.values, _matrixSize);
		return *this;
	}

	Matrix4x4 inverse();
	float determinant();
	
	static Matrix4x4 createTranslation(float tx, float ty, float tz);
	static Matrix4x4 createScale(float sx, float sy, float sz);
	static Matrix4x4 createUniformScale(float s);
	static Matrix4x4 createRotX(float theta);
	static Matrix4x4 createRotY(float theta);
	static Matrix4x4 createRotZ(float theta);

};

#endif
