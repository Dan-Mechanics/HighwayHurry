#pragma once
#include <SFML/Graphics.hpp>

/// <summary>
/// Aka GameClock.
/// </summary>
class Time {
public:
	float fixedInterval{};
	float deltaTime{};

	Time();
	Time(int timestep);

	/// <summary>
	/// https://www.udacity.com/blog/2021/05/c-pass-by-reference-explained.html
	/// Call this in a while loop.
	/// </summary>
	/// <returns>The amount of fixed ticks to perform.</returns>
	int processFrame();
	void reset();

private:
	float timer = 0;
	sf::Clock deltaClock;
};