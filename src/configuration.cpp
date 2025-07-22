#include "configuration.hpp"

namespace emulator {
	std::unordered_map<std::string, std::string> getStart(const char *path);
	std::unordered_map<std::string, std::string> getBeat(const char *path);
	std::unordered_map<std::string, std::string> getCommands(const char *path);

	configuration::configuration(const char *path) {
		rapidxml::file<> xmlFile(path);
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		
		rapidxml::xml_node<> *node = doc.first_node("config");

		rapidxml::xml_node<> *asize = node -> first_node("asize");
		adress_size = (unsigned char)(std::stoi(std::string(asize->value())));

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




