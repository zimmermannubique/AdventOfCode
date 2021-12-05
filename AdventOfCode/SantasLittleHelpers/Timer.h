//
//  Timer.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 05.12.21.
//

#ifndef Timer_h
#define Timer_h

#include <iostream>
#include <chrono>

class Timer {
  public:
    void start() {
        startTime = std::chrono::high_resolution_clock::now();
    }

    void stop() {
        stopTime = std::chrono::high_resolution_clock::now();
        printDuration();
    }

  private:
    void printDuration() {
        auto d = std::chrono::duration_cast<std::chrono::microseconds>(stopTime - startTime);
        std::cout << "\nSolving took: " << d.count()/1000.0 << " milliseconds." << std::endl;
    }

  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> stopTime;

};

#endif /* Timer_h */
