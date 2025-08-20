#ifndef VARIABLES_MANAGER_DV_EM_HPP
#define	VARIABLES_MANAGER_DV_EM_HPP
#include <map>
#include <string>
#include <vector>
#include "variable.hpp"

namespace dv_em {
		class variables_manager {
			private:
				std::map<std::string, variable> _variables;
			public:
				bool write(std::string var_name, unsigned short int index, unsigned short int var_offset, unsigned short int input_offset, std::vector<int> value);
				bool read(std::string var_name, unsigned short int index, unsigned short int var_offset, unsigned short int input_offset, std::vector<int>& value);
		};
}
#endif
