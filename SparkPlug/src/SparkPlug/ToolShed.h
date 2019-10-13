#pragma once

#include <chrono>
#include <vector>
#include <iostream>
#include <thread>
#include <GLFW/glfw3.h>
#include "Core.h"

namespace SparkPlug {

	//	The main class for SparkPlug
	class SPARKPLUG_API ToolShed {
	public:
		// Constant value to set desired rate of update (4 ms/update ~ 250 updates/sec)
		constexpr static std::chrono::high_resolution_clock::duration DESIRED_UPDATE_DURATION = std::chrono::nanoseconds(4 * 1000000);

		bool is_running;	// A boolean value storing whether or not the game should be running
		int frame_counter = 0;		// A counter that determines where to add the frame in the vector of average time deltas

		std::vector <std::chrono::high_resolution_clock::duration> frame_durations;								// A vector with the time deltas for the last 250 frames (~1 sec)
		std::chrono::high_resolution_clock::duration average_frame_duration = std::chrono::nanoseconds(5 * 1000000);		// The running average of the time delta vector, initialized slightly above desired duration to allow for a smooth start up

		GLFWwindow* window;	//	OpenGL window to render

		void updateFrameVector(const std::chrono::high_resolution_clock::duration &dur);	//	A method to update the vector of most recent 250 time deltas and update average_frame_duration

		ToolShed();
		virtual ~ToolShed();

		void Initialize();
		void Render();
		void Run();
	};

	//	Method defined in Garage.cpp
	//	Returns: dynamically instance of Garage (a pointer to a Garage)
	ToolShed* OpenToolShed();

}

