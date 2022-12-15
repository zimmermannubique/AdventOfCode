//
//  AdventTask8.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 08.12.21.
//

#ifndef AdventTask8_h
#define AdventTask8_h

#include <AdventTask.h>

class AdventTask8 : public AdventTask<8> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        auto field = parse(file);

        int n = 0;
        for(auto& i : fromTo(1, (int)field.size()-2, 1, (int)field[0].size()-2)) {
            n += check(field, i.first, i.second) ? 1 : 0;
        }

        n += field.size() * 2 + field[0].size() * 2 - 4;
        std::cout << n << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        auto field = parse(file);

        int max = 0;
        for(auto& i : fromTo(1, (int)field.size()-2, 1, (int)field[0].size()-2)) {
            max = std::max(score(field, i.first, i.second), max);
        }

        std::cout << max << std::endl;
    }

    bool check(const std::vector<std::vector<int>> &field, int m, int n) {
        int value = field[m][n];

        for(auto& i : iterators(field, m, n)) {
            bool allSmaller = true;
            for(auto& j : i) {
                allSmaller = allSmaller && (field[j.first][j.second] < value);
            }

            if(allSmaller) { return true; }
        }

        return false;
    }

    int score(const std::vector<std::vector<int>> &field, int m, int n) {
        int value = field[m][n];

        int score = 1;
        for(auto& i : iterators(field, m, n)) {
            int p = 0;
            for(auto& j : i) {
                p += 1;
                if(field[j.first][j.second] >= value) { break; }
            }

            score *= p;
        }

        return score;
    }

    std::vector<std::vector<int>> parse(std::ifstream& file) {
        std::vector<std::vector<int>> field;

        std::string input;
        while(file >> input) {
            field.push_back({});
            for(auto& i : input) {
                int n = (int)i - 48;
                field.back().push_back(n);
            }
        }

        return field;
    }

    std::vector<std::pair<int,int>> fromTo(int i1, int i2, int j1, int j2, bool reverse = false) {
        std::vector<std::pair<int,int>> pairs;
        for(int i=i1;i<=i2;++i) {
            for(int j=j1;j<=j2;++j) {
                pairs.push_back(std::make_pair(i,j));
            }
        }

        if(reverse) {
            std::reverse(pairs.begin(), pairs.end());
        }

        return pairs;
    }

    std::vector<std::vector<std::pair<int,int>>> iterators(const std::vector<std::vector<int>> &field, int m, int n) {
        auto left = fromTo(0, m-1, n, n, true);
        auto right = fromTo(m+1, (int)field[0].size()-1, n, n);
        auto top = fromTo(m, m, 0, n-1, true);
        auto bottom = fromTo(m, m, n+1, (int)field[m].size()-1);
        return { left, right, top, bottom };
    }
};

#endif /* AdventTask8_h */
