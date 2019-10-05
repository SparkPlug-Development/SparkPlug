#include <SparkPlug.h>

//	Class extending ToolShed
//	Where all compponents of the game are utilized (essentially the game class)
class Garage : public SparkPlug::ToolShed {
public:
	Garage() {

	}

	~Garage() {

	}
};

//	Declared in EntryPoint.h
//	Returns: dynamically instance of Garage (a pointer to a Garage)
SparkPlug::ToolShed* SparkPlug::OpenToolShed() {
	return new Garage();
}