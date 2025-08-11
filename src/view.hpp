#ifndef VIEW_DV_H
#define VIEW_DV_H
#include "configuration.hpp"
#include <iostream>
#include <fstream>
#include <unordered_map>

namespace dv_em {
	class view {
		char v_border_symb = '|';
		char h_border_symb = '-';
		public:
			std::string *input;
			std::unordered_map<std::string, std::string*> registers;
			std::string *output;
			std::string *memory;
			void print();
			view(std::string *input,
					std::string *output,
					std::unordered_map<std::string, std::string*> registers,
					std::string *memory);
			friend std::ostream &operator<<(std::ostream &ostream, view v);
	};
}
#endif
