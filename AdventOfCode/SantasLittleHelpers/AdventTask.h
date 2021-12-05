//
//  AdventTask.hpp
//  AdventOfCode
//
//  Created by Marco Zimmermann on 01.12.21.
//

#ifndef AdventTask_hpp
#define AdventTask_hpp

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include <limits>
#include <bitset>
#include <numeric>
#include <functional>

static void startAdventOfCode() {
    std::cout << "🎄🎄🎄 Advent of Code 🎄🎄🎄" << std::endl;
}

template<int N>
class AdventTask {
  public:
    void solveSilverTask() {
        printDivider(true);
        solveTask(true);
        std::cout << std::endl;
    }

    void solveGoldTask() {
        printDivider(false);
        solveTask(false);
        std::cout << std::endl;
    }

  protected:
    virtual void solveSilver(std::ifstream &file) = 0;
    virtual void solveGold(std::ifstream &file) = 0;

  private:
    void printDivider(bool silver) {
        std::string img = N == 5 ? " ☕ " : " 🎁 ";
        std::cout << "\n🪢🪢🪢" << img << N << " " << (silver ? "🪙 SILVER 🪙" : "⭐  GOLD  ⭐") << img << "🪢🪢🪢\n\n";
    }

    void solveTask(bool silver) {
        std::stringstream ss;
        ss << N << "/input";

        std::ifstream f(ss.str());

        if(silver) {
            solveSilver(f);
        } else {
            solveGold(f);
        }
    }
};

#endif /* AdventTask_hpp */
