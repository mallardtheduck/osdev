#ifndef _TABLE_HPP
#define _TABLE_HPP

#include <map>
#include <vector>
#include <string>
#include <iostream>


typedef std::map<std::string, std::string> table_row;

struct table{
	std::vector<std::string> headers;
	std::vector<table_row> rows;
};

table parsecsv(std::istream &file);
void display_table(table tbl, size_t width, std::ostream &output=std::cout);
std::vector<std::string> splitline(const std::string &line, char delim);

#endif
