#pragma once

namespace SparkPlug {
	_declspec(dllimport) void Print();
}

int main() {
	SparkPlug::Print();
	return 0;
}