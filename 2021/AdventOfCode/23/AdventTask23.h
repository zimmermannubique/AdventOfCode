//
//  AdventTask23.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 23.12.21.
//

#ifndef AdventTask23_h
#define AdventTask23_h

#include "State.h"

class AdventTask23 : public AdventTask<23> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        solve(file, false);
    }

    virtual void solveGold(std::ifstream &file) {
        solve(file, true);
    }

    void solve(std::ifstream &file, bool useMiddle) {
        State start = input(file, useMiddle);

        std::deque<State> states;
        states.push_front(start);

        std::map<std::string, int64_t> checked;

        int64_t score = std::numeric_limits<int64_t>::max();

        while(states.size() > 0) {
            auto s = states.front(); states.pop_front();
            auto key = s.key();

            if(checked.count(key) > 0 && checked[key] < s.score) {
                continue;
            }

            checked[key] = s.score;

            if(s.isFinished()) {
                score = std::min(score, s.score);
            } else if(s.score < score) {
                for(auto& i : s.possibleMoves()) {
                    auto key = i.key();

                    int64_t count = checked.count(key);
                    if((count > 0 && checked[key] > i.score) || count == 0) {
                        states.push_back(i);
                        checked[key] = i.score;
                    }
                }
            }
        }

        std::cout << "Score: " << score << std::endl;
    }

    State input(std::ifstream &file, bool useMiddle) {
        auto s = State(useMiddle);

        std::string input;
        file >> input; file >> input;

        file >> input;
        auto upper = StringHelper::split(input, '#');
        copy(upper.begin() + 3, upper.begin() + 7, std::back_inserter(s.upper));

        file >> input;
        auto lower = StringHelper::split(input, '#');
        copy(lower.begin() + 1, lower.begin() + 5, std::back_inserter(s.lower));

        return s;
    }
};

#endif /* AdventTask23_h */
