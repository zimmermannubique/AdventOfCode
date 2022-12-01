//
//  Scanner.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 19.12.21.
//

#ifndef Scanner_h
#define Scanner_h

struct Mode {
    Mode(const std::vector<int> &indices, const std::vector<int> &multiplier)
    : indices(indices), multiplier(multiplier) {};

    std::vector<int> indices;
    std::vector<int> multiplier;
};

struct Point3D {
    Point3D(int x, int y, int z) : x(x), y(y), z(z) {
        p.push_back(x); p.push_back(y); p.push_back(z);
    }

    Point3D get(Mode& mode) const {
        return Point3D(p[mode.indices[0]] * mode.multiplier[0],
                       p[mode.indices[1]] * mode.multiplier[1],
                       p[mode.indices[2]] * mode.multiplier[2]);
    }

    bool operator==(const Point3D& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator<(const Point3D& lhs) const {
        return std::tie(x,y,z) < std::tie(lhs.x,lhs.y,lhs.z);
    }

    int manhattan(const Point3D& lhs) {
        return std::abs(x - lhs.x) + std::abs(y - lhs.y) + std::abs(z - lhs.z);
    }

    Point3D operator+(const Point3D &a) const { return Point3D(x + a.x, y + a.y, z + a.z); }
    Point3D operator-(const Point3D &a) const { return Point3D(x - a.x, y - a.y, z - a.z); }

  public:
    // crazy double memory comsumption!
    std::vector<int> p;
    int x; int y; int z;
};

class Scanner {
  public:
    std::vector<Point3D> points = {};
    std::vector<Point3D> mergedScanners = { Point3D(0,0,0) };

    void add(const Scanner& scanner, Mode &mode, const Point3D& translation) {
        for(const auto& p : scanner.points) {
            bool has = false;
            auto pM = p.get(mode) - translation;

            for(const auto& p0 : points) {
                if(p0 == pM) {
                    has = true;
                    break;
                }
            }

            if(!has) {
                points.push_back(pM);
            }
        }

        for(auto& ms : scanner.mergedScanners) {
            mergedScanners.push_back(translation - ms);
        }
    }

    int largestManhattanDistance() {
        int max = 0;
        for(auto& m : mergedScanners) {
            for(auto& n : mergedScanners) {
                max = std::max(max, m.manhattan(n));
            }
        }

        return max;
    }
};

#endif /* Scanner_h */
