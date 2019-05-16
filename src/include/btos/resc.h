#ifndef _RESC_H
#define _RESC_H

#include <util/bt_enum.h>

#ifdef __cplusplus
	#include <istream>
	#include <string>
#else
	#include <stdbool.h>
#endif

NS_BEGIN(btos)
NS_BEGIN(resc)

typedef void* RescHandle;

EXTERN_C_BEGIN

RescHandle Resc_LocalOpen(const char *data, size_t size);
RescHandle Resc_FileOpen(const char *filename);
RescHandle Resc_FDOpen(int fd);

int Resc_OpenResc(RescHandle h, const char *filename);
bool Resc_RescExists(RescHandle h, const char *filename);

int Resc_OpenTar(RescHandle h);

EXTERN_C_END

#ifdef __cplusplus

inline RescHandle Resc_FileOpen(const std::string &filename){
	return Resc_FileOpen(filename.c_str());
}

inline int Resc_OpenResc(RescHandle h, const std::string &filename){
	return Resc_OpenResc(h, filename.c_str());
}

std::istream &Resc_OpenRescStream(RescHandle h, const std::string &filename);
std::istream &Resc_OpenTarStream(RescHandle h);

#endif

NS_END
NS_END

#endif