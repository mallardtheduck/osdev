#ifndef _STRING_HPP
#define _STRING_HPP

/* $Id: my_string.h 16 2007-12-07 17:43:41Z csl $
 *
 * Copyright (C) Christian Stigen Larsen, 2007
 * Placed in the Public Domain by the author.
 *
 * My go at writing a simple string class.
 *
 * You can probably replace std::string with this one in many
 * cases, but a lot of stuff is missing, and I would recommend
 * you stick to std::string anyway.
 *
 * I want to point out that there is nothing fancy about this class.
 * It keeps every string in its own buffer, and copies as often as
 * needed.
 *
 * However, I believe that is a good approach.  For instance, it
 * uses malloc rather than new, which makes it possible to use
 * realloc.  On many systems, realloc will try to use up "invisible"
 * space that was used by malloc to pad a string for memory alignment.
 * That makes it potentially fast for small concatenations.
 *
 * I don't propose to use this class for anything practical, since
 * we already have std::string, but it may be an interesting read
 * for C++ novices at the very least.
 *
 * If you're actually going to use this, at least inline c_str(),
 * empty(), size() and operator[], or even all of the one-line
 * functions.
 *
 * Please send bug reports and suggestions to <csl@sublevel3.org>
 *
 */

#include "kernel.hpp"

class string {
	char* p;
public:
	typedef size_t size_type;
	static const size_type npos;

	string();
	virtual ~string();
	string(const string&);
	string(const char*);
	string(const char);
	string& operator=(const char*);
	string& operator=(const string&);
	string& operator+=(const string&);
	friend string operator+(const string& lhs, const string& rhs);
	bool operator==(const char*) const;
	bool operator==(const string&) const;
	bool operator!=(const char*) const;
	bool operator!=(const string&) const;
	void clear();
	size_type size() const;
	bool empty() const;
	const char* c_str() const;
	string substr(const size_type start, const size_type length) const;
	char operator[](const size_type n) const;
	char at(const size_type n) const;
	string& erase(size_type pos, size_type len);
};

#endif
