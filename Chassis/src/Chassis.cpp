#include <SparkPlug.h>

//	Class extending ToolShed
//	Where all compponents of the game are utilized (essentially the game class)
class Chassis : public SparkPlug::ToolShed {
public:
	Chassis() {

	}

	~Chassis() {

	}
};

//	Declared in EntryPoint.h
//	Returns: dynamically instance of Workspace (a pointer to a Workspace)
SparkPlug::ToolShed* SparkPlug::OpenToolShed() {
	return new Chassis();
}