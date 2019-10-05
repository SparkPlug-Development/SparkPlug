#include "ToolShed.h"

namespace SparkPlug {

	ToolShed::ToolShed() {
		//	Initialize the vector of the frame durations to have 250 durations
		//	250 frame durations are initialized to be over desired update time so the engine can have a slow start up
		frame_durations.reserve(250);
		for (int i = 0; i < 250; i++)
			frame_durations.push_back(std::chrono::milliseconds(5));
	}


	ToolShed::~ToolShed()
	{
	}

	void ToolShed::updateFrameVector(const std::chrono::high_resolution_clock::duration &dur) {
		//	Add current duration to vector at index specified by frame_counter
		frame_durations[frame_counter] = dur;

		//	Increment the counter if it is less than 250
		//	Reset the counter if it is >= 250
		if (frame_counter < 250)
			frame_counter++;
		else
			frame_counter = 0;

		//	Update the average frame rate
		std::chrono::high_resolution_clock::duration total;
		for (size_t i = 0; i < frame_durations.size(); i++) total += frame_durations[i];
		average_frame_duration = total / 250;
	}

	void ToolShed::Initialize() {
		//	Set is_running to true
		is_running = true;
	}

	void ToolShed::Run() {
		//	Initialize the game
		Initialize();

		//	Create threads for rendering, sound, networking

		//-----	----- -----	GAME LOOOP	----- ----- -----//
		//	Variables for storing times and running time delta average over a duration
		//	Get current time
		std::chrono::high_resolution_clock::time_point RUN_START_TIME = std::chrono::high_resolution_clock::now();
		std::chrono::high_resolution_clock::time_point FRAME_START;
		std::chrono::high_resolution_clock::time_point FRAME_END;
		std::chrono::high_resolution_clock::duration FRAME_TIME_DELTA;
		int count = 0;
		std::cout << DESIRED_UPDATE_DURATION.count() << "\n";
		std::cout << average_frame_duration.count() << "\n";

		while (is_running) {
			//	Update the frame start time
			FRAME_START = std::chrono::high_resolution_clock::now();

			//	Get input from user

			//	Update (AI, Physics, etc...)

			//	Update the frame end time
			FRAME_END = std::chrono::high_resolution_clock::now();

			//	Calculate time delta for current frame and update running average
			FRAME_TIME_DELTA = std::chrono::duration_cast<std::chrono::milliseconds>(FRAME_END - FRAME_START);
			std::cout << FRAME_TIME_DELTA.count() << "\n";

			//	Add the most recent time delta to the vector of averages
			updateFrameVector(FRAME_TIME_DELTA);
			
			//	Determine how long to sleep
			std::cout << "Sleep for " << DESIRED_UPDATE_DURATION.count() - average_frame_duration.count() << "\n";
			if ((DESIRED_UPDATE_DURATION.count() - average_frame_duration.count()) > 0) {
				std::cout << "sleeping for " << DESIRED_UPDATE_DURATION.count() - average_frame_duration.count() << "\n";
				std::this_thread::sleep_for(std::chrono::duration_cast<std::chrono::milliseconds>(DESIRED_UPDATE_DURATION - average_frame_duration));
			}

			std::cout << "\n";
			count++;

			if (count > 15)
				std::this_thread::sleep_for(std::chrono::seconds(20));

		}

		//	Finish threads

		//	Exit game
	}

}