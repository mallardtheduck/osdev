#include <module/module.inc>

EXTERN_C int module_main(IModuleAPI *api, char *){
	ModuleInit(api);
    return 0;
}