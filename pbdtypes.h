#ifndef SK_PBDTYPES_H
#define SK_PBDTYPES_H

#include <cstdint>
#include <iostream>
#include "util.h"
#include "basictypes.h"

// Compatibility types from old code.
using byte = uint8_t;
using uint32 = uint32_t;

enum class eDataFormatType : byte {
    GenericFormat,
    Ps2Format,
    XboxFormat,
    NgcFormat
};

struct tPbdHeader {
    byte version[3];
    eDataFormatType format;

    uint32 NumPlayerStarts;
    uint32 NumPatches;
    uint32 NumInstances;
    uint32 NumParticleInstances;
    uint32 NumMaterials;
    uint32 NumMaterialBlocks;
    uint32 NumLights;
    uint32 NumSplines;
    uint32 NumSplineSegments;
    uint32 NumTextureFlips;
    uint32 NumModels;
    uint32 Unknown;                    // 0x30, unused
    uint32 NumTextures;
    uint32 NumCameras;
    uint32 LightMapSize;
    uint32 PlayerStartOffset;
    uint32 PatchOffset;
    uint32 InstanceOffset;
    uint32 Unknown2;                // 0x4c, unused
    uint32 MaterialOffset;
    uint32 MaterialBlocksOffset;
    uint32 LightsOffset;
    uint32 SplineOffset;
    uint32 SplineSegmentOffset;
    uint32 TextureFlipOffset;
    uint32 ModelPointerOffset;
    uint32 ModelsOffset;
    uint32 ParticleModelPointerOffset;
    uint32 ParticleModelsOffset;
    uint32 CameraPointerOffset;
    uint32 CamerasOffset;
    uint32 HashOffset;
};


struct tSpline {
	tVec3 points[2];
	uint32_t unknwon;
	uint32_t id_or_something;
	uint32_t unknown2[2];
	
	void Dump(std::ostream& os) {
		os << "    Points: \n";
		for(int i = 0 ; i < 2; ++i)
			os << strfmt("        %d: (%f,%f,%f)\n", i, points[i].x, points[i].y, points[i].z);
	}
};

static_assert(sizeof(tSpline) == 0x28, "FUCKED IT UP!!!");

struct tSplineSegment {
	tMat4 matrix;
	//tVec4 scaleFactor; //?
	//uint32_t unk[4];
		
	void Dump(std::ostream& os) {
		matrix.Dump(os);
	}
	
	
};


#endif // SK_PBDTYPES_H