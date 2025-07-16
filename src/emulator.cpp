#include "emulator.hpp"
#include "configuration.hpp"
#include "emulatorInstructionsStore.hpp"

namespace Emulator {
	emulator::emulator(const char *path) {
		_kernel_commands = new std::unordered_map<char, void (*)(int*)>(GetEmulatorInstructions());
		configuration config(path);
		//_view(
		//здесь из конфига и надо создать все потроха эмулятора
		//_view.print();
		//executor = new executor(config);
	}

	void emulator::run() {
		std::cout << "run emulator" << std::endl;
	}

	void emulator::stop(std::string path) {
	}

	void emulator::process(char symb, int* args) {
		auto funcptr = _kernel_commands -> at(symb);
		(*(funcptr))(args);
		std::cout << "processed symbol:" << symb << std::endl;
	}

	emulator::~emulator() {
		std::cout<< "emulator destruction" << std::endl;
		delete _kernel_commands;
	}
}
