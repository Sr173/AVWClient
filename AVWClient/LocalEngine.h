#pragma once
#include "IAVEngine.hpp"

class LocalEngine : public IAVEngine
{
public:
	LocalEngine();
	~LocalEngine();
	int add_virus_db(std::vector<std::string> paths);
	unsigned int get_db_known_virus() { return virus_num_; }
	scan_result scan_file(std::string path);
	auto get_db_num() { return db_num; }
private:
	struct cl_engine* engine;
	unsigned int virus_num_;
	unsigned db_num;
};

