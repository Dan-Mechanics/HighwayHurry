#pragma once
#include <SFML/Graphics.hpp>

class Time {
public:
	float fixedInterval{};
	float deltaTime{};

	Time();
	Time(int timestep);

	int processFrame();
	void reset();

private:
	float timer = 0;
	sf::Clock deltaClock;
};

