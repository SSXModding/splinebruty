#ifndef SK_GAMEPINE_H
#define SK_GAMEPINE_H

#include "basictypes.h"

/**
 * Wrapper over pine for our uses.
 * Does not expose pine.
 */
struct GamePine {
	GamePine();
	~GamePine();

	void SetRiderPosition(tVec3 vec);
	
	void SetRiderSpeedMult(float value);
	
	
	void WriteVec3(uintptr_t address, tVec3 vec);
	void WriteFloat(uintptr_t address, float val);
};

#endif