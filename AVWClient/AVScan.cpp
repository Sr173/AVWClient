#include "AVScan.h"
#include "Config.hpp"
#include "windows.h"
#include "Common.h"
#include "LocalEngine.h"
#include <mutex>
#include <codecvt>
#include "../thrty_party/libgo/libgo.h"
#include "../thrty_party/ClamAV/libclamav/clamav.h"

void AVScan::add_engine(IAVEngine* engine)
{

}


scan_result AVScan::scan_path(std::string path)
{
	return scan_result{};
}

void AVScan::set_maximum_number_of_threads(int number)
{

}

void AVScan::create_scan_thread(thread_context* tc)
{
}

void AVScan::start(LocalEngine* engine)
{
	static auto is_create_thread = false;
	is_begining_ = true;
	this->engine = engine;
	path_.clear();
	path_.push_back(Config::getPtr()->scan_path);
	all_count = 0;
	virus_.clear(); clean_.clear(); scan_file_.clear(); 
	scan_file_.push_back("");
	if (!is_create_thread) {
		for (int i = 0; i < Config::getPtr()->thread_num; i++) {
			is_create_thread = true;
			auto ptr = std::make_shared<thread_context>();
			all_thread_context.push_back(ptr);
			std::thread(&AVScan::scan_thread, this, ptr.get()).detach();
		}
	}
}

void AVScan::abort()
{
	is_begining_ = false;
}

bool AVScan::is_begining()
{
	return is_begining_;
}

bool WCharStringToUTF8String(const std::wstring& wstr, std::string& u8str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> conv;
	u8str = conv.to_bytes(wstr);
	return true;
}


bool StringToWideString(const std::string& src, std::wstring& wstr)
{
	std::locale sys_locale("");
	const char* data_from = src.c_str();
	const char* data_from_end = src.c_str() + src.size();
	const char* data_from_next = 0;

	wchar_t* data_to = new wchar_t[src.size() + 1];
	wchar_t* data_to_end = data_to + src.size() + 1;
	wchar_t* data_to_next = 0;

	wmemset(data_to, 0, src.size() + 1);

	typedef std::codecvt<wchar_t, char, mbstate_t> convert_facet;
	mbstate_t in_state = { 0 };
	auto result = std::use_facet<convert_facet>(sys_locale).in(
		in_state, data_from, data_from_end, data_from_next,
		data_to, data_to_end, data_to_next);
	if (result == convert_facet::ok)
	{
		wstr = data_to;
		delete[] data_to;
		return true;
	}
	delete[] data_to;
	return false;
}

std::string string_to_utf8(std::string s) {
	using namespace std;
	const char* GBK_LOCALE_NAME = ".936"; //GBK在windows下的locale name		

	//构造GBK与wstring间的转码器（wstring_convert在析构时会负责销毁codecvt_byname，所以不用自己delete）
	wstring_convert<codecvt_byname<wchar_t, char, mbstate_t>> cv1(new codecvt_byname<wchar_t, char, mbstate_t>(GBK_LOCALE_NAME));
	wstring tmp_wstr = cv1.from_bytes(s);

	wstring_convert<codecvt_utf8<wchar_t>> cv2;
	string utf8_str = cv2.to_bytes(tmp_wstr);
	return utf8_str;
}

void AVScan::scan_thread(thread_context* tc)
{
	tc->current_thread_system_id = GetCurrentThreadId();
	for (;;) {
		auto cur = scan_file_.pop();
		scan_number_ = scan_file_.size();
		tc->current_scan_file_name = string_to_utf8(cur);
		auto result = engine->scan_file(cur);
		{
			result.virus_name = string_to_utf8(result.virus_name);
			std::lock_guard<std::mutex> m(lock_vector_);
			if (clean_.size() > 10) clean_.clear();

			if (result.result == SS_Virus)
				virus_.push_back(result);
			else
				clean_.push_back(result);
			
			tc->current_scan_file_count++;
		}
		{
			static std::mutex mut;
			std::lock_guard<std::mutex> m(mut);
			while (scan_file_.empty()) {
				auto dir = path_.pop();
				auto res = file::get_all_file_by_dir(dir);
				for (auto i : res.sub_dir) {
					path_.push_back(res.path + i);
				}
				for (auto i : res.file) {
					scan_file_.push_back(res.path + i);
				}
				current_scan_path = dir;
				current_path_number_ = res.file.size();
			}
		}
	}
}
