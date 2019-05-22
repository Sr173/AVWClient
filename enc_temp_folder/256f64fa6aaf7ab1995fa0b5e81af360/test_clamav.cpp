#include "../thrty_party/ClamAV/libclamav/clamav.h"
#include "iostream"

int main()
{
	std::cout << "init:" << cl_init(1) << std::endl;
	system("pause");
}