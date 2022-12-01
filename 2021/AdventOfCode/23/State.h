//
//  State.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 23.12.21.
//

#ifndef State_h
#define State_h

struct State {
    State(bool useMiddle) : useMiddle(useMiddle) {}

    bool useMiddle = false;
    std::vector<std::string> upper = {};
    std::vector<std::string> middleUp = {"D", "C", "B", "A"};
    std::vector<std::string> middleLow = {"D", "B", "A", "C"};
    std::vector<std::string> lower = {};

    std::vector<std::string> top = {"", "", /* A */ "", /* B */  "", /* C */ "", /* D */ "", ""};
    int64_t score = 0;

    std::vector<State> possibleMoves() {
        std::vector<State> states;

        for(int i=0; i<top.size(); ++i) {
            if(top[i] == "") { continue; }
            int idx = index(top[i]);

            bool middle = useMiddle ? (middleLow[idx] == top[i] && middleUp[idx] == top[i]) : true;

            if(top[i] == lower[idx] && upper[idx] == "" && middle) {
                if(canMoveBottom(idx, i)) {
                    State newS = *this;
                    newS.score += cost(top[i], idx, i);
                    newS.upper[idx] = top[i];
                    newS.top[i] = "";
                    states.push_back(newS);
                }
            }

            if(useMiddle) {
                // middleUp
                if(top[i] == lower[idx] && middleLow[idx] == top[i] && upper[idx] == "" && middleUp[idx] == "") {
                    if(canMoveBottom(idx, i)) {
                        State newS = *this;
                        newS.score += cost(top[i], idx, i) + 1 * cost(top[i]);
                        newS.middleUp[idx] = top[i];
                        newS.top[i] = "";
                        states.push_back(newS);
                    }
                }

                // middleLow
                if(top[i] == lower[idx] && upper[idx] == "" && middleLow[idx] == "" && middleUp[idx] == "") {
                    if(canMoveBottom(idx, i)) {
                        State newS = *this;
                        newS.score += cost(top[i], idx, i) + 2 * cost(top[i]);
                        newS.middleLow[idx] = top[i];
                        newS.top[i] = "";
                        states.push_back(newS);
                    }
                }
            }

            middle = useMiddle ? (middleUp[idx] == "" && middleLow[idx] == "") : true;

            if(lower[idx] == "" && upper[idx] == "" && middle) {
                if(canMoveBottom(idx, i)) {
                    State newS = *this;
                    newS.score += cost(top[i], idx, i) + (useMiddle ? 3 : 1) * cost(top[i]);
                    newS.lower[idx] = top[i];
                    newS.top[i] = "";
                    states.push_back(newS);
                }
            }
        }

        // if one can be moved down, that's the best option always,
        // so return
        if(states.size() > 0) {
            return states;
        }

        for(int i=0; i<upper.size(); ++i) {
            if(upper[i] != "") {
                for(int j=0; j<top.size(); ++j) {
                    if(isTopReachable(i, j)) {
                        State newS = *this;
                        newS.score += cost(upper[i], i, j);
                        newS.upper[i] = "";
                        newS.top[j] = upper[i];
                        states.push_back(newS);
                    }
                }
            }
        }

        if(useMiddle) {
            for(int i=0; i<middleUp.size(); ++i) {
                if(middleUp[i] != "" && upper[i] == "") {
                    for(int j=0; j<top.size(); ++j) {
                        if(isTopReachable(i, j)) {
                            State newS = *this;
                            newS.score += cost(middleUp[i], i, j) + cost(middleUp[i]);
                            newS.middleUp[i] = "";
                            newS.top[j] = middleUp[i];
                            states.push_back(newS);
                        }
                    }
                }
            }


            for(int i=0; i<middleLow.size(); ++i) {
                if(middleLow[i] != "" && middleUp[i] == "" && upper[i] == "") {
                    for(int j=0; j<top.size(); ++j) {
                        if(isTopReachable(i, j)) {
                            State newS = *this;
                            newS.score += cost(middleLow[i], i, j) + 2 * cost(middleLow[i]);
                            newS.middleLow[i] = "";
                            newS.top[j] = middleLow[i];
                            states.push_back(newS);
                        }
                    }
                }
            }
        }


        for(int i=0; i<lower.size(); ++i) {
            bool middle = useMiddle ? (middleLow[i] == "" && middleUp[i] == "") : true;

            if(lower[i] != "" && upper[i] == "" && middle) {
                for(int j=0; j<top.size(); ++j) {
                    if(isTopReachable(i, j)) {
                        State newS = *this;
                        newS.score += cost(lower[i], i, j) + (useMiddle ? 3 : 1) * cost(lower[i]);
                        newS.lower[i] = "";
                        newS.top[j] = lower[i];
                        states.push_back(newS);
                    }
                }
            }
        }

        return states;
    }

    bool isTopReachable(int index, int topIndex) {
        float startIndex = 1.5 + index;

        if(startIndex > topIndex) {
            for(int i=floor(startIndex); i>=topIndex; --i) {
                if(top[i] != "") { return false; }
            }
        } else {
            for(int i=ceil(startIndex); i<=topIndex; ++i) {
                if(top[i] != "") { return false; }
            }
        }

        return true;
    }

    bool canMoveBottom(int index, int topIndex) {
        float startIndex = 1.5 + index;

        if(startIndex > topIndex) {
            for(int i=floor(startIndex); i>topIndex; --i) {
                if(top[i] != "") { return false; }
            }
        } else {
            for(int i=ceil(startIndex); i<topIndex; ++i) {
                if(top[i] != "") { return false; }
            }
        }

        return true;
    }

    int64_t cost(const std::string& letter, int index, int topIndex) {
        float startIndex = 1.5 + index;
        auto letterCost = cost(letter);

        int64_t start = (startIndex > topIndex) ? floor(startIndex) : ceil(startIndex);
        int64_t c = (std::abs(topIndex - start) + 1) * 2 * letterCost;

        if(topIndex == 0 || topIndex == top.size() - 1) {
            c -= letterCost;
        }

        return c;
    }

    int index(const std::string& letter) {
        if(letter == "A") return 0;
        if(letter == "B") return 1;
        if(letter == "C") return 2;
        if(letter == "D") return 3;
        return 0;
    }

    int cost(const std::string& letter) {
        if(letter == "A") return 1;
        if(letter == "B") return 10;
        if(letter == "C") return 100;
        if(letter == "D") return 1000;
        return 0;
    }

    bool isFinished() {
        std::vector<std::string> correct = {"A", "B", "C", "D"};

        if(useMiddle) {
            return lower == correct && upper == correct && middleLow == correct && middleUp == correct;
        } else {
            return lower == correct && upper == correct;
        }
    }

    std::string key() {
        std::stringstream ss;

        std::vector<std::vector<std::string>> levels = {lower, upper, top};
        if(useMiddle) {
            levels.push_back(middleLow);
            levels.push_back(middleUp);
        }

        for(auto& level : levels) {
            for(auto& i : level) {
                ss << ((i == "") ? "-" : i);
            }
        }

        return ss.str();
    }
};

#endif /* State_h */
