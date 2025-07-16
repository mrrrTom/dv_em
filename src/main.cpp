#include <iostream>
#include "emulator.hpp"
//https://unix.stackexchange.com/a/617600
//stty raw (without new line and etc) - stty sane https://www.ibm.com/docs/en/zvm/7.3?topic=commands-stty-set-display-terminal-options
//
int main(int argc, char *argv[]) {
	if (argc != 3) {
		//ToDo exception
		return -1;
	}
	
	Emulator::emulator *e = new Emulator::emulator(argv[1]);
	bool run = true;
	e->run();
	while (run) {
		auto key = std::cin.get();
		if (key == 3) {
			std::cout << "CTLR + C pressed";
			break;
		}
		
		int args[2] { 5, 8};
		e->process(key, args);
	}

	e->stop(argv[1]);
}


