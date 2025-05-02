#ifndef REGISTER_DV_H
#define REGISTER_DV_H
#include <string>

namespace Emulator {
	struct pregister{
		std::string name;
		unsigned char size;
		void *value;
	};
}
#endif

