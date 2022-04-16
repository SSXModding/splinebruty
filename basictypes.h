#ifndef SK_BASICTYPES_H
#define SK_BASICTYPES_H

#include "util.h"

// Basic fundamental types of the BX code

struct tVec3 {
	float x, y, z;
	
	// Helpy-welpy
	//void WriteInto(PINE::PCSX2& pcsx2Emu, uintptr_t offset) {
	//	std::cout << strfmt("Writing (%f, %f, %f) to 0x%08x...\n", x, y, z, offset);
		// I may need to endian swap
	//	pcsx2Emu.Write<float>(offset, (x));
	//	pcsx2Emu.Write<float>(offset + 4, (y));
	//	pcsx2Emu.Write<float>(offset + 8, (z + 10)); // Fudge factor to avoid player stop failing
	//}
	
	void Dump(std::ostream& os) {
		os << strfmt("(%f, %f, %f)", x, y, z);
	}
};

struct tVec4 {
	float x, y, z, w;
	
	// Helpy-welpy
	//void WriteInto(PINE::PCSX2& pcsx2Emu, uintptr_t offset) {
		//std::cout << strfmt("Writing (%f, %f, %f, %f) to 0x%08x...\n", x, y, z, w, offset);
		// I may need to endian swap
	//	pcsx2Emu.Write<float>(offset, (x));
	//	pcsx2Emu.Write<float>(offset + 4, (y));
	//	pcsx2Emu.Write<float>(offset + 8, (z + 15)); // Fudge factor to avoid player stop failing
	//}
	
	void Dump(std::ostream& os) {
		os << strfmt("(%f, %f, %f)", x, y, z, w);
	}
};

struct tMat4 {
	tVec4 rows[4];
	
	void Dump(std::ostream& os) {
		os << "    Rows: \n";
		for(int i = 0 ; i < 4; ++i)
			os << strfmt("        %d: (%f,%f,%f,%f)\n", i, rows[i].x, rows[i].y, rows[i].z, rows[i].w);
	}
	
	// final row is translation
	tVec3 AsVec3() const {
		return tVec3 {
			rows[3].x,
			rows[3].y,
			rows[3].z
		};
	}
};

#endif // SK_BASICTYPES_H