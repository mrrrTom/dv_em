#ifndef TEST_DV_EM_HPP
#define TEST_DV_EM_HPP
#include <string>

using namespace std;

namespace dv_em_test
{
	class test
	{
		public:
			virtual string get_name()
			{
				return "default";
			}

			virtual string execute()
			{
				return "it was not a real test";
			}
	};

	class test_result
	{
		public:
			bool success;
			string output;
	};

	class configuration_test : public test
	{
		public:
			virtual string get_name();
			virtual string execute();
	};
}
#endif
