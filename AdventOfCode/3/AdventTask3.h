//
//  AdventTask3.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 03.12.21.
//

#include "AdventTask.h"

class AdventTask3 : public AdventTask<3> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::vector<int64_t> numbers;
        std::string input;

        while (file >> input) {
            if(input.size() > numbers.size()) {
                numbers.resize(input.size(), 0);
            }

            for(size_t i=0; i<input.size(); ++i) {
                numbers[i] += input[i] == '1' ? 1 : -1;
            }
        }

        std::string gamma;
        std::string eps;
        for(auto& n : numbers) {
            gamma.push_back(n > 0 ? '1' : '0');
            eps.push_back(n > 0 ? '0' : '1');
        }

        auto gD = std::bitset<64>(gamma).to_ullong();
        auto eD = std::bitset<64>(eps).to_ullong();

        std::cout << "Result: " << gD << "*" << eD << " = " << gD*eD << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        std::vector<int64_t> numbersA, numbersB;
        std::vector<std::string> inputsA, inputsB;
        std::string input;

        while (file >> input) {
            if(input.size() > numbersA.size()) {
                numbersA.resize(input.size(), 0);
                numbersB.resize(input.size(), 0);
            }

            inputsA.push_back(input);
            inputsB.push_back(input);
        }

        auto gD = std::bitset<64>(computeLastElement(inputsA, numbersA, [](auto&& n) { return (n>=0 ? '0' : '1'); })).to_ullong();
        auto sD = std::bitset<64>(computeLastElement(inputsB, numbersB, [](auto&& n) { return (n>=0 ? '1' : '0'); })).to_ullong();

        std::cout << "Result: " << gD << "*" << sD << " = " << gD*sD << std::endl;
    }

  private:
    void recalculate(const std::vector<std::string> &inputs, std::vector<int64_t> &numbers) {
        std::fill(numbers.begin(), numbers.end(), 0);

        for(const auto& input : inputs) {
            for(size_t i=0; i<input.size(); ++i) {
                numbers[i] += input[i] == '1' ? 1 : -1;
            }
        }
    }

    std::string computeLastElement(std::vector<std::string> &inputs, std::vector<int64_t> &numbers, std::function<char (int64_t)> evaluator) {
        int index = 0;
        while(inputs.size() > 1) {
            recalculate(inputs, numbers);
            inputs.erase(std::remove_if(inputs.begin(), inputs.end(), [&](auto&& x) { return x[index] == evaluator(numbers[index]); }), inputs.end());
            ++index;
        }

        return inputs[0];
    }
};
