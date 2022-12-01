//
//  AdventTask24.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 24.12.21.
//

#ifndef AdventTask24_h
#define AdventTask24_h

#include "ALU.h"

class AdventTask24 : public AdventTask<24> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        solve(file, true);
    }

    virtual void solveGold(std::ifstream &file) {
        solve(file, false);
    }

    void solve(std::ifstream &file, bool silver) {
        auto instructions = input(file);

        std::deque<InputSet> states;
        states.push_front(InputSet(silver));

        std::map<std::string, int64_t> checked;

        InputSet biggest;
        while(states.size() > 0) {
            auto s = states.front(); states.pop_front();
            auto key = s.key();

            if(checked.count(key) > 0) {
                continue;
            }

            checked[key] = 1;

            if(s.isValid(instructions)) {
                s.inputs.pop_back();
                biggest = s;
                break;
            } else {
                for(auto& i : s.followSets(instructions)) {
                    if(checked.count(i.key()) == 0) {
                        states.push_front(i);
                    }
                }
            }
        }

        for(auto& n : biggest.inputs) {
            std::cout << n;
        }
        std::cout << std::endl;
    }

    std::vector<Instruction> input(std::ifstream &file) {
        std::vector<Instruction> instructions;
        while(file.good()) {
            std::string operation, a, b = "";

            file >> operation >> a;
            if(operation != "inp") {
                file >> b;
            }

            instructions.emplace_back(operation, a, b);
        }

        return instructions;
    }
};

#endif /* AdventTask24_h */
