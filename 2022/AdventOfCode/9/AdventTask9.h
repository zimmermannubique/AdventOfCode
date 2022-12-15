//
//  AdventTask9.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 09.12.21.
//

#ifndef AdventTask9_h
#define AdventTask9_h

#include <AdventTask.h>

struct Pos {
    Pos(int x, int y): x(x), y(y) {};
    int x, y;

    bool operator<(const Pos& rhs) const {
        return std::tie(x, y) < std::tie(rhs.x, rhs.y);
    }
};

class AdventTask9 : public AdventTask<9> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        solve(file, 2);
    }

    virtual void solveGold(std::ifstream &file) {
        solve(file, 10);
    }

    void solve(std::ifstream& file, int number) {
        std::vector<Pos> positions;
        for(int i=0; i<number; ++i) {
            positions.push_back(Pos(0,0));
        }

        std::string m; int n;
        std::set<Pos> all;
        all.insert(positions[0]);

        while (file >> m >> n) {
            for(int i=0; i<n; ++i) {
                for(int j=0; j<positions.size()-1; ++j) {
                    simulateStep(positions[j], positions[j+1], m, j==0);
                }

                all.insert(positions[positions.size() - 1]);
            }
        }

        std::cout << all.size() << std::endl;
    }

    void simulateStep(Pos& H, Pos& T, const std::string& m, bool move) {
        if(move) {
            switch (m[0]) {
                case 'L': { H.x -= 1; break; }
                case 'R': { H.x += 1; break; }
                case 'U': { H.y += 1; break; }
                case 'D': { H.y -= 1; break; }
                default : { break; }
            }
        }

        if(abs(H.x - T.x) > 1 || abs(H.y - T.y) > 1) {
            T.x = T.x + ((H.x == T.x) ? 0 : (H.x > T.x ? 1 : -1));
            T.y = T.y + ((H.y == T.y) ? 0 : (H.y > T.y ? 1 : -1));
        }
    }
};

#endif /* AdventTask9_h */
