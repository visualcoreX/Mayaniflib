/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#ifndef _BSVERTEXDATA_H_
#define _BSVERTEXDATA_H_

#include "../NIF_IO.h"

// Include structures
#include "HalfVector3.h"
#include "HalfTexCoord.h"
#include "ByteColor4.h"
namespace Niflib {


/*!  */
struct BSVertexData {
	/*! Default Constructor */
	NIFLIB_API BSVertexData();
	/*! Default Destructor */
	NIFLIB_API ~BSVertexData();
	/*! Copy Constructor */
	NIFLIB_API BSVertexData( const BSVertexData & src );
	/*! Copy Operator */
	NIFLIB_API BSVertexData & operator=( const BSVertexData & src );
	/*! Unknown. */
	HalfVector3 vertex;
	/*! Unknown. */
	hfloat dotnormal_;
	/*! Unknown. */
	HalfTexCoord uv;
	/*! Unknown. */
	array<8,byte > unknown8Bytes;
	/*! Unknown. */
	ByteColor4 vertexColors;
	/*! Unknown. */
	array<2,unsigned int > unknown2Ints;
	/*! Unknown. */
	array<4,hfloat > unknown4Halfs;
	/*! Unknown. */
	array<4,byte > unknown4Bytes;
	/*! Unknown. */
	unsigned int unknownInt1;
	/*! Unknown. */
	array<2,unsigned int > unknown2Ints2;
	//--BEGIN MISC CUSTOM CODE--//

	//--END CUSTOM CODE--//
};

}
#endif
