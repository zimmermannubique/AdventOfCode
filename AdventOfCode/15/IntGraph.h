//
//  IntGraph.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 15.12.21.
//

#ifndef IntGraph_h
#define IntGraph_h

class IntGraph {
  public:
    void addEdge(const int &u, const int &v, int weight) {
        adjacent[u].push_back(std::make_pair(v, weight));
    }

    void shortestPath(int src, int dest)
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
    }

  private:
    std::unordered_map<int, std::vector<std::pair<int, int>>> adjacent;
};

#endif /* IntGraph_h */
