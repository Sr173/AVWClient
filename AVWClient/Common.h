#pragma once
#include <string>
#include <vector>

struct enum_file
{
	std::string path;
	std::vector<std::string> sub_dir;
	std::vector<std::string> file;
};

namespace file {
	enum_file get_all_file_by_dir(std::string path, std::string filter = "*.*");
}