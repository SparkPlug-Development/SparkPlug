#pragma once

namespace SparkPlug {
	_declspec(dllimport) void Print();
}

void main() {
	SparkPlug::Print();
}