/* $Id: my_string.cpp 16 2007-12-07 17:43:41Z csl $
 *
 * Copyright (C) Christian Stigen Larsen, 2007
 * Placed in the Public Domain by the author.
 *
 * Bug reports or suggestions to <csl@sublevel3.org>
 *
 * IMPLEMENTATION NOTES
 *
 * My goal was to create a small, and conceptually simple
 * string class.  I allocate unique memory for every object
 * created, instead of doing anything fancy.
 *
 * I've taken care about the order in which I free memory,
 * in case we are copying overlapping regions.
 *
 * I should also have thrown some exceptions, feel free to
 * add that yourself (and send me the patch).
 *
 * I don't check if realloc returns NULL, though.
 *
 */

#include "kernel.hpp"
#include "string.hpp"

const string::size_type string::npos = static_cast<size_t>(-1);

/*
 * Like new, we want to guarantee that we NEVER
 * return NULL.  Loop until there is free memory.
 *
 */
static char* malloc_never_null(const size_t b)
{
	char *p;

	do {
		p = static_cast<char*>(malloc(b));
	} while ( p == NULL );

	return p;
}

static char* strdup_never_null(const char* s)
{
	const size_t len = strlen(s)+1;
	char *p = malloc_never_null(len);
	memcpy(p, s, len);
	return p;
}

string::string() : p(strdup_never_null(""))
{
}

string::~string()
{
	free(p);
}

string::string(const string& s) : p(strdup_never_null(s.p))
{
}

string::string(const char* s) : p(strdup_never_null(s))
{
}

string& string::operator=(const char* s)
{
	if ( p != s ) {
		// this should work with overlapping memory
		char *copy = strdup_never_null(s);
		free(p);
		p = copy;
	}

	return *this;
}

string& string::operator=(const string& s)
{
	return operator=(s.p);
}

string& string::operator+=(const string& s)
{
	const size_type lenp = strlen(p);
	const size_type lens = strlen(s.p) + 1;
	p = static_cast<char*>(realloc(p, lenp + lens)); // could return NULL
	memmove(p+lenp, s.p, lens); // p and s.p MAY overlap
	return *this;
}

bool string::operator==(const char* s) const
{
	return !strcmp(p, s);
}

bool string::operator==(const string& s) const
{
	return !strcmp(p, s.p);
}

void string::clear()
{
	free(p);
	p = strdup_never_null("");
}

string operator+(const string& lhs, const string& rhs)
{
	return string(lhs) += rhs;
}

string::size_type string::size() const
{
	return strlen(p);
}

bool string::empty() const
{
	return *p == '\0';
}

const char* string::c_str() const
{
	return p;
}

string string::substr(const size_type start, const size_type len_orig) const
{
	string s;
	size_type len = strlen(p);

	if ( start > len )
		panic("STRING: Out of range (substr).");//throw std::out_of_range("my::string::substr");

	if ( len > len_orig )
		len = len_orig;

	free(s.p);
	s.p = malloc_never_null(len+1);
	memcpy(s.p, p + start, len);
	s.p[len] = '\0';

	return s;
}

// unchecked access
char string::operator[](const size_type n) const
{
	return p[n];
}

// checked access
char string::at(const size_type n) const
{
	if ( n > strlen(p) )
		panic("STRING: Out of range (at).");//throw std::out_of_range("my::string::at()");

	return p[n];
}

string& string::erase(size_type pos, size_type len)
{
	size_type s = size();

	if ( pos > s )
		panic("STRING: Out of range (erase).");//throw std::out_of_range("my::string::erase");

	s -= pos;
	if ( len > s )
		len = s;
	++s;

	// erase by overwriting
	memmove(p + pos, p + pos + len, s);

	// remove unused space
	p = static_cast<char*>(realloc(p, s+pos));

	return *this;
}

