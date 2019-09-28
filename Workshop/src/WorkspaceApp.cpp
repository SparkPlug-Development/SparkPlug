#include <SparkPlug.h>

class Workspace : public SparkPlug::Application {
public:
	Workspace() {

	}

	~Workspace() {

	}
};

SparkPlug::Application* SparkPlug::CreateApplication() {
	return new Workspace();
}