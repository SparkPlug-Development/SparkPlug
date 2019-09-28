#pragma once

#ifdef SP_PLATFORM_WINDOWS
	#ifdef SP_BUILD_DLL
		#define SPARKPLUG_API __declspec(dllexport)
	#else
		#define SPARKPLUG_API __declspec(dllimport)
	#endif
#endif
