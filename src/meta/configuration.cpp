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
const std::string reg_root_name = "registers";
const std::string reg_entity_name = "reg";
const std::string reg_name_attr = "name";
const std::string reg_comment_attr = "comment";
const std::string reg_size_attr = "size";
const std::string reg_mode_attr = "modes";

const std::string var_name = "variables";
const std::string var_root_name = "variables";
const std::string var_entity_name = "var";
const std::string var_name_attr = "name";
const std::string var_comment_attr = "comment";
const std::string var_size_attr = "size";
const std::string var_depth_attr = "depth";
const std::string var_visibility_attr = "is_visible";
const std::string var_format_attr = "format_string";

const std::string start_name = "start";
const std::string start_root_name = "start";

const std::string beat_name = "beat";
const std::string beat_root_name = "beat";

const std::string em_com_name = "emulator_commands";
const std::string em_com_root_name = "commands";
const std::string em_com_name_attr = "name";
const std::string em_com_entity_name = "command";

const std::string ke_com_name = "kernel_commands";
const std::string ke_com_root_name = "commands";
const std::string ke_com_name_attr = "name";
const std::string ke_com_entity_name = "command";

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

		std::string ke_commands_path = get_node_path(cnfg_node, ke_com_name);
		kernel_commands = get_ke_commands(ke_commands_path);
	}

	configuration::~configuration() {
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
	rapidxml::xml_node<> *reg_node = doc.first_node(reg_root_name);
	std::vector<dv_em::register_scheme> regs;
	
	rapidxml::xml_node<> *cur_reg = reg_node -> first_node(reg_entity_name);
	do 	{
			dv_em::register_scheme scheme;
			rapidxml::xml_attribute<> *name_attr = cur_reg -> first_attribute(reg_name_attr);
			scheme.name = name_attr -> value();

			rapidxml::xml_attribute<> *comment_attr = cur_reg -> first_attribute(reg_comment_attr);
			scheme.comment = comment_attr -> value();

			rapdixml::xml_attribute<> *size_attr = cur_reg -> first_attribute(reg_size_attr);
			scheme.size = (unsigned char)(std::stoi(std::string(size_attr -> value())));

			rapidxml::xml_attribute<> *allowed_modes_attr = cur_reg -> first_attribute(reg_mode_attr);
			scheme.user_allowed_modes = (unsignded char)(std::stoi(std::string(allowed_modes_attr -> value())));

			regs.push_back(scheme);
			cur_reg = cur_reg -> next_sibling();
		} while (cur_reg);

	return regs;
}

std::vector<variable_scheme> get_variables(std::string path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	rapidxml::xml_node<> *var_node = doc.first_node(var_root_name);
	std::vector<dv_em::variable_scheme> vars;
	
	rapidxml::xml_node<> *cur_var = var_node -> first_node(var_entity_name);
	do 	{
			dv_em::variable_scheme scheme;
			rapidxml::xml_attribute<> *name_attr = cur_var -> first_attribute(var_name_attr);
			scheme.name = name_attr -> value();

			rapidxml::xml_attribute<> *comment_attr = cur_var -> first_attribute(var_comment_attr);
			scheme.comment = comment_attr -> value();

			rapdixml::xml_attribute<> *size_attr = cur_var -> first_attribute(var_size_attr);
			scheme.size = (unsigned char)(std::stoi(std::string(size_attr -> value())));

			rapidxml::xml_attribute<> *depth_attr = cur_var -> first_attribute(var_mode_attr);
			scheme.depth = (unsignded char)(std::stoi(std::string(depth_attr -> value())));

			rapidxml::xml_attribute<> *visibility_attr = cur_var -> first_attribute(var_visibility_attr);
			scheme.is_visible = (unsigned char)(std::stoi(std::string(visibility_attr -> value())));

			rapidxml::xml_attribute<> *format_str_attr = cur_var -> first_attribute(var_format_attr);
			scheme.format_string = format_str_attr -> value();
			
			vars.push_back(scheme);
			cur_var = cur_var -> next_sibling();
		} while (cur_var);

	return vars;
}

std::string get_start_state(std::string path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	rapidxml::xml_node<> *start_node = doc.first_node(start_root_name);
	return std::string(start_node -> value());
}

std::string get_beat(std::string path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	rapidxml::xml_node<> *beat_node = doc.first_node(beat_root_name);
	return std::string(beat_node -> value());
}

std::map<std::string, std::string> get_em_commads(std::string path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	rapidxml::xml_node<> *commands_node = doc.first_node(em_com_root_name);
	std::map<std::string, std::string> commands;

	rapidxml::xml_node<> *cur_command = commands_node -> first_node(em_com_entity_name);
	do 	{
			rapidxml::xml_attribute<> *name_attr = cur_command -> first_attribute(em_com_name_attr);
			std::string name = name_attr -> value();

			commands.insert( {name, std::string(cur_command -> value())});	
			cur_command = cur_command -> next_sibling();
		} while (cur_command);

	return commands;
}

std::map<std::string, std::string> get_ke_commands(std::string path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	rapidxml::xml_node<> *commands_node = doc.first_node(ke_com_root_name);
	std::map<std::string, std::string> commands;

	rapidxml::xml_node<> *cur_command = commands_node -> first_node(ke_com_entity_name);
	do 	{
			rapidxml::xml_attribute<> *name_attr = cur_command -> first_attribute(ke_com_name_attr);
			std::string name = name_attr -> value();

			commands.insert( {name, std::string(cur_command -> value())});	
			cur_command = cur_command -> next_sibling();
		} while (cur_command);

	return commands;
}

std::string get_node_path(rapidxml::xml_node<> *cnfg_node, std::string node_name)
{
	rapidxml::xml_node<> *node = cnfg_node -> first_node(node_name);
	rapidxml::xml_attribute<> *path_attr = node -> first_attribute(path_name);
	return path_attr->value();
}

