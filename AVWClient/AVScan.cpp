#include "AVScan.h"


void AVScan::add_engine(IAVEngine* engine)
{
	engines.push_back(engine);
}

std::vector<scan_result> AVScan::scan_file(std::string filePath)
{
	std::vector<scan_result> result;
	for (auto i : engines)
	{
		result.push_back(i->scan_file(filePath));
	}
	return std::move(result);
}

scan_result AVScan::scan_path(std::string path)
{
	return scan_result{};
}

void AVScan::set_maximum_number_of_threads(int number)
{

}