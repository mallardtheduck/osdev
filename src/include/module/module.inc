#include <btos_module.h>
#include <cstdarg>

IModuleAPI *API;

static void ModuleInit(IModuleAPI *api){
	API = api;
}

extern "C" void panic(const char *msg){
	API->Panic(msg);
}

extern "C" void *malloc(size_t bytes){
	return API->MemAlloc(bytes);
}

extern "C" void free(void *ptr){
	API->Free(ptr);
}

extern "C" void *realloc(void *ptr, size_t new_size){
	return API->ReAlloc(ptr, new_size);
}

extern "C" void *memset(void *ptr, int value, size_t num){
	return API->MemSet(ptr, value, num);
}

extern "C" void *memcpy(void *dst, const void *src, size_t size){
	return API->MemCopy(dst, src, size);
}

extern "C" void *memmove(void *dst, void *src, size_t size){
	return API->MemMove(dst, src, size);
}

extern "C" int strcmp(const char *a, const char *b){
	return API->StrCompare(a, b);
}

extern "C" void strncpy(char *dst, const char *src, size_t size){
	return API->StrCopy(dst, src, size);
}

extern "C" void dbgout(const char *msg){
	API->DebugOutput(msg);
}

extern "C" int vsprintf(char *str, const char *fmt, __builtin_va_list ap){
	return API->VStrPrintF(str, fmt, ap);
}

extern "C" int vsnprintf(char *str, size_t size, const char *fmt, __builtin_va_list ap){
	return API->VStrPrintF(str, size, fmt, ap);
}

extern "C" int sprintf(char *str, const char *fmt, ...){
	va_list va;
	va_start(va, fmt);
	auto ret = vsprintf(str, fmt, va);
	va_end(va);
	return ret;
}

extern "C" int snprintf(char *str, size_t size, const char *fmt, ...){
	va_list va;
	va_start(va, fmt);
	auto ret = vsnprintf(str, size, fmt, va);
	va_end(va);
	return ret;
}

extern "C" int dbgpf(const char *fmt, ...){
	char dbgbuf[256] = {0};
	va_list va;
	va_start(va, fmt);
	auto ret = vsnprintf(dbgbuf, 255, fmt, va);
	va_end(va);
	dbgout(dbgbuf);
	return ret;
}

IProcess &CurrentProcess(){
	return API->CurrentProcess();
}

extern "C" void __cxa_pure_virtual()
{
	panic("Pure virtual function call!");
}

extern "C" int __cxa_atexit(void (* /*func*/) (void *), void * /*arg*/, void * /*dso_handle*/) {
	return 0;
} 
void *__dso_handle;
