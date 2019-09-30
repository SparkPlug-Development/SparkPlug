#pragma once

#include "Core.h"

namespace SparkPlug {

	//	The main class for SparkPlug
	class SPARKPLUG_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//	Method defined in WorkspaceApp.cpp
	//	Returns: dynamically instance of Workspace (a pointer to a Workspace)
	Application* CreateApplication();

}

