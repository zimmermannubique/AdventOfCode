//
//  AdventTask8.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 08.12.21.
//

#ifndef AdventTask8_h
#define AdventTask8_h

#include <AdventTask.h>

#include <set>

class AdventTask8 : public AdventTask<8> {
  protected:
    virtual void solveSilver(std::ifstream &file) {

        std::vector<std::string> inputs(10);
        std::vector<std::string> tests(4);

        std::string input;

        int64_t sum = 0;

        while (file.good()) {
            for(int i=0; i<inputs.size(); ++i) {
                file >> inputs[i];
            }

            file >> input;

            for(int i=0; i<tests.size(); ++i) {
                file >> tests[i];
            }

            for(int i=0; i<tests.size(); ++i) {
                sum += check(tests[i], inputs) ? 1 : 0;
            }

            file >> std::ws;
        }

        std::cout << "Result: " << sum << std::endl;
    }

    virtual bool check(std::string& i, std::vector<std::string> &inputs) {
        return i.size() == 2 || i.size() == 3 || i.size() == 4 || i.size() == 7;
    }

    virtual void solveGold(std::ifstream &file) {

        std::vector<std::string> inputs(10);
        std::vector<std::string> tests(4);

        std::string input;

        int64_t sumTot = 0;

        while (file.good()) {
            for(int i=0; i<inputs.size(); ++i) {
                file >> inputs[i];
                std::sort(inputs[i].begin(), inputs[i].end());
            }

            file >> input;

            for(int i=0; i<tests.size(); ++i) {
                file >> tests[i];
                std::sort(tests[i].begin(), tests[i].end());
            }

            int64_t sum = 0;
            for(int i=0; i<tests.size(); ++i) {
                sum = 10 * sum + check2(tests[i], inputs);
            }

            file >> std::ws;

            sumTot += sum;
        }

        std::cout << "Result: " << sumTot << std::endl;
    }

    virtual int check2(std::string& j, std::vector<std::string> &inputs) {
        std::map<std::string, int> stringMap;

        // LET THE UGLYNESS BEGIN... ;-)
        std::vector<std::string> fives;
        std::vector<std::string> sixes;

        std::string four;
        std::string nine;
        std::string eight;
        std::string three;

        for(auto& i : inputs) {
            if(i.size() == 7) {
                stringMap[i] = 8;
                eight = i;
            }

            if(i.size() == 2) {
                stringMap[i] = 1;
            }

            if(i.size() == 3) {
                stringMap[i] = 7;
            }

            if(i.size() == 4) {
                stringMap[i] = 4;
                four = i;
            }

            if(i.size() == 5) {
                fives.push_back(i);
            }

            if(i.size() == 6) {
                sixes.push_back(i);
            }
        }

        std::string two = "";
        for(int i=0; i<fives.size(); ++i) {
            bool hadEmpty = false;
            for(auto ii : fives[i]) {
                int sum = 0;

                for(int j=0; j<fives.size(); ++j) {
                    if(j!=i) {
                        sum += std::find(fives[j].begin(), fives[j].end(), ii) != fives[j].end() ? 1 : 0;
                    }
                }

                if(sum == 0) {
                    hadEmpty = true;
                }
            }

            if(!hadEmpty) {
                stringMap[fives[i]] = 3;
                three = fives[i];

                nine = setSet({ fives[i], four });
                stringMap[nine] = 9;
            }
        }

        std::string five = "";

        for(int i=0; i<fives.size(); ++i) {
            if(stringMap.count(fives[i]) && stringMap[fives[i]] == 3) { continue; }

            if(setSet({ fives[i], nine }) == nine) {
                five = fives[i];
                stringMap[five] = 5;
            } else {
                two = fives[i];
                stringMap[two] = 2;
            }
        }

        for(int i=0; i<sixes.size(); ++i) {
            if(sixes[i] == nine) {
                continue;
            }

            if(setSet({ five, sixes[i] }) == eight) {
                stringMap[sixes[i]] = 0;
            } else {
                stringMap[sixes[i]] = 6;
            }
        }

        return stringMap[j];
    }

    std::string setSet(const std::vector<std::string> &ss) {
        std::string result;
        for(auto i = 'a'; i<='g'; ++i) {
            for(auto& s : ss) {
                if(std::find(s.begin(),s.end(), i) != s.end()) {
                    result.push_back(i);
                    break;
                }
            }
        }

        std::sort(result.begin(), result.end());
        return result;
    }
};

#endif /* AdventTask8_h */
