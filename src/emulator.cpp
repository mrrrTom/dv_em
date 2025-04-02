#include <iostream>
#include "emulator.h"

emulator::emulator(std::string path) {
	configuration _config(path);
	//view _view(config);
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
