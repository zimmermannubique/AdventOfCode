//
//  VentBoard.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 05.12.21.
//

#ifndef VentBoard_h
#define VentBoard_h

struct VentPoint {
    VentPoint(int x, int y) : x(x), y(y) {};

    VentPoint(std::string &p) {
        std::stringstream ss(p);
        ss >> x; ss.ignore(1); ss >> y;
    }

    bool operator==(const VentPoint& rhs) const {
        return x == rhs.x && y == rhs.y;
    }

    int x, y;
};

struct VentLine {
    VentLine(VentPoint p0, VentPoint p1) : p0(p0), p1(p1) {}

    bool horizontalOrVertical() {
        return p0.x == p1.x || p0.y == p1.y;
    }

    std::vector<VentPoint> coveringPoints() {
        int dx = (p0.x == p1.x) ? 0 : ((p0.x < p1.x) ? 1 : -1);
        int dy = (p0.y == p1.y) ? 0 : ((p0.y < p1.y) ? 1 : -1);

        std::vector<VentPoint> ps = { p0 };

        for(auto p = p0; p != p1;) {
            p.x += dx;
            p.y += dy;
            ps.push_back(p);
        }

        return ps;
    }

    VentPoint p0;
    VentPoint p1;
};

class VentBoard {
  public:
    VentBoard(int n) : n(n) {
        board.resize(n * n, 0);
    }

    void addLine(VentLine &l) {
        for(auto& p : l.coveringPoints()) {
            board[p.x * n + p.y] += 1;
        }
    }

    int64_t result() {
        return std::count_if(board.begin(), board.end(), [](auto&& b){ return b >= 2; });
    }

  private:
    int n;
    std::vector<int64_t> board;
};

#endif /* VentBoard_h */
