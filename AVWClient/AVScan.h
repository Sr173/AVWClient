#pragma once
#include <vector>
#include <string>
#include "IAVEngine.hpp"
#include "Observer.hpp"
#include "BlockQueue.h"

class LocalEngine;

struct ScanObservers {
	enum { ScanFinished };
	using ObserverTable = std::tuple<
		Observer<void(scan_result result)>
	>;
};

//单线程调用
class AVScan : public Observable<ScanObservers>
{
public:
	void add_engine(IAVEngine* engine);
	void scan_file(std::string file);
	void scan_path(std::string path);
	void set_maximum_number_of_threads(int number);
private:
	std::vector<IAVEngine*> engines;
};

