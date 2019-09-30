#pragma once

#include <Windows.h>

//	Ensure the platform is Windows
#ifdef SP_PLATFORM_WINDOWS

//	Method defined in WorkspaceApp.cpp
//	Returns: dynamically instance of Workspace (a pointer to a Workspace)
extern SparkPlug::Application* SparkPlug::CreateApplication();

int main(int argc, char *argv[]) {
	SetConsoleTitle("SparkPlug");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "...Engine started...\n";

	//	Dynamically allocate an instance of Workspace
	SparkPlug::Application *app = SparkPlug::CreateApplication();

	//	Start the game
	(*app).Run();

	//	Explicitly destroy game
	delete app;

	return 0;
}

#endif