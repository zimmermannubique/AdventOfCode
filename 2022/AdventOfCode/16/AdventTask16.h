//
//  AdventTask16.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 16.12.21.
//

#ifndef AdventTask16_h
#define AdventTask16_h

#include "AdventTask.h"

struct State {
    int64_t sum = 0;
    int64_t moves;
    std::string current;
    std::vector<std::string> open = {};
};

struct State2 {
    int64_t sum = 0;
    int64_t moves;
    std::vector<std::string> current;
    std::vector<std::string> open = {};
};

class AdventTask16 : public AdventTask<16> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::map<std::string, std::vector<std::string>> graph;
        std::map<std::string, int> isOpenMap;
        std::map<std::string, int> rates;

        parseInput(file, graph, rates);

        int64_t max = 0;

        int all = 0;
        for(auto& a : graph) {
            all += rates[a.first] > 0 ? 1 : 0;
        }

        std::vector<State> states;
        State s;
        s.moves = 30;
        s.current = "AA";
        states.push_back(s);

        while(states.size() != 0) {
            auto s = states.back(); states.pop_back();
            max = std::max(s.sum, max);

            if(s.moves == 0 || s.open.size() == all) {
                max = std::max(s.sum, max);
            } else {
                if(std::find(s.open.begin(), s.open.end(), s.current) == s.open.end() && rates[s.current] > 0) {
                    // open
                    State open = s;
                    open.moves--;
                    open.sum += open.moves * rates[s.current];
                    open.open.push_back(s.current);

                    if(open.open.size() == all) {
                        max = std::max(open.sum, max);
                    } else {
                        states.insert(states.begin(), open);
                    }
                }

                for(auto &neighbor : graph[s.current]) {
                    bool hasBetter = false;
                    for(auto& ss : states) {
                        if(ss.current == neighbor && ss.moves >= (s.moves-1) && ss.sum >= s.sum) {
                            hasBetter = true;
                            break;
                        }
                    }

                    if(!hasBetter) {
                        State move = s;
                        move.moves--;
                        move.current = neighbor;
                        states.insert(states.begin(), move);
                    }
                }
            }
        }

        std::cout << max << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        std::map<std::string, std::vector<std::string>> graph;
        std::map<std::string, int> rates;

        parseInput(file, graph, rates);

        int64_t max = 0;

        int all = 0;
        for(auto& a : graph) {
            all += rates[a.first] > 0 ? 1 : 0;
        }

        std::vector<State2> states;
        State2 s;
        s.moves = 26;
        s.current = { "AA", "AA" };
        states.push_back(s);

        while(states.size() != 0) {
            auto s = states.back(); states.pop_back();
            max = std::max(s.sum, max);

            if(s.moves == 0 || s.open.size() == all) {
                max = std::max(s.sum, max);
            } else {
                std::vector<bool> canOpen = {false, false};
                std::vector<std::vector<std::string>> canMove = { {  }, { } };

                for(int i=0; i<s.current.size(); ++i) {
                    auto current = s.current[i];

                    if(std::find(s.open.begin(), s.open.end(), current) == s.open.end() && rates[current] > 0) {
                        // open
                        State2 open = s;
                        open.moves--;
                        open.sum += open.moves * rates[current];
                        open.open.push_back(current);
                        canOpen[i] = true;
                    }

                    for(auto &neighbor : graph[current]) {
                        canMove[i].push_back(neighbor);
                    }
                }

                if(canOpen[0] && canOpen[1] && s.current[0] != s.current[1]) {
                    State2 open = s;
                    open.moves--;
                    open.sum += open.moves * rates[s.current[0]] + open.moves * rates[s.current[1]];
                    open.open.push_back(s.current[0]);
                    open.open.push_back(s.current[1]);

                    open.current = s.current;

                    states.insert(states.begin(), open);
                } else if(canOpen[0]) {
                    auto current = s.current[0];

                    for(auto& i : canMove[1]) {
                        State2 open = s;
                        open.moves--;
                        open.sum += open.moves * rates[current];
                        open.open.push_back(current);
                        open.current = { current, i };

                        states.insert(states.begin(), open);
                    }
                } else if(canOpen[1]) {
                    auto current = s.current[1];

                    for(auto& i : canMove[0]) {
                        State2 open = s;
                        open.moves--;
                        open.sum += open.moves * rates[current];
                        open.open.push_back(current);
                        open.current = { i, current };

                        states.insert(states.begin(), open);
                    }
                }

                for(auto &i : canMove[0]) {
                    for(auto& j : canMove[1]) {
                        if(i == j) {
                            continue;
                        }
                        bool hasBetter = false;
                        for(auto& ss : states) {
                            auto same = ss.current[0] == i && ss.current[1] == j;
                            if(same && ss.moves >= (s.moves-1) && ss.sum >= s.sum) {
                                hasBetter = true;
                                break;
                            }
                        }

                        if(!hasBetter) {
                            State2 move = s;
                            move.moves--;
                            move.current = { i, j };
                            states.insert(states.begin(), move);
                        }
                    }
                }
            }
        }

        std::cout << max << std::endl;
    }

    void parseInput(std::ifstream& file, std::map<std::string, std::vector<std::string>> &graph, std::map<std::string, int> &rates) {
        std::string start = "Valve ";
        std::string rate = " has flow rate=";
        std::string valves1 = "; tunnel leads to valve ";
        std::string valves2 = "; tunnels lead to valves ";

        std::string operation;

        while (!file.eof()) {
            getline(file, operation);

            if(operation == "") {
                continue;
            }

            auto i = StringHelper::split(operation, start);
            auto names = StringHelper::split(i[1], rate);
            auto valuesNeigh = StringHelper::split(names[1], valves1);

            if(valuesNeigh.size() != 2) {
                valuesNeigh = StringHelper::split(names[1], valves2);
            }

            std::string n = names[0];
            int rate = std::stoi(valuesNeigh[0]);

            auto neighbors = StringHelper::split(valuesNeigh[1], ", ");

            graph[n] = neighbors;
            rates[n] = rate;
        }
    }

    pi getXY(std::string& input) {
        auto i = StringHelper::split(input, ", y=");
        StringHelper::split(i[0], "x=");
        return std::make_pair(std::stoi(i[0]), std::stoi(i[1]));
    }
};


#endif /* AdventTask16_h */
