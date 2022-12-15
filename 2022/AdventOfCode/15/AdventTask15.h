//
//  AdventTask15.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 15.12.21.
//

#ifndef AdventTask15_h
#define AdventTask15_h

#include "AdventTask.h"

typedef std::pair<int64_t,int64_t> pi;

class AdventTask15 : public AdventTask<15> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        int64_t maxX = 0, minX = 0;
        auto inputs = getInput(file, minX, maxX);

        int sum = 0;
        for(auto i=minX-1; i<=maxX+1; ++i) {
            auto p = std::make_pair(i,2000000);

            auto notPossible = false;
            for(auto &i : inputs) {
                auto &S = i.first;
                auto &B = i.second;

                auto dist = abs(B.first - S.first) + abs(B.second - S.second);

                auto distSP = abs(p.first - S.first) + abs(p.second - S.second);
                auto distBP = abs(p.first - B.first) + abs(p.second - B.second);

                if(distSP == 0 || distBP == 0) {
                    continue;
                }

                if(distSP <= dist) {
                    notPossible = true;
                }
            }

            if(notPossible) {
                sum++;
            }
        }

        std::cout << sum << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        int64_t maxX = 0, minX = 0;
        auto inputs = getInput(file, minX, maxX);

        int n = 4000000;
        pi p = std::make_pair(0,0);

        for(int64_t i=0; i<=n; ++i) {

            std::vector<int64_t> js;

            for(auto &input : inputs) {
                auto &S = input.first;
                auto &B = input.second;
                
                auto dist = abs(B.first - S.first) + abs(B.second - S.second) + 1;

                int64_t c = abs(abs(S.first - i) - dist);

                if(c >= 0) {
                    auto s = S.second + c;
                    auto l = S.second - c;

                    if(s >= 0 && s <= n) {
                        js.push_back(s);
                    }

                    if(l >= 0 && l <= n) {
                        js.push_back(l);
                    }
                }
            }

            for(auto& j : js) {
                p.first = i;
                p.second = j;

                auto notPossible = false;
                for(auto &input : inputs) {
                    auto &S = input.first;
                    auto &B = input.second;

                    auto dist = abs(B.first - S.first) + abs(B.second - S.second);

                    auto distSP = abs(p.first - S.first) + abs(p.second - S.second);
                    auto distBP = abs(p.first - B.first) + abs(p.second - B.second);

                    if(distSP <= dist || distBP == 0) {
                        notPossible = true;
                        break;
                    }
                }

                if(!notPossible) {
                    std::cout << i << " / " << j << " => " << i * n + j << std::endl;
                    return;
                }
            }
        }
    }

    std::vector<std::string> split(std::string& input, const std::string& delimiter) {
        size_t pos = 0;
        std::vector<std::string> w;
        while ((pos = input.find(delimiter)) != std::string::npos) {
            w.push_back(input.substr(0, pos));
            input.erase(0, pos + delimiter.length());
        }

        if(input.size() > 0) {
            w.push_back(input);
        }

        return w;
    }

    pi getXY(std::string& input) {
        auto i = split(input, ", y=");
        split(i[0], "x=");
        return std::make_pair(std::stoi(i[0]), std::stoi(i[1]));
    }

    std::vector<std::pair<pi,pi>> getInput(std::ifstream& file, int64_t &minX, int64_t &maxX) {
        std::vector<std::pair<pi,pi>> inputs;

        std::string operation;

        while (!file.eof()) {
            getline(file, operation);

            if(operation == "") {
                continue;
            }

            auto i = split(operation, ": closest beacon is at ");
            split(i[0], "Sensor at ");

            auto S = getXY(i[0]);
            auto B = getXY(i[1]);
            inputs.push_back(std::make_pair(S, B));

            auto dist = abs(B.first - S.first) + abs(B.second - S.second);

            auto px = S.first - dist;
            if(px < minX) {
                minX = px;
            }

            px = S.first + dist;
            if(px > maxX) {
                maxX = px;
            }
        }

        return inputs;
    }
};

#endif /* AdventTask15_h */
