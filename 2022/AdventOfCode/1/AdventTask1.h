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
        std::string input;
        int64_t max = 0;
        int64_t sum = 0;

        while (!file.eof()) {
            getline(file, input);
            if(input != "") {
                sum += std::stoi(input);
            } else {
                if(sum > max) {
                    max = sum;
                }
                sum = 0;
            }
        }

        std::cout << max << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        std::string input;
        std::vector<int64_t> numbers;

        int64_t sum = 0;
        while (!file.eof()) {
            getline(file, input);
            if(input != "") {
                sum += std::stoi(input);
            } else {
                numbers.push_back(sum);
                sum = 0;
            }
        }

        std::sort(numbers.begin(), numbers.end(), std::greater<int64_t>());
        std::cout << numbers[0] + numbers[1] + numbers[2] << std::endl;
    }
};
