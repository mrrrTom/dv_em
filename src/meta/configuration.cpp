#include "configuration.hpp"
const std::string cnfg_node_name = "config";
const std::string mem_name = "memory";
const std::string mem_root_name = "memory_cell";
const std::string mem_addr_size_name = "address_size";
const std::string mem_com_first_bit_name = "command_first_bit";
const std::string mem_com_last_bit_name = "command_last_bit";
const std::string mem_arg_first_bit_name = "arguments_first_bit";
const std::string mem_arg_last_bit_name = "arguments_last_bit";
const std::string mem_fixed_oper_name = "fixed_operands_size";
const std::string mem_operand_size_name = "operand_size";
const std::string reg_name = "registers";
const std::string var_name = "variables";
const std::string start_name = "start";
const std::string beat_name = "beat";
const std::string em_com_name = "emulator_commands";
const std::string ker_com_name = "kernel_commands";
const std::string path_name = "path";

cell_scheme get_memory(std::string path);
std::vector<register_scheme> get_registers(std::string path);
std::vector<variable_scheme> get_variables(std::string path);
std::string get_start_state(std::string path);
std::string get_beat(std::string path);
std::map<std::string, std::string> get_em_commads(std::string path);
std::map<std::string, std::string> get_ke_commands(std::string path);
std::string get_node_path(rapidxml::xml_node<> *cnfg_node, std::string node_name);

namespace dv_em {
	configuration::configuration(const std::string path) {
		rapidxml::file<> xmlFile(path);
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *cnfg_node = doc.first_node(cnfg_node_name);
		std::string memory_path = get_node_path(cnfg_node, mem_name);
		memory_model = get_memory(memory_path);
		
		std::string registers_path = get_node_path(cnfg_node, reg_name);
		registers_model = get_registers(registers_path);

		std::string variables_path = get_node_path(cnfg_node, var_name);
		variables_model = get_variables(variables_path);

		std::string start_path = get_node_path(cnfg_node, start_name);
		start_state = get_start_state(start_path);

		std::string beat_path = get_node_path(cnfg_node, beat_name);
		beat = get_beat(beat_path);

		std::string em_commands_path = get_node_path(cnfg_node, em_com_name);
		emulator_commands = get_em_commands(em_commands_path);

		std::string ke_commands_path = get_node_path(cnfg_node, ker_com_name);
		kernel_commands = get_ke_commands(ke_commands_path);
	}
}


cell_scheme get_memory(std::string path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *mem_node = doc.first_node(mem_root_name);
	dv_em::cell_scheme mem;
	
	rapidxml::xml_node<> *addr_size = mem_node -> first_node(mem_addr_size_name);
	mem.address_size = (unsigned char)(std::stoi(std::string(addr_size -> value())));
	
	rapidxml::xml_node<> *com_first_bit = mem_node -> first_node(mem_com_first_bit_name);
	mem.command_first_bit = (unsigned short int)(std::stoi(std::string(com_first_bit -> value())));

	rapidxml::xml_node<> *com_last_bit = mem_node -> first_node(mem_com_last_bit_name);
	mem.command_last_bit = (unsigned short int)(std::stoi(std::string(com_last_bit -> value())));

	rapidxml::xml_node<> *arg_first_bit = mem_node -> first_node(mem_arg_first_bit_name);
	mem.arguments_first_bit = (unsigned short int)(std::stoi(std::string(arg_first_bit -> value())));

	rapidxml::xml_node<> *arg_last_bit = mem_node -> first_node(mem_arg_last_bit_name);
	mem.arguments_last_bit = (unsigned short int)(std::stoi(std::string(arg_last_bit -> value())));

	rapidxml::xml_node<> *fixed_operand_size = mem_node -> first_node(mem_fixed_oper_name);
	mem.fixed_operand_size = (bool)(std::stoi(std::string(fixed_operand_size -> value())));

	rapidxml::xml_node<> *operand_size = mem_node -> first_node(mem_operand_size_name);
	mem.operand_size = (unsigned short int)(std::stoi(std::string(operand_size -> value())));

	return mem;
}

std::vector<register_scheme> get_registers(std::string path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());
	rapidxml::xml_node<> *reg_node = doc.first_node(mem_root_name);
	std::vector<dv_em::register_scheme> regs;
}

std::vector<variable_scheme> get_variables(std::string path);
std::string get_start_state(std::string path);
std::string get_beat(std::string path);
std::map<std::string, std::string> get_em_commads(std::string path);
std::map<std::string, std::string> get_ke_commands(std::string path);
std::string get_node_path(rapidxml::xml_node<> *cnfg_node, std::string node_name);


		rapidxml::xml_node<> *csize = node -> first_node("csize");
		cop_size = (unsigned char)(std::stoi(std::string(csize -> value())));

		rapidxml::xml_node<> *osize = node -> first_node("osize");
		operand_size = (unsigned char)(std::stoi(std::string(osize -> value())));

		rapidxml::xml_node<> *ocount = node -> first_node("ocount");
		operands_count = (unsigned char)(std::stoi(std::string(ocount -> value())));
		
		rapidxml::xml_node<> *registersNode = node -> first_node("registers");
		rapidxml::xml_node<> *reg = registersNode -> first_node("reg");
		do 	{
			unsigned char regSize = (unsigned char)(std::stoi(std::string(reg -> value())));
			rapidxml::xml_attribute<> *regAttr = reg -> first_attribute("name");
			std::string regName = regAttr -> value();
			registers.insert({regName, regSize});
			reg = reg -> next_sibling();
		} while (reg);

		rapidxml::xml_node<> *startNode = node -> first_node("start");
		rapidxml::xml_attribute<> *startPathAttr = startNode -> first_attribute("path");
		std::string startPath = startPathAttr -> value();
		start = getStart(startPath.c_str());
		 
		rapidxml::xml_node<> *beatNode = node -> first_node("beat");
		rapidxml::xml_attribute<> *beatPathAttr = beatNode -> first_attribute("path");
		std::string beatPath = beatPathAttr -> value();
		beat = getBeat(beatPath.c_str());

		rapidxml::xml_node<> *commandsNode = node -> first_node("commandos");
		rapidxml::xml_attribute<> *commandsPathAttr = commandsNode -> first_attribute("path");
		std::string commandsPath = commandsPathAttr -> value();
		commands = getCommands(commandsPath.c_str());
	}

	std::unordered_map<std::string, std::string> getStart(const char *path) {
		rapidxml::file<> xmlFile(path);
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *node = doc.first_node("start");
		
		std::unordered_map<std::string, std::string> startValues;
		rapidxml::xml_node<> *reg = node -> first_node("reg");
		do 	{
			std::string regVal = std::string(reg -> value());
			rapidxml::xml_attribute<> *regAttr = reg -> first_attribute("name");
			std::string regName = regAttr -> value();
			startValues.insert({regName, regVal});
			reg = reg -> next_sibling();
		} while (reg);
		
		return startValues;
	}

	std::unordered_map<std::string, std::string> getBeat(const char *path) {
		rapidxml::file<> xmlFile(path);
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *node = doc.first_node("beat");
		
		std::unordered_map<std::string, std::string> beatValues;
		rapidxml::xml_node<> *reg = node -> first_node("reg");
		do 	{
			std::string regVal = std::string(reg -> value());
			rapidxml::xml_attribute<> *regAttr = reg -> first_attribute("name");
			std::string regName = regAttr -> value();
			beatValues.insert({regName, regVal});
			reg = reg -> next_sibling();
		} while (reg);
		
		return beatValues;
	}

	std::unordered_map<std::string, std::string> getCommands(const char *path) {
		rapidxml::file<> xmlFile(path);
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *node = doc.first_node("commands");
		
		std::unordered_map<std::string, std::string> commandsValues;
		rapidxml::xml_node<> *op = node -> first_node("op");
		do 	{
			rapidxml::xml_attribute<> *opAttr = op -> first_attribute("name");
			std::string opName = opAttr -> value();
			std::string opVal = std::string(op -> value());
			commandsValues.insert({opName, opVal});
			op = op -> next_sibling();
		} while (op);
		
		return commandsValues;
	}

	configuration::~configuration() {
	} 
}

std::string get_node_path(rapidxml::xml_node<> *cnfg_node, std::string node_name)
{
	rapidxml::xml_node<> *node = cnfg_node -> first_node(node_name);
	rapidxml::xml_attribute<> *path_attr = node -> first_attribute(path_name);
	return path_attr->value();
}

