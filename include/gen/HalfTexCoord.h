/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

#ifndef _HALFTEXCOORD_H_
#define _HALFTEXCOORD_H_

#include "../NIF_IO.h"

namespace Niflib {

/*! Texture coordinates (u,v) stored as half floats. */
struct HalfTexCoord {
	/*! Default Constructor */
	NIFLIB_API HalfTexCoord() : u((hfloat)0), v((hfloat)0) {}
	/*! Default Destructor */
	NIFLIB_API ~HalfTexCoord() {}
	/*! Copy Constructor */
	NIFLIB_API HalfTexCoord( const HalfTexCoord & src ) { *this = src; }
	/*! Copy Operator */
	NIFLIB_API HalfTexCoord & operator=( const HalfTexCoord & src ) {
		u = src.u;
		v = src.v;
		return *this;
	}
	/*! First coordinate. */
	hfloat u;
	/*! Second coordinate. */
	hfloat v;
};

}

#endif

