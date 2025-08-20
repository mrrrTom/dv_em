#include "configuration.hpp"
const char* cnfg_node_name = "config";

const char* mem_name = "memory";
const char* mem_root_name = "memory_cell";
const char* mem_addr_size_name = "address_size";
const char* mem_com_first_bit_name = "command_first_bit";
const char* mem_com_last_bit_name = "command_last_bit";
const char* mem_arg_first_bit_name = "arguments_first_bit";
const char* mem_arg_last_bit_name = "arguments_last_bit";
const char* mem_fixed_oper_name = "fixed_operands_size";
const char* mem_operand_size_name = "operand_size";

const char* reg_name = "registers";
const char* reg_root_name = "registers";
const char* reg_entity_name = "reg";
const char* reg_name_attr = "name";
const char* reg_comment_attr = "comment";
const char* reg_size_attr = "size";
const char* reg_mode_attr = "modes";

const char* var_name = "variables";
const char* var_root_name = "variables";
const char* var_entity_name = "var";
const char* var_name_attr = "name";
const char* var_comment_attr = "comment";
const char* var_size_attr = "size";
const char* var_depth_attr = "depth";
const char* var_visibility_attr = "is_visible";
const char* var_format_attr = "format_string";

const char* start_name = "start";
const char* start_root_name = "start";

const char* beat_name = "beat";
const char* beat_root_name = "beat";

const char* em_com_name = "emulator_commands";
const char* em_com_root_name = "commands";
const char* em_com_name_attr = "name";
const char* em_com_entity_name = "command";

const char* ke_com_name = "kernel_commands";
const char* ke_com_root_name = "commands";
const char* ke_com_name_attr = "name";
const char* ke_com_entity_name = "command";

const char* path_name = "path";

dv_em::cell_scheme get_memory(const char* path);
std::vector<dv_em::register_scheme> get_registers(const char* path);
std::vector<dv_em::variable_scheme> get_variables(const char* path);
std::string get_start_state(const char* path);
std::string get_beat(const char* path);
std::map<std::string, std::string> get_em_commands(const char* path);
std::map<std::string, std::string> get_ke_commands(const char* path);
char* get_node_path(rapidxml::xml_node<> *cnfg_node, const char* node_name);

namespace dv_em {
	configuration::configuration(const std::string input_path) {
		const char* path = input_path.c_str();
		rapidxml::file<> xmlFile(path);
		rapidxml::xml_document<> doc;
		doc.parse<0>(xmlFile.data());
		rapidxml::xml_node<> *cnfg_node = doc.first_node(cnfg_node_name);
		char* memory_path = get_node_path(cnfg_node, mem_name);
		memory_model = get_memory(memory_path);
		
		char* registers_path = get_node_path(cnfg_node, reg_name);
		registers_model = get_registers(registers_path);

		char* variables_path = get_node_path(cnfg_node, var_name);
		variables_model = get_variables(variables_path);

		char* start_path = get_node_path(cnfg_node, start_name);
		start_state = get_start_state(start_path);

		char* beat_path = get_node_path(cnfg_node, beat_name);
		beat = get_beat(beat_path);

		char* em_commands_path = get_node_path(cnfg_node, em_com_name);
		emulator_commands = get_em_commands(em_commands_path);

		char* ke_commands_path = get_node_path(cnfg_node, ke_com_name);
		kernel_commands = get_ke_commands(ke_commands_path);
	}

	configuration::~configuration() {
	} 
}

dv_em::cell_scheme get_memory(const char *path)
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

std::vector<dv_em::register_scheme> get_registers(const char *path)
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

			rapidxml::xml_attribute<> *size_attr = cur_reg -> first_attribute(reg_size_attr);
			scheme.size = (unsigned char)(std::stoi(std::string(size_attr -> value())));

			rapidxml::xml_attribute<> *allowed_modes_attr = cur_reg -> first_attribute(reg_mode_attr);
			scheme.user_allowed_modes = (unsigned char)(std::stoi(std::string(allowed_modes_attr -> value())));

			regs.push_back(scheme);
			cur_reg = cur_reg -> next_sibling();
		} while (cur_reg);

	return regs;
}

std::vector<dv_em::variable_scheme> get_variables(const char *path)
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

			rapidxml::xml_attribute<> *size_attr = cur_var -> first_attribute(var_size_attr);
			scheme.size = (unsigned char)(std::stoi(std::string(size_attr -> value())));

			rapidxml::xml_attribute<> *depth_attr = cur_var -> first_attribute(var_depth_attr);
			scheme.depth = (unsigned char)(std::stoi(std::string(depth_attr -> value())));

			rapidxml::xml_attribute<> *visibility_attr = cur_var -> first_attribute(var_visibility_attr);
			scheme.is_visible = (unsigned char)(std::stoi(std::string(visibility_attr -> value())));

			rapidxml::xml_attribute<> *format_str_attr = cur_var -> first_attribute(var_format_attr);
			scheme.format_string = format_str_attr -> value();
			
			vars.push_back(scheme);
			cur_var = cur_var -> next_sibling();
		} while (cur_var);

	return vars;
}

std::string get_start_state(const char *path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	rapidxml::xml_node<> *start_node = doc.first_node(start_root_name);
	return std::string(start_node -> value());
}

std::string get_beat(const char *path)
{
	rapidxml::file<> xmlFile(path);
	rapidxml::xml_document<> doc;
	doc.parse<0>(xmlFile.data());

	rapidxml::xml_node<> *beat_node = doc.first_node(beat_root_name);
	return std::string(beat_node -> value());
}

std::map<std::string, std::string> get_em_commands(const char *path)
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

std::map<std::string, std::string> get_ke_commands(const char *path)
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

char* get_node_path(rapidxml::xml_node<> *cnfg_node, const char* node_name)
{
	rapidxml::xml_node<> *node = cnfg_node -> first_node(node_name);
	rapidxml::xml_attribute<> *path_attr = node -> first_attribute(path_name);
	return path_attr->value();
}

