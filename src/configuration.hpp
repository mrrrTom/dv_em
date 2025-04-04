#ifndef CONFIGURATION_DV_H
#define CONFIGURATION_DV_H
#include <unordered_map>
#include <string>
#include "pregister.hpp"
#include "rapidxml.hpp"
#include "rapidxml_utils.hpp"

struct configuration{
	std::unordered_map<std::string, pregister *> registers;	

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
	std::unordered_map<std::string, std::string> commandos;
	
	configuration(const char *path);
};
#endif
