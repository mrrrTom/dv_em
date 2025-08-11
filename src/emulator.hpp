#ifndef EMULATOR_DV_H
#define EMULATOR_DV_H

#include "configuration.hpp"
#include "view.hpp"
#include <unordered_map>
#include <string>
#include <iostream>

namespace emulator {
	class emulator {
		private:
			void (*) (memory_manager mm, registers_manager rm) _start_command;
			executor _executor;
			memory_manager _mm;
			registers_manager _rm;
			variables_manager _vm;
			view _view;
		public:
			emulator(std::string configPath, std::string codePath);
			void start();
			void process(char symb, vector<int> args);
			void stop();
			~emulator();
	};
}
#endif
