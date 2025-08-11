#ifndef CONFIGURATION_DV_H
#define CONFIGURATION_DV_H
#include <unordered_map>
#include <string>
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <iostream>
#incluede "cell_scheme.hpp"
#include "register_scheme.hpp"
#include "variable_scheme.hpp"

namespace dv_em {
	struct configuration{
		cell_scheme memory_model;
		register_scheme* registers_model;
		variable_scheme* variables_model;
		std::string start_state;
		std::string beat;
		std::unordered_map<std::string, std::string> kernel_commands;
		std::unordered_map<std::string, std::string> user_commands;
		
		configuration(const char *path);
		~configuration();
	};
}
#endif
