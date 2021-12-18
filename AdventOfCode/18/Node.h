//
//  Node.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 18.12.21.
//

#ifndef Node_h
#define Node_h

struct Node : public std::enable_shared_from_this<Node> {
    Node(int value, std::shared_ptr<Node> parent) : value(value), left(nullptr), right(nullptr), parent(parent) {}
    Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right) : value(-1), left(left), right(right), parent(nullptr) {}

    int value;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    std::shared_ptr<Node> parent;

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

  private:
    bool isValue() {
        return !(left && right);
    }

    bool parentOfValues() {
        return !isValue() && (left->isValue() && right->isValue());
    }

    bool explode() {
        std::stack<std::pair<std::shared_ptr<Node>, int>> stack;
        stack.emplace(shared_from_this(), 0);

        while(stack.size() > 0) {
            auto top = stack.top(); stack.pop();
            if(top.second == 4 && top.first->parentOfValues()) {
                auto toExplode = top.first;
                fill(toExplode, toExplode->left->value, true);
                fill(toExplode, toExplode->right->value, false);
                toExplode->left = nullptr;
                toExplode->right = nullptr;
                toExplode->value = 0;
                return true;
            }

            if(top.first->right) { stack.emplace(top.first->right, top.second + 1); }
            if(top.first->left) { stack.emplace(top.first->left, top.second + 1); }
        }

        return false;
    }

    void fill(std::shared_ptr<Node> startNode, int value, bool goToLeft) {
        auto startParent = valueParent(startNode, goToLeft);
        if(!startParent) { return; }

        auto start = goToLeft ? startParent->left : startParent->right;

        std::stack<std::shared_ptr<Node>> stack;
        stack.push(start);

        while(stack.size() > 0) {
            auto top = stack.top(); stack.pop();
            if(top->isValue()) {
                top->value += value;
                return;
            }

            auto first = goToLeft ? top->left : top->right;
            auto second = goToLeft ? top->right : top->left;
            if(first) { stack.push(first); }
            if(second) { stack.push(second); }
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
        std::stack<std::shared_ptr<Node>> stack;
        stack.emplace(shared_from_this());

        while(stack.size() > 0) {
            auto top = stack.top(); stack.pop();
            if(top->isValue() && top->value >= 10) {
                top->left = std::make_shared<Node>(std::floor(top->value / 2.0), top);
                top->right = std::make_shared<Node>(std::ceil(top->value / 2.0), top);
                return true;
            }

            if(top->right) { stack.push(top->right); }
            if(top->left) { stack.push(top->left); }
        }

        return false;
    }
};

#endif /* Node_h */
