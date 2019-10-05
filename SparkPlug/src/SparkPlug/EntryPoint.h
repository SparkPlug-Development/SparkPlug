#pragma once

#include <Windows.h>

//	Ensure the platform is Windows
#ifdef SP_PLATFORM_WINDOWS

//	Method defined in Garage.cpp
//	Returns: dynamically instance of Garage (a pointer to a Garage)
extern SparkPlug::ToolShed* SparkPlug::OpenToolShed();

int main(int argc, char *argv[]) {
	SetConsoleTitle("SparkPlug");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	std::cout << "...Engine started...\n";

	//	Dynamically allocate a Garage
	SparkPlug::ToolShed *garage = SparkPlug::OpenToolShed();

	//	Start the game
	(*garage).Run();

	//	Explicitly destroy game
	delete garage;

	return 0;
}

#endif