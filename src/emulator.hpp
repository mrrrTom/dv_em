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
			kernelCommandsStore _commandsStore;
			//view _view;
		public:
			emulator(const char *configPath, const char *codePath);
			void run();
			void process(const char symb, int *args);
			void stop();
			~emulator();
	};
}
#endif
