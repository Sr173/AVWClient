#include "LocalEngine.h"
#include "ClamAv.h"


LocalEngine::LocalEngine()
{
	engine = cl_engine_new();
}


LocalEngine::~LocalEngine()
{
	cl_engine_free(engine);
}

int LocalEngine::add_virus_db(std::vector<std::string> paths)
{
	int old_db_num = db_num;
	for (auto& str : paths) {
		add_virus_db(str);
	}
	return db_num - old_db_num;
}

int LocalEngine::add_virus_db(std::string path)
{
	if (is_build_) return 0;
	int old_num = virus_num_;
	int old_db_num = db_num;
	cl_load(path.c_str(), engine, &virus_num_, CL_DB_STDOPT);
	if (virus_num_ - old_num > 0) {
		db_num++;
	}
	return db_num - old_db_num;
}

scan_result LocalEngine::scan_file(std::string path)
{
	scan_result sr;
	sr.file_name = path;
	cl_scan_options opt;
	opt.general = CL_SCAN_GENERAL_ALLMATCHES;
	opt.parse = CL_SCAN_PARSE_PE;
	sr.scan_bytes = 0;
	const char* buffer = 0;
	int re = cl_scanfile(path.c_str(), &buffer, &sr.scan_bytes, engine, &opt);
	if (buffer)
		sr.virus_name = buffer;
	if (re == CL_CLEAN) sr.result = SS_Clean;
	else if (re == CL_VIRUS) 
		sr.result = SS_Virus;
	else sr.result = SS_Error;
	return sr;
}

void LocalEngine::compiled()
{
	cl_engine_compile(engine);
	is_build_ = true;
}
