#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <thread>
#include <chrono>

#include "pbdtypes.h"
#include "gamepine.h"

void SetPosWithFudge(GamePine& pine, const tVec3& vec) {
	tVec3 copy = vec;
	copy.x += 15.0f; // fudge
	
	std::cout << strfmt("setting pos to (%f, %f, %f)\n", copy.x, copy.y, copy.z);
	pine.SetRiderSpeedMult(0.0);
	pine.SetRiderPosition(copy);
}


int main(int argc, char** argv) {
	if(argc != 2) {
		std::cout << strfmt("usage: \"%s\" [path to PBD file]\n", argv[0]);
		std::cout << strfmt("needs PCSX2 with PINE enabled to function\n");
		return 1;
	}
	
	std::ifstream ifs(argv[1], std::ifstream::binary);
	
	if(!ifs) {
		std::cout << "couldnt open\n";
		return 1;
	}
	
	GamePine pine;
	
	tPbdHeader header;
	
	if(!ReadInto(ifs, header)) {
		std::cout << "couldnt read header\n";
		return 1;
	}


#if 1	
	std::cout << strfmt("splines at offset %d\n", header.SplineOffset);
	
	ifs.seekg(header.SplineOffset, std::ifstream::beg);
	
	std::vector<tSpline> splines(header.NumSplines);
	
	for(int i = 0; i < header.NumSplines; ++i) {
		if(!ReadInto(ifs,splines[i])) {
			std::cout << strfmt("couldnt read spline %d\n", i);
			return 1;
		} else {
			// dump again?
		}
	}
	
	// Writer loop
	
	for(int i = 0; i < header.NumSplines; ++i) {
		try {
			SetPosWithFudge(pine, splines[i].points[0]);
			//std::cout << strfmt("Setting to point finished. Waiting 2 secs\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(950));
			
			SetPosWithFudge(pine, splines[i].points[1]);
			//std::cout << strfmt("Setting to point finished. Waiting 2 secs\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(950));
		} catch(...) {
			std::cout << strfmt("Trying to set to point failed :(\n");
			break;
		}
	}
#endif

// Spline segments
#if 1
	ifs.seekg(header.SplineSegmentOffset, std::ifstream::beg);
	std::vector<tSplineSegment> segments(header.NumSplineSegments);
	
	for(int i = 0; i < header.NumSplineSegments; ++i) {
		if(!ReadInto(ifs,segments[i])) {
			std::cout << strfmt("couldnt read spline %d\n", i);
			return 1;
		} else {
			//segments[i].Dump(std::cout);
		}
	}
	
	// Another writer loop
	
	for(int i = 0; i < header.NumSplineSegments; ++i) {
		// all of the even ones are wildly broken for some reason
		// so skip past them as a hack
		if((i % 2))
			continue;
		
		try {
			SetPosWithFudge(pine, segments[i].matrix.AsVec3());
			
			//std::cout << strfmt("Setting to point finished.\n");
			std::this_thread::sleep_for(std::chrono::milliseconds(1500));
		} catch(...) {
			std::cout << strfmt("Trying to set to point failed :(\n");
			break;
		}
	}
#endif
	
}