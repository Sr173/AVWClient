#pragma once
#include "IAVEngine.hpp"

class OnlineEngine : public IAVEngine
{
public:
	int add_virus_db(std::string path) override;
	unsigned int get_db_known_virus() override;
	scan_result scan_file(std::string path) override;
};

