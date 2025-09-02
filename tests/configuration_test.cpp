#include "tests.hpp"
#include "configuration.hpp"
#include <fstream>
#include <cstdio>

using namespace std;
using namespace dv_em;

namespace dv_em_test
{
	test_result no_config_file();
	test_result empty_config_file();
	test_result memory_parsing();
	test_result registers_parsing();
	test_result variables_parsing();
	test_result start_parsing();
	test_result beat_parsing();
	test_result emulator_parsing();
	test_result kernel_parsing();

	string configuration_test::get_name()
	{
		return "Configuration tests";
	}

	string configuration_test::execute()
	{
		string result = "";
		vector<test_result (*) ()> config_tests;
		config_tests.push_back(&no_config_file);
		config_tests.push_back(&empty_config_file);
		config_tests.push_back(&memory_parsing);
		config_tests.push_back(&registers_parsing);
		config_tests.push_back(&variables_parsing);
		config_tests.push_back(&start_parsing);
		config_tests.push_back(&beat_parsing);
		config_tests.push_back(&emulator_parsing);
		config_tests.push_back(&kernel_parsing);
		
		for (auto test:config_tests)
		{
			auto tr = test();
			auto output = tr.output;
			if (tr.success)
			{
				result += ("\t\033[32m" + tr.output + "\033[0m");
			}
			else
			{
				result += ("\t\033[31m" + tr.output + "\033[0m");
			}

			result += '\n';
		}
	
		return result;
	}

	// files level checks
	test_result no_config_file()
	{
		try 
		{
			test_result r;
			dv_em::configuration config ("unreal path");
			r.success = !config.initialized;
			r.output = "no configuration file check";
			return r;
		}
		catch (...)
		{
			test_result err_r;
			err_r.success = false;
			err_r.output = "no configuration file check got execution error";
			return err_r;
		}
	}

	test_result empty_config_file()
	{
		try
		{
			test_result r;
			string empty_file_name = "./tests/empty.xml";
			ofstream empty_file (empty_file_name);
			empty_file.close();
			dv_em::configuration config(empty_file_name);
		
			r.success = config.initialized &&
						(!config.memory_model) &&
						(config.registers_model.size() == 0) &&
						(config.variables_model.size() == 0) &&
						(config.start_state == "") &&
						(config.beat == "") &&
						(config.emulator_commands.size() == 0) &&
						(config.kernel_commands.size() == 0);
		
			r.output = "empty configuration file check";
			remove(empty_file_name.c_str());
			return r;
		}
		catch (...)
		{
			test_result err_r;
			err_r.success = false;
			err_r.output = "empty configuration file check got execution error";
			return err_r;
		}
	}

	void create_memory_file(string file_name, cell_scheme data)
	{
		ofstream fs(file_name);
		string xml_data = "<memory_cell>";
		xml_data += ("<address_size>" + to_string(data.address_size));
		xml_data += "</address_size>";
		xml_data += ("<command_first_bit>" + to_string(data.command_first_bit));
		xml_data += "</command_first_bit>";
		xml_data += ("<command_last_bit>" + to_string(data.command_last_bit));
		xml_data += "</command_last_bit>";
		xml_data += ("<arguments_first_bit>" + to_string(data.arguments_first_bit));
		xml_data += "</arguments_first_bit>";
		xml_data += ("<arguments_last_bit>" + to_string(data.arguments_last_bit));
		xml_data += "</arguments_last_bit>";
		xml_data += ("<fixed_operand_size>" + to_string(data.fixed_operand_size));
		xml_data += "</fixed_operand_size>";
		xml_data += ("<operand_size>" + to_string(data.operand_size));
		xml_data += "</operand_size>";
		xml_data += "</memory_cell>";
		fs << xml_data;
		fs.close();
	}

	// parsing meta datas
	test_result memory_parsing()
	{
		try
		{
			test_result r;
			string memory_file_name = "./tests/memory_parsing_test_memory_config.xml";
			cell_scheme mm {
				4,
				17,
				29,
				12,
				222,
				0,
				34
			};
			create_memory_file(memory_file_name, mm); 
			
			string config_file_name = "./tests/memory_parsing_test_config.xml";
			ofstream config_file (config_file_name);
			string config_file_data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
			config_file_data += "<config> <memory path=\'";
			config_file_data += memory_file_name;
			config_file_data += "\'/> </config>";
			config_file << config_file_data;
			config_file.close();
			r.output = "memory parsing check";
			configuration config(config_file_name);
			
			r.success = config.initialized &&
						(config.memory_model -> address_size == mm.address_size) &&
						(config.memory_model -> command_first_bit == mm.command_first_bit) &&
						(config.memory_model -> command_last_bit == mm.command_last_bit) &&
						(config.memory_model -> arguments_first_bit == mm.arguments_first_bit) &&
						(config.memory_model -> arguments_last_bit == mm.arguments_last_bit) &&
						(config.memory_model -> fixed_operand_size == mm.fixed_operand_size) &&
						(config.memory_model -> operand_size == mm.operand_size);
			remove(memory_file_name.c_str());
			remove(config_file_name.c_str());
			return r;
		}
		catch (exception& e)
		{
			test_result err_r;
			err_r.success = false;
			string msg = e.what();
			err_r.output = ("memory parsing check got execution error: " + msg + '\n');
			return err_r;
		}
	}
	
	void create_registers_file(string file_name, vector<register_scheme> registers)
	{
		ofstream fs(file_name);
		string xml_data = "<registers>";
		for (auto reg:registers)
		{
			xml_data += ("<reg name=\"" + reg.name);
			xml_data += "\" ";
			xml_data += ("comment=\"" + reg.comment);
			xml_data += "\" ";
			xml_data += ("size=\'" + to_string(reg.size));
			xml_data += "\' ";
			xml_data += ("modes=\'" + to_string(reg.user_allowed_modes));
			xml_data += "\' />";
		}
		xml_data += "</registers>";
		fs << xml_data;
		fs.close();
	}

	test_result registers_parsing()
	{
		try
		{
			test_result r;
			string registers_file_name = "./tests/registers_parsing_test_registers_config.xml";
			register_scheme r1 {
				"first_register",
				"this is first created register",
				10,
				2
			};
			register_scheme r2 {
				"second_register",
				"this is second created register",
				12,
				1
			};
			
			create_registers_file(registers_file_name, vector<register_scheme> {r1, r2});
			string config_file_name = "./tests/registers_parsing_test_config.xml";
			ofstream config_file (config_file_name);
			string config_file_data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
			config_file_data += "<config> <registers path=\'";
			config_file_data += registers_file_name;
			config_file_data += "\'/> </config>";
			config_file << config_file_data;
			config_file.close();
			r.output = "registers parsing check";
			configuration config(config_file_name);

			r.success = config.initialized &&
						(config.registers_model[0].name == r1.name) &&
						(config.registers_model[0].comment == r1.comment) &&
						(config.registers_model[0].size == r1.size) &&
						(config.registers_model[0].user_allowed_modes) &&
						(config.registers_model[1].name == r2.name) &&
						(config.registers_model[1].comment == r2.comment) &&
						(config.registers_model[1].size == r2.size) &&
						(config.registers_model[1].user_allowed_modes);
			remove(config_file_name.c_str());
			remove(registers_file_name.c_str());
			return r;
		}
		catch (exception& e)
		{
			test_result err_r;
			err_r.success = false;
			string msg = e.what();
			err_r.output = ("registers parsing check got execution error: " + msg + '\n');
			return err_r;
		}
	}
	
	void create_variables_file(string file_name, vector<variable_scheme> vars)
	{
		ofstream fs(file_name);
		string xml_data = "<variables>";
		for (auto var:vars)
		{
			xml_data += ("<var name=\"" + var.name);
			xml_data += "\" ";
			xml_data += ("comment=\"" + var.comment);
			xml_data += "\" ";
			xml_data += ("size=\'" + to_string(var.size));
			xml_data += "\' ";
			xml_data += ("depth=\'" + to_string(var.depth));
			xml_data += "\' ";
			xml_data += ("is_visible=\'" + to_string(var.is_visible));
			xml_data += "\' ";
			xml_data += ("format_string=\'" + var.format_string);
			xml_data += "\' />";
		}
		xml_data += "</variables>";
		fs << xml_data;
		fs.close();
	}

	test_result variables_parsing()
	{
		try
		{
			test_result r;
			string variables_file_name = "./tests/variables_parsing_test_variables_config.xml";
			variable_scheme v1 {
				"var1",
				"first created variable",
				12,
				2,
				1,
				"{*(&%#$"
			};
			variable_scheme v2 {
				"var2",
				"second created variable",
				18,
				5,
				0,
				"113423%$^"
			};
			create_variables_file(variables_file_name, vector<variable_scheme> {v1, v2});
			string config_file_name = "./tests/variables_parsing_test_config.xml";
			ofstream config_file (config_file_name);
			string config_file_data = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
			config_file_data += "<config> <variables path=\'";
			config_file_data += variables_file_name;
			config_file_data += "\'/> </config>";
			config_file << config_file_data;
			config_file.close();
			r.output = "variables parsing check";
			configuration config(config_file_name);

			r.success = config.initialized &&
						(config.variables_model[0].name == v1.name) &&
						(config.variables_model[0].comment == v1.comment) &&
						(config.variables_model[0].size == v1.size) &&
						(config.variables_model[0].depth == v1.depth) &&
						(config.variables_model[0].is_visible == v1.is_visible) &&
						(config.variables_model[0].format_string == v1.format_string) &&
						(config.variables_model[1].name == v2.name) &&
						(config.variables_model[1].comment == v2.comment) &&
						(config.variables_model[1].size == v2.size) &&
						(config.variables_model[1].depth == v2.depth) &&
						(config.variables_model[1].is_visible == v2.is_visible) &&
						(config.variables_model[1].format_string == v2.format_string);
			remove(config_file_name.c_str());
			remove(variables_file_name.c_str());
			return r;
		}
		catch (exception& e)
		{
			test_result err_r;
			err_r.success = false;
			string msg = e.what();
			err_r.output = ("registers parsing check got execution error: " + msg + '\n');
			return err_r;
		}
	}
	
	void create_start_file(string file_name, string start_state)
	{
		ofstream fs(file_name);
		string xml_data = "<start>";
		xml_data += start_state;
		xml_data += "</start>";
		fs << xml_data;
		fs.close();
	}

	test_result start_parsing()
	{
		try
		{
			test_result r;
			string start_file_name = "./tests/start_parsing_test_start_config.xml";
			string s = "this is start state";
			create_start_file(start_file_name, s);
			string config_file_name = "./tests/start_parsing_test_config.xml";
			ofstream config_file (config_file_name);
			string config_file_data = "<?xml version=\"1.0\" encofing=\"UTF-8\"?>";
			config_file_data += "<config> <start path=\'";
			config_file_data += start_file_name;
			config_file_data += "\'/> </config>";
			config_file << config_file_data;
			config_file.close();
			r.output = "start state parsing check";
			configuration config(config_file_name);

			r.success = config.initialized &&
						(config.start_state == s);
			remove(config_file_name.c_str());
			remove(start_file_name.c_str());
			return r;
		}
		catch (exception& e)
		{
			test_result err_r;
			err_r.success = false;
			string msg = e.what();
			err_r.output = ("start parsing check got execution error: " + msg + '\n');
			return err_r;
		}
	}

	void create_beat_file(string file_name, string beat)
	{
		ofstream fs(file_name);
		string xml_data = "<beat>";
		xml_data += beat;
		xml_data += "</beat>";
		fs << xml_data;
		fs.close();
	}

	test_result beat_parsing()
	{
		try
		{
			test_result r;
			string beat_file_name = "./tests/beat_parsing_test_beat_config.xml";
			string b = "this is beat";
			create_beat_file(beat_file_name, b);
			string config_file_name = "./tests/beat_parsing_test_config.xml";
			ofstream config_file (config_file_name);
			string config_file_data = "<?xml version=\"1.0\" encofing=\"UTF-8\"?>";
			config_file_data += "<config> <beat path=\'";
			config_file_data += beat_file_name;
			config_file_data += "\'/> </config>";
			config_file << config_file_data;
			config_file.close();
			r.output = "beat parsing check";
			configuration config(config_file_name);

			r.success = config.initialized &&
						(config.beat == b);
			remove(config_file_name.c_str());
			remove(beat_file_name.c_str());
			return r;
		}
		catch (exception& e)
		{
			test_result err_r;
			err_r.success = false;
			string msg = e.what();
			err_r.output = ("beat parsing check got execution error: " + msg + '\n');
			return err_r;
		}
	}

	test_result emulator_parsing()
	{
		test_result r;
		r.success = false;
		r.output = "default";
		return r;
	}

	test_result kernel_parsing()
	{
		test_result r;
		r.success = false;
		r.output = "default";
		return r;
	}
}

