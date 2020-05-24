#pragma once
//utilities
#include <iostream>
#include <memory>
#include <utility>
#include <thread>

//algorithm
#include <algorithm>
#include <functional>

//std data structure
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <unordered_map>
#include <unordered_set>


#ifdef JSENGINE_PLATFORM_WINDOWS
    //#include <Windows.h>
#endif

//JSEngine
#include "Core/Log.h"
#include "Debug/SimpleProfiler.h"

#define JS_OPTIMIZE_OFF __pragma(optimize("", off));
#define JS_OPTIMIZE_ON __pragma(optimize("", on))
