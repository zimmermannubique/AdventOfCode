//
//  AdventTask14.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 14.12.21.
//

#ifndef AdventTask14_h
#define AdventTask14_h

#include "AdventTask.h"

class AdventTask14 : public AdventTask<14> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        int globalMaxY;
        auto field = getField(file, globalMaxY);

        bool isOver = false;

        int count = 0;

        while(!isOver) {
            std::pair<int, int> sp = std::make_pair(500,0);

            bool isMoving = true;

            while(isMoving) {
                if(field.count(std::make_pair(sp.first, sp.second + 1)) == 0 && sp.second <= globalMaxY + 2) {
                    sp.second = sp.second + 1;
                } else if(field.count(std::make_pair(sp.first - 1, sp.second + 1)) == 0 && sp.second <= globalMaxY + 2) {
                    sp.first = sp.first - 1;
                    sp.second = sp.second + 1;
                } else if(field.count(std::make_pair(sp.first + 1, sp.second + 1)) == 0 && sp.second <= globalMaxY + 2) {
                    sp.first = sp.first + 1;
                    sp.second = sp.second + 1;
                } else {
                    isMoving = false;
                }

                if(!isMoving) {
                    field[sp] = true;
                }

                if(sp.second == globalMaxY) {
                    isMoving = false;
                    isOver = true;
                    break;
                }
            }

            count++;
        }

        std::cout << count - 1;
    }

    virtual void solveGold(std::ifstream &file) {
        int globalMaxY;
        auto field = getField(file, globalMaxY);

        bool isOver = false;
        int count = 0;

        while(!isOver) {
            auto alwaysStart = std::make_pair(500,0);
            std::pair<int, int> sp = alwaysStart;

            bool isMoving = true;

            while(isMoving) {
                if(field.count(std::make_pair(sp.first, sp.second + 1)) == 0 && sp.second + 1 < globalMaxY + 2) {
                    sp.second = sp.second + 1;
                } else if(field.count(std::make_pair(sp.first - 1, sp.second + 1)) == 0 && sp.second + 1 < globalMaxY + 2) {
                    sp.first = sp.first - 1;
                    sp.second = sp.second + 1;
                } else if(field.count(std::make_pair(sp.first + 1, sp.second + 1)) == 0 && sp.second + 1 < globalMaxY + 2) {
                    sp.first = sp.first + 1;
                    sp.second = sp.second + 1;
                } else {
                    isMoving = false;
                }

                if(!isMoving) {
                    field[sp] = true;

                    if(sp == alwaysStart) {
                        isOver = true;
                        break;
                    }
                }
            }

            count++;
        }

        std::cout << count;
    }

    std::map<std::pair<int,int>, bool> getField(std::ifstream& file, int& globalMaxY) {
        std::string input;
        std::map<std::pair<int, int>, bool> field;

        globalMaxY = 0;
        while (!file.eof()) {
            getline(file, input);

            if(input == "") {
                continue;
            }

            size_t pos = 0;
            std::vector<std::string> w;
            std::string delimiter = " -> ";
            while ((pos = input.find(delimiter)) != std::string::npos) {
                w.push_back(input.substr(0, pos));
                input.erase(0, pos + delimiter.length());
            }

            if(input.size() > 0) {
                w.push_back(input);
            }

            std::vector<std::pair<int, int>> wp;
            for(auto& p : w) {
                auto a = StringHelper::split(p, ',');
                wp.push_back(std::make_pair(std::stoi(a[0]), std::stoi(a[1])));
            }

            for(int i=0; i<wp.size()-1; ++i) {
                auto p = wp[i];
                auto pi = wp[i+1];

                auto minX = std::min(p.first, pi.first);
                auto maxX = std::max(p.first, pi.first);
                auto minY = std::min(p.second, pi.second);
                auto maxY = std::max(p.second, pi.second);

                for(int j=minX; j<=maxX; ++j) {
                    for(int l=minY; l<=maxY; ++l) {
                        field[std::make_pair(j,l)] = true;

                        if(l >= globalMaxY) {
                            globalMaxY = l;
                        }
                    }
                }
            }
        }

        return field;
    }
};

#endif /* AdventTask14_h */
