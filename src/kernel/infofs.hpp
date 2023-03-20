#ifndef _INFOFS_HPP
#define _INFOFS_HPP

#include <module/utils/function.hpp>

class IInfoFS : private nonmovable{
	public:
	virtual void Register(const char *name, function<char*()> fn) = 0;

	virtual ~IInfoFS(){}
};

void InfoRegister(const char *name, function<char*()> fn);

void Info_Init();

#endif