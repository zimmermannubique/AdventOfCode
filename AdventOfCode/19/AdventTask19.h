//
//  AdventTask19.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 19.12.21.
//

#ifndef AdventTask19_h
#define AdventTask19_h

#include "Scanner.h"

class AdventTask19 : public AdventTask<19> {
  protected:
    std::vector<Mode> modes = allModes();
    std::vector<Scanner> scanners;

    virtual void solveSilver(std::ifstream &file) {
        scanners = getScanners(file);

        while(scanners.size() > 1) {
            bool breakFlag = false;
            for(int i=0; i<scanners.size(); ++i) {
                if(breakFlag) { break; }
                for(int j=0; j<scanners.size(); ++j) {
                    if(i!=j) {
                        auto res = mergeIfPossible(scanners[i], scanners[j]);

                        if(res) {
                            scanners.erase(scanners.begin() + j);
                            breakFlag = true;
                            break;
                        }
                    }
                }
            }
        }

        std::cout << scanners[0].points.size() << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        // Dr Gold Punkt: Manhatttan oder manhatttan nid!
        std::cout << scanners[0].largestManhattanDistance() << std::endl;
    }

    std::vector<Scanner> getScanners(std::ifstream &file) {
        std::vector<Scanner> scanners;
        
        std::string input;
        while(file >> input) {
            if(input.starts_with("--")) {
                scanners.push_back(Scanner());
                file >> input; file >> input; file >> input;
            } else {
                scanners.back().points.push_back(point(input));
            }
        }

        return scanners;
    }

    Point3D point(const std::string& commaNumbers) {
        std::vector<int> n;
        std::stringstream ss(commaNumbers);
        int i;
        while (ss >> i) {
            n.push_back(i);
            ss.ignore(1);
        }

        return Point3D(n[0], n[1], n[2]);
    }

    std::vector<Mode> allModes() {
        std::vector<Mode> modes;
        modes.push_back(Mode({0,1,2}, {1,1,1})); // {x, y, -z}
        modes.push_back(Mode({2,1,0}, {-1,1,1})); // {z, y, x}
        modes.push_back(Mode({0,1,2}, {-1,1,-1})); // {-x, y, z}
        modes.push_back(Mode({2,1,0}, {1,1,-1})); // {-z, y, -x}
        modes.push_back(Mode({0,1,2}, {1,-1,-1})); // {x, -y, z}
        modes.push_back(Mode({2,1,0}, {1,-1,1})); // {-z, -y, x}
        modes.push_back(Mode({0,1,2}, {-1,-1,1})); // {-x, -y, -z}
        modes.push_back(Mode({2,1,0}, {-1,-1,-1})); // {z, -y, -x}
        modes.push_back(Mode({2,0,1}, {-1,1,-1})); // {z, x, -y}
        modes.push_back(Mode({1,0,2}, {1,1,-1})); // {y, x, z}
        modes.push_back(Mode({2,0,1}, {1,1,-1})); // {-z, x, -y}
        modes.push_back(Mode({1,0,2}, {-1,1,1})); // {-y, x, -z}
        modes.push_back(Mode({1,0,2}, {1,-1,1})); // {y, -x, -z}
        modes.push_back(Mode({2,0,1}, {-1,-1,1})); // {z, -x, y}
        modes.push_back(Mode({1,0,2}, {-1,-1,-1})); // {-y, -x, z}
        modes.push_back(Mode({2,0,1}, {1,-1,-1})); // {-z, -x, -y}
        modes.push_back(Mode({1,2,0}, {1,-1,-1})); // {y, z, -x}
        modes.push_back(Mode({0,2,1}, {1,-1,1})); // {x, z, y}
        modes.push_back(Mode({1,2,0}, {-1,-1,1})); // {-y, z, x}
        modes.push_back(Mode({0,2,1}, {-1,-1,-1})); // {-x, z, -y}
        modes.push_back(Mode({0,2,1}, {1,1,-1})); // {x, -z, -y}
        modes.push_back(Mode({1,2,0}, {1,1,1})); // {y, -z, x}
        modes.push_back(Mode({0,2,1}, {-1,1,1})); // {-x, -z, y}
        modes.push_back(Mode({1,2,0}, {-1,1,-1})); // {-y, -z, -x}
        return modes;
    }

    bool mergeIfPossible(Scanner& zero, Scanner &b) {
        for(auto &mode : modes) {
            std::map<Point3D, int> tMap;

            for(const auto &pZero : zero.points) {
                for(const auto &p1 : b.points) {
                    auto p1m = p1.get(mode);
                    auto t = p1m - pZero;

                    tMap[t]++;
                }
            }

            auto max = std::max_element(tMap.begin(), tMap.end(),
                [](const auto& p1, const auto& p2) {
                    return p1.second < p2.second; });

            if(max->second >= 12) {
                zero.add(b, mode, max->first);
                return true;;
            }
        }

        return false;
    }
};

#endif /* AdventTask19_h */
