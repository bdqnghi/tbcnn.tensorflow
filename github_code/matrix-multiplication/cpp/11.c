//----------------------------------------------------------------------
/// \author Group: 20
/// \brief special matric class took from AG02
/// Last Changes: 22.06.2008
//----------------------------------------------------------------------


/************************************************************************/
/* 711.013.EEGS.2007                                                    */
/*                                                                      */
/* Aufgabe 16: Raytracer mit stackbasierter Eingabesprache              */
/* Gruppe G02                                                           */
/*                                                                      */
/* file: Matrix4x4.h                                                    */
/* author(s): ulrich krispel, andreas dolinsek                          */
/************************************************************************/

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
	
	// ==operator
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

	/** \brief returns an element at a specific position */
	inline float getElement(int row, int column) {
		return values[row][column];
	}

	/** alter specific matrix element */
	inline void setElement(int row, int column, float value) {
		values[row][column] = value;
	}

	/** matrix-multiplication */
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

	/** multiply with a scalar */
	inline void scale(float value) {
		for (int y=0; y<4; y++)
			for (int x=0; x<4; x++) {
				values[y][x] *= value;
			}
	}

	/** multiply with a Vector */
	/*
	inline Vec3* multiply(Vec3 &v) {
		double result[4] = { 0 };
		for (int i=0; i<4; i++) {
			for (int j=0; j<3; j++) {
				result[i] += values[i][j] * v[j];
			}
			result[i] += values[i][3];
		}
		// divide out homogeneous factor
		return new Vec3(result[0]/result[3], result[1]/result[3], result[2]/result[3]);
	}
	*/

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
			// divide out homogeneous factor
			return Vec3(result[0]/result[3], result[1]/result[3], result[2]/result[3]);
	}

	/** sets all elements to 0 */
	inline void clear() {
		memset(values, 0, _matrixSize);
	}

	/** makes itself the identity matrix */
	inline void identity() {
		memcpy (values, _values_identity, _matrixSize);
	}

	/** copy matrix contents */
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
