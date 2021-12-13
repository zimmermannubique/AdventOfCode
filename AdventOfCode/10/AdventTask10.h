//
//  AdventTask10.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 10.12.21.
//

#ifndef AdventTask10_h
#define AdventTask10_h

#include <AdventTask.h>

class AdventTask10 : public AdventTask<10> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::string input;
        std::stack<char> stack;

        std::int64_t sum = 0;

        while(file >> input) {
            for(const auto& i : input) {
                if(isOpening(i)) {
                    stack.push(i);
                } else {
                    auto o = stack.top(); stack.pop();

                    if(!doMatch(o, i)) {
                        sum += scoreSilver(i);
                        break;
                    }
                }
            }
        }

        std::cout << "Result: " << sum << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        std::string input;
        std::vector<int64_t> sums;

        while(file >> input) {
            std::stack<char> stack;
            bool corruptInput = false;

            for(const auto& i : input) {
                if(isOpening(i)) {
                    stack.push(i);
                } else {
                    auto o = stack.top();
                    stack.pop();

                    if(!doMatch(o, i)) {
                        corruptInput = true;
                        break;
                    }
                }
            }

            if(!corruptInput) {
                int64_t sum = 0;

                while(stack.size() > 0) {
                    auto o = stack.top(); stack.pop();
                    sum = 5 * sum + scoreGold(o);
                }

                sums.push_back(sum);
            }
        }

        std::sort(sums.begin(), sums.end());
        std::cout << "Result: " << sums[sums.size() / 2] << std::endl;
    }

    int64_t scoreSilver(const char &i) {
        if(i == ']') return 57;
        if(i == '>') return 25137;
        if(i == ')') return 3;
        if(i == '}') return 1197;
        return 0;
    }

    int64_t scoreGold(const char &i) {
        if(i == '{') return 3;
        if(i == '(') return 1;
        if(i == '<') return 4;
        if(i == '[') return 2;
        return 0;
    }

    bool isOpening(const char &i) {
        return i == '{' || i == '<' || i == '[' || i == '(';
    }

    bool doMatch(const char &o, const char &c) {
        return (o == '<' && c == '>') ||
               (o == '{' && c == '}') ||
               (o == '[' && c == ']') ||
               (o == '(' && c == ')');
    }
};

#endif /* AdventTask10_h */
