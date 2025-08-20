#ifndef	TRANSLATOR_DV_EM_HPP
#define TRANSLATOR_DV_EM_HPP
#include <string>
#include "statement.hpp"
#include <vector>

namespace dv_em {
	class translator {
		public:
			std::vector<statement> translate(std::string command);
			std::vector<statement> inerpret(std::string state);
	};
}
#endif
