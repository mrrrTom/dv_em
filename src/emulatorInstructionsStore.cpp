#include "emulatorInstructionsStore.hpp"

namespace {
	void next_step(int *args) {
		std::cout << "next_step func" << args[0] << std::endl;
	}
}

namespace Emulator {
	std::unordered_map<char, void (*)(int*)> GetEmulatorInstructions() {
		std::unordered_map<char, void (*)(int*)> result {
			{'n', &next_step}
		};

		return result;
	}
}
