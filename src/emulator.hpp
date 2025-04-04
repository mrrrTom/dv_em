#ifndef EMULATOR_DV_H
#define EMULATOR_DV_H

#include "configuration.hpp"
#include "view.hpp"
#include <unordered_map>
#include <string>
#include <iostream>

class emulator {
	private:
		configuration _config;
		view _view;
	public:
		emulator(const char *path);
		void run();
		void process(char symb);
		void stop(std::string path);
};
#endif
