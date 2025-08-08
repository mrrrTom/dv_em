#ifndef	TRANSLATOR_DV_EM_HPP
#define TRANSLATOR_DV_EM_HPP
#include <string>
#include "statement.hpp"
#include <vector>

namespace dv_em {
	class translator {
		public:
			vector<statement> translate(std::string command);
			vector<statement> inerpret(std::string state);
	};
}
#endif
