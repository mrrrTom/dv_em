#ifndef EXECUTOR_DV_H
#define EXECUTOR_DV_H
#include <map>
#include <vector>
#include "statement.hpp"
#include <string>

namespace dv_em {
	class executor {
		private:
			std::map<std::string, std::vector<statement>> _kernel_commands;
			std::map<std::string, std::vector<statement>> _emulator_commands;
		public:
			std::string execute(std::string command, std::vector<int> args);
			void execute(unsigned short int call_address);
			
	};
}
#endif
