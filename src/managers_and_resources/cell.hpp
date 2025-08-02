#ifndef CELL_RESOURCE_DV_HPP
#define CELL_RESOURCE_DV_HPP
	namespace emulator {
		class cell {
			private:
				unsigned short int _command_first_bit;
				unsigned short int _command_last_bit;
				unsigned short int _value_first_bit;
				unsigned short int _value_last_bit;
			public:
				int* adress;
				int* value;
				int* get_command();
				int* get_operand();
		}
	}
#endif
