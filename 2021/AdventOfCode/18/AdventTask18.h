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
        std::shared_ptr<Node> root = nullptr;
        std::shared_ptr<Node> rightest = nullptr;

        while(file >> input) {
            auto i = tree(input, false);
            root = !root ? i.first : reducedRoot(root, rightest, i.first, i.second);
            rightest = root->rightest();
        }

        std::cout << "Result: " << root->totalSum() << std::endl;
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
                auto l = tree(summands[i], true);
                auto r = tree(summands[j], false);
                max = std::max(max, i==j ? 0 : reducedRoot(l.first, l.second, r.first, r.second)->totalSum());
            }
        }

        std::cout << "Result: " << max << std::endl;
    }

    std::pair<std::shared_ptr<Node>, std::shared_ptr<Node>> tree(const std::string& input, bool isLeft) {
        auto newRoot = std::make_shared<Node>(Node(-1, nullptr));
        auto currentNode = newRoot;

        std::shared_ptr<Node> left = nullptr;
        std::shared_ptr<Node> right = nullptr;

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

                Node::newLeftRightValuePair(right, currentNode);

                if(!left) { left = currentNode; }
                right = currentNode;
                currentNode = currentNode->parent;
            }
        }

        return std::make_pair(newRoot, isLeft ? right : left);
    }

    std::shared_ptr<Node> reducedRoot(std::shared_ptr<Node> left, std::shared_ptr<Node> leftRightestValueNode,  std::shared_ptr<Node> right, std::shared_ptr<Node> rightLeftestValueNode) {
        auto root = std::make_shared<Node>(left, right);
        root->left->parent = root;
        root->right->parent = root;

        Node::newLeftRightValuePair(leftRightestValueNode, rightLeftestValueNode);

        root->reduce();
        return root;
    }
};

#endif /* AdventTask18_h */
