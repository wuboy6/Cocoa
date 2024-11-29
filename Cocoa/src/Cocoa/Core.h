#pragma once

#ifdef CO_PLATEFORM_WINDOWS
	#ifdef CO_BUILD_DLL 
		#define COCOA_API __declspec(dllexport)
	#else
		#define COCOA_API __declspec(dllimport)
	#endif
#else 
	#error Cocoa only suport Windodws
#endif

#ifdef CO_DEBUG
	#define CO_ENABLE_ASSERTS
#endif

#ifdef CO_ENABLE_ASSERTS
	#define CO_ASSERT(x,...) {if(!(x)) {CO_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak();}}
	#define CO_CORE_ASSERT(x,...) {if(!(x)) {CO_CORE_ERROR("Assertion Failed: {0}",__VA_ARGS__);__debugbreak();}}
#else
	#define CO_ASSERT(x,...)
	#define CO_CORE_ASSERT(x,...)
#endif


#define BIT(x) (1 << x)

#define CO_BIND_EVENT_FN(fn) std::bind(&fn,this,std::placeholders::_1)