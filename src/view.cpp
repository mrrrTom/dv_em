#include "view.hpp"

namespace Emulator {
	view::view(configuration config) {
	}

	void view::print() {
	std::cout<<*this;
	}

	std::ostream &operator<<(std::ostream &stream, view v) {
	for (int i = 0; i < v.hSize; i++) {
		stream << v.hBorderSymb;
	}

	std::cout << std::endl;

	for (int i = 0; i < v.vSize; i++) {
		stream << v.vBorderSymb;
		for (int j = 0; j < (v.hSize - 2); j++) {
			stream << ' ';
		}
		stream << v.vBorderSymb << std::endl;
	}

	for (int i = 0; i < v.hSize; i++) {
		stream << v.hBorderSymb;
	}

	return stream;
	}
}
