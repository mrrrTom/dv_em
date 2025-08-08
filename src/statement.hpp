#ifndef STATEMENT_DV_EM_HPP
#define STATEMENT_DV_EM_HPP
#include "statement.hpp"
#include <vector>

namespace dv_em {
	struct statement {
		private:
			statement_type _type;
			std::vector<statement> operands;
		public:
			statement_type get_type();
			statement(std::vector<statement> operands);
	};
}
#endif
