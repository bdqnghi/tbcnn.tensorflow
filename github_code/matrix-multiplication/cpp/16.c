#include "stdio.h"
#include "WolframLibrary.h"

EXTERN_C DLLEXPORT mint WolframLibrary_getVersion( ) { return WolframLibraryVersion; }
EXTERN_C DLLEXPORT int WolframLibrary_initialize( WolframLibraryData libData) { return 0; }
EXTERN_C DLLEXPORT void WolframLibrary_uninitialize( WolframLibraryData libData) { return; }

EXTERN_C DLLEXPORT int MatrixMultiplication(WolframLibraryData libData, mint Argc, MArgument *Args, MArgument Res) {
	MTensor x,y,z;
	mint xrank, yrank;
	mint const* xdims;
	mint const* ydims;
	mint zdims[2], pos[2];
	mreal* zdata;
	mint row,col,rows,cols,i;
	mreal a,b;
	int err;

	x = MArgument_getMTensor(Args[0]);
	xrank = libData->MTensor_getRank(x);
	xdims = libData->MTensor_getDimensions(x);
	//printf("x rows: %lli\n", xdims[0]);
	//printf("x cols: %lli\n", xdims[1]);

	y = MArgument_getMTensor(Args[1]);
	yrank = libData->MTensor_getRank(y);
	ydims = libData->MTensor_getDimensions(y);
	//printf("y rows: %lli\n", ydims[0]);
	//printf("y cols: %lli\n", ydims[1]);

	zdims[0] = xdims[0];
	zdims[1] = ydims[1];
	//printf("z rows: %lli\n", zdims[0]);
	//printf("z cols: %lli\n", zdims[1]);

	err = libData->MTensor_new( MType_Real, 2, zdims, &z);
	zdata = libData->MTensor_getRealData(z);

  rows=zdims[0];
	cols=zdims[1];
	//printf("rows: %lli\n",rows);
	//printf("cols: %lli\n",cols);

	for(row=0; row<rows; row++) {
		for(col=0; col<cols; col++ ) {
			zdata[ col+cols*row ] = 0.0;
			for(i=0; i<xdims[1]; i++ ) {
				pos[0] = row+1;
				pos[1] = i+1;
				err = libData->MTensor_getReal(x,pos,&a);
				//printf("a: %g\n", a);
				pos[0] = i+1;
				pos[1] = col+1;
				err = libData->MTensor_getReal(y,pos,&b);
				//printf("b: %g\n", b);
				zdata[ col+cols*row ] += a * b;
				//printf("zdata: %g\n", zdata[col+cols*row]);
			}
		}
	}


	MArgument_setMTensor(Res,z);
	return LIBRARY_NO_ERROR;
}
