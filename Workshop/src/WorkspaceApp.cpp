#include <SparkPlug.h>

//	Class extending Application
//	Where all compponents of the game are utilized (essentially the game class)
class Workspace : public SparkPlug::Application {
public:
	Workspace() {

	}

	~Workspace() {

	}
};

//	Declared in EntryPoint.h
//	Returns: dynamically instance of Workspace (a pointer to a Workspace)
SparkPlug::Application* SparkPlug::CreateApplication() {
	return new Workspace();
}