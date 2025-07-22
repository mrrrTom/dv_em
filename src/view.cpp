#include "view.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

namespace emulator {
		view::view(std::string *input,
					std::string *output,
					std::unordered_map<std::string, std::string *> registers,
					std::string *memory) {
			this->input = input;
			this->output = output;
			this->registers = registers;
			this->memory = memory;
	}

	void view::print() {
		std::cout<<*this;
	}

	winsize getTerminalWindow();
		
	std::ostream &operator<<(std::ostream &stream, view v) {
		winsize size = getTerminalWindow();
		int width = (int)size.ws_col;
		int hight = (int)size.ws_row;

		for (int i = 0; i < width; i++) {
			stream << v.hBorderSymb;
		}

		std::cout << std::endl;

		for (int i = 0; i < hight; i++) {
			stream << v.vBorderSymb;
			for (int j = 0; j < (width - 2); j++) {
				stream << ' ';
			}
			stream << v.vBorderSymb << std::endl;
		}

		for (int i = 0; i < width; i++) {
			stream << v.hBorderSymb;
		}

		return stream;
	}

	winsize getTerminalWindow() {
		struct winsize size;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		return size;
	}
}
