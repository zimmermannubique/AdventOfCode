//
//  AdventTask12.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 12.12.21.
//

#ifndef AdventTask12_h
#define AdventTask12_h

#include <AdventTask.h>

#include "Graph.h"

class AdventTask12 : public AdventTask<12> {
  protected:

    virtual void solveSilver(std::ifstream &file) {
        Graph g = input(file);
        g.paths("start", "end");
    }

    virtual void solveGold(std::ifstream &file) {
        Graph g = input(file);
        g.pathsWithTwiceRule("start", "end");
    }

    std::pair<std::string, std::string> split(const std::string& s)
    {
        auto pos = s.find('-');
        return std::make_pair(s.substr(0, pos), s.substr(pos+1, s.length()));
    }

    Graph input(std::ifstream &file) {
        Graph graph;

        std::string input;
        while(file >> input) {
            auto uv = split(input);
            graph.addEdge(uv.first, uv.second);
        }

        return graph;
    }

};

#endif /* AdventTask12_h */
