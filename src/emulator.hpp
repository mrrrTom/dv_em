#ifndef EMULATOR_DV_H
#define EMULATOR_DV_H

#include "configuration.hpp"
#include "view.hpp"
#include <unordered_map>
#include <string>
#include <iostream>

namespace Emulator {
	class emulator {
		private:
			std::unordered_map<char, void (*)(int*)> *_kernel_commands;
			//view _view;
		public:
			emulator(const char *path);
			void run();
			void process(char symb, int *args);
			void stop(std::string path);
			~emulator();
	};
}
#endif
