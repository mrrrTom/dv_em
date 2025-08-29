#include "tests.hpp"
#include "configuration.hpp"

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
				result += ("\033[32m" + tr.output + "\033[0m");
			}
			else
			{
				result += ("\033[31m" + tr.output + "\033[0m");
			}

			result += '\n';
		}
	
		return result;
	}

	// files level checks
	test_result no_config_file()
	{
		test_result r;
		dv_em::configuration config ("unreal path");
		r.success = !config.initialized;
		r.output = "empty configuration file check";
		return r;
	}

	test_result empty_config_file()
	{
		test_result r;
		r.success = false;
		r.output = "default";
		return r;
	}

	// parsing meta datas
	test_result memory_parsing()
	{
		test_result r;
		r.success = false;
		r.output = "default";
		return r;
	}

	test_result registers_parsing()
	{
		test_result r;
		r.success = false;
		r.output = "default";
		return r;
	}

	test_result variables_parsing()
	{
		test_result r;
		r.success = false;
		r.output = "default";
		return r;
	}

	test_result start_parsing()
	{
		test_result r;
		r.success = false;
		r.output = "default";
		return r;
	}

	test_result beat_parsing()
	{
		test_result r;
		r.success = false;
		r.output = "default";
		return r;
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
