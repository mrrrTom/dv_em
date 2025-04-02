#ifndef CONFIGURATION_DV_H
#define CONFIGURATION_DV_H
#include <unordered_map.h>

struct configuration {
	std::unordered_map<std::string, *register> registers;	

	unsigned byte adress_size;
	unsigned byte cop_size;
	unsigned byte operand_size;
	unsigned byte operands_count;
	
	//start (initialize registers)
	//register_name register_start_value
	std::unordered_map<std::string, string> start;

	//frame (returns command pointer)
	//registers new values
	//+output new value
	std::unordered_map<std::string, std::string> beat;

	//commands
	//command_name command_body
	std::unordered_map<std::string, string> commandos;
	
	configuration(std::string path);
}
#endif
