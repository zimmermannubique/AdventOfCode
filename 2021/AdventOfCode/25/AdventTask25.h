//
//  AdventTask25.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 25.12.21.
//

#ifndef AdventTask25_h
#define AdventTask25_h

class AdventTask25 : public AdventTask<25> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        auto grid = input(file);

        bool moves = true;
        int numberOfMoves = 0;

        while(moves) {
            moves = move(grid);
            numberOfMoves++;
        }

        std::cout << "Result: " << numberOfMoves << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        // there was no gold...
    }

    bool move(std::vector<std::string>& grid) {
        bool moved = false;

        for(int i=0; i<grid.size(); ++i) {
            bool isLeftSet = grid[i][0] != '.';
            for(int j=0; j<grid[i].size(); ++j) {
                if(grid[i][j] == '>') {
                    auto newJ = j+1 >= grid[i].size() ? 0 : j+1;
                    if((newJ != 0 && grid[i][newJ] == '.') || (newJ == 0 && !isLeftSet)) {
                        grid[i][j] = '.';
                        grid[i][newJ] = '>';
                        moved = true;
                        j++;
                    }
                }
            }
        }

        for(int j=0; j<grid[0].size(); ++j) {
            bool isTopSet = grid[0][j] != '.';

            for(int i=0; i<grid.size(); ++i) {
                if(grid[i][j] == 'v') {
                    auto newI = i+1 >= grid.size() ? 0 : i+1;
                    if((newI != 0 && grid[newI][j] == '.') || (newI == 0 && !isTopSet)) {
                        grid[i][j] = '.';
                        grid[newI][j] = 'v';
                        moved = true;
                        i++;
                    }
                }
            }
        }

        return moved;
    }

    void print(std::vector<std::string>& grid) {
        for(int i=0; i<grid.size(); ++i) {
            std::cout << grid[i] << std::endl;
        }

        std::cout << "======" << std::endl;
    }

    std::vector<std::string> input(std::ifstream &file) {
        std::vector<std::string> s;
        std::string input;

        while(file >> input) {
            s.push_back(input);
        }

        return s;
    }
};

#endif /* AdventTask25_h */
