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
		// Constant value to set desired rate of update for game loop and render loop
		constexpr static std::chrono::high_resolution_clock::duration DESIRED_PHYS_UPDATE_DURATION = std::chrono::nanoseconds(4 * 1000000);	//	(4 ms/update ~ 250 updates/sec)
		std::chrono::high_resolution_clock::duration DESIRED_RENDER_UPDATE_DURATION = std::chrono::nanoseconds((int) ((1.0/max_fps) * 1000000));

		bool is_running;
		int frame_counter;		// A counter determining index to add frame duration in time delta array. Utilized in updateFrameVector()

		std::chrono::high_resolution_clock::duration frame_durations[250];		// A vector with the time deltas for the last 250 frames (~1 sec)
		std::chrono::high_resolution_clock::duration average_frame_duration;			// The running average of the time delta vector, initialized slightly above desired duration to allow for a smooth start up

		GLFWwindow* window;

		//	-----	----- SETTINGS	-----	-----	//
		bool fullscreen;
		int monitor_res_height;
		int monitor_res_width;
		int desired_res_height;
		int desired_res_width;
		int max_fps;
		//	-----	-----	-----	-----	-----	//

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

