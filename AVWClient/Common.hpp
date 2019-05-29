#pragma once
#include <string>
#include <vector>

struct enum_file
{
	std::vector<std::string> dir;
	std::vector<std::string> file;
};

namespace file {
	enum_file get_all_file_by_dir(std::string path) {
		_finddata64i32_t data;
		auto handle = _findfirst(path.c_str(), &data);
		do {

			std::cout << data.name << " " << data.size << std::endl;
		} while (!_findnext(handle, &data));
	}
}