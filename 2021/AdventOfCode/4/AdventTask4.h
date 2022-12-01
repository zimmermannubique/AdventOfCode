//
//  AdventTask4.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 04.12.21.
//

#include "AdventTask.h"
#include "Board.h"

class AdventTask4 : public AdventTask<4> {
  protected:
    std::vector<int> numbers;
    std::vector<Board<5>> boards;

    virtual void solveSilver(std::ifstream &file) {
        fill(file);

        for(auto& i : numbers) {
            for(auto& b : boards) {
                b.select(i);

                if(b.hasWon()) {
                    std::cout << "Board won: " << b.result(i) << std::endl;
                    return;
                }
            }
        }
    }

    virtual void solveGold(std::ifstream &file) {
        fill(file);

        int boardsWon = 0;

        for(auto& i : numbers) {
            for(auto& b : boards) {
                bool alreadyWon = b.hasWon();
                b.select(i);

                if(b.hasWon() && !alreadyWon) {
                    boardsWon++;

                    if(boardsWon == boards.size()) {
                        std::cout << "Board won last: " << b.result(i) << std::endl;
                        return;
                    }
                }
            }
        }
    }

  private:
    void fill(std::ifstream &file) {
        numbers.clear();
        boards.clear();

        std::string commaNumbers;
        file >> commaNumbers;

        std::stringstream ss(commaNumbers);
        int i;
        while (ss >> i) {
            numbers.push_back(i);
            ss.ignore(1);
        }

        while(file.good()) {
            boards.push_back(Board<5>(file));
        }
    }

};
