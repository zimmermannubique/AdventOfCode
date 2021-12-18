//
//  Node.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 18.12.21.
//

#ifndef Node_h
#define Node_h

struct Node {
    Node(int value, std::shared_ptr<Node> parent)
      : value(value), left(nullptr), right(nullptr), parent(parent) {}

    Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right)
      : value(-1), left(left), right(right), parent(nullptr) {}

    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;

    bool isValue() {
        return !(left && right);
    }

    bool parentOfValues() {
        return !isValue() && (left->isValue() && right->isValue());
    }

    int totalSum() {
        return isValue() ? value : (3 * left->totalSum() + 2 * right->totalSum());
    }

    void reduce() {
        bool r = true;

        while(r) {
            r = explode();
            if(r) { continue; }
            r = split();
        }
    }

    bool explode() {
        std::stack<std::pair<std::shared_ptr<Node>, int>> stack;

        if(right) { stack.emplace(right, 1); }
        if(left) { stack.emplace(left, 1); }

        std::shared_ptr<Node> toExplode = nullptr;
        while(stack.size() > 0) {
            auto top = stack.top(); stack.pop();
            if(top.second == 4 && top.first->parentOfValues()) {
                toExplode = top.first;
                break;
            } else {
                if(top.first->right) { stack.emplace(top.first->right, top.second + 1); }
                if(top.first->left) { stack.emplace(top.first->left, top.second + 1); }
            }
        }

        if(toExplode) {
            fill(toExplode, toExplode->left->value, true);
            fill(toExplode, toExplode->right->value, false);
            toExplode->left = nullptr;
            toExplode->right = nullptr;
            toExplode->value = 0;
            return true;
        } else {
            return false;
        }
    }

    void fill(std::shared_ptr<Node> startNode, int value, bool goToLeft) {
        auto startParent = valueParent(startNode, goToLeft);
        if(!startParent) {
            return;
        }

        std::stack<std::shared_ptr<Node>> stack;

        if(goToLeft) {
            if(startParent->left) { stack.push(startParent->left); }
        } else {
            if(startParent->right) { stack.push(startParent->right); }
        }

        std::shared_ptr<Node> toExplode = nullptr;
        while(stack.size() > 0) {
            auto top = stack.top(); stack.pop();
            if(top->isValue()) {
                top->value += value;
                break;
            } else {
                if(goToLeft) {
                    if(top->left) { stack.push(top->left); }
                    if(top->right) { stack.push(top->right); }
                } else {
                    if(top->right) { stack.push(top->right); }
                    if(top->left) { stack.push(top->left); }
                }
            }
        }
    }

    std::shared_ptr<Node> valueParent(std::shared_ptr<Node> node, bool goToLeft) {
        auto current = node;
        auto parent = node->parent;

        while(parent && ((goToLeft ? parent->left : parent->right) == current)) {
            current = parent;
            parent = parent->parent;
        }

        return parent;
    }

    bool split() {
        std::stack<std::pair<std::shared_ptr<Node>, int>> stack;

        if(right) { stack.emplace(right, 1); }
        if(left) { stack.emplace(left, 1); }

        std::shared_ptr<Node> toSplit = nullptr;
        while(stack.size() > 0) {
            auto top = stack.top(); stack.pop();
            if(top.first->isValue() && top.first->value >= 10) {
                toSplit = top.first;
                break;
            } else {
                if(top.first->right) { stack.emplace(top.first->right, top.second + 1); }
                if(top.first->left) { stack.emplace(top.first->left, top.second + 1); }
            }
        }

        if(toSplit) {
            int left = std::floor(toSplit->value / 2.0);
            int right = std::ceil(toSplit->value / 2.0);
            toSplit->left = std::make_shared<Node>(left, toSplit);
            toSplit->right = std::make_shared<Node>(right, toSplit);
            return true;
        } else {
            return false;
        }
    }
};


#endif /* Node_h */
