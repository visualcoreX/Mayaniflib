/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//---THIS FILE WAS AUTOMATICALLY GENERATED.  DO NOT EDIT---//

//To change this file, alter the niftools/docsys/gen_niflib.py Python script.

#include "../../include/gen/BSVertexData.h"
#include "../../include/gen/HalfVector3.h"
#include "../../include/gen/HalfTexCoord.h"
#include "../../include/gen/ByteColor4.h"
using namespace Niflib;

//Constructor
BSVertexData::BSVertexData() : dotnormal_((hfloat)0), unknownInt1((unsigned int)0) {};

//Copy Constructor
BSVertexData::BSVertexData( const BSVertexData & src ) {
	*this = src;
};

//Copy Operator
BSVertexData & BSVertexData::operator=( const BSVertexData & src ) {
	this->vertex = src.vertex;
	this->dotnormal_ = src.dotnormal_;
	this->uv = src.uv;
	this->unknown8Bytes = src.unknown8Bytes;
	this->vertexColors = src.vertexColors;
	this->unknown2Ints = src.unknown2Ints;
	this->unknown4Halfs = src.unknown4Halfs;
	this->unknown4Bytes = src.unknown4Bytes;
	this->unknownInt1 = src.unknownInt1;
	this->unknown2Ints2 = src.unknown2Ints2;
	return *this;
};

//Destructor
BSVertexData::~BSVertexData() {};

//--BEGIN MISC CUSTOM CODE--//

//--END CUSTOM CODE--//
