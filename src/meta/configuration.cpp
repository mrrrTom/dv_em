#include "configuration.hpp"
const std::string cnfg_node_name = "config";
const std::string mem_name = "memory";
const std::string reg_name = "registers";
const std::string var_name = "variables";
const std::string beat_name = "beat";
const std::string em_com_name = "emulator_commands";
const std::string ker_com_name = "kernel_commands";
const std::string path_name = "path";

namespace dv_em {
	cell_scheme get_memory(std::string path);
	std::vector<register_scheme> get_registers(std::string path);
	std::vector<variable_scheme> get_variables(std::string path);
	std::string get_start_state(std::string path);
	std::string get_beat(std::string path);
	std::map<std::string, std::string> get_em_commads(std::string path);
	std::map<std::string, std::string> get_ke_commands(std::string path);
	
	configuration::configuration(const std::string path) {
		rapidxml::file<> xmlFile(path);
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		
		rapidxml::xml_node<> *cnfg_node = doc.first_node("config");

		rapidxml::xml_node<> *mem_node = cnfg_node -> first_node("memory");
		rapidxml::xml_attribute<> *mem_path_attr = mem_node -> first_attribute("path");
		std::string memory_path = std::string(memory->value())));

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




