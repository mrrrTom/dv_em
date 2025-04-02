#ifndef EMULATOR_DV_H
#define EMULATOR_DV_H

#include <configuration.h>
#include <view.h>
#include <unordered_map>
#include <string>
class emulator {
	private:
		configuration _config;
		view _view;
	public:
		emulator(std::string path);
		void run();
		void process(char symb);
		void stop(std::string path);
};
#endif
