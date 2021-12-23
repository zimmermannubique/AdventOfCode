//
//  AdventTask17.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 17.12.21.
//

#ifndef AdventTask17_h
#define AdventTask17_h

class AdventTask17 : public AdventTask<17> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::pair<int, int> x, y;
        input(file, x, y);

        bool found = false;
        int max = 0;
        for(int j=1000; j>=0; --j) {
            if(found) { break; }

            for(int i=x.second; i>=0; --i) {
                int height;
                bool success = simulate(i, j, x, y, height);
                if(success) {
                    max = height;
                    found = true;
                }
            }
        }

        std::cout << "Result: " << max;
    }

    virtual void solveGold(std::ifstream &file) {
        std::pair<int, int> x, y;
        input(file, x, y);

        int res = 0;
        int height;
        for(int i=x.second; i>=0; --i) {
            for(int j=y.first - 10; j<10000; ++j) {
                res += simulate(i, j, x, y, height) ? 1 : 0;
            }
        }

        std::cout << "Result: " << res;
    }

    int simulate(int startX, int startY, std::pair<int, int> &x, std::pair<int, int> &y, int& height) {
        int posX = 0;
        int posY = 0;
        int velX = startX;
        int velY = startY;

        height = 0;

        while(posX < x.second && posY > y.first) {
            posX += velX;
            posY += velY;
            height = std::max(posY, height);

            if(posX >= x.first && posX <= x.second && posY <= y.second && posY >= y.first) {
                return true;
            }

            if(velX > 0) {
                velX--;
            } else if(velX < 0) {
                velX++;
            }

            velY--;
        }

        return false;
    }


    std::pair<int, int> split(const std::string& s) {
        auto pos = s.find("..");
        return std::make_pair(std::stoi(s.substr(0, pos)), std::stoi(s.substr(pos+2, s.length())));
    }

    void input(std::ifstream &file, std::pair<int, int> &x, std::pair<int, int> &y) {
        std::string input;
        while(file >> input) {
            if(input.starts_with("x")) {
                input = input.substr(2, input.size()-3);
                x = split(input);
            }

            if(input.starts_with("y")) {
                input = input.substr(2, input.size()-2);
                y = split(input);
            }
        }
    }
};

#endif /* AdventTask17_h */
