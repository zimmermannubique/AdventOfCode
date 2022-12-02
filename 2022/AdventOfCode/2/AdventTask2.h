//
//  AdventTask2.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 02.12.21.
//

#include "AdventTask.h"

class AdventTask2 : public AdventTask<2> {
protected:
    virtual void solveSilver(std::ifstream &file) {
        std::string one, two;
        int64_t value = 0;

        while (file >> one >> two) {
            value += score(one, two);
        }

        std::cout << value << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        std::string one, two;
        int64_t value = 0;

        while (file >> one >> two) {
            std::string newTwo = getNewTwo(one, two);
            value += score(one, newTwo);
        }

        std::cout << value << std::endl;
    }

    int score(std::string& one, std::string& two) {
        std::vector<int> points = {0, 3, 6};
        std::vector<int> rot = {1, 0, 2};
        int index = one[0] - 'A';

        int result = points[rotateIndex(two, rot[index])];

        std::vector<int> second = {1, 2, 3};
        result += second[rotateIndex(two, 0)];

        return result;
    }

    std::string getNewTwo(std::string& one, std::string& two) {
        std::vector<std::string> p = { "X", "Y", "Z" };
        std::vector<int> rot = {2, 0, 1};
        int index = one[0] - 'A';

        return p[rotateIndex(two, rot[index])];
    }

    int rotateIndex(std::string& input, int rotate) {
        int start = input[0] - 'X';
        return (start + rotate) % 3;
    }
};
