#pragma once
#include "Singleton.hpp"
#include <string>
#include "vector"

enum RunnerModel
{
	Online,
	OffLine
};

class Config : public Singleton<Config>
{
public:
	int thread_num = 1;
	std::string db_uri;
	RunnerModel runner_model;
	std::vector <std::string> db_all_type;
	std::vector<int> select_db_path;
	std::string scan_path;
	int db_num;
	const std::string app_path = "C:\\Users\\admin\\AppData\\Roaming\\cClamAV\\";
};
