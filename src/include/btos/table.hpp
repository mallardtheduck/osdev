#ifndef _TABLE_HPP
#define _TABLE_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>

namespace btos_api{
	typedef std::map<std::string, std::string> table_row;
	
	struct table{
		std::vector<std::string> headers;
		std::vector<table_row> rows;
	};
	
	std::vector<std::string> splitline(const std::string &line, char delim);
	std::vector<std::string> splitcsv(const std::string &line);
	table parsecsv(std::istream &file);
	void trim(std::string &str);
}

#endif