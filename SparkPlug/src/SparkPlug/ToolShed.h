#pragma once

#include "Core.h"

namespace SparkPlug {

	//	The main class for SparkPlug
	class SPARKPLUG_API ToolShed
	{
	public:
		ToolShed();
		virtual ~ToolShed();

		void Run();
	};

	//	Method defined in Chassis.cpp
	//	Returns: dynamically instance of Chassis (a pointer to a Chassis)
	ToolShed* OpenToolShed();

}

