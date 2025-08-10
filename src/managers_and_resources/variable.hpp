#ifndef VARIABLE_DV_EM_HPP
#define VARIABLE_DV_EM_HPP
#include <vector>

	namespace dv_em {
		class variable {
			private:
				unsigned short int _size;
				unsigned short int _depth;
				std::vector<std::vector<int>> _value;
			public:
				unsigned char allowed_user_nodes;
				bool write(std::vector<std::vector<int>> value, std::vector<unsigned short int> input_offsets, std::vector<unsigned short int> value_offsets, unsigned short int depth_offset);
				bool read(std::vector<std::vector<int>>& value, std::vector<unsigned short int> output_offsets, std::vector<unsigned short int> value_offsets, unsigned short int depth_offset);
		};
	}
#endif
