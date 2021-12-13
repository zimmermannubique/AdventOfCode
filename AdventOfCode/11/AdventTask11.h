//
//  AdventTask11.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 11.12.21.
//

#ifndef AdventTask11_h
#define AdventTask11_h

#include <AdventTask.h>

class AdventTask11 : public AdventTask<11> {
  protected:
    int n = 10;

    virtual void solveSilver(std::ifstream &file) {
        auto level = input(file);

        int64_t flashes = 0;

        for(int s=0; s<100; ++s) {
            for(auto &l : level) {
                l++;
            }

            auto flashing = true;

            while(flashing) {
                flashing = false;

                for(int i=0; i<n; ++i) {
                    for(int j=0; j<n; ++j) {
                        if(level[i*n + j] > 9) {
                            feedNeighbors(level, i, j);
                            flashing = true;
                            flashes++;
                        }
                    }
                }
            }
        }

        std::cout << "Result: " << flashes << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        auto level = input(file);

        int step = 0;

        while(true) {
            step++;

            for(auto &l : level) {
                l++;
            }

            auto flashing = true;
            while(flashing) {
                flashing = false;
                auto zeros = 0;

                for(int i=0; i<n; ++i) {
                    for(int j=0; j<n; ++j) {
                        if(level[i*n + j] == 0) {
                            zeros++;
                        } else if(level[i*n + j] > 9) {
                            feedNeighbors(level, i, j);
                            flashing = true;
                            zeros++;
                        }
                    }
                }

                if(zeros == level.size()) {
                    std::cout << "Step: " << step << std::endl;
                    return;
                }
            }
        }
    }

    inline void feedNeighbors(std::vector<int> &level, int i, int j) {
        for(auto& x : { i-1, i, i+1 }) {
            for(auto& y: { j-1, j, j+1 }) {
                if(x >= 0 && y >= 0 && x < n && y < n && level[x*n + y] != 0) {
                    level[x*n + y]++;
                }
            }
        }

        level[i*n + j] = 0;
    }

    std::vector<int> input(std::ifstream &file) {
        std::vector<int> level;

        std::string input;
        while(file >> input) {
            for(auto& i : input) {
                level.push_back((int)i - 48);
            }
        }

        return level;
    }
};

#endif /* AdventTask11_h */
