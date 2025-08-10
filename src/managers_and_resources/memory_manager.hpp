#ifndef MEMORY_MANAGER_DV_EM
#define MEMORY_MANAGER_DV_EM
#include <vector>
#include "cell.hpp"

namespace dv_em {
	class memory_manager {
		public:
			bool set_cursor(vector<unsigned int> address);
			bool write(vector<int> bits, unsigned short int start unsigned short int bits_count);
			vector<int> read(unsigned short int start, unsigned short int bits_ccount);
			bool move_next();
	};
}
#endif
