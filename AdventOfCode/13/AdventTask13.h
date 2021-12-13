//
//  AdventTask13.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 13.12.21.
//

#include "AdventTask.h"

#include "Manual.h"

class AdventTask13 : public AdventTask<13> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::string input;
        std::set<ManualPoint> points;
        bool scanPoints = true;

        while(file.good()) {
            file >> input;

            if(input == "fold" || input== "along") {
                scanPoints = false;
                continue;
            }

            if(scanPoints) {
                points.insert(ManualPoint(input));
            }
            else {
                points = doFold(points, input);
                std::cout << "New Points: " << points.size();
                break;
            }
        }
    }

    virtual void solveGold(std::ifstream &file) {
        std::string input;
        std::set<ManualPoint> points;
        bool scanPoints = true;

        while(file.good()) {
            file >> input;

            if(input == "fold" || input== "along") {
                scanPoints = false;
                continue;
            }

            if(scanPoints) {
                points.insert(ManualPoint(input));
            }
            else {
                points = doFold(points, input);
            }
        }

        int maxX = 0;
        int maxY = 0;
        for(auto &p : points) {
            maxX = std::max(maxX, p.x);
            maxY = std::max(maxY, p.y);
        }

        std::vector<std::vector<char>> image(maxY+1, std::vector<char>(maxX+1, '.'));

        for(auto &p : points) {
            image[p.y][p.x] = 'X';
        }

        for(int i=0; i<image.size(); ++i) {
            for(int j=0; j<image[i].size(); ++j) {
                std::cout << image[i][j];
            }

            std::cout << std::endl;
        }
    }

    std::pair<std::string, std::string> split(const std::string& s)
    {
        auto pos = s.find('=');
        return std::make_pair(s.substr(0, pos), s.substr(pos+1, s.length()));
    }

    bool isX(const std::string& s)
    {
        return s.find("x") != std::string::npos;
    }

    std::set<ManualPoint> doFold(const std::set<ManualPoint>& points, const std::string &input) {
        auto fold = split(input);
        bool isXFold = isX(fold.first);
        int foldValue = std::stoi(fold.second);

        std::set<ManualPoint> newPoints;

        for(auto &p : points) {
            int value = isXFold ? p.x : p.y;

            if(value < foldValue) {
                newPoints.insert(p);
            } else if(value > foldValue) {
                int newValue = foldValue - std::abs(foldValue - value);
                if(newValue >= 0) {
                    if(isXFold) {
                        newPoints.insert(ManualPoint(newValue, p.y));
                    } else {
                        newPoints.insert(ManualPoint(p.x, newValue));
                    }
                }
            }
        }

        return newPoints;
    }
};
