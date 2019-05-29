#pragma once
#include <vector>
#include <string>
#include "IAVEngine.hpp"
#include "Observer.hpp"
#include "BlockQueue.h"
#include "Singleton.hpp"

class LocalEngine;

struct ScanObservers {
	enum { ScanFinished };
	using ObserverTable = std::tuple<
		Observer<void(scan_result result)>
	>;
};

struct thread_context {
	std::string current_scan_file_name;
	void* current_thread_system_id;
	int current_scan_file_count;
};

//单线程调用
class AVScan : public Observable<ScanObservers>,public Singleton<AVScan>
{
public:
	void add_engine(IAVEngine* engine);
	std::vector<scan_result> scan_file(std::string file);
	scan_result scan_path(std::string path);
	void set_maximum_number_of_threads(int number);
	void create_scan_thread(thread_context* tc);
private:
	std::vector<IAVEngine*> engines;
	std::vector<thread_context> all_thread_;
};

