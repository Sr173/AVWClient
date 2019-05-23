#pragma once
#include "IAVEngine.hpp"

class AVEngine : public IAVEngine
{
public:
	AVEngine();
	~AVEngine();
	int add_virus_db(std::string path);
	unsigned int get_db_known_virus() { return virus_num_; }
	scan_result scan_file(std::string path);
private:
	struct cl_engine* engine;
	unsigned int virus_num_;
};

