#ifndef CONFIGURATION_DV_H
#define CONFIGURATION_DV_H
#include <unordered_map>
#include <string>
#include "pregister.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"
#include <iostream>
namespace emulator {
	struct configuration{
		std::unordered_map<std::string, unsigned char> registers;	

		unsigned char adress_size;
		unsigned char cop_size;
		unsigned char operand_size;
		unsigned char operands_count;
		
		//start (initialize registers)
		//register_name register_start_value
		std::unordered_map<std::string, std::string> start;

		//frame (returns command pointer)
		//registers new values
		//+output new value
		std::unordered_map<std::string, std::string> beat;

		//commands
		//command_name command_body
		std::unordered_map<std::string, std::string> commands;
		
		configuration(const char *path);
		~configuration();
	};
}
#endif
