//
//  AdventTask.hpp
//  AdventOfCode
//
//  Created by Marco Zimmermann on 01.12.21.
//

#ifndef AdventTask_hpp
#define AdventTask_hpp

#include "Timer.h"
#include "StringHelper.h"

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
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <queue>
#include <memory>

static void startAdventOfCode() {
    std::cout << "🎄🎄🎄 Advent of Code 🎄🎄🎄" << std::endl;
}

template<int N>
class AdventTask {
  public:
    void solveSilverTask() {
        solveTask(true);
    }

    void solveGoldTask() {
        solveTask(false);
    }

  protected:
    virtual void solveSilver(std::ifstream &file) = 0;
    virtual void solveGold(std::ifstream &file) = 0;

  private:
    void printDivider(bool silver) {
        std::string img = N == 10 ? " 👕 " :(N == 5 ? " ☕ " : " 🎁 ");

        std::cout << "\n🪢🪢🪢" << img << N << " " << (silver ? "🪙 SILVER 🪙" : "⭐  GOLD  ⭐") << img << "🪢🪢🪢\n";
        std::cout << std::endl;
    }

    void solveTask(bool silver) {
        std::stringstream ss;
        ss << N << "/input";

        std::ifstream f(ss.str());

        printDivider(silver);

        Timer t;
        t.start();

        if(silver) {
            solveSilver(f);
        } else {
            solveGold(f);
        }

        t.stop();
    }
};

#endif /* AdventTask_hpp */
