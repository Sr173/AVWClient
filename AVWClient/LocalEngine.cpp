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

int LocalEngine::add_virus_db(std::string path)
{
	int old_num = virus_num_;
	cl_load(path.c_str(), engine, &virus_num_, CL_DB_STDOPT);
	return virus_num_ - old_num;
}

scan_result LocalEngine::scan_file(std::string path)
{
	scan_result sr;
	sr.file_name = path;
	cl_scan_options opt;
	opt.general = CL_SCAN_GENERAL_ALLMATCHES;
	opt.parse = CL_SCAN_PARSE_PE;

	char name_buffer[100];
	int re = cl_scanfile(path.c_str(), (const char**)(&name_buffer), &sr.scan_bytes, engine, &opt);
	if (re == CL_CLEAN) sr.result = SS_Clean;
	else if (re == CL_CLEAN) sr.result = SS_Virus;
	else sr.result = SS_Error;
	return sr;
}
