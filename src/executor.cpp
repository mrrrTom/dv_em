#include "executor.hpp"

namespace emulator {

	executor::executor(registersManager regManager, memoryManager memManager) {
		_regManager = regManager;
		_memManager = memManager;
	}

	void executor::run() {
		// run through all memory
		for(cell c :: _memManager) {
			
		}
	}
}
