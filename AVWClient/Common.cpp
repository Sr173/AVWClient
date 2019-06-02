#include "Common.h"
#include "io.h"

enum_file file::get_all_file_by_dir(std::string path,std::string filter)
{
	enum_file result;

	_finddata64i32_t data;
	result.path = path;
	path += filter;
	auto handle = _findfirst(path.c_str(), &data);
	if (handle <= 0) return result;
	do {
		if (data.attrib != _A_SUBDIR) {
			if ((strcmp(data.name,".") && strcmp(data.name, "..")))
				result.file.push_back(data.name);
		}
		else {
			if ((strcmp(data.name, ".") && strcmp(data.name, "..")))
				result.sub_dir.push_back(std::string(data.name) + "\\");
		}
	} while (!_findnext(handle, &data));	
	return result;
}
