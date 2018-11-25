











#if (_MSC_VER > 1000) || defined(SGI_COMPILER)
#pragma once
#endif





#ifndef _MATRIXMN_H_
#define _MATRIXMN_H_




#include "SIBCMathLib.h"







class XSICOREEXPORT CSIBCMatrixMNd
{
	
	public:

		
		
		

		
		CSIBCMatrixMNd();

		
		 ~CSIBCMatrixMNd();

		
		
		

		
		bool SetDimensions(const int in_M, const int in_N);

		
		bool Set( const CSIBCMatrixMNd& in_mat);

		
		void Copy( const CSIBCMatrixMNd& in_mat);

		
		CSIBCMatrixMNd& Transpose(const CSIBCMatrixMNd& in_mat);

		
		
		

		
		int GetNbRow( void ) const;

		
		int GetNbCol( void ) const;

		
		double Get( const int in_nRow, const int in_nCol ) const;

		
		
		
		
		
		void Set( int in_nRow, int in_nCol, const double in_dVal );

		
		void SetIdentity( void );

		
		
		

		
		CSIBCMatrixMNd& Mul( const CSIBCMatrixMNd& in_mat1, const CSIBCMatrixMNd& in_mat2 );

		
		bool Mul( const CSIBCMatrixMNd& in_mat );

		
		bool LeftMul( const CSIBCMatrixMNd& in_mat );

		
		bool GrevilleInverse(const CSIBCMatrixMNd& in_mat);

		
		bool GrevilleInverse(const CSIBCMatrixMNd& in_mat, const unsigned int in_NbRow,	const unsigned int in_NbCol);

		
		CSIBCMatrixMNd& Add( const CSIBCMatrixMNd& in_mat1, const CSIBCMatrixMNd& in_mat2);

		
		CSIBCMatrixMNd& Sub( const CSIBCMatrixMNd& in_mat1, const CSIBCMatrixMNd& in_mat2);

		
		CSIBCMatrixMNd& Add( const CSIBCMatrixMNd& in_mat );

		
		CSIBCMatrixMNd& Sub( const CSIBCMatrixMNd& in_mat );

	
	protected:

		
		
		

	
	private:
		
		
		

		
		void InverseVector(double *in_pdVct, double * out_pdInvVct, int in_len);

		
		double SumAbsVal( double *in_pdVct, int in_len);

		
		
		

		
		int m_nRow;

		
		int m_nCol;

		
		double**	m_dMatrixMN;

		
		
		

		
		CSIBCMatrixMNd ( const CSIBCMatrixMNd& in_matrix );

		
		CSIBCMatrixMNd& operator =( const CSIBCMatrixMNd& in_matrix );
};

#endif 
