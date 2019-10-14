#include "ToolShed.h"

namespace SparkPlug {

	ToolShed::ToolShed() {
		is_running = false;
		frame_counter = 0;
		average_frame_duration = std::chrono::nanoseconds(5 * 1000000);

		//	Get settings from file
		fullscreen = false;
		monitor_res_height = 1920;
		monitor_res_width = 1080;
		desired_res_height = 800;
		desired_res_width = 450;
		max_fps = 60;

		//	Initialize the vector of the frame durations to have 250 durations
		//	250 frame durations are initialized to be over desired update time so the engine can have a slow start up
		for (int i = 0; i < 250; i++)
			frame_durations[i] = std::chrono::nanoseconds(5 * 1000000);
	}


	ToolShed::~ToolShed()
	{
	}

	void ToolShed::updateFrameVector(const std::chrono::high_resolution_clock::duration & dur) {
		//	Add current duration to vector at index specified by frame_counter
		std::chrono::nanoseconds olddur = frame_durations[frame_counter];
		frame_durations[frame_counter] = dur;

		//	Increment the counter if it is less than 250
		//	Reset the counter if it is >= 250
		if (frame_counter < 249)
			frame_counter++;
		else
			frame_counter = 0;

		//	Update the average frame rate
		std::chrono::high_resolution_clock::duration total;
		average_frame_duration -= (olddur / 250);
		average_frame_duration += (dur / 250);
	}

	void ToolShed::Initialize() {
		is_running = true;

		//	Initialize OpenGL
		if (!glfwInit())
			exit;
		if (fullscreen) {
			window = glfwCreateWindow(monitor_res_height, monitor_res_width, "GARAGE", glfwGetPrimaryMonitor(), NULL);
		}
		else
			window = glfwCreateWindow(desired_res_height, desired_res_width, "GARAGE", NULL, NULL);

		if (!window)
		{
			glfwTerminate();
			exit;
		}
		glfwMakeContextCurrent(window);
	}

	void ToolShed::Render() {
		std::chrono::high_resolution_clock::time_point FRAME_START;
		std::chrono::high_resolution_clock::time_point FRAME_END;
		std::chrono::high_resolution_clock::duration FRAME_TIME_DELTA;

		while (is_running) {
			FRAME_START = std::chrono::high_resolution_clock::now();

			//	Render to the OpenGL window
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);

			//	Calculate time delta for current frame
			FRAME_END = std::chrono::high_resolution_clock::now();
			FRAME_TIME_DELTA = FRAME_END - FRAME_START;

			//	Determine how long to sleep
			if ((DESIRED_RENDER_UPDATE_DURATION.count() - FRAME_TIME_DELTA.count()) > 0) {
				//	Sleep until end of current time step
				std::this_thread::sleep_for(DESIRED_RENDER_UPDATE_DURATION - FRAME_TIME_DELTA);
			}
			else if (DESIRED_PHYS_UPDATE_DURATION.count() - FRAME_TIME_DELTA.count() < 0) {
				//	Sleep for remaining time until next time step
				std::this_thread::sleep_for((DESIRED_RENDER_UPDATE_DURATION - FRAME_TIME_DELTA) % DESIRED_RENDER_UPDATE_DURATION);
			}
		}
	}

	void ToolShed::Run() {
		Initialize();

		//	Create threads for rendering, sound, networking
		std::thread render_thread (&ToolShed::Render, this);

		//-----	----- -----	GAME LOOOP	----- ----- -----//
		//	Variables for storing times and running time delta average over a duration
		std::chrono::high_resolution_clock::time_point RUN_START_TIME = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point FRAME_START;
		std::chrono::high_resolution_clock::time_point FRAME_END;
		std::chrono::high_resolution_clock::duration FRAME_TIME_DELTA;

		while (is_running) {
			FRAME_START = std::chrono::high_resolution_clock::now();

			//	Get input from user
			glfwPollEvents();
			is_running = !glfwWindowShouldClose(window);

			//	Update (AI, Physics, etc...)

			//	Calculate time delta for current frame and update running average
			FRAME_END = std::chrono::high_resolution_clock::now();
			FRAME_TIME_DELTA = FRAME_END - FRAME_START;
			updateFrameVector(FRAME_TIME_DELTA);

			//	Determine how long to sleep
			if ((DESIRED_PHYS_UPDATE_DURATION.count() - average_frame_duration.count()) > 0) {
				//	Sleep until end of current time step
				std::this_thread::sleep_for(DESIRED_PHYS_UPDATE_DURATION - average_frame_duration);
			}
			else if (DESIRED_PHYS_UPDATE_DURATION.count() - average_frame_duration.count() < 0) {
				//	Sleep for remaining time until next time step
				std::this_thread::sleep_for((DESIRED_PHYS_UPDATE_DURATION - average_frame_duration) % DESIRED_PHYS_UPDATE_DURATION);
			}
		}

		glfwTerminate();

		//	Finish threads
		render_thread.join();

		//	Exit game
	}

}