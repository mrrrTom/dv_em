#include <iostream>
#include <vector>
#include "tests.hpp"

using namespace std;
using namespace dv_em_test;

int main()
{
	cout << "testing started" << endl;
	vector<test*> tests
	{
		new configuration_test()
	};

	for (int i = 0; i < tests.size(); i++)
	{
		test* t = tests[i];
		cout << "executes test: " << t -> get_name() << " with result:\n"
			<< t -> execute() << endl;

		delete(t);
	}
	
	cout << "testing finished" << endl;
	return 0;
}
