#include "emulator.hpp"
#include "configuration.hpp"

emulator::emulator(const char *path) {
	configuration _config(path);
	view _view(_config);
	//view.print();
	//executor = new executor(config);
}
void emulator::run() {
	std::cout << "started emulator ";	
}

void emulator::stop(std::string path) {
}

void emulator::process(char symb) {
}
