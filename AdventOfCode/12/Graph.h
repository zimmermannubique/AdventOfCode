//
//  Graph.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 12.12.21.
//

#ifndef Graph_h
#define Graph_h

class Graph {
  public:
    void addEdge(const std::string &u, const std::string &v) {
        adjacent[u].push_back(v);
        adjacent[v].push_back(u);

        if(isLower.count(u) == 0) {
            isLower[u] = isLowercase(u);
        }

        if(isLower.count(v) == 0) {
            isLower[v] = isLowercase(v);
        }
    }

    void paths(const std::string &start, const std::string &end) {
        int p = pathsRecursive(start, end, {}, false);
        std::cout << "Result: " << p << std::endl;
    }

    void pathsWithTwiceRule(const std::string &start, const std::string &end) {
        int p = pathsRecursive(start, end, {}, true);
        std::cout << "Result: " << p << std::endl;
    }

  private:
    int pathsRecursive(const std::string &start, const std::string &end, std::unordered_map<std::string, int> visited, bool allowTwice) {

        if(isLower[start]) {
            visited[start] = visited[start] + 1;
        }

        if(allowTwice && (start == "start" || start == "end")) {
            visited[start] = 2;
        }

        if(start == end) {
            return 1;
        } else {
            int sum = 0;

            for(auto& i : adjacent[start]) {
                auto vi = visited[i];
                if(vi == 0) {
                    sum += pathsRecursive(i, end, visited, allowTwice);
                } else if(allowTwice && vi < 2) {
                    sum += pathsRecursive(i, end, visited, false);
                }
            }

            return sum;
        }
    }

    bool isLowercase(const std::string& str) {
        return std::string::npos == str.find_first_not_of(allLower);
    }

    std::unordered_map<std::string, std::vector<std::string>> adjacent;
    std::unordered_map<std::string, bool> isLower;

    const std::string allLower = "abcdefghijklmnopqrstuvwxyz";
};

#endif /* Graph_h */
