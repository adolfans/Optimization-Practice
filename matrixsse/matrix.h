#pragma once

#ifndef __MATRIX_H__
#define __MATRIX_H__
#include "xmmintrin.h"

class Matrix4x4_SSE
{
public:
	__m128	v[4];
	inline void Identify();
	inline void FromAlignedMemory( float* );
	inline void ToAlignedMemory( float* ) const;
	inline void operator *= ( const Matrix4x4_SSE& );
	inline Matrix4x4_SSE operator * ( const Matrix4x4_SSE& ) const;
	inline void Set( const float xx, const float xy, const float xz, const float xw,
		const float yx, const float yy, const float yz, const float yw,
		const float zx, const float zy, const float zz, const float zw,
		const float wx, const float wy, const float wz, const float ww );
	inline void Print();
};

void Matrix4x4_SSE::Identify()
{
	__declspec(align(16)) float matrix[16]
	= { 1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1 };
	v[0] = _mm_load_ps( &matrix[0] );
	v[1] = _mm_load_ps( &matrix[4] );
	v[2] = _mm_load_ps( &matrix[8] );
	v[3] = _mm_load_ps( &matrix[12] );
}

void Matrix4x4_SSE::FromAlignedMemory( float* ptr )
{
	v[0] = _mm_load_ps( &ptr[0] );
	v[1] = _mm_load_ps( &ptr[4] );
	v[2] = _mm_load_ps( &ptr[8] );
	v[3] = _mm_load_ps( &ptr[12] );
}

void Matrix4x4_SSE::ToAlignedMemory( float* ptr ) const
{
	_mm_store_ps( &ptr[0] , v[0] );
	_mm_store_ps( &ptr[4] , v[1] );
	_mm_store_ps( &ptr[8] , v[2] );
	_mm_store_ps( &ptr[12], v[3] );
}

void Matrix4x4_SSE::Set( const float xx, const float xy, const float xz, const float xw,
	const float yx, const float yy, const float yz, const float yw,
	const float zx, const float zy, const float zz, const float zw,
	const float wx, const float wy, const float wz, const float ww )
{
	__declspec(align(16)) float matrix[16] = { xx, xy, xz, xw,
		yx, yy, yz, yw,
		zx, zy, zz, zw,
		wx, wy, wz, ww };
	v[0] = _mm_load_ps( &matrix[0] );
	v[1] = _mm_load_ps( &matrix[4] );
	v[2] = _mm_load_ps( &matrix[8] );
	v[3] = _mm_load_ps( &matrix[12] );
}

void Matrix4x4_SSE::operator *= ( const Matrix4x4_SSE& multiplier )
{
	*this = *this * multiplier;
}

Matrix4x4_SSE Matrix4x4_SSE::operator *( const Matrix4x4_SSE& multiplier ) const
{
	Matrix4x4_SSE result;
	Matrix4x4_SSE transposedMultiplier;
	transposedMultiplier.v[0] = multiplier.v[0];
	transposedMultiplier.v[1] = multiplier.v[1];
	transposedMultiplier.v[2] = multiplier.v[2];
	transposedMultiplier.v[3] = multiplier.v[3];
	_MM_TRANSPOSE4_PS( transposedMultiplier.v[0], transposedMultiplier.v[1], transposedMultiplier.v[2], transposedMultiplier.v[3] );
	for( int i = 0; i != 4; ++ i )
	{
		__m128 tmp[4];
		tmp[0] = _mm_mul_ps( v[i], transposedMultiplier.v[0] );
		tmp[1] = _mm_mul_ps( v[i], transposedMultiplier.v[1] );
		tmp[2] = _mm_mul_ps( v[i], transposedMultiplier.v[2] );
		tmp[3] = _mm_mul_ps( v[i], transposedMultiplier.v[3] );
		_MM_TRANSPOSE4_PS( tmp[0], tmp[1], tmp[2], tmp[3] );
		result.v[i] = _mm_add_ps( tmp[0], tmp[1] );
		result.v[i] = _mm_add_ps( result.v[i], tmp[2] );
		result.v[i] = _mm_add_ps( result.v[i], tmp[3] );
	}

	return result;
}

void Matrix4x4_SSE::Print()
{
	__declspec(align(16)) float  matrix[16];
	_mm_store_ps( &matrix[0], v[0] );
	_mm_store_ps( &matrix[4], v[1] );
	_mm_store_ps( &matrix[8], v[2] );
	_mm_store_ps( &matrix[12], v[3] );
	printf( "%f,\t%f,\t%f,\t%f\n%f,\t%f,\t%f,\t%f\n%f,\t%f,\t%f,\t%f\n%f, %f, %f, %f\n", 
		matrix[0],
		matrix[1],
		matrix[2],
		matrix[3],
		matrix[4],
		matrix[5],
		matrix[6],
		matrix[7],
		matrix[8],
		matrix[9],
		matrix[10],
		matrix[11],
		matrix[12],
		matrix[13],
		matrix[14],
		matrix[15]);
}
  

class Matrix3x3_SSE
{
public:
	__m128	v[3];
	Matrix3x3_SSE operator * ( const Matrix3x3_SSE& ) const;
};

Matrix3x3_SSE Matrix3x3_SSE::operator *( const Matrix3x3_SSE& multiplier ) const
{
	Matrix3x3_SSE result;
	Matrix4x4_SSE transposedMultiplier;
	transposedMultiplier.v[0] = multiplier.v[0];
	transposedMultiplier.v[1] = multiplier.v[1];
	transposedMultiplier.v[2] = multiplier.v[2];
	//transposedMultiplier.v[3] = multiplier.v[3];
	_MM_TRANSPOSE4_PS( transposedMultiplier.v[0], transposedMultiplier.v[1], transposedMultiplier.v[2], transposedMultiplier.v[3] );
	for( int i = 0; i != 3; ++ i )
	{
		__m128 tmp[4];
		tmp[0] = _mm_mul_ps( v[i], transposedMultiplier.v[0] );
		tmp[1] = _mm_mul_ps( v[i], transposedMultiplier.v[1] );
		tmp[2] = _mm_mul_ps( v[i], transposedMultiplier.v[2] );
		//tmp[3] = _mm_mul_ps( v[i], transposedMultiplier.v[3] );
		_MM_TRANSPOSE4_PS( tmp[0], tmp[1], tmp[2], tmp[3] );
		result.v[i] = _mm_add_ps( tmp[0], tmp[1] );
		result.v[i] = _mm_add_ps( result.v[i], tmp[2] );
	}
	return result;
}


#endif
