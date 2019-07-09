#ifndef _RESC_H
#define _RESC_H

#include <util/bt_enum.h>

#ifdef __cplusplus
	#include <istream>
	#include <string>
#else
	#include <stdbool.h>
#endif

NS_BEGIN(btos_api)
NS_BEGIN(resc)

typedef void* RescHandle;
typedef void* RescList;

EXTERN_C_BEGIN

RescHandle Resc_LocalOpen(const char *data, size_t size);
RescHandle Resc_FileOpen(const char *filename);
RescHandle Resc_FDOpen(int fd);

void Resc_Close(RescHandle h);

int Resc_OpenResc(RescHandle h, const char *filename);
bool Resc_RescExists(RescHandle h, const char *filename);
const char *Resc_GetLocal(RescHandle h, const char *filename, size_t *size);

int Resc_OpenTar(RescHandle h);

RescList Resc_ListBegin(RescHandle h);
size_t Resc_ListCount(RescList l);
const char *Resc_ListGetName(RescList l, size_t idx);
void Resc_ListEnd(RescList l);

EXTERN_C_END

#ifdef __cplusplus

inline RescHandle Resc_FileOpen(const std::string &filename){
	return Resc_FileOpen(filename.c_str());
}

inline int Resc_OpenResc(RescHandle h, const std::string &filename){
	return Resc_OpenResc(h, filename.c_str());
}

#endif

NS_END
NS_END

#endif