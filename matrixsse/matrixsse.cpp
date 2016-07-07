// matrixsse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "matrix.h"

int _tmain(int argc, _TCHAR* argv[])
{
	Matrix4x4_SSE testIdentity;
	//testIdentity.Set( 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 );

	testIdentity.Set( 0.16544487, -0.98621905, 0.00000000, 0,
						0.98621905, 0.16544487, 0.00000000, 0,
						0, 0, 1, 0,
						0, 0, 0, 1 );

	Matrix4x4_SSE testSomeMatrix;
	testSomeMatrix.Set( 1, 0, 0, 0, 0, 3.1391647e-007, 1, 0, 0, -1, 3.1391647e-007, 0, 0, 0, 0, 1 );

	testSomeMatrix *= testIdentity;

	//test
	///ttttttttttttt
	testSomeMatrix.Print();
	return 0;
}

