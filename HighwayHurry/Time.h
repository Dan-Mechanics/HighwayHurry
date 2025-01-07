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
	/// Call this in a while loop.
	/// Based on this --> https://docs.unity3d.com/6000.0/Documentation/ScriptReference/Physics.Simulate.html
	/// </summary>
	/// <returns>The amount of fixed ticks to perform.</returns>
	int processFrame();
	void reset();

private:
	float timer = 0;
	sf::Clock deltaClock;
};