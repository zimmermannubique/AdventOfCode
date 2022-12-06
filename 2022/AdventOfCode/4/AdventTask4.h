//
//  AdventTask4.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 04.12.21.
//

#include "AdventTask.h"

class AdventTask4 : public AdventTask<4> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        char unneeded;
        int min1,max1,min2,max2;

        int fullOverlap = 0;

        while (file >> min1 >> unneeded >> max1 >> unneeded >> min2 >> unneeded >> max2) {
            bool in1 = (min1 <= min2) && (max1 >= max2);
            bool in2 = (min2 <= min1) && (max2 >= max1);
            fullOverlap += (in1 || in2) ? 1 : 0;
        }

        std::cout << fullOverlap << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        char unneeded;
        int min1,max1,min2,max2;

        int partOverlap = 0;

        while (file >> min1 >> unneeded >> max1 >> unneeded >> min2 >> unneeded >> max2) {
            bool out1 = (max1 < min2) || (min1 > max2);
            bool out2 = (max2 < min1) || (min2 > max1);
            partOverlap += (out1 && out2) ? 0 : 1;
        }

        std::cout << partOverlap << std::endl;
    }
};
