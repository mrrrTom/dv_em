#ifndef CONFIGURATION_DV_H
#define CONFIGURATION_DV_H
#include <map>
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <iostream>
#incluede "cell_scheme.hpp"
#include "register_scheme.hpp"
#include "variable_scheme.hpp"
#include <vector>

namespace dv_em {
	struct configuration{
		cell_scheme memory_model;
		vector<register_scheme> registers_model;
		vector<variable_scheme> variables_model;
		std::string start_state;
		std::string beat;
		std::map<std::string, std::string> emulator_commands;
		std::map<std::string, std::string> kernel_commands;
		
		configuration(const std::string path);
		~configuration();
	};
}
#endif
