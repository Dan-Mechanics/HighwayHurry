#include "Time.h"
#include <iostream>
#include "Utils.h"

Time::Time() {
    int timestep = 50; 

    fixedInterval = 1.0f / timestep;

    reset();
}

Time::Time(int timestep) {
    if (timestep <= 0) {
        timestep = 50; 
        print("ERROR: if (timestep <= 0) ");
    }

    fixedInterval = 1.0f / timestep;

    reset();
}

/// <summary>
/// https://www.udacity.com/blog/2021/05/c-pass-by-reference-explained.html
/// C++ doesnt care if you return true with an int function. great.
/// Call this in a while loop.
/// </summary>
/// <returns>The amount of fixed ticks to perform.</returns>
int Time::processFrame() {
    int counter = 0;
    
    deltaTime = deltaClock.restart().asSeconds();

    timer += deltaTime;

    while (timer >= fixedInterval) {
        timer -= fixedInterval;

        // Do fixed tick here.

        counter++;
    }

    return counter;
}

void Time::reset() {
    deltaClock.restart();
    timer = 0;
}