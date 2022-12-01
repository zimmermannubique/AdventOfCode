//
//  Range.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 22.12.21.
//

#ifndef Range_h
#define Range_h

struct CubePoint {
    CubePoint(int64_t x, int64_t y, int64_t z) : x(x), y(y), z(z) {}

    bool operator==(const CubePoint& rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }

    bool operator<(const CubePoint& lhs) const {
        return std::tie(x,y,z) < std::tie(lhs.x,lhs.y,lhs.z);
    }

    CubePoint operator+(const CubePoint &a) const { return CubePoint(x + a.x, y + a.y, z + a.z); }
    CubePoint operator-(const CubePoint &a) const { return CubePoint(x - a.x, y - a.y, z - a.z); }

  public:
    int64_t x; int64_t y; int64_t z;
};

struct Range {
    Range(std::pair<int64_t, int64_t> x, std::pair<int64_t, int64_t> y, std::pair<int64_t, int64_t> z, bool on) : xR(x), yR(y), zR(z), on(on) {}

    std::pair<int64_t, int64_t> xR, yR, zR;
    bool on;
    std::vector<Range> intersections;

    int64_t number() {
        int64_t sum = (int64_t(std::abs(xR.second - xR.first) + 1)) * (std::abs(yR.second - yR.first)+ 1) * (std::abs(zR.second - zR.first)+1);

        for(auto& i : intersections) {
            sum -= i.number();
        }

        return sum;
    }

    void add(Range& range) {
        auto inter = intersection(*this, range);
        if(inter.size() > 0) {
            for(auto &i : intersections) {
                i.add(inter[0]);
            }

            intersections.push_back(inter[0]);
        }
    }

    std::vector<Range> intersection(const Range& rangeA, const Range& rangeB) {
        auto aMaxX = std::max(rangeA.xR.first, rangeA.xR.second);
        auto aMaxY = std::max(rangeA.yR.first, rangeA.yR.second);
        auto aMaxZ = std::max(rangeA.zR.first, rangeA.zR.second);

        auto aMinX = std::min(rangeA.xR.first, rangeA.xR.second);
        auto aMinY = std::min(rangeA.yR.first, rangeA.yR.second);
        auto aMinZ = std::min(rangeA.zR.first, rangeA.zR.second);

        auto bMaxX = std::max(rangeB.xR.first, rangeB.xR.second);
        auto bMaxY = std::max(rangeB.yR.first, rangeB.yR.second);
        auto bMaxZ = std::max(rangeB.zR.first, rangeB.zR.second);

        auto bMinX = std::min(rangeB.xR.first, rangeB.xR.second);
        auto bMinY = std::min(rangeB.yR.first, rangeB.yR.second);
        auto bMinZ = std::min(rangeB.zR.first, rangeB.zR.second);

        bool c1 = aMaxX < bMinX || bMaxX < aMinX;
        bool c2 = aMaxY < bMinY || bMaxY < aMinY;
        bool c3 = aMaxZ < bMinZ || bMaxZ < aMinZ;

        if(c1 || c2 || c3) {
            return {};
        } else {
            auto x = std::make_pair(std::max(aMinX, bMinX), std::min(aMaxX, bMaxX));
            auto y = std::make_pair(std::max(aMinY, bMinY), std::min(aMaxY, bMaxY));
            auto z = std::make_pair(std::max(aMinZ, bMinZ), std::min(aMaxZ, bMaxZ));
            return { Range(x, y, z, true) };
        }

        return {};
    }
};

#endif /* Range_h */
