#include "Common.h"
#include "iostream"

int majdsfiosdhfioin() {
	auto i = file::get_all_file_by_dir("C:\\Users\\admin\\personal\\Graduation Project\\source\\AVWClient\\AVWClient\\");
	for (auto& gg : i.file) {
		std::cout << gg << std::endl;
	}
	return 0;
}