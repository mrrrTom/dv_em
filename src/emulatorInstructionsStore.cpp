#include "emulatorInstructionsStore.hpp"

namespace {
	void next_step(int *args, emulator::executor) {
		std::cout << "next_step func" << args[0] << std::endl;
		emulator::executor.run();
	}
}

namespace emulator {
	std::unordered_map<char, void (*)(int*)> GetEmulatorInstructions() {
		std::unordered_map<char, void (*)(int*)> result {
			{'n', &next_step}
		};

		return result;
	}
}
