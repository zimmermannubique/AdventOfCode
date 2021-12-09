//
//  AdventTask7.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 07.12.21.
//

#ifndef AdventTask7_h
#define AdventTask7_h

#include <AdventTask.h>

class AdventTask7 : public AdventTask<7> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        solve(getNumbers(file), [](auto&& i) { return (int64_t)i; });
    }

    virtual void solveGold(std::ifstream &file) {
        auto numbers = getNumbers(file);

        int max = *std::max_element(numbers.begin(), numbers.end());

        std::vector<int64_t> costMap = { 0 };
        for(int i=1; i<=max; ++i) {
            costMap[i] = costMap[i-1] + i;
        }

        solve(numbers, [&](auto&& i) { return costMap[i]; });
    }

  private:
    void solve(const std::vector<int> &numbers, const std::function<int64_t (int)> &costFunction) {
        int max = *std::max_element(numbers.begin(), numbers.end());

        int64_t minFuel = std::numeric_limits<int64_t>::max();

        for(int i=0; i<=max; ++i) {
            int64_t sumFuel = std::accumulate(numbers.begin(), numbers.end(), 0, [&](int s, int n) { return s + costFunction(abs(n - i)); });
            minFuel = std::min(minFuel, sumFuel);
        }

        std::cout << "Result: " << minFuel;
    }

    std::vector<int> getNumbers(std::ifstream &file) {
        std::vector<int> numbers;
        std::string commaNumbers;
        file >> commaNumbers;

        std::stringstream ss(commaNumbers);
        int i;
        while (ss >> i) {
            numbers.push_back(i);
            ss.ignore(1);
        }

        return numbers;
    }
};


#endif /* AdventTask7_h */
