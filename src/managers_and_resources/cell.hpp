#ifndef CELL_RESOURCE_DV_EM_HPP
#define CELL_RESOURCE_DV_EM_HPP
#include <vector>
	namespace dv_em {
		class cell {
			private:
				unsigned short int _command_first_bit;
				unsigned short int _command_last_bit;
				unsigned short int _value_first_bit;
				unsigned short int _value_last_bit;
			public:
				std::vector<int> adress;
				std::vector<int> value;
				std::vector<int> get_command();
				std::vector<int> get_operand();
		};
	}
#endif
