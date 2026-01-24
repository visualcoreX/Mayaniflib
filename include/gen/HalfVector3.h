/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _HALFVECTOR3_H_
#define _HALFVECTOR3_H_

#include "../NIF_IO.h"

namespace Niflib {

/*! A vector in 3D space (x,y,z) stored as half floats. */
struct HalfVector3 {
	/*! Default Constructor */
	NIFLIB_API HalfVector3() : x((hfloat)0), y((hfloat)0), z((hfloat)0) {}
	/*! Default Destructor */
	NIFLIB_API ~HalfVector3() {}
	/*! Copy Constructor */
	NIFLIB_API HalfVector3( const HalfVector3 & src ) { *this = src; }
	/*! Copy Operator */
	NIFLIB_API HalfVector3 & operator=( const HalfVector3 & src ) {
		x = src.x;
		y = src.y;
		z = src.z;
		return *this;
	}
	/*! First coordinate. */
	hfloat x;
	/*! Second coordinate. */
	hfloat y;
	/*! Third coordinate. */
	hfloat z;
};

}

#endif

