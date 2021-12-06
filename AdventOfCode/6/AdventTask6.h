//
//  AdventTask6.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 06.12.21.
//

#ifndef AdventTask6_h
#define AdventTask6_h

class AdventTask6 : public AdventTask<6> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        auto numbers = getNumbers(file);

        for(int i=0; i<80; ++i) {
            int addNew = 0;
            for(auto& l : numbers) {
                if(l == 0) {
                    addNew++;
                    l = 6;
                } else {
                    l--;
                }
            }

            for(int j=0; j<addNew; ++j) {
                numbers.push_back(8);
            }
        }

        std::cout << "Result: " << numbers.size() << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        auto numbers = getNumbers(file);

        std::vector<int64_t> lanterns(9, 0);

        for(auto& n : numbers) {
            lanterns[n]++;
        }

        for(int i=0; i<256; ++i) {
            std::rotate(lanterns.begin(), lanterns.begin() + 1, lanterns.end());
            lanterns[6] += lanterns[8];
        }

        std::cout << "Result: " << std::accumulate(lanterns.begin(), lanterns.end(), int64_t(0)) << std::endl;
    }

    void solveGoldAlternative(const std::vector<int> &numbers) {
        std::map<int, int64_t> lanterns;

        int days = 256;
        for(auto& n : numbers) {
            auto [iterator, inserted] = lanterns.try_emplace(days - n, 1);
            if (!inserted) { iterator->second = iterator->second + 1; }
        }

        int64_t sum = 0;
        for(int i=days; i>=0; --i) {
            auto search = lanterns.find(i);
            if(search != lanterns.end()) {
                auto n = search->second;
                sum += n;

                for(int k=i; k>0; k-=7) {
                    int next = k-7-2;
                    if(next > 0) {
                        auto [iterator, inserted] = lanterns.try_emplace(next, n);
                        if (!inserted) { iterator->second = iterator->second + n; }
                    } else {
                        // created but will not reproduce, just add
                        sum += n;
                    }
                }
            }
        }

        std::cout << "Result: " << sum << std::endl;
    }

  private:
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

#endif /* AdventTask6_h */
