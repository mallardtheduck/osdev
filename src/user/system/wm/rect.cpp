#include "rect.hpp"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <btos.h>

using namespace std;
using namespace gds;

#define DBG(x) do{std::stringstream dbgss; dbgss << x << std::endl; bt_zero(dbgss.str().c_str());}while(0)


