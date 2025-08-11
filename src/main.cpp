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
	
	dv_em::emulator *e = new dv_em::emulator(argv[1]);
	bool run = true;
	e->run();
	while (run) {
		std::cout << "started circle" << std::endl;
		//auto key = std::cin.get();
		/*if (key == 3) {
			std::cout << "CTLR + C pressed";
			break;
		}*/
		
		std::string input;
		std::cin >> input;
		e->process(input[0], input.substr(2));
		std::cout << "returned to main" << std::endl;
	}

	e->stop(argv[1]);
}


