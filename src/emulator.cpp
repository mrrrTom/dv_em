#include "emulator.hpp"

namespace dv_em {
	emulator::emulator(const std::string path) {
		configuration config(path);
		//_view(
		//здесь из конфига и надо создать все потроха эмулятора
		//_view.print();
		//executor = new executor(config);
	}

	void emulator::start() {
		std::cout << "run emulator" << std::endl;
	}

	//void emulator::stop(std::string path) {
	//}

	//void emulator::process(char symb, int* args) {
		//auto funcptr = _kernel_commands -> at(symb);
		//(*(funcptr))(args);
		//std::cout << "processed symbol:" << symb << std::endl;
	//}

	emulator::~emulator() {
		std::cout<< "emulator destruction" << std::endl;
	}
}
