//
//  AdventTask14.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 14.12.21.
//

#ifndef AdventTask14_h
#define AdventTask14_h

#include "AdventTask.h"

#include <list>

class AdventTask14 : public AdventTask<14> {
  protected:
    std::map<std::string, std::string> insertions;

    virtual void solveSilver(std::ifstream &file) {
        std::list<char> list;
        std::string templateString;

        file >> templateString;

        for(auto& i : templateString) {
            list.push_back(i);
        }

        fillInsertions(file);

        for(int i=0; i<10; ++i) {
            insert(list);
        }

        std::vector<int64_t> counts(26, 0);
        for (auto it=list.begin(); it != list.end(); ++it) {
            counts[*it - 65]++;
        }

        showResult(counts);
    }

    virtual void solveGold(std::ifstream &file) {
        std::map<std::string, int64_t> pairs;
        std::string templateString;

        file >> templateString;

        for(int i=0; i<templateString.size()-1; ++i) {
            pairs[{templateString[i] , templateString[i+1]}]++;
        }

        fillInsertions(file);

        for(int i=0; i<40; ++i) {
            pairs = insert(pairs);
        }

        std::vector<int64_t> counts(26, 0);
        for(auto& p : pairs) {
            counts[char(p.first[1]) - 65] += p.second;
        }

        showResult(counts);
    }

    void insert(std::list<char> &list) {
        for (auto it=list.begin(); it != list.end();)
        {
            auto a = *it;

            ++it;
            if(it == list.end()) {
                break;
            }

            auto b = *it;

            std::string key = {a , b};
            std::string ins = insertions[key];

            if(ins.size() > 0) {
                list.insert(it, ins[0]);
            }
        }
    }

    std::map<std::string, int64_t> insert(const std::map<std::string, int64_t> &pairs) {
        std::map<std::string, int64_t> newPairs;

        for(auto& p : pairs) {
            std::string ins = insertions[p.first];

            if(ins.size() > 0) {
                newPairs[p.first[0] + ins] += p.second;
                newPairs[ins + p.first[1]] += p.second;
            }
        }

        return newPairs;
    }

    void showResult(const std::vector<int64_t> &counts) {
        int64_t min = std::numeric_limits<int64_t>::max();
        int64_t max = 0;
        for(auto& i : counts) {
            if(i > 0) {
                min = std::min(i, min);
                max = std::max(i, max);
            }
        }

        std::cout << "Result: " << max-min;
    }

    void fillInsertions(std::ifstream &file) {
        insertions.clear();

        while(file.good()) {
            std::string a, b, c;
            file >> a >> b >> c;

            insertions[a] = c;
        }
    }
};

#endif /* AdventTask14_h */
