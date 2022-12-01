//
//  AdventTask22.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 22.12.21.
//

#ifndef AdventTask22_h
#define AdventTask22_h

#include "Range.h"

class AdventTask22 : public AdventTask<22> {
  protected:
    std::map<CubePoint, int> onOff;

    virtual void solveSilver(std::ifstream &file) {
        std::vector<Range> ranges;

        while(file.good()) {
            std::pair<int64_t, int64_t> xR, yR, zR;
            bool on;

            input(file, xR, yR, zR, on);

            ranges.emplace_back(xR, yR, zR, on);

            file >> std::ws;

            if(xR.first > 50 || yR.first > 50 || zR.first > 50) { continue; }
            if(xR.second < -50 || yR.second < -50 || zR.second < -50) { continue; }

            xR.first = std::max(int64_t(-50), xR.first);
            yR.first = std::max(int64_t(-50), yR.first);
            zR.first = std::max(int64_t(-50), zR.first);

            xR.second = std::min(int64_t(50), xR.second);
            yR.second = std::min(int64_t(50), yR.second);
            zR.second = std::min(int64_t(50), zR.second);

            for(auto x=xR.first; x<=xR.second; ++x) {
                for(auto y=yR.first; y<=yR.second; ++y) {
                    for(auto z=zR.first; z<=zR.second; ++z) {
                        auto p = CubePoint(x, y, z);

                        auto it = onOff.find(p);
                        if(!on && it != onOff.end()) {
                            onOff.erase(it);
                        } else if(on) {
                            onOff[p] = 1;
                        }
                    }
                }
            }
        }

        std::cout << "Result: " << onOff.size() << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        std::vector<Range> ranges;

        while(file.good()) {
            std::pair<int64_t, int64_t> xR, yR, zR;
            bool on;

            input(file, xR, yR, zR, on);
            ranges.emplace_back(xR, yR, zR, on);

            file >> std::ws;
        }

        std::vector<Range> resultRanges = { ranges[0] };

        for(int i=1; i<ranges.size(); ++i) {
            if(ranges[i].on) {
                for(auto& rr : resultRanges) {
                    rr.add(ranges[i]);
                }

                resultRanges.push_back(ranges[i]);
            } else {
                for(auto& rr : resultRanges) {
                    rr.add(ranges[i]);
                }
            }
        }

        int64_t sum = 0;
        for(auto& r : resultRanges) {
            sum += r.number();
        }

        std::cout << "Result: " << sum << std::endl;
    }

    std::pair<int64_t, int64_t> split(const std::string& s)
    {
        auto pos = s.find("..");
        return std::make_pair(std::stoi(s.substr(0, pos)), std::stoi(s.substr(pos+2, s.length())));
    }

    void input(std::ifstream &file, std::pair<int64_t, int64_t> &x, std::pair<int64_t, int64_t> &y, std::pair<int64_t, int64_t> &z, bool& on) {
        std::string input;
        file >> input;

        on = input.starts_with("on");

        file >> input;

        auto inputs = StringHelper::split(input, ',');

        for(auto& input : inputs) {
            if(input.starts_with("x")) {
                input = input.substr(2, input.size());
                x = split(input);
            }
            else if(input.starts_with("y")) {
                input = input.substr(2, input.size());
                y = split(input);
            }
            else if(input.starts_with("z")) {
                input = input.substr(2, input.size());
                z = split(input);
            }
        }
    }

};

#endif /* AdventTask22_h */
