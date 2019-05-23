#include "../thrty_party/ClamAV/libclamav/clamav.h"
#include "iostream"

int mainchawefdsfwer()
{
	cl_initialize_crypto();
	std::cout << "init:" << cl_init(1) << std::endl;
	auto engine = cl_engine_new();
	unsigned int a = 0;
	//std::cout << cl_load("C:\\Users\\admin\\Personal\\lib\\clamav\\cvd\\daily.mdb", engine, &a, CL_DB_STDOPT) << std::endl;
	std::cout << cl_load("C:\\Users\\admin\\Personal\\lib\\clamav\\cvd\\daily.ldb", engine, &a, CL_DB_STDOPT) << std::endl;

	system("pause");
	return 1;
}