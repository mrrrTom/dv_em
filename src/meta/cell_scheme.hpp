#ifndef REGISTER_SCHEME_META_DV_HPP
#define REGISTER_SCHEME_META_DV_HPP
	
	namespace dv_em {
		struct cell_scheme {
			unsigned char address_size;
			unsigned short int command_first_bit;
			unsigned short int command_last_bit;
			unsigned short int arguments_firts_bit;
			unsigned short int arguments_last_bit;
			bool fixed_operand_size;
			unsigned short int operand_size;
		};
	}
#endif
