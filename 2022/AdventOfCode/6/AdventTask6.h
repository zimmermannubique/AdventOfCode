//
//  AdventTask6.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 06.12.21.
//

#ifndef AdventTask6_h
#define AdventTask6_h

#include <AdventTask.h>

class AdventTask6 : public AdventTask<6> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        solve(file, 4);
    }

    virtual void solveGold(std::ifstream &file) {
        solve(file, 14);
    }

    void solve(std::ifstream &file, int n) {
        std::string message;
        file >> message;

        for(int i=0; i<message.size() - n; i++) {
            auto sub = message.substr(i, n);
            auto set = std::set<char>(sub.begin(), sub.end());

            if(set.size() == n) {
                std::cout << i + n << std::endl;
                return;
            }
        }
    }
};

#endif /* AdventTask6_h */
