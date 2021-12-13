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
        auto pos = p.find(',');
        x = std::stoi(p.substr(0, pos));
        y = std::stoi(p.substr(pos+1, p.length()));
    }

    bool operator==(const ManualPoint& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    int x, y;
};

// class for hash function
class ManualPointHash {
public:
    // id is returned as hash function
    size_t operator()(const ManualPoint& t) const
    {
        return t.x << 16 | t.y;
    }
};

#endif /* Manual_h */
