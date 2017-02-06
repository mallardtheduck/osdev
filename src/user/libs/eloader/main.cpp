#include <iostream>
#include <eloader/eloader.h>

using namespace std;

int main(){
	size_t count = EL_GetModuleCount();
	for(size_t i = 0; i < count; ++i){
		EL_Module mod = EL_GetModule(i);
		cout << "Module: " << mod.name << " (ID: " << mod.id << ")" << endl;
		cout << "Base: " << hex << mod.base << " Limit: " << mod.limit << endl;
	}
	
	void *addr = EL_GetSymbol(0, "EL_LoadLibrary");
	cout << "EL_LoadLibrary: " << addr << endl;
	
	return 0;
}
