//
//  AdventTask18.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 18.12.21.
//

#ifndef AdventTask18_h
#define AdventTask18_h

#include "Node.h"

class AdventTask18 : public AdventTask<18> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::string input;
        std::vector<std::shared_ptr<Node>> summands;

        while(file >> input) {
            summands.push_back(tree(input));
        }

        auto r = summands[0];

        for(int i=1; i<summands.size(); ++i) {
            r = root(r, summands[i]);
            r->reduce();
        }

        std::cout << r->totalSum();
    }

    virtual void solveGold(std::ifstream &file) {
        std::string input;
        std::vector<std::string> summands;

        while(file >> input) {
            summands.push_back(input);
        }

        auto max = 0;

        for(int i=0; i<summands.size(); ++i) {
            for(int j=0; j<summands.size(); ++j) {
                if(i!=j) {
                    auto r = root(tree(summands[i]), tree(summands[j]));
                    r->reduce();
                    max = std::max(max, r->totalSum());
                }
            }
        }

        std::cout << max;
    }

    std::shared_ptr<Node> tree(const std::string& input) {
        auto newRoot = std::make_shared<Node>(Node(-1, nullptr));
        auto currentNode = newRoot;

        for(auto& i : input) {
            if(i == '[') {
                currentNode->left = std::make_shared<Node>(-1, currentNode);
                currentNode = currentNode->left;
            } else if(i == ']') {
                currentNode = currentNode->parent;
            } else if(isdigit(i)) {
                int n = (int)i - 48;
                currentNode->value = n;
                currentNode = currentNode->parent;
            } else if (i == ',') {
                currentNode->right = std::make_shared<Node>(-1, currentNode);
                currentNode = currentNode->right;
            }
        }

        return newRoot;
    }

    std::shared_ptr<Node> root(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
        auto root = std::make_shared<Node>(left, right);
        root->left->parent = root;
        root->right->parent = root;
        return root;
    }
};


#endif /* AdventTask18_h */
