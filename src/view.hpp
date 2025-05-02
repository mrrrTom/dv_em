#ifndef VIEW_DV_H
#define VIEW_DV_H
#include "configuration.hpp"
#include <iostream>
#include <fstream>

namespace Emulator {
	class view {
		char vBorderSymb = '|';
		char hBorderSymb = '-';
		int vSize = 20;
		int hSize = 40;
		public:
			void print();
			view(configuration config);
			friend std::ostream &operator<<(std::ostream &ostream, view v);
	};
}
#endif
