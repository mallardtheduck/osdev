#ifndef MODULE_STRING_HPP
#define MODULE_STRING_HPP

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

#include <btos_module.h>

inline static size_t string_strlen(const char *s){
    const char *p = s;
    while (*s) ++s;
    return s - p;
}

/*
 * Like new, we want to guarantee that we NEVER
 * return NULL.  Loop until there is free memory.
 *
 */
static char* malloc_never_null(const size_t b)
{
	char *p = nullptr;

	do{
		p = static_cast<char*>(malloc(b));
	}while(!p);

	return p;
}

static char* strdup_never_null(const char* s)
{
	const size_t len = string_strlen(s)+1;
	char *p = malloc_never_null(len);
	memcpy(p, s, len);
	return p;
}

class string {
	char* p;
public:
	typedef size_t size_type;
	constexpr static size_type npos = static_cast<size_t>(-1);

	string() : p(strdup_never_null("")) {}
	~string(){
		free(p);
	}
	string(const string &s) : p(strdup_never_null(s.p)) {}
	string(const char *s) :  p(strdup_never_null(s)) {}
	string(const char c) : p(strdup_never_null("*")){
		p[0]=c;
	}

	string& operator=(const char* s){
		if ( p != s ) {
			// this should work with overlapping memory
			char *copy = strdup_never_null(s);
			free(p);
			p = copy;
		}

		return *this;
	}
	string& operator=(const string &s){
		return operator=(s.p);
	}

	string& operator+=(const string& s){
		const size_type lenp = string_strlen(p);
		const size_type lens = string_strlen(s.p) + 1;
		p = static_cast<char*>(realloc(p, lenp + lens)); // could return NULL
		memmove(p+lenp, s.p, lens); // p and s.p MAY overlap
		return *this;
	}

	friend string operator+(const string& lhs, const string& rhs){
		return string(lhs) += rhs;
	}

	bool operator==(const char* s) const{
		return !strcmp(p, s);
	}
	bool operator==(const string& s) const{
		return !strcmp(p, s.p);
	}
	
	bool operator!=(const char* s) const{
		return !(*this==s);
	}
	bool operator!=(const string& s) const{
		return !(*this==s);
	}

	void clear(){
		free(p);
		p = strdup_never_null("");
	}

	size_type size() const{
		return string_strlen(p);
	}
	size_type length() const{
		return string_strlen(p);
	}

	bool empty() const{
		return *p == '\0';
	}

	const char* c_str() const{
		return p;
	}

	string substr(const size_type start, const size_type len_orig) const{
		string s;
		size_type len = string_strlen(p);

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

	char operator[](const size_type n) const{
		return p[n];
	}
	char at(const size_type n) const{
		if ( n > string_strlen(p) )
			panic("STRING: Out of range (at).");//throw std::out_of_range("my::string::at()");

		return p[n];
	}

	string& erase(size_type pos, size_type len){
		size_type s = size();

		if ( pos > s )
			panic("STRING: Out of range (erase).");

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

	char *begin(){
		return p;
	}

	const char *begin() const{
		return p;
	}

	char *end(){
		return &p[string_strlen(p)];
	}

	const char *end() const{
		return &p[string_strlen(p)];
	}
};

#endif