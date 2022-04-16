#include "gamepine.h"

#include "third_party/pine/src/pine.h"

/**
 * global copy of pine object.
 *
 * internally reference counted, 
 * deleted when gamepine instances hit 0
 */
PINE::PCSX2* gPcsx2Emu = nullptr;
int gPcsx2RefCnt = 0;


// Offsets

// offset to player.
// To get this:
// break at 0x110e08
// note down a0 value
// PUT IT HERE.
//constexpr static auto PLAYER_OFFSET = 0x00894dc0;


constexpr static auto PLAYER_ADDR_OFFSET = 0x007db34c;

constexpr static auto PLAYER_SPEEDMUL_OFFSET = 0x9ac;
constexpr static auto PLAYER_POSITION_OFFSET = 0x9c0;

static uintptr_t gRiderAddr;

GamePine::GamePine() {
	// Create PINE instance, if required
	if(gPcsx2Emu != nullptr || gPcsx2RefCnt == 0) {
		gPcsx2Emu = new PINE::PCSX2();
		gPcsx2RefCnt = 1;
	} else {
		// Increment reference count
		gPcsx2RefCnt++;
	}
	
	// seems to always contain the rider address
	//gRiderAddr = _byteswap_ulong(gPcsx2Emu->Read<uintptr_t>(PLAYER_ADDR_OFFSET));
	gRiderAddr = gPcsx2Emu->Read<uintptr_t>(PLAYER_ADDR_OFFSET);
	std::cout << strfmt("Rider's at 0x%08x\n", gRiderAddr);
}

GamePine::~GamePine() {
	// Free the PINE instance if all references to it would drop
	// by this object destructing
	if(--gPcsx2RefCnt == 0)
		delete gPcsx2Emu;
}

void GamePine::SetRiderPosition(tVec3 vec) {
	WriteVec3(gRiderAddr + PLAYER_POSITION_OFFSET, vec);
}
	
void GamePine::SetRiderSpeedMult(float value) {
	WriteFloat(gRiderAddr + PLAYER_SPEEDMUL_OFFSET, value);
}
	
void GamePine::WriteVec3(uintptr_t address, tVec3 vec) {
	//std::cout << strfmt("Writing (%f, %f, %f) to 0x%08x...\n", x, y, z, address);
	gPcsx2Emu->Write<float>(address, vec.x);
	gPcsx2Emu->Write<float>(address + 4, vec.y);
	gPcsx2Emu->Write<float>(address + 8, vec.z);
}

void GamePine::WriteFloat(uintptr_t address, float val) {
	gPcsx2Emu->Write<float>(address, val);
}