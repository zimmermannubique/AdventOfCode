//
//  AdventTask5.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 05.12.21.
//

#ifndef AdventTask5_h
#define AdventTask5_h

#include "VentBoard.h"

class AdventTask5 : public AdventTask<5> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        solve(file, true);
    }

    virtual void solveGold(std::ifstream &file) {
        solve(file, false);
    }

  private:
    void solve(std::ifstream &file, bool isSilver) {
        std::vector<VentLine> lines;
        int max = 0;

        while(file.good()) {
            std::string input;

            file >> input;
            auto p0 = VentPoint(input);

            // ignore "->"
            file >> input;

            file >> input;
            auto p1 = VentPoint(input);

            max = std::max({max, p0.x, p0.y, p1.x, p1.y});
            lines.push_back(VentLine(p0, p1));

            file >> std::ws;
        }

        VentBoard vb(max + 1);

        for(auto& l : lines) {
            if(isSilver && !l.horizontalOrVertical()) { continue; }
            vb.addLine(l);
        }

        std::cout << vb.result() << std::endl;
    }
};

#endif /* AdventTask5_h */
