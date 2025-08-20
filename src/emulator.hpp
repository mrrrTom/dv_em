#ifndef EMULATOR_DV_H
#define EMULATOR_DV_H

#include "meta/configuration.hpp"
#include "view.hpp"
#include <unordered_map>
#include <string>
#include <iostream>
#include <vector>
#include "managers_and_resources/registers_manager.hpp"
#include "managers_and_resources/memory_manager.hpp"
#include "managers_and_resources/variables_manager.hpp"
#include "executor.hpp"

namespace dv_em {
	class emulator {
		private:
			//void (* _start_command)(memory_manager mm, registers_manager rm);
			//executor _executor;
			//memory_manager _mm;
			//registers_manager _rm;
			//variables_manager _vm;
			//view _view;
		public:
			emulator(std::string configPath /*, std::string codePath*/);
			void start();
			void process(char symb, std::vector<int> args);
			void stop();
			~emulator();
	};
}
#endif
