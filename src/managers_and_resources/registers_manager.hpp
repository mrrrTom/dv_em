#ifndef REGISTERS_MANAGER_DV_EM_HPP
#define REGISTERS_MANAGER_DV_EM_HPP

#include <string>
#include <vector>
#include <map>
#include "pregister.hpp"

namespace dv_em {
	class registers_manager {
		private:
			std::map<std::string, pregister> _registers;
		public:
			bool write(std::string register_name, vector<int> value, unsigned int short register_offset, unsigned int short value_offset);
			bool read(std::string register_name, vector<int>& value, unsigned int short register_offset, unsigned int short result_offset);
	};
}

#endif
