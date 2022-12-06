//
//  AdventTask5.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 05.12.21.
//

#ifndef AdventTask5_h
#define AdventTask5_h

#include <AdventTask.h>

class AdventTask5 : public AdventTask<5> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        auto allStacks = getAllStacks(file);
        
        std::string unneeded;
        int n,from,to;

        while (file >> unneeded >> n >> unneeded >> from >> unneeded >> to) {
            for(int i=0; i<n; ++i) {
                auto top = allStacks[from-1].top(); allStacks[from-1].pop();
                allStacks[to-1].push(top);
            }
        }

        print(allStacks);
    }

    virtual void solveGold(std::ifstream &file) {
        auto allStacks = getAllStacks(file);

        std::string unneeded;
        int n,from,to;

        while (file >> unneeded >> n >> unneeded >> from >> unneeded >> to) {
            std::deque<char> crate;
            for(int i=0; i<n; ++i) {
                auto top = allStacks[from-1].top(); allStacks[from-1].pop();
                crate.push_front(top);
            }

            for(int i=0; i<n; ++i) {
                allStacks[to-1].push(crate[i]);
            }
        }

        print(allStacks);
    }

    std::vector<std::stack<char>> getAllStacks(std::ifstream& file) {
        std::string pack;
        int number = 0;

        std::vector<std::vector<char>> stacks;

        while (!file.eof()) {
            getline(file, pack);

            if(pack == "") {
                break;
            }

            std::vector<char> stack;

            for(int i=0; i<pack.size(); i+=4) {
                if(pack[i] == ' ') {
                    stack.push_back(' ');
                } else if(pack[i] == '[') {
                    stack.push_back(pack[i+1]);
                }
            }

            number = std::max(number, (int)stack.size());
            stacks.push_back(stack);
        }

        std::vector<std::stack<char>> allStacks(number, std::stack<char>());

        for(int i=(int)stacks.size()-2; i>=0; --i) {
            for(int j=0; j<stacks[i].size(); ++j) {
                if(stacks[i][j] != ' ') {
                    allStacks[j].push(stacks[i][j]);
                }
            }
        }

        return allStacks;
    }

    void print(std::vector<std::stack<char>> &stacks) {
        for(auto& s : stacks) {
            if(s.size() > 0) { std::cout << s.top(); }
        }
        
        std::cout << std::endl;
    }
};

#endif /* AdventTask5_h */
