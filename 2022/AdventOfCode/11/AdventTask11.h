//
//  AdventTask11.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 11.12.21.
//

#ifndef AdventTask11_h
#define AdventTask11_h

enum Operator {
    plus, multiply
};

struct Operation {
    Operation() {};
    Operation(std::string &input) {
        auto oper = StringHelper::split(input, ' ');

        leftOld = oper[1] == "old";
        if(!leftOld) { leftConst = std::stoi(oper[1]); }

        rightOld = oper[3] == "old";
        if(!rightOld) { rightConst = std::stoi(oper[3]); }

        switch(oper[2][0]) {
            case '+': { o = Operator::plus; break; }
            case '*': { o = Operator::multiply; break; }
        }
    }

    int64_t applyOperation(int64_t i) {
        int64_t l = leftOld ? i : leftConst;
        int64_t r = rightOld ? i : rightConst;

        switch(o) {
            case Operator::multiply: { return l * r; }
            case Operator::plus: { return l + r; }
        }
    }

    bool leftOld;
    bool rightOld;
    int leftConst;
    int rightConst;
    Operator o;
};

class Monkey {
  public:
    std::vector<int64_t> items;
    int divisible;
    Operation operation;
    int trueMonkey;
    int falseMonkey;

    int64_t inspections = 0;

    void doRound(std::vector<Monkey> &monkeys, int64_t globalModulo, bool silver) {
        for(auto& i : items) {
            auto level = operation.applyOperation(i);

            if(silver) { level = level / 3; }

            bool d = level % divisible == 0;

            monkeys[d ? trueMonkey : falseMonkey].addItem(level, globalModulo, silver);
            inspections++;
        }

        items.clear();
    }

    void addItem(int64_t i, int64_t globalModulo, bool silver) {
        if(!silver) {
            i = i % globalModulo;
        }

        items.push_back(i);
    }
};

#include <AdventTask.h>

class AdventTask11 : public AdventTask<11> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        solve(file, 20, true);
    }

    virtual void solveGold(std::ifstream &file) {
        solve(file, 10000, false);
    }

    void solve(std::ifstream &file, int n, bool silver) {
        std::string s;
        std::vector<Monkey> monkeys;

        while (!file.eof()) {
            Monkey m;

            // Monkey: i
            getline(file, s);

            // Items
            getline(file, s);

            auto itemsSplit = StringHelper::split(s, ':');
            auto items = StringHelper::split(itemsSplit.back(), ',');
            for(auto& l : items) {
                m.items.push_back(std::stoi(l));
            }

            // Operation
            getline(file, s);
            
            auto split = StringHelper::split(s, '=');
            m.operation = Operation(split.back());

            // Divisible
            getline(file, s);

            auto div = StringHelper::split(s, ' ');
            m.divisible = std::stoi(div.back());

            // True: Monkey
            getline(file, s);

            auto trueM = StringHelper::split(s, ' ');
            m.trueMonkey = std::stoi(trueM.back());

            // False: Monkey
            getline(file, s);

            auto falseM = StringHelper::split(s, ' ');
            m.falseMonkey = std::stoi(falseM.back());

            getline(file, s);

            monkeys.push_back(m);
        }

        int globalModulo = 1;
        for(auto& m : monkeys) {
            globalModulo *= m.divisible;
        }

        for(auto round=0; round<n; ++round) {
            for(auto& m : monkeys) {
                m.doRound(monkeys, globalModulo, silver);
            }
        }

        std::sort(monkeys.begin(), monkeys.end(), [](auto&& a, auto&& b) {
            return a.inspections > b.inspections;
        });

        std::cout << monkeys[0].inspections * monkeys[1].inspections << std::endl;
    }

    void printMonkeys(std::vector<Monkey>& monkeys) {
        int index = 0;
        for(auto& m : monkeys) {
            std::cout << "Monkey " << index << ": ";
            for(auto& i : m.items) {
                std::cout << i << " ";
            }
            std::cout << std::endl;
            index++;
        }

        std::cout << std::endl;

        index = 0;
        for(auto& m : monkeys) {
            std::cout << "Monkey " << index++ << ": " << m.inspections;
            std::cout << std::endl;
        }

        std::cout << std::endl;
    }
};

#endif /* AdventTask11_h */
