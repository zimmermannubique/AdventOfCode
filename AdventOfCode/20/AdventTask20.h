//
//  AdventTask20.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 20.12.21.
//

#ifndef AdventTask20_h
#define AdventTask20_h

class AdventTask20 : public AdventTask<20> {
  protected:
    std::vector<std::vector<std::vector<bool>>> grid;
    std::vector<bool> algorithm;

    virtual void solveSilver(std::ifstream &file) {
        solve(file, 2);
    }

    virtual void solveGold(std::ifstream &file) {
        solve(file, 50);
    }

    void solve(std::ifstream &file, int iterations) {
        algorithm.clear();
        grid.clear();

        while(algorithm.size() < 512) {
            char c; file >> c;
            algorithm.push_back(c == '#');
        }

        std::string input;
        while(file >> input) {
            grid.push_back({});
            for(auto& c : input) {
                grid.back().push_back({ c == '#' });
            }
        }

        // add padding
        int add = iterations;
        int s = (int)input.size() + 2 * add;
        auto paddingTop = std::vector<std::vector<bool>>(s, { false });
        auto padding = std::vector<std::vector<bool>>(add, {false });

        for(auto& v : grid) {
            v.insert(v.begin(), padding.begin(), padding.end());
            v.insert(v.end(), padding.begin(), padding.end());
        }

        for(int i=0; i<add; ++i) {
            grid.insert(grid.begin(), paddingTop);
            grid.insert(grid.end(), paddingTop);
        }

        // solve
        bool outside = false;

        for(int s=0; s<iterations; ++s) {
            for(int i=0; i<grid.size(); ++i) {
                for(int j=0; j<grid[i].size(); ++j) {
                    grid[i][j].push_back(calculate(i, j, s, outside));
                }
            }

            outside = outside ? algorithm.back() : algorithm.front();
        }

        int count = 0;
        for(int i=0; i<grid.size(); ++i) {
            for(int j=0; j<grid[i].size(); ++j) {
                count += grid[i][j].back() ? 1 : 0;
            }
        }

        std::cout << "Count: " << count;
    }

    bool calculate(int i, int j, int s, bool outside) {
        std::string bits = "";
        for(int x=-1; x<2; ++x) {
            for(int y=-1; y<2; ++y) {
                int ix = i + x;
                int jy = j + y;
                bool inside = ix >= 0 && ix < grid.size() && jy >= 0 && jy < grid[0].size();
                bits.push_back((inside ? grid[ix][jy][s] : outside) ? '1' : '0');
            }
        }

        auto value = std::bitset<9>(bits).to_ullong();
        return algorithm[value];
    }
};

#endif /* AdventTask20_h */
