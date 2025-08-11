#ifndef VARIABLE_SCHEME_META_DV_HPP
#define VARIABLE_SCHEME_META_DV_HPP
#include <string>
	namespace dv_em {
		struct variable_scheme {
			std::string name;
			std::string comment;
			unsigned short int size;
			unsigned short int depth;
			bool is_visible;
			std::string format_string;
		};
	}
#endif
