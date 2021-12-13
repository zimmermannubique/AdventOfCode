//
//  Manual.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 13.12.21.
//

#ifndef Manual_h
#define Manual_h

struct ManualPoint {
    ManualPoint(int x, int y) : x(x), y(y) {};

    ManualPoint(std::string &p) {
        std::stringstream ss(p);
        ss >> x; ss.ignore(1); ss >> y;
    }

    bool operator==(const ManualPoint& rhs) {
        return x == rhs.x && y == rhs.y;
    }

    bool operator<(const ManualPoint& rhs) const
    {
        return x < rhs.x || (x == rhs.x && y < rhs.y);
    }

    int x, y;
};

#endif /* Manual_h */
