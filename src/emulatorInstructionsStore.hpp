#ifndef EMULATOR_INSTRUCTIONS_STORE_DV_H
#define EMULATOR_INSTRUCTIONS_STORE_DV_H
#include <unordered_map>
#include <iostream>

namespace emulator {
	std::unordered_map<char, void (*)(int*)> GetEmulatorInstructions();
}

#endif
