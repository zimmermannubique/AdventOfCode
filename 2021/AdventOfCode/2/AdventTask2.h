//
//  AdventTask2.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 02.12.21.
//

#include "AdventTask.h"

class AdventTask2 : public AdventTask<2> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::string motion;
        int64_t x = 0, y = 0;
        int64_t value;
        while (file >> motion >> value) {
            if(motion == "forward") {
                x += value;
            } else if(motion == "down") {
                y += value;
            } else if(motion == "up") {
                y -= value;
            }
        }

        std::cout << "Result: " << x << "*" << y << " = " << x*y << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        std::string motion;
        int64_t x = 0, depth = 0, aim = 0;
        int64_t value;

        while (file >> motion >> value) {
            if(motion == "down") {
                aim += value;
            } else if(motion == "up") {
                aim -= value;
            } else if(motion == "forward") {
                x += value;
                depth += aim * value;
            }
        }

        std::cout << "Result: " << x << "*" << depth << " = " << x*depth << std::endl;
    }
};
