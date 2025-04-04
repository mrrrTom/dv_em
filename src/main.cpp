#include <iostream>
#include "emulator.hpp"


int main(int argc, char *argv[]) {
	if (argc != 3) {
		//ToDo exception
		return -1;
	}
	
	emulator *e = new emulator(argv[0]);
	bool run = true;
	e->run();
	while (run) {
		auto key = std::cin.get();
		if (key == 3) {
			std::cout << "CTLR + C pressed";
			break;
		}
		
		e->process(key);
	}

	e->stop(argv[1]);
}


