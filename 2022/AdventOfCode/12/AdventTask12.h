//
//  AdventTask12.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 12.12.21.
//

#ifndef AdventTask12_h
#define AdventTask12_h

#include <AdventTask.h>

class IntGraph {
  public:
    void addEdge(const int &u, const int &v, int weight) {
        adjacent[u].push_back(std::make_pair(v, weight));
    }

    int shortestPath(int src, int dest)
    {
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>> , std::greater<std::pair<int, int>>> queue;

        std::vector<int> distances(adjacent.size(), std::numeric_limits<int>::max());

        queue.push(std::make_pair(0, src));
        distances[src] = 0;

        while (!queue.empty())
        {
            int u = queue.top().second;

            if(u == dest) {
                break;
            }

            queue.pop();

            for (auto i = adjacent[u].begin(); i != adjacent[u].end(); ++i)
            {
                int v = (*i).first;
                int weight = (*i).second;

                if(distances[u] + weight < distances[v])
                {
                    distances[v] = distances[u] + weight;
                    queue.push(std::make_pair(distances[v], v));
                }
            }
        }

        std::cout << "Result: " << distances[dest] << std::endl;
        return distances[dest];
    }

  private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjacent;
};


class AdventTask12 : public AdventTask<12> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::string g;
        std::vector<std::string> grid;

        while (file >> g) {
            grid.push_back(g);
        }

        IntGraph graph = buildGraph(grid);
    }

    virtual void solveGold(std::ifstream &file) {
    }

    IntGraph buildGraph(const std::vector<std::string> &grid) {
        IntGraph g;

        int m = (int)grid[0].size();
        int n = (int)grid.size();

        std::pair<int, int> start;
        std::pair<int, int> end;

        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {
                char current;
                if(grid[i][j] == 'S') {
                    current = 'a';
                    start = std::make_pair(i, j);
                } else if(grid[i][j] == 'E') {
                    current = 'z';
                    end = std::make_pair(i, j);
                } else {
                    current = grid[i][j];
                }

                auto neigh = neighbors(i, j, n, m);

                for(auto& nb : neigh) {
                    auto des = grid[nb.first][nb.second];

                    if(des == 'S') {
                        des = 'a';
                    } else if(des == 'E') {
                        des = 'z';
                    }

                    if((int)des - (int)current <= 1) {
                        g.addEdge(i*m + j, nb.first*m + nb.second, 1);
                    }
                }
            }
        }

        std::cout << "Shortest from S" << std::endl;

        int min = g.shortestPath(start.first * m + start.second, end.first * m + end.second);

        for(int i=0; i<n; ++i) {
            for(int j=0; j<m; ++j) {

                if(grid[i][j] == 'S' || grid[i][j] == 'a') {
                    int ijMin = g.shortestPath(i * m + j, end.first * m + end.second);

                    if(ijMin < min) {
                        min = ijMin;
                    }
                }
            }
        }

        std::cout << "Shortest from any a: " << min << std::endl;

        return g;
    }

    std::vector<std::pair<int, int>> neighbors(int i, int j, int n, int m) {
        std::vector<std::pair<int, int>> pairs;

        if(i > 0) { pairs.emplace_back(i-1, j); }
        if(i < n-1) { pairs.emplace_back(i+1, j); }
        if(j > 0) { pairs.emplace_back(i, j-1); }
        if(j < m-1) { pairs.emplace_back(i, j+1); }

        return pairs;
    }
};

#endif /* AdventTask12_h */
