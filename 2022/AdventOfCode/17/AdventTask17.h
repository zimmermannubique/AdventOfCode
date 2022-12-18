//
//  AdventTask17.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 17.12.21.
//

#ifndef AdventTask17_h
#define AdventTask17_h

#include "AdventTask.h"

class Coord {
  public:
    Coord(int x, int y) : x(x), y(y) {}

    bool operator<(const Coord& rhs) const {
        return std::tie(x, y) < std::tie(rhs.x, rhs.y);
    }

    int x;
    int y;
};

enum TileType : int {
    lineHorizontal = 0,
    cross,
    reverseL,
    lineVertical,
    block
};

class Tile {
  public:
    static std::vector<Coord> coords(TileType &t) {
        std::vector<Coord> c;

        switch (t) {
            case lineHorizontal: {
                c.push_back(Coord(2,0));
                c.push_back(Coord(3,0));
                c.push_back(Coord(4,0));
                c.push_back(Coord(5,0));
                break;
            }

            case cross: {
                c.push_back(Coord(3,0));
                c.push_back(Coord(3,2));
                c.push_back(Coord(3,1));
                c.push_back(Coord(2,1));
                c.push_back(Coord(4,1));
                break;
            }

            case reverseL: {
                c.push_back(Coord(4,0));
                c.push_back(Coord(4,1));
                c.push_back(Coord(4,2));
                c.push_back(Coord(3,2));
                c.push_back(Coord(2,2));
                break;
            }

            case lineVertical: {
                c.push_back(Coord(2,0));
                c.push_back(Coord(2,1));
                c.push_back(Coord(2,2));
                c.push_back(Coord(2,3));
                break;
            }

            case block: {
                c.push_back(Coord(2,0));
                c.push_back(Coord(3,0));
                c.push_back(Coord(2,1));
                c.push_back(Coord(3,1));
                break;
            }

            default:
                break;
        }

        return c;
    }

    static void move(std::deque<std::string> &field, std::vector<Coord>& coords, bool left) {
        for(auto& i : coords) {
            auto x = i.x + (left ? -1 : 1);
            if(x < 0 || x > 7) {
                return;
            }

            if(field[i.y][x] != '.') {
                return;
            }
        }

        for(auto &c : coords) {
            c.x += (left ? -1 : 1);
        }
    }

    static bool moveDownIfPossible(std::deque<std::string> &field, std::vector<Coord>& coords) {
        for(auto& i : coords) {
            auto y = i.y + 1;

            if(y == field.size()) {
                return false;
            }

            if(field[y][i.x] != '.') {
                return false;
            }
        }

        for(auto &c : coords) {
            c.y += 1;
        }

        return true;
    }

    static int newLines(TileType &t) {
        switch (t) {
            case lineHorizontal: { return 4; }
            case cross: { return  6; }
            case reverseL: { return 6; }
            case lineVertical: { return 7; }
            case block: { return 5; }
        }
    }

    static void print(std::deque<std::string> &field, std::vector<Coord>& coords) {
        return;
        for(int i=0; i<field.size(); ++i) {
            for(int j=0; j<field[i].size(); ++j) {
                bool has = false;
                for(auto& coord : coords) {
                    if(coord.x == j && coord.y == i) {
                        has = true;
                    }
                }

                std::cout << (has ? '@' : field[i][j]);
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

    static int removeLines(std::deque<std::string> &field) {
        std::map<std::pair<int,int>, bool> coords;

        std::stack<Coord> c;
        for(auto i=0; i<field[0].size(); ++i) {
            if(field[0][i] == '.') {
                c.push(Coord(i, 0));
            }
        }

        if(c.size() == 0) {
            return 0;
        }

        int maxY = 0;

        while(c.size() > 0) {
            Coord cur = c.top(); c.pop();

            coords[std::make_pair(cur.x, cur.y)] = true;
            maxY = std::max(cur.y, maxY);

            for(int i=-1; i<=1; ++i) {
                for(int j=0; j<=1; ++j) {
                    if(abs(i) + abs(j) != 1) {
                        continue;
                    }

                    auto x = cur.x + i;
                    auto y = cur.y + j;

                    if(x < 0 || x >= field[0].size()) {
                        continue;
                    }

                    if(y < 0 || y >= field.size()) {
                        continue;
                    }

                    if(field[y][x] != '.') {
                        continue;
                    }

                    if(coords.count(std::make_pair(x, y)) > 0) {
                        continue;
                    }

                    c.push(Coord(x,y));
                }
            }
        }

        int remove = (int)field.size() - maxY - 1;
        for(int i=0; i<remove; ++i) {
            field.pop_back();
        }

        return remove;
    }
};

class AdventTask17 : public AdventTask<17> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        solve(file, 2022);
    }

    virtual void solveGold(std::ifstream &file) {
        solve(file, 1000000000000);
    }

    void solve(std::ifstream &file, int64_t numberOfTiles) {
        std::string input;
        file >> input;

        std::deque<std::string> field;
        std::string empty = ".......";

        std::map<std::string, std::pair<int64_t, int64_t>> cycle;

        bool tileIsDown = true;
        TileType currentType = TileType::lineHorizontal;
        std::vector<Coord> currentCoords;

        int64_t tilesDown = 0;
        int64_t removed = 0;

        int index = 0;

        while(true) {
            auto a = input[index];
            index = (index + 1) % input.size();

            if(tileIsDown) {
                std::stringstream ss;
                ss << index << " - ";
                ss << currentType << " - ";
                for(auto& f : field) {
                    ss << f << " - ";
                }

                auto s = ss.str();

                if(cycle.count(s)) {
                    auto i = cycle[s];

                    auto diff = tilesDown - i.first;
                    auto removeDiff = removed - i.second;

                    while(tilesDown + diff < numberOfTiles) {
                        tilesDown += diff;
                        removed += removeDiff;
                    }
                } else {
                    cycle[s] = std::make_pair(tilesDown, removed);
                }
            }

            if(tileIsDown) {
                int n = Tile::newLines(currentType);
                for(int i=0; i<n; ++i) {
                    field.push_front(empty);
                }

                currentCoords = Tile::coords(currentType);
                Tile::print(field, currentCoords);
            }

            Tile::move(field, currentCoords, a == '<');

            if(Tile::moveDownIfPossible(field, currentCoords)) {
                tileIsDown = false;
            } else {
                tileIsDown = true;
                tilesDown++;

                currentType = (TileType)((currentType + 1) % 5);

                for(auto& c : currentCoords) {
                    field[c.y][c.x] = '#';
                }

                while(field.front() == empty) {
                    field.pop_front();
                }

                currentCoords.clear();

                Tile::print(field, currentCoords);
                removed += Tile::removeLines(field);
                Tile::print(field, currentCoords);
            }

            if(tilesDown == numberOfTiles) {
                Tile::print(field, currentCoords);
                std::cout << field.size() + removed << std::endl;
                break;
            }
        }
    }
};

#endif /* AdventTask17_h */
