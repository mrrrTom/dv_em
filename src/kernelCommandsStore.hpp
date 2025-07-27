#ifndef KERNEL_COMMANDS_STORE_DV_H
#define KERNEL_COMMANDS_STORE_DV_H
#include <unordered_map>
#include <iostream>

namespace emulator {
	class kernelCommandsStore {
		void (*)(int*) ResolveCommand(unsigned long long int commandId);
	}
}

#endif
