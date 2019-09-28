#pragma once

#ifdef SP_PLATFORM_WINDOWS

extern SparkPlug::Application* SparkPlug::CreateApplication();

int main(int argc, char *argv[]) {
	std::cout << "Engine started\n";
	auto app = SparkPlug::CreateApplication();
	(*app).Run();
	delete app;
	return 0;
}

#endif