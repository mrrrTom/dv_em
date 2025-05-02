#include "emulator.hpp"
#include "configuration.hpp"

namespace Emulator {
	emulator::emulator(const char *path) :
			_config(path),
			_view(_config)
	{
		_view.print();
		//executor = new executor(config);
	}
	void emulator::run() {
		std::cout << "started emulator ";	
	}

	void emulator::stop(std::string path) {
	}

	void emulator::process(char symb) {
	}
}
