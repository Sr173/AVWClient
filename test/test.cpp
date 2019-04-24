// test.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
//#include "D:\\bysj\\libgo\\libgo\\libgo.h"
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <io.h>
#include <fcntl.h>
#include <string>
#include "map"
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "windows.h"

using boost::property_tree::ptree;
using boost::property_tree::read_json;
using boost::property_tree::write_json;


void example() {
	// Write json.
	ptree pt;
	pt.put("foo", "bar");
	std::ostringstream buf;
	write_json(buf, pt, false);
	std::string json = buf.str(); // {"foo":"bar"}

	// Read json.
	ptree pt2;
	std::istringstream is(json);
	read_json(is, pt2);
	std::string foo = pt2.get<std::string>("foo");
}

std::map<std::string, std::string> json2map(std::string json) {
	std::map<std::string, std::string> jsonMap;
	ptree pt2;
	std::istringstream is(json);
	ptree child;


	read_json(is, pt2);
	for (auto& i : pt2) {
		jsonMap[i.first] = i.second.data();
	}
	return jsonMap;
}

std::string map2json(const std::map<std::string, std::string>& map) {
	ptree pt;
	for (auto& entry : map)
		pt.put(entry.first, entry.second);
	ptree child;
	child.push_back(std::make_pair("", ptree("1")));
	child.push_back(std::make_pair("", ptree("2")));
	pt.push_back(std::make_pair("ssr", child));
	std::ostringstream buf;
	write_json(buf, pt, false);
	return buf.str();
}
int main()
{
	std::map<std::string, std::string> jsonMap;
	SetConsoleOutputCP(CP_UTF8);

	jsonMap[u8"哈哈"] = "1111";
	jsonMap[u8"GG"] = "2222";
	jsonMap[u8"那你"] = "3333";

	auto strJson =  map2json(jsonMap);
	std::cout << strJson << std::endl;
	auto retnJsonMap = json2map(strJson);

	for (auto i : retnJsonMap) {
		std::cout << i.first << " " << i.second << std::endl;
	}
	return 0;
}