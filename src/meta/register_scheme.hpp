#ifndef REGISTER_SCHEME_META_DV_HPP
#define REGISTER_SCHEME_META_DV_HPP
#include <string>

namespace emulator {
	struct register_scheme {
		std::string name;
		std::string comment;
		unsigned char size;
		unsigned char user_allowed_modes;
	};
}
#endif
