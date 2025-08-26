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

	class configuration_test : public test
	{
		public:
			virtual string get_name();
			virtual string execute();
	};
}
