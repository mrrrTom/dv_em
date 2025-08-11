#include "executor.hpp"

namespace dv_em {
	executor::executor(registersManager regManager, memoryManager memManager) {
		_regManager = regManager;
		_memManager = memManager;
	}

	void executor::run() {
		// run through all memory
		for(cell c :: _memManager) {
		//кто-то должен выполнять юзерские команды тоже. Получается, что екзекьютор сам и должен: в него надо грузить эти команды, их надо создавать каким-то образом	
		}
	}
}
