#include "ToolShed.h"

namespace SparkPlug {

	ToolShed::ToolShed() {
		is_running = false;

		//	Initialize the vector of the frame durations to have 250 durations
		//	250 frame durations are initialized to be over desired update time so the engine can have a slow start up
		frame_durations.reserve(250);
		for (int i = 0; i < 250; i++)
			frame_durations.push_back(std::chrono::nanoseconds(5 * 1000000));
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
		average_frame_duration -= (olddur / 250);	//	Remove the old frame from the average
		average_frame_duration += (dur / 250);		//	Add the new frame to the average
	}

	void ToolShed::Initialize() {
		//	Set is_running to true
		is_running = true;

		//	Initialize OpenGL
		if (!glfwInit())
			exit;
		window = glfwCreateWindow(640, 480, "GARAGE", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			exit;
		}
		glfwMakeContextCurrent(window);
	}

	void ToolShed::Render() {
		while (is_running) {
			//	Render to the OpenGL window
			glClear(GL_COLOR_BUFFER_BIT);
			glfwSwapBuffers(window);
		}
	}

	void ToolShed::Run() {
		//	Initialize the game
		Initialize();

		//	Create threads for rendering, sound, networking
		std::thread render_thread (&ToolShed::Render, this);

		//-----	----- -----	GAME LOOOP	----- ----- -----//
		//	Variables for storing times and running time delta average over a duration
		//	Get current time
		std::chrono::high_resolution_clock::time_point RUN_START_TIME = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point FRAME_START;
		std::chrono::high_resolution_clock::time_point FRAME_END;
		std::chrono::high_resolution_clock::duration FRAME_TIME_DELTA;

		while (is_running) {
			//	Update the frame start time
			FRAME_START = std::chrono::high_resolution_clock::now();

			//	Get input from user
			glfwPollEvents();
			is_running = !glfwWindowShouldClose(window);

			//	Update (AI, Physics, etc...)

			//	Update the frame end time
			FRAME_END = std::chrono::high_resolution_clock::now();

			//	Calculate time delta for current frame and update running average
			FRAME_TIME_DELTA = FRAME_END - FRAME_START;

			//	Add the most recent time delta to the vector of averages
			updateFrameVector(FRAME_TIME_DELTA);

			//	Determine how long to sleep
			if ((DESIRED_UPDATE_DURATION.count() - average_frame_duration.count()) > 0) {
				std::this_thread::sleep_for(DESIRED_UPDATE_DURATION - average_frame_duration);
			}
			else if (DESIRED_UPDATE_DURATION.count() - average_frame_duration.count() < 0) {
				//	Sleep for remaining time until next time step
				std::this_thread::sleep_for((DESIRED_UPDATE_DURATION - average_frame_duration) % DESIRED_UPDATE_DURATION);
			}
		}

		glfwTerminate();

		//	Finish threads
		render_thread.join();

		//	Exit game
	}

}