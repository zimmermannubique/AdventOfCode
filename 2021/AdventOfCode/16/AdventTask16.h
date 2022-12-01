//
//  AdventTask16.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 16.12.21.
//

#ifndef AdventTask16_h
#define AdventTask16_h

class AdventTask16 : public AdventTask<16> {
  protected:

    virtual void solveSilver(std::ifstream &file) {
        solve(file, true);
    }

    virtual void solveGold(std::ifstream &file) {
        solve(file, false);
    }

    void solve(std::ifstream &file, bool silver) {
        std::string input;
        file >> input;

        std::cout << "Result: " << parse(toBinary(input), 0, silver).first << std::endl;
    }

    std::string toBinary(const std::string &numbers) {
        std::unordered_map<char, std::string> binary;
        binary['0'] = "0000"; binary['1'] = "0001"; binary['2'] = "0010"; binary['3'] = "0011";
        binary['4'] = "0100"; binary['5'] = "0101"; binary['6'] = "0110"; binary['7'] = "0111";
        binary['8'] = "1000"; binary['9'] = "1001"; binary['A'] = "1010"; binary['B'] = "1011";
        binary['C'] = "1100"; binary['D'] = "1101"; binary['E'] = "1110"; binary['F'] = "1111";

        std::string newNumbers;
        newNumbers.reserve(4 * numbers.size());

        for(auto& n : numbers) {
            for(auto& b : binary[n]) {
                newNumbers.push_back(b);
            }
        }

        return newNumbers;
    }

    std::pair<int64_t, int64_t> parse(const std::string &input, int start, bool silver) {
        auto v = numberFromBits(input, start, 3);
        auto t = numberFromBits(input, start+3, 3);
        int index = start + 6;

        if(t == 4) {
            auto parsed = parseNumbers(input, index);
            // return the version in silver, return the number in gold
            return std::make_pair(silver ? v : parsed.first, parsed.second + index - start);
        } else {
            auto lengthId = std::bitset<64>(input.substr(index,1)).to_ullong();
            index++;

            std::vector<int64_t> sols;

            if(lengthId == 0) {
                // get how many bits
                auto l = numberFromBits(input, index, 15);
                index += 15;

                if(silver) {
                    // build the sum
                    t = 0;
                    sols.push_back(v);
                }

                int plength = 0;
                while(plength < l) {
                    auto p = parse(input, index, silver);
                    sols.push_back(p.first);
                    plength += p.second;
                    index += p.second;
                }
            } else {
                // get how many numbers
                auto l = numberFromBits(input, index, 11);
                index += 11;

                if(silver) {
                    // build the sum and add own version
                    t = 0;
                    sols.push_back(v);
                }

                for(int i=0; i<l; ++i) {
                    auto p = parse(input, index, silver);
                    sols.push_back(p.first);
                    index+= p.second;
                }
            }

            return std::make_pair(calculate(sols, t), index-start);
        }
    }

    int64_t calculate(const std::vector<int64_t> &sols, int64_t t) {
        switch(t) {
            case 1: { return std::accumulate(sols.begin(), sols.end(), int64_t(1), std::multiplies<int64_t>()); }
            case 2: { return *std::min_element(sols.begin(),sols.end()); }
            case 3: { return *std::max_element(sols.begin(),sols.end()); }
            case 5: { return sols[0] > sols[1] ? 1 : 0; }
            case 6: { return sols[0] < sols[1] ? 1 : 0; }
            case 7: { return sols[0] == sols[1] ? 1 : 0; }

            default: {
                return std::accumulate(sols.begin(), sols.end(), int64_t(0));
            }
        }
    }

    int64_t numberFromBits(const std::string& input, int start, int bits) {
        return std::bitset<64>(input.substr(start,bits)).to_ullong();
    }

    std::pair<int64_t, int64_t> parseNumbers(const std::string& input, int start) {
        std::string result;

        int64_t count = 0;
        for(int i=start; i<input.size(); i+=5) {
            count++;
            for(int j=0; j<4; ++j) {
                result.push_back(input[i+1 + j]);
            }

            if(input[i] == '0') {
                break;
            }
        }

        return std::make_pair(std::bitset<128>(result).to_ullong(), count * 5);
    }
};

#endif /* AdventTask16_h */
