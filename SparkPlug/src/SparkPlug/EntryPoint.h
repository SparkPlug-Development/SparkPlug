#pragma once

#include <Windows.h>

//	Ensure the platform is Windows
#ifdef SP_PLATFORM_WINDOWS

//	Method defined in Chassis.cpp
//	Returns: dynamically instance of Chassis (a pointer to a Chassis)
extern SparkPlug::ToolShed* SparkPlug::OpenToolShed();

int main(int argc, char *argv[]) {
	SetConsoleTitle("SparkPlug");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "...Engine started...\n";

	//	Dynamically allocate a Chassis
	SparkPlug::ToolShed *frame = SparkPlug::OpenToolShed();

	//	Start the game
	(*frame).Run();

	//	Explicitly destroy game
	delete frame;

	return 0;
}

#endif