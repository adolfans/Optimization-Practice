#pragma once

#ifndef __VECTOR_H__
#define __VECTOR_H__

#include "xmmintrin.h"
#include "matrix.h"

class Vector3D_SSE
{
	__m128 v;
	Vector3D_SSE operator * ( const Matrix4x4_SSE& ) const;
	void Scale( const Vector3D_SSE& );
};

Vector3D_SSE Vector3D_SSE::operator*( const Matrix4x4_SSE& multiplier ) const
{
	Vector3D_SSE result;
	Matrix4x4_SSE transposedMultiplier;
	transposedMultiplier.v[0] = multiplier.v[0];
	transposedMultiplier.v[1] = multiplier.v[1];
	transposedMultiplier.v[2] = multiplier.v[2];
	transposedMultiplier.v[3] = multiplier.v[3];
	_MM_TRANSPOSE4_PS( transposedMultiplier.v[0], transposedMultiplier.v[1], transposedMultiplier.v[2], transposedMultiplier.v[3] );
	__m128 tmp[4];
	tmp[0] = _mm_mul_ps( v, transposedMultiplier.v[0] );
	tmp[1] = _mm_mul_ps( v, transposedMultiplier.v[1] );
	tmp[2] = _mm_mul_ps( v, transposedMultiplier.v[2] );
	tmp[3] = _mm_mul_ps( v, transposedMultiplier.v[3] );
	_MM_TRANSPOSE4_PS( tmp[0], tmp[1], tmp[2], tmp[3] );
	result.v = _mm_add_ps( tmp[0], tmp[1] );
	result.v = _mm_add_ps( result.v, tmp[2] );
	result.v = _mm_add_ps( result.v, tmp[3] );
}

void Vector3D_SSE::Scale( const Vector3D_SSE& multiplier )
{
	v = _mm_mul_ps( v, multiplier.v );
}

#endif