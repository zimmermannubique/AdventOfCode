//
//  AdventTask3.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 03.12.21.
//

#include "AdventTask.h"

class AdventTask3 : public AdventTask<3> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::string pack;
        int sum = 0;

        while (file >> pack) {
            auto firstPart = pack.substr(0, pack.size() / 2);
            auto secondPart = pack.substr(pack.size() / 2, pack.size() / 2);

            std::set<char> firstSet(firstPart.begin(), firstPart.end());
            std::set<char> secondSet(secondPart.begin(), secondPart.end());

            auto vec = { firstSet, secondSet };
            sum += solve(vec);
        }

        std::cout << sum << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        std::string pack;
        int sum = 0;

        std::vector<std::set<char>> group;

        while (file >> pack) {
            group.emplace_back(pack.begin(), pack.end());

            if(group.size() == 3) {
                sum += solve(group);
                group.clear();
            }
        }

        std::cout << sum << std::endl;
    }

    int solve(const std::vector<std::set<char>>& group) {
        std::set<char> intersection;

        bool first = true;
        for(auto& g : group) {
            if(first) {
                intersection = g;
            } else {
                std::set<char> next;
                std::set_intersection(intersection.begin(), intersection.end(), g.begin(), g.end(),
                                      std::inserter(next, next.begin()));
                intersection = next;
            }

            first = false;
        }

        for(auto& i : intersection) {
            return (int)(i) - (std::islower(i) ? ((int)('a') - 1) : ((int)('A') - 27));
        }

        return 0;
    }
};
