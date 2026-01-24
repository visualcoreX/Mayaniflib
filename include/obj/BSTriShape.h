/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

#ifndef _BSTRISHAPE_H_
#define _BSTRISHAPE_H_

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "BSShape.h"

// Include structures
#include "../Ref.h"
#include "../gen/BSVertexData.h"
namespace Niflib {

// Forward define of referenced NIF objects
class NiObject;
class NiProperty;
class BSTriShape;
typedef Ref<BSTriShape> BSTriShapeRef;

/*! Fallout 4 */
class BSTriShape : public BSShape {
public:
	/*! Constructor */
	NIFLIB_API BSTriShape();

	/*! Destructor */
	NIFLIB_API virtual ~BSTriShape();

	/*!
	 * A constant value which uniquly identifies objects of this type.
	 */
	NIFLIB_API static const Type TYPE;

	/*!
	 * A factory function used during file reading to create an instance of this type of object.
	 * \return A pointer to a newly allocated instance of this type of object.
	 */
	NIFLIB_API static NiObject * Create();

	/*!
	 * Summarizes the information contained in this object in English.
	 * \param[in] verbose Determines whether or not detailed information about large areas of data will be printed out.
	 * \return A string containing a summary of the information within the object in English.  This is the function that Niflyze calls to generate its analysis, so the output is the same.
	 */
	NIFLIB_API virtual string asString( bool verbose = false ) const;

	/*!
	 * Used to determine the type of a particular instance of this object.
	 * \return The type constant for the actual type of the object.
	 */
	NIFLIB_API virtual const Type & GetType() const;

	//--BEGIN MISC CUSTOM CODE--//
	NIFLIB_API const vector<BSVertexData> & GetVertexData() const;
	NIFLIB_API const vector<Triangle> & GetTriangles() const;
	NIFLIB_API byte GetVertexFlags1() const;
	NIFLIB_API Niflib::array<2,Ref<NiProperty> > GetBSProperties() const;

	//--END CUSTOM CODE--//
protected:
	/*! Unknown. */
	array<4,float > unknown4Floats;
	/*! Unknown. */
	Ref<NiObject > skin;
	/*! Unknown. */
	array<2,Ref<NiProperty > > bsProperties;
	/*! Unknown. */
	byte vertexflag1;
	/*! Unknown. */
	byte vertexflag2;
	/*! Unknown. */
	byte vertexflag3;
	/*! Unknown. */
	byte vertexflag4;
	/*! Unknown. */
	byte vertexflag5;
	/*! Unknown. */
	byte vertexflag6;
	/*! Unknown. */
	byte vertexflag7;
	/*! Unknown. */
	byte vertexflag8;
	/*! Unknown. */
	mutable unsigned int numTriangles;
	/*! Unknown. */
	mutable unsigned short numVertices;
	/*! Unknown. */
	unsigned int dataSize;
	/*! Unknown. */
	vector<BSVertexData > vertexData;
	/*! Unknown. */
	vector<Triangle > triangles;
public:
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info );
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual void FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info );
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObjectRef> GetRefs() const;
	/*! NIFLIB_HIDDEN function.  For internal use only. */
	NIFLIB_HIDDEN virtual list<NiObject *> GetPtrs() const;
};

//--BEGIN FILE FOOT CUSTOM CODE--//

//--END CUSTOM CODE--//

} //End Niflib namespace
#endif
