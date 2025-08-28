#include "tests.hpp"
#include "configuration.hpp"

using namespace std;

namespace dv_em_test
{
	string configuration_test::get_name()
	{
		return "Configuration tests";
	}

	string configuration_test::execute()
	{
		string result = "checked: ";
		result += no_config_file() + " ";
		result += empty_config_file() + " ";
		result += memory_parsing() + " ";
		result += registers_parsing() + " ";
		result += variables_parsing() + " ";
		result += start_parsing() + " ";
		result += beat_parsing() + " ";
		result += emulator_parsing() + " ";
		result += kernel_parsing() + " ";
	}

	// files level checks
	string no_config_file()
	{
		configuration config ("unreal path");
		
	}

	string empty_config_file()
	{
	}

	// parsing meta datas
	string memory_parsing()
	{
	}

	string registers_parsing()
	{
	}

	string variables_parsing()
	{
	}

	string start_parsing()
	{
	}

	string beat_parsing()
	{
	}

	string emulator_parsing()
	{
	}

	string kernel_parsing()
	{
	}
}
