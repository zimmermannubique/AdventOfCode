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

        std::string emptyLine;
        std::string commaNumbers;
        file >> commaNumbers;

        size_t pos = 0;
        while ((pos = commaNumbers.find(",")) != std::string::npos) {
            numbers.push_back(std::stoi(commaNumbers.substr(0, pos)));
            commaNumbers.erase(0, pos + 1);
        }
        numbers.push_back(std::stoi(commaNumbers));

        while(file.good()) {
            auto b = Board<5>(file);

            if(file.good()) {
                boards.push_back(b);
            }
        }
    }

};
