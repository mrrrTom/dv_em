#ifndef REGISTER_DV_H
#define REGISTER_DV_H
#include <string>
#include <vector>
namespace dv_em {
	class pregister{
		private:
			unsigned short int _size;
			vector<int> _value;
		public:
			unsigned char allowed_user_nodes;
			bool write(vector<int> value, unsigned short int input_offset, unsigned short int value_offset);
			bool read(vector<int>& value, unsigned short int output_offset, unsigned short int value_offset);
	};
}
#endif

