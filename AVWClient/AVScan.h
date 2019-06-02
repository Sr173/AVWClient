#pragma once
#include <vector>
#include <string>
#include "IAVEngine.hpp"
#include "Observer.hpp"
#include "BlockQueue.h"
#include "Singleton.hpp"
#include <memory>
#include <deque>
#include <mutex>

class LocalEngine;

struct ScanObservers {
	enum { ScanFinished };
	using ObserverTable = std::tuple<
		Observer<void(scan_result result)>
	>;
};

struct thread_context {
	std::string current_scan_file_name;
	int current_thread_system_id;
	int current_scan_file_count;
};

//单线程调用
class AVScan : public Observable<ScanObservers>,public Singleton<AVScan>
{
public:
	void add_engine(IAVEngine* engine);
	scan_result scan_path(std::string path);
	void set_maximum_number_of_threads(int number);
	void create_scan_thread(thread_context* tc);
	void start(LocalEngine* engine);
	void abort();
	bool is_begining();
	auto get_clean() {
		std::lock_guard<std::mutex> m(lock_vector_);
		return clean_;
	}
	auto get_virtus() {
		std::lock_guard<std::mutex> m(lock_vector_);
		return virus_;
	}
	std::vector<std::shared_ptr<thread_context>> all_thread_context;
	std::string current_scan_path;
	int current_path_number_;
	int scan_number_;
	int all_count;
private:
	LocalEngine* engine;
	bool is_begining_ = false;
	void scan_thread(thread_context* tc);
	BlockQueue<std::string> path_;
	BlockQueue<std::string> scan_file_;
	std::mutex lock_vector_;
	std::vector<scan_result> virus_;
	std::vector<scan_result> clean_;
};

