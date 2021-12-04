//
//  AdventTask1.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 01.12.21.
//

#include "AdventTask.h"

class AdventTask1 : public AdventTask<1> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        int64_t c = 0;
        int64_t current = std::numeric_limits<int64_t>::max();
        int64_t input;

        while(file >> input) {
            c += ((input > current) ? 1 : 0);
            current = input;
        }

        std::cout << "Result: " << c << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        int64_t input;
        std::vector<int64_t> inputs;
        while (file >> input) {
            inputs.push_back(input);
        }

        int64_t c = 0;
        int64_t current = std::numeric_limits<int64_t>::max();

        int sliding = 3;

        for(int i=0; i<inputs.size()-sliding + 1; ++i) {
            int64_t s = 0;
            for(int j=0; j<sliding; ++j) {
                s += inputs[i + j];
            }

            if(s > current) {
                c++;
            }

            current = s;
        }

        std::cout << "Result: " << c << std::endl;
    }
};
