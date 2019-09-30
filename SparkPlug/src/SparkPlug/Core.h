#pragma once

//	Ensure the platform is Windows
#ifdef SP_PLATFORM_WINDOWS
	//	Determine whether to import or export the library during linking
	#ifdef SPARKPLUG_BUILD_DLL
		#define SPARKPLUG_API __declspec(dllexport)
	#else
		#define SPARKPLUG_API __declspec(dllimport)
	#endif
#endif
