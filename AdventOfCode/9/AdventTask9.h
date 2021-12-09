//
//  AdventTask9.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 09.12.21.
//

#ifndef AdventTask9_h
#define AdventTask9_h

#include <AdventTask.h>

#include <set>

class AdventTask9 : public AdventTask<9> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::vector<std::vector<int>> lava;

        std::string input;
        while(file >> input) {
            lava.push_back({});
            for(auto& i : input) {
                int n = (int)i - 48;
                lava.back().push_back(n);
            }
        }

        int64_t sum = 0;

        for(int i=0; i<lava.size(); ++i) {
            for(int j=0; j<lava[i].size(); ++j) {
                int value = lava[i][j];
                int t = (j > 0) ? lava[i][j-1] : 10;
                int l = (i > 0) ? lava[i-1][j] : 10;
                int r = (j < lava[i].size()-1) ? lava[i][j+1] : 10;
                int b = (i < lava.size()-1) ? lava[i+1][j] : 10;

                if(value < t && value < l && value < r && value < b) {
                    sum += (1 + value);
                }
            }
        }

        std::cout << sum << std::endl;
    }


    virtual void solveGold(std::ifstream &file) {
        std::vector<std::vector<int>> lava;
        std::vector<std::vector<int>> helper;

        std::string input;
        while(file >> input) {
            lava.push_back({});
            helper.push_back({});
            for(auto& i : input) {
                int n = (int)i - 48;
                lava.back().push_back(n);
                helper.back().push_back(n == 9 ? 1000 : 0);
            }
        }

        int number = 1;
        for(int i=0; i<lava.size(); ++i) {
            for(int j=0; j<lava[i].size(); ++j) {
                if(helper[i][j] > 0) {
                    continue;
                }

                number++;

                floodFill(lava, helper, i, j, lava[i][j], number);
            }
        }

        std::vector numbers(number + 1, 0);

        for(int i=0; i<lava.size(); ++i) {
            for(int j=0; j<lava[i].size(); ++j) {
                if(helper[i][j] == 1000) {
                    continue;
                }

                numbers[helper[i][j]]++;
            }
        }

        std::sort(numbers.begin(), numbers.end(), std::greater<int>());
        std::cout << "Result: " << numbers[0]*numbers[1]*numbers[2];
    }


    void floodFill(std::vector<std::vector<int>> &lava, std::vector<std::vector<int>> &helper, int x, int y, int start, int number)
    {
        if (x < 0 || x >= lava.size() || y < 0 || y >= lava[x].size()) {
            return;
        }

        int value = lava[x][y];

        if(helper[x][y] >= number) {
            return;
        }

        if (value >= start) {
            helper[x][y] = number;
        }

        floodFill(lava, helper, x+1, y, value, number);
        floodFill(lava, helper, x-1, y, value, number);
        floodFill(lava, helper, x, y+1, value, number);
        floodFill(lava, helper, x, y-1, value, number);
    }
};

#endif /* AdventTask9_h */
