#include "view.hpp"
#include <sys/ioctl.h>
#include <unistd.h>

namespace dv_em {
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

	winsize get_terminal_window();
		
	std::ostream &operator<<(std::ostream &stream, view v) {
		winsize size = get_terminal_window();
		int width = (int)size.ws_col;
		int hight = (int)size.ws_row;

		for (int i = 0; i < width; i++) {
			stream << v.h_border_symb;
		}

		std::cout << std::endl;

		for (int i = 0; i < hight; i++) {
			stream << v.v_border_symb;
			for (int j = 0; j < (width - 2); j++) {
				stream << ' ';
			}
			stream << v.v_border_symb << std::endl;
		}

		for (int i = 0; i < width; i++) {
			stream << v.h_border_symb;
		}

		return stream;
	}

	winsize get_terminal_window() {
		struct winsize size;
		ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
		return size;
	}
}
