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
        std::shared_ptr<Node> r = nullptr;

        while(file >> input) {
            auto i = tree(input);
            r = !r ? i : reducedRoot(r, i);
        }

        std::cout << "Result: " << r->totalSum() << std::endl;
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
                max = std::max(max, i==j ? 0 : reducedRoot(tree(summands[i]), tree(summands[j]))->totalSum());
            }
        }

        std::cout << "Result: " << max << std::endl;
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
            } else if (i == ',') {
                currentNode->right = std::make_shared<Node>(-1, currentNode);
                currentNode = currentNode->right;
            } else {
                int n = (int)i - 48;
                currentNode->value = n;
                currentNode = currentNode->parent;
            }
        }

        return newRoot;
    }

    std::shared_ptr<Node> reducedRoot(std::shared_ptr<Node> left, std::shared_ptr<Node> right) {
        auto root = std::make_shared<Node>(left, right);
        root->left->parent = root;
        root->right->parent = root;
        root->reduce();
        return root;
    }
};

#endif /* AdventTask18_h */
