//
//  AdventTask15.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 15.12.21.
//

#ifndef AdventTask15_h
#define AdventTask15_h

#include "AdventTask.h"
#include "IntGraph.h"

#include <list>

class AdventTask15 : public AdventTask<15> {
  protected:

    virtual void solveSilver(std::ifstream &file) {
        auto numbers = input(file);
        shortestPath(numbers);
    }

    virtual void solveGold(std::ifstream &file) {
        auto numbers = input(file);

        int oldN = (int)numbers.size();
        auto s = 5;

        // build up to the bottom
        for(int a=1; a<s; ++a) {
            for(int i=0; i<oldN; ++i) {
                numbers.emplace_back(modified(numbers[i], a));
            }
        }

        // build up to the right
        for(int a=1; a<s; ++a) {
            for(int i=0; i<numbers.size(); ++i) {
                for(int j=0; j<oldN; ++j) {
                    numbers[i].emplace_back(increment(numbers[i][j], a));
                }
            }
        }

        shortestPath(numbers);
    }

    std::vector<int> modified(const std::vector<int> &v, int a) {
        std::vector<int> vRes;
        for(auto& i : v) {
            vRes.emplace_back(increment(i,a));
        }

        return vRes;
    }

    int increment(int v, int a) {
        int res = v + a;
        return res >= 10 ? (res - 9) : res;
    }

    inline int index(int i, int j, int n) {
        return i * n + j;
    }

    void shortestPath(const std::vector<std::vector<int>> &numbers) {
        IntGraph g;
        int n = (int)numbers.size();

        for(int i=0; i<n; ++i) {
            for(int j=0; j<n; ++j) {
                int ijIndex = index(i, j, n);
                if(i-1 >= 0) { g.addEdge(ijIndex, index(i-1, j, n), numbers[i-1][j]); }
                if(i+1 <  n) { g.addEdge(ijIndex, index(i+1, j, n), numbers[i+1][j]); }
                if(j+1 <  n) { g.addEdge(ijIndex, index(i, j+1, n), numbers[i][j+1]); }
                if(j-1 >= 0) { g.addEdge(ijIndex, index(i, j-1, n), numbers[i][j-1]); }
            }
        }

        g.shortestPath(0, n*n-1);
    }

    std::vector<std::vector<int>> input(std::ifstream& file) {
        std::vector<std::vector<int>> numbers;

        std::string input;
        while(file >> input) {
            numbers.push_back({});
            for(auto& i : input) {
                int n = (int)i - 48;
                numbers.back().push_back(n);
            }
        }

        return numbers;
    }
};

#endif /* AdventTask15_h */
