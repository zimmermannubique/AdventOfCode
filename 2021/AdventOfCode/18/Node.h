//
//  Node.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 18.12.21.
//

#ifndef Node_h
#define Node_h

struct Node : public std::enable_shared_from_this<Node> {
    Node(int value, std::shared_ptr<Node> parent) : value(value), parent(parent) {}
    Node(std::shared_ptr<Node> left, std::shared_ptr<Node> right) : value(-1), left(left), right(right) {}

    int value;
    std::shared_ptr<Node> left = nullptr;
    std::shared_ptr<Node> right = nullptr;
    std::shared_ptr<Node> parent = nullptr;
    std::shared_ptr<Node> valueLeft = nullptr;
    std::shared_ptr<Node> valueRight = nullptr;

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

    std::shared_ptr<Node> rightest() {
        auto t = shared_from_this();
        while(!t->isValue()) { t = t->right; }
        return t;
    }

    static void newLeftRightValuePair(std::shared_ptr<Node> &left, std::shared_ptr<Node> right) {
        if(left) { left->valueRight = right; }
        if(right) { right->valueLeft = left; }
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

                auto valueLeft = toExplode->left->valueLeft;
                auto valueRight = toExplode->right->valueRight;
                if(valueLeft) { valueLeft->value += toExplode->left->value; }
                if(valueRight) { valueRight->value += toExplode->right->value; }

                Node::newLeftRightValuePair(valueLeft, toExplode);
                Node::newLeftRightValuePair(toExplode, valueRight);

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

    bool split() {
        std::stack<std::shared_ptr<Node>> stack;
        stack.emplace(shared_from_this());

        while(stack.size() > 0) {
            auto top = stack.top(); stack.pop();
            if(top->isValue() && top->value >= 10) {
                top->left = std::make_shared<Node>(std::floor(top->value / 2.0), top);
                top->right = std::make_shared<Node>(std::ceil(top->value / 2.0), top);
                Node::newLeftRightValuePair(top->valueLeft, top->left);
                Node::newLeftRightValuePair(top->right, top->valueRight);
                Node::newLeftRightValuePair(top->left, top->right);
                return true;
            }

            if(top->right) { stack.push(top->right); }
            if(top->left) { stack.push(top->left); }
        }

        return false;
    }
};

#endif /* Node_h */
