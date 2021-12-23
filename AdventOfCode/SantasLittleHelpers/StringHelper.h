//
//  StringHelper.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 23.12.21.
//

#ifndef StringHelper_h
#define StringHelper_h

#include <vector>
#include <string>

class StringHelper {
  public:
    static std::vector<std::string> split(const std::string& s, char delimiter) {
        std::vector<std::string> v;

        size_t i = 0;
        size_t pos = s.find(delimiter);

        if (pos == std::string::npos) {
            v.push_back(s);
        } else {
            while (pos != std::string::npos) {
                v.push_back(s.substr(i, pos-i));
                i = ++pos;
                pos = s.find(delimiter, pos);

                if (pos == std::string::npos) {
                    v.push_back(s.substr(i, s.length()));
                }
            }
        }

        return v;
    }
};

#endif /* StringHelper_h */
