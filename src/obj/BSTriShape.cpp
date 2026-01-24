/* Copyright (c) 2006, NIF File Format Library and Tools
All rights reserved.  Please see niflib.h for license. */

//-----------------------------------NOTICE----------------------------------//
// Some of this file is automatically filled in by a Python script.  Only    //
// add custom code in the designated areas or it will be overwritten during  //
// the next update.                                                          //
//-----------------------------------NOTICE----------------------------------//

//--BEGIN FILE HEAD CUSTOM CODE--//

//--END CUSTOM CODE--//

#include "../../include/FixLink.h"
#include "../../include/ObjectRegistry.h"
#include "../../include/NIF_IO.h"
#include "../../include/obj/BSTriShape.h"
#include "../../include/gen/BSVertexData.h"
#include "../../include/gen/HalfVector3.h"
#include "../../include/gen/HalfTexCoord.h"
#include "../../include/gen/ByteColor4.h"
#include "../../include/obj/NiObject.h"
#include "../../include/obj/NiProperty.h"
#include "../../include/nif_math.h"
#include <algorithm>
#include <cstring>
using namespace Niflib;

//Definition of TYPE constant
const Type BSTriShape::TYPE("BSTriShape", &BSShape::TYPE );

BSTriShape::BSTriShape() : skin(NULL), vertexflag1((byte)0), vertexflag2((byte)0), vertexflag3((byte)0), vertexflag4((byte)0), vertexflag5((byte)0), vertexflag6((byte)0), vertexflag7((byte)0), vertexflag8((byte)0), numTriangles((unsigned int)0), numVertices((unsigned short)0), dataSize((unsigned int)0) {
	//--BEGIN CONSTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

BSTriShape::~BSTriShape() {
	//--BEGIN DESTRUCTOR CUSTOM CODE--//

	//--END CUSTOM CODE--//
}

const Type & BSTriShape::GetType() const {
	return TYPE;
}

NiObject * BSTriShape::Create() {
	return new BSTriShape;
}

void BSTriShape::Read( istream& in, list<unsigned int> & link_stack, const NifInfo & info ) {
	//--BEGIN PRE-READ CUSTOM CODE--//

	//--END CUSTOM CODE--//

	unsigned int block_num;
	BSShape::Read( in, link_stack, info );
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknown4Floats[i1], in, info );
	};
	NifStream( block_num, in, info );
	link_stack.push_back( block_num );
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		NifStream( block_num, in, info );
		link_stack.push_back( block_num );
	};
	NifStream( vertexflag1, in, info );
	NifStream( vertexflag2, in, info );
	NifStream( vertexflag3, in, info );
	NifStream( vertexflag4, in, info );
	NifStream( vertexflag5, in, info );
	NifStream( vertexflag6, in, info );
	NifStream( vertexflag7, in, info );
	NifStream( vertexflag8, in, info );
	NifStream( numTriangles, in, info );
	NifStream( numVertices, in, info );
	NifStream( dataSize, in, info );
	if ( (dataSize > 0) ) {
		const std::streampos dataStart = in.tellg();
		in.seekg(0, std::ios::end);
		const std::streampos dataEnd = in.tellg();
		in.seekg(dataStart, std::ios::beg);
		const size_t remaining = (dataEnd > dataStart) ? static_cast<size_t>(dataEnd - dataStart) : 0;

		size_t expectedPerVertex = 8; // HalfVector3 + dotnormal
		if ( vertexflag1 != 4 ) {
			expectedPerVertex += 4; // uv
		}
		if ( vertexflag1 > 3 ) {
			expectedPerVertex += 8;
		}
		if ( vertexflag1 == 6 ) {
			expectedPerVertex += 4;
		}
		if ( vertexflag1 == 7 ) {
			expectedPerVertex += 8;
		}
		if ( vertexflag1 >= 8 ) {
			expectedPerVertex += 12; // 4 halfs + 4 bytes
		}
		if ( vertexflag1 == 9 ) {
			expectedPerVertex += 4;
		}
		if ( vertexflag1 == 10 ) {
			expectedPerVertex += 8;
		}

		const size_t expectedVertexBytes = static_cast<size_t>(numVertices) * expectedPerVertex;
		const size_t expectedTriangleBytes = static_cast<size_t>(numTriangles) * 6;
		const size_t expectedTotal = expectedVertexBytes + expectedTriangleBytes;
		const bool useFallback = expectedTotal > remaining;
		bool trianglesFromRaw = false;

		if ( !useFallback ) {
			vertexData.resize(numVertices);
			for (unsigned int i2 = 0; i2 < vertexData.size(); i2++) {
				NifStream( vertexData[i2].vertex.x, in, info );
				NifStream( vertexData[i2].vertex.y, in, info );
				NifStream( vertexData[i2].vertex.z, in, info );
				NifStream( vertexData[i2].dotnormal_, in, info );
				if ( (vertexflag1 != 4) ) {
					NifStream( vertexData[i2].uv.u, in, info );
					NifStream( vertexData[i2].uv.v, in, info );
				};
				if ( (vertexflag1 > 3) ) {
					for (unsigned int i4 = 0; i4 < 8; i4++) {
						NifStream( vertexData[i2].unknown8Bytes[i4], in, info );
					};
				};
				if ( (vertexflag1 == 6) ) {
					NifStream( vertexData[i2].vertexColors.r, in, info );
					NifStream( vertexData[i2].vertexColors.g, in, info );
					NifStream( vertexData[i2].vertexColors.b, in, info );
					NifStream( vertexData[i2].vertexColors.a, in, info );
				};
				if ( (vertexflag1 == 7) ) {
					for (unsigned int i4 = 0; i4 < 2; i4++) {
						NifStream( vertexData[i2].unknown2Ints[i4], in, info );
					};
				};
				if ( (vertexflag1 >= 8) ) {
					for (unsigned int i4 = 0; i4 < 4; i4++) {
						NifStream( vertexData[i2].unknown4Halfs[i4], in, info );
					};
					for (unsigned int i4 = 0; i4 < 4; i4++) {
						NifStream( vertexData[i2].unknown4Bytes[i4], in, info );
					};
				};
				if ( (vertexflag1 == 9) ) {
					NifStream( vertexData[i2].unknownInt1, in, info );
				};
				if ( (vertexflag1 == 10) ) {
					for (unsigned int i4 = 0; i4 < 2; i4++) {
						NifStream( vertexData[i2].unknown2Ints2[i4], in, info );
					};
				};
			};
		} else {
			const size_t triangleBytesMax = remaining;
			size_t vertexBytes = std::min(static_cast<size_t>(dataSize), triangleBytesMax);
			size_t maxTrianglesByRemaining = 0;
			if ( triangleBytesMax > vertexBytes ) {
				maxTrianglesByRemaining = (triangleBytesMax - vertexBytes) / 6;
			}
			if ( numTriangles > maxTrianglesByRemaining ) {
				numTriangles = static_cast<unsigned int>(maxTrianglesByRemaining);
			}

			std::vector<unsigned char> raw(vertexBytes);
			if ( vertexBytes > 0 ) {
				in.read(reinterpret_cast<char*>(raw.data()), vertexBytes);
			}

			vertexData.resize(numVertices);
			const size_t stride = (numVertices > 0) ? (vertexBytes / numVertices) : 0;
			const bool useFloatPos = stride >= 12;
			const bool useHalfPos = !useFloatPos && stride >= 6;

			auto readFloat = [](const unsigned char* ptr) {
				float value = 0.0f;
				std::memcpy(&value, ptr, sizeof(float));
				return value;
			};

			auto readHalf = [](const unsigned char* ptr) {
				hfloat value = 0;
				std::memcpy(&value, ptr, sizeof(hfloat));
				return HalfToFloat(value);
			};

			auto scoreUVOffsetFloat = [&](size_t offset) {
				if ( offset + 8 > stride ) {
					return static_cast<size_t>(0);
				}
				const size_t sampleCount = std::min(static_cast<size_t>(numVertices), static_cast<size_t>(16));
				size_t score = 0;
				for ( size_t i = 0; i < sampleCount; ++i ) {
					const unsigned char* v = raw.data() + i * stride + offset;
					const float u = readFloat(v);
					const float vcoord = readFloat(v + 4);
					if ( std::isfinite(u) && std::isfinite(vcoord) && u > -2.0f && u < 2.0f && vcoord > -2.0f && vcoord < 2.0f ) {
						++score;
					}
				}
				return score;
			};

			auto scoreUVOffsetHalf = [&](size_t offset) {
				if ( offset + 4 > stride ) {
					return static_cast<size_t>(0);
				}
				const size_t sampleCount = std::min(static_cast<size_t>(numVertices), static_cast<size_t>(16));
				size_t score = 0;
				for ( size_t i = 0; i < sampleCount; ++i ) {
					const unsigned char* v = raw.data() + i * stride + offset;
					const float u = readHalf(v);
					const float vcoord = readHalf(v + 2);
					if ( std::isfinite(u) && std::isfinite(vcoord) && u > -2.0f && u < 2.0f && vcoord > -2.0f && vcoord < 2.0f ) {
						++score;
					}
				}
				return score;
			};

			size_t uvOffset = static_cast<size_t>(-1);
			bool uvIsFloat = false;
			if ( stride >= 20 ) {
				const size_t candidates[] = { 12, 16, 20, 24 };
				size_t bestScore = 0;
				for ( size_t candidate : candidates ) {
					size_t score = scoreUVOffsetFloat(candidate);
					if ( score > bestScore ) {
						bestScore = score;
						uvOffset = candidate;
						uvIsFloat = true;
					}
				}
			}
			if ( uvOffset == static_cast<size_t>(-1) && stride >= 10 ) {
				const size_t candidates[] = { 8, 10, 12, 14 };
				size_t bestScore = 0;
				for ( size_t candidate : candidates ) {
					size_t score = scoreUVOffsetHalf(candidate);
					if ( score > bestScore ) {
						bestScore = score;
						uvOffset = candidate;
						uvIsFloat = false;
					}
				}
			}

			for ( unsigned int i2 = 0; i2 < numVertices; ++i2 ) {
				if ( stride == 0 ) {
					break;
				}
				const unsigned char* v = raw.data() + static_cast<size_t>(i2) * stride;
				float x = 0.0f;
				float y = 0.0f;
				float z = 0.0f;
				if ( useFloatPos ) {
					x = readFloat(v);
					y = readFloat(v + 4);
					z = readFloat(v + 8);
				} else if ( useHalfPos ) {
					x = readHalf(v);
					y = readHalf(v + 2);
					z = readHalf(v + 4);
				}

				vertexData[i2].vertex.x = FloatToHalf(x);
				vertexData[i2].vertex.y = FloatToHalf(y);
				vertexData[i2].vertex.z = FloatToHalf(z);

				if ( uvOffset != static_cast<size_t>(-1) && uvOffset + 4 <= stride ) {
					float u = 0.0f;
					float vcoord = 0.0f;
					if ( uvIsFloat ) {
						u = readFloat(v + uvOffset);
						vcoord = readFloat(v + uvOffset + 4);
					} else {
						u = readHalf(v + uvOffset);
						vcoord = readHalf(v + uvOffset + 2);
					}
					vertexData[i2].uv.u = FloatToHalf(u);
					vertexData[i2].uv.v = FloatToHalf(vcoord);
				}
			}

			if ( stride > 0 ) {
				const size_t vertexSectionBytes = stride * static_cast<size_t>(numVertices);
				if ( vertexSectionBytes < vertexBytes ) {
					const size_t rawTriangleBytes = vertexBytes - vertexSectionBytes;
					const size_t rawTriangleCount = rawTriangleBytes / 6;
					if ( rawTriangleCount > 0 ) {
						trianglesFromRaw = true;
						const size_t triangleCount = std::min(static_cast<size_t>(numTriangles), rawTriangleCount);
						triangles.resize(static_cast<unsigned int>(triangleCount));
						const unsigned char* triPtr = raw.data() + vertexSectionBytes;
						for ( size_t t = 0; t < triangleCount; ++t ) {
							const unsigned char* p = triPtr + t * 6;
							triangles[static_cast<unsigned int>(t)].v1 = static_cast<unsigned short>(p[0] | (p[1] << 8));
							triangles[static_cast<unsigned int>(t)].v2 = static_cast<unsigned short>(p[2] | (p[3] << 8));
							triangles[static_cast<unsigned int>(t)].v3 = static_cast<unsigned short>(p[4] | (p[5] << 8));
						}
					}
				}
			}
		}
		if ( !trianglesFromRaw ) {
			triangles.resize(numTriangles);
			for (unsigned int i2 = 0; i2 < triangles.size(); i2++) {
				NifStream( triangles[i2], in, info );
			};
		}
	};

	//--BEGIN POST-READ CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void BSTriShape::Write( ostream& out, const map<NiObjectRef,unsigned int> & link_map, list<NiObject *> & missing_link_stack, const NifInfo & info ) const {
	//--BEGIN PRE-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//

	BSShape::Write( out, link_map, missing_link_stack, info );
	numVertices = (unsigned short)(vertexData.size());
	numTriangles = (unsigned int)(triangles.size());
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		NifStream( unknown4Floats[i1], out, info );
	};
	if ( info.version < VER_3_3_0_13 ) {
		WritePtr32( &(*skin), out );
	} else {
		if ( skin != NULL ) {
			map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(skin) );
			if (it != link_map.end()) {
				NifStream( it->second, out, info );
				missing_link_stack.push_back( NULL );
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( skin );
			}
		} else {
			NifStream( 0xFFFFFFFF, out, info );
			missing_link_stack.push_back( NULL );
		}
	}
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( info.version < VER_3_3_0_13 ) {
			WritePtr32( &(*bsProperties[i1]), out );
		} else {
			if ( bsProperties[i1] != NULL ) {
				map<NiObjectRef,unsigned int>::const_iterator it = link_map.find( StaticCast<NiObject>(bsProperties[i1]) );
				if (it != link_map.end()) {
					NifStream( it->second, out, info );
					missing_link_stack.push_back( NULL );
				} else {
					NifStream( 0xFFFFFFFF, out, info );
					missing_link_stack.push_back( bsProperties[i1] );
				}
			} else {
				NifStream( 0xFFFFFFFF, out, info );
				missing_link_stack.push_back( NULL );
			}
		}
	};
	NifStream( vertexflag1, out, info );
	NifStream( vertexflag2, out, info );
	NifStream( vertexflag3, out, info );
	NifStream( vertexflag4, out, info );
	NifStream( vertexflag5, out, info );
	NifStream( vertexflag6, out, info );
	NifStream( vertexflag7, out, info );
	NifStream( vertexflag8, out, info );
	NifStream( numTriangles, out, info );
	NifStream( numVertices, out, info );
	NifStream( dataSize, out, info );
	if ( (dataSize > 0) ) {
		for (unsigned int i2 = 0; i2 < vertexData.size(); i2++) {
			NifStream( vertexData[i2].vertex.x, out, info );
			NifStream( vertexData[i2].vertex.y, out, info );
			NifStream( vertexData[i2].vertex.z, out, info );
			NifStream( vertexData[i2].dotnormal_, out, info );
			if ( (vertexflag1 != 4) ) {
				NifStream( vertexData[i2].uv.u, out, info );
				NifStream( vertexData[i2].uv.v, out, info );
			};
			if ( (vertexflag1 > 3) ) {
				for (unsigned int i4 = 0; i4 < 8; i4++) {
					NifStream( vertexData[i2].unknown8Bytes[i4], out, info );
				};
			};
			if ( (vertexflag1 == 6) ) {
				NifStream( vertexData[i2].vertexColors.r, out, info );
				NifStream( vertexData[i2].vertexColors.g, out, info );
				NifStream( vertexData[i2].vertexColors.b, out, info );
				NifStream( vertexData[i2].vertexColors.a, out, info );
			};
			if ( (vertexflag1 == 7) ) {
				for (unsigned int i4 = 0; i4 < 2; i4++) {
					NifStream( vertexData[i2].unknown2Ints[i4], out, info );
				};
			};
			if ( (vertexflag1 >= 8) ) {
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					NifStream( vertexData[i2].unknown4Halfs[i4], out, info );
				};
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					NifStream( vertexData[i2].unknown4Bytes[i4], out, info );
				};
			};
			if ( (vertexflag1 == 9) ) {
				NifStream( vertexData[i2].unknownInt1, out, info );
			};
			if ( (vertexflag1 == 10) ) {
				for (unsigned int i4 = 0; i4 < 2; i4++) {
					NifStream( vertexData[i2].unknown2Ints2[i4], out, info );
				};
			};
		};
		for (unsigned int i2 = 0; i2 < triangles.size(); i2++) {
			NifStream( triangles[i2], out, info );
		};
	};

	//--BEGIN POST-WRITE CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::string BSTriShape::asString( bool verbose ) const {
	//--BEGIN PRE-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//

	stringstream out;
	unsigned int array_output_count = 0;
	out << BSShape::asString();
	numVertices = (unsigned short)(vertexData.size());
	numTriangles = (unsigned int)(triangles.size());
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 4; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    Unknown 4 Floats[" << i1 << "]:  " << unknown4Floats[i1] << endl;
		array_output_count++;
	};
	out << "  Skin:  " << skin << endl;
	array_output_count = 0;
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
			break;
		};
		if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
			break;
		};
		out << "    BS Properties[" << i1 << "]:  " << bsProperties[i1] << endl;
		array_output_count++;
	};
	out << "  VertexFlag1:  " << vertexflag1 << endl;
	out << "  VertexFlag2:  " << vertexflag2 << endl;
	out << "  VertexFlag3:  " << vertexflag3 << endl;
	out << "  VertexFlag4:  " << vertexflag4 << endl;
	out << "  VertexFlag5:  " << vertexflag5 << endl;
	out << "  VertexFlag6:  " << vertexflag6 << endl;
	out << "  VertexFlag7:  " << vertexflag7 << endl;
	out << "  VertexFlag8:  " << vertexflag8 << endl;
	out << "  Num Triangles:  " << numTriangles << endl;
	out << "  Num Vertices:  " << numVertices << endl;
	out << "  Data Size:  " << dataSize << endl;
	if ( (dataSize > 0) ) {
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < vertexData.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			out << "      x:  " << vertexData[i2].vertex.x << endl;
			out << "      y:  " << vertexData[i2].vertex.y << endl;
			out << "      z:  " << vertexData[i2].vertex.z << endl;
			out << "      dotNormal?:  " << vertexData[i2].dotnormal_ << endl;
			if ( (vertexflag1 != 4) ) {
				out << "        u:  " << vertexData[i2].uv.u << endl;
				out << "        v:  " << vertexData[i2].uv.v << endl;
			};
			if ( (vertexflag1 > 3) ) {
				array_output_count = 0;
				for (unsigned int i4 = 0; i4 < 8; i4++) {
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
						break;
					};
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						break;
					};
					out << "          Unknown 8 Bytes[" << i4 << "]:  " << vertexData[i2].unknown8Bytes[i4] << endl;
					array_output_count++;
				};
			};
			if ( (vertexflag1 == 6) ) {
				out << "        r:  " << vertexData[i2].vertexColors.r << endl;
				out << "        g:  " << vertexData[i2].vertexColors.g << endl;
				out << "        b:  " << vertexData[i2].vertexColors.b << endl;
				out << "        a:  " << vertexData[i2].vertexColors.a << endl;
			};
			if ( (vertexflag1 == 7) ) {
				array_output_count = 0;
				for (unsigned int i4 = 0; i4 < 2; i4++) {
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
						break;
					};
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						break;
					};
					out << "          Unknown 2 Ints[" << i4 << "]:  " << vertexData[i2].unknown2Ints[i4] << endl;
					array_output_count++;
				};
			};
			if ( (vertexflag1 >= 8) ) {
				array_output_count = 0;
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
						break;
					};
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						break;
					};
					out << "          Unknown 4 Halfs[" << i4 << "]:  " << vertexData[i2].unknown4Halfs[i4] << endl;
					array_output_count++;
				};
				array_output_count = 0;
				for (unsigned int i4 = 0; i4 < 4; i4++) {
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
						break;
					};
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						break;
					};
					out << "          Unknown 4 Bytes[" << i4 << "]:  " << vertexData[i2].unknown4Bytes[i4] << endl;
					array_output_count++;
				};
			};
			if ( (vertexflag1 == 9) ) {
				out << "        Unknown Int 1:  " << vertexData[i2].unknownInt1 << endl;
			};
			if ( (vertexflag1 == 10) ) {
				array_output_count = 0;
				for (unsigned int i4 = 0; i4 < 2; i4++) {
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
						break;
					};
					if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
						break;
					};
					out << "          Unknown 2 Ints 2[" << i4 << "]:  " << vertexData[i2].unknown2Ints2[i4] << endl;
					array_output_count++;
				};
			};
		};
		array_output_count = 0;
		for (unsigned int i2 = 0; i2 < triangles.size(); i2++) {
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				out << "<Data Truncated. Use verbose mode to see complete listing.>" << endl;
				break;
			};
			if ( !verbose && ( array_output_count > MAXARRAYDUMP ) ) {
				break;
			};
			out << "      Triangles[" << i2 << "]:  " << triangles[i2] << endl;
			array_output_count++;
		};
	};
	return out.str();

	//--BEGIN POST-STRING CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

void BSTriShape::FixLinks( const map<unsigned int,NiObjectRef> & objects, list<unsigned int> & link_stack, list<NiObjectRef> & missing_link_stack, const NifInfo & info ) {
	//--BEGIN PRE-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//

	BSShape::FixLinks( objects, link_stack, missing_link_stack, info );
	skin = FixLink<NiObject>( objects, link_stack, missing_link_stack, info );
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		bsProperties[i1] = FixLink<NiProperty>( objects, link_stack, missing_link_stack, info );
	};

	//--BEGIN POST-FIXLINKS CUSTOM CODE--//
	//--END CUSTOM CODE--//
}

std::list<NiObjectRef> BSTriShape::GetRefs() const {
	list<Ref<NiObject> > refs;
	refs = BSShape::GetRefs();
	if ( skin != NULL )
		refs.push_back(StaticCast<NiObject>(skin));
	for (unsigned int i1 = 0; i1 < 2; i1++) {
		if ( bsProperties[i1] != NULL )
			refs.push_back(StaticCast<NiObject>(bsProperties[i1]));
	};
	return refs;
}

std::list<NiObject *> BSTriShape::GetPtrs() const {
	list<NiObject *> ptrs;
	ptrs = BSShape::GetPtrs();
	for (unsigned int i1 = 0; i1 < 2; i1++) {
	};
	return ptrs;
}

//--BEGIN MISC CUSTOM CODE--//
const vector<BSVertexData> & BSTriShape::GetVertexData() const {
	return vertexData;
}

const vector<Triangle> & BSTriShape::GetTriangles() const {
	return triangles;
}

byte BSTriShape::GetVertexFlags1() const {
	return vertexflag1;
}

Niflib::array<2,Ref<NiProperty> > BSTriShape::GetBSProperties() const {
	return bsProperties;
}
//--END CUSTOM CODE--//
