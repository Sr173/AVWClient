﻿#pragma once
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
	std::string db_all_type;
	std::vector<int> select_db_path;
};