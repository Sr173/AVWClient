#pragma once
#include <string>
#include <vector>

enum scan_status
{
	SS_Clean,
	SS_Virus,
	SS_Error
};

struct scan_result
{
	scan_status result;
	std::string file_name;
	std::string virus_name;
	unsigned long scan_bytes;
	unsigned long time;
};

class IAVEngine
{
public:
	virtual int add_virus_db(std::string path) = 0;
	virtual unsigned int get_db_known_virus() = 0;
	virtual scan_result scan_file(std::string path) = 0;
};

