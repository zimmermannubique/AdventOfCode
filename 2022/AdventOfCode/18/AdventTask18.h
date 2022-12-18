//
//  AdventTask18.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 18.12.21.
//

#ifndef AdventTask18_h
#define AdventTask18_h

#include "AdventTask.h"

struct Point3D {
    Point3D(int x, int y, int z) : x(x), y(y), z(z) {};

    bool operator==(const Point3D& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator<(const Point3D& lhs) const {
        return std::tie(x,y,z) < std::tie(lhs.x,lhs.y,lhs.z);
    }

    std::vector<Point3D> neighbors() const {
        std::vector<Point3D> ps;
        for(int i=-1;i<=1;++i) {
            for(int j=-1;j<=1;++j) {
                for(int k=-1;k<=1;++k) {
                    if(abs(i) + abs(j) + abs(k) != 1) { continue; }
                    ps.push_back(Point3D(x + i, y + j, z + k));
                }
            }
        }

        return ps;
    }

  public:
    int x; int y; int z;
};

class AdventTask18 : public AdventTask<18> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        auto points = getInput(file);
        std::cout << getArea(points) << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        auto points = getInput(file);

        Point3D min = Point3D(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
        Point3D max = Point3D(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), std::numeric_limits<int>::min());

        for(auto& pp : points) {
            auto &p = pp.first;

            min.x = std::min(min.x, p.x);
            min.y = std::min(min.y, p.y);
            min.z = std::min(min.z, p.z);

            max.x = std::max(max.x, p.x);
            max.y = std::max(max.y, p.y);
            max.z = std::max(max.z, p.z);
        }

        std::vector<Point3D> additional;

        for(int x=min.x; x<=max.x; ++x) {
            for(int y=min.y; y<=max.y; ++y) {
                for(int z=min.z; z<=max.z; ++z) {
                    auto p = Point3D(x, y, z);
                    if(points.count(p)) { continue; }

                    if(floodFill(points, p, min, max)) {
                        additional.push_back(p);
                    }
                }
            }
        }

        for(auto& p : additional) {
            points[p] = true;
        }

        std::cout << getArea(points) << std::endl;
    }

    std::map<Point3D, bool> getInput(std::ifstream& file) {
        std::string input;
        std::map<Point3D, bool> points;

        while (!file.eof()) {
            getline(file, input);
            if(input == "") { continue; }
            auto split = StringHelper::split(input, ',');

            auto p = Point3D(std::stoi(split[0]), std::stoi(split[1]), std::stoi(split[2]));
            points[p] = true;
        }

        return points;
    }

    bool floodFill(std::map<Point3D, bool> &points, const Point3D &checkPoint, const Point3D &globalMin, const Point3D &globalMax) {
        std::map<Point3D, bool> coords;
        std::stack<Point3D> c;

        c.push(checkPoint);

        Point3D min = Point3D(std::numeric_limits<int>::max(), std::numeric_limits<int>::max(), std::numeric_limits<int>::max());
        Point3D max = Point3D(std::numeric_limits<int>::min(), std::numeric_limits<int>::min(), std::numeric_limits<int>::min());

        bool isOutside = false;
        while(c.size() > 0) {
            auto cur = c.top(); c.pop();

            coords[cur] = true;

            isOutside = (cur.x < globalMin.x || cur.x > globalMax.x) ||
            (cur.y < globalMin.y || cur.y > globalMax.y) ||
            (cur.z < globalMin.z || cur.z > globalMax.z);

            if(isOutside) {
                break;
            }

            for(auto& n : cur.neighbors()) {
                if(coords.count(n) > 0) {
                    continue;
                }

                if(points.count(n) > 0) {
                    continue;
                }

                c.push(n);
            }
        }

        return !isOutside;
    }

    int64_t getArea(const std::map<Point3D, bool> &points) {
        int64_t sum = 0;
        for(auto& p : points) {
            int uncovered = 0;
            for(const auto& n : p.first.neighbors()) {
                uncovered += (points.count(n) == 0) ? 1 : 0;
            }

            sum += uncovered;
        }

        return sum;
    }
};

#endif /* AdventTask18_h */
