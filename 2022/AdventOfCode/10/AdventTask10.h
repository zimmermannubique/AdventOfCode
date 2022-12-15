//
//  AdventTask10.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 10.12.21.
//

#ifndef AdventTask10_h
#define AdventTask10_h

#include <AdventTask.h>

class AdventTask10 : public AdventTask<10> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::vector<int> cycles = { 20, 60, 100, 140, 180, 220 };
        int x = 1, cycle = 1;

        std::string operation;
        int64_t sum = 0;

        while (file >> operation) {
            if(operation == "noop") {
                cycle++;
                sum += check(cycles, cycle, x);

            } else {
                cycle++;
                sum += check(cycles, cycle, x);

                int d;
                file >> d;
                x += d;

                cycle++;
                sum += check(cycles, cycle, x);
            }
        }

        std::cout << sum << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        int x = 1, cycle = 1;

        std::string operation;
        std::string result;

        while (file >> operation) {
            if(operation == "noop") {
                result.push_back(getCode(cycle, x));
                updateCycle(result, cycle);
            } else {
                result.push_back(getCode(cycle, x));
                updateCycle(result, cycle);

                result.push_back(getCode(cycle, x));
                updateCycle(result, cycle);

                int d;
                file >> d;
                x += d;
            }
        }

        std::cout << result << std::endl;
    }

    int check(std::vector<int> &m, int cycle, int x) {
        return std::find(m.begin(), m.end(), cycle) != m.end() ? x * cycle : 0;
    }

    char getCode(int cycle, int x) {
        return (abs(x-(cycle-1)) <= 1) ? '#' : '.';
    }

    void updateCycle(std::string& result, int& cycle) {
        cycle++;
        if((cycle-1) % 40 == 0) {
            cycle = 1;
            result.push_back('\n');
        }
    }
};

#endif /* AdventTask10_h */
