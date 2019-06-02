#pragma once
#include "IAVEngine.hpp"
#include <boost\beast\http\detail\rfc7230.hpp>

class LocalEngine : public IAVEngine
{
public:
	LocalEngine();
	~LocalEngine();
	int add_virus_db(std::vector<std::string> paths);
	int add_virus_db(std::string path);
	unsigned int get_db_known_virus() { return virus_num_; }
	scan_result scan_file(std::string path);
	auto get_db_num() { return db_num; }
	void compiled();
private:
	struct cl_engine* engine;
	unsigned int virus_num_;
	unsigned db_num;
	bool is_build_ = false;
};

