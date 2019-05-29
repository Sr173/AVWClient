
#include <iostream>
#include "io.h"

int main()
{
	std::string path = "C:\\Users\\admin\\personal\\Graduation Project\\source\\AVWClient\\AVWClient\\*";
	_finddata64i32_t data;
	auto handle = _findfirst(path.c_str(), &data);
	do {

		std::cout << data.name << " " << data.size << std::endl;
	} while (!_findnext(handle, &data));
}
