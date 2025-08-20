#ifndef MEMORY_MANAGER_DV_EM
#define MEMORY_MANAGER_DV_EM
#include <vector>
#include "cell.hpp"

namespace dv_em {
	class memory_manager {
		public:
			bool set_cursor(std::vector<unsigned int> address);
			bool write(std::vector<int> bits, unsigned short int start, unsigned short int bits_count);
			std::vector<int> read(unsigned short int start, unsigned short int bits_count);
			bool move_next();
	};
}
#endif
