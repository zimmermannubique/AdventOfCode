//
//  AdventTask13.h
//  AdventOfCode
//
//  Created by Marco Zimmermann on 13.12.21.
//

#ifndef AdventTask13_h
#define AdventTask13_h

struct Node : public std::enable_shared_from_this<Node> {
    Node(int v) : value(v), nodes({}) {};
    Node(): value(-1), nodes({}) { };

    std::vector<std::shared_ptr<Node>> nodes;
    std::shared_ptr<Node> parent;
    int value = -1;
    std::string input;

    bool isValue() {
        return value != -1;
    }

    bool isEvaluatable() {
        if(isValue()) {
            return true;
        }

        if(isEmpty()) {
            return true;
        }

        return false;
    }

    std::vector<int> getValues() {
        if(isValue()) {
            return { value };
        }

        return {};
    }

    bool isEmpty() {
        return value == -1 && nodes.size() == 0;
    }

    int isRightOrder(std::shared_ptr<Node> &other) {
        if(isEvaluatable() && other->isEvaluatable()) {
            auto l = getValues();
            auto r = other->getValues();

            int n = (int)std::max(l.size(), r.size());

            for(int i=0; i<n; ++i) {
                if(i >= l.size()) {
                    return -1;
                } else if(i >= r.size()) {
                    return 1;
                } else {
                    if(l[i] != r[i]) {
                        return l[i] < r[i] ? -1 : 1;
                    }
                }
            }

            return 0;
        } else {
            std::vector<std::shared_ptr<Node>> l = nodes;
            if(isValue()) {
                l = { shared_from_this() };
            }

            std::vector<std::shared_ptr<Node>> r = other->nodes;
            if(other->isValue()) {
                r = { other };
            }

            int n = (int)std::max(l.size(), r.size());

            for(auto i=0; i<n; i++) {
                if(i >= l.size()) {
                    return -1;
                } else if(i >= r.size()) {
                    return 1;
                } else {
                    auto &ll = l[i];
                    auto &rr = r[i];

                    int s = ll->isRightOrder(rr);
                    if(s != 0) {
                        return s;
                    }
                }
            }

            return 0;
        }
    }

    void print() {
        if(nodes.size() > 0) {
            std::cout << "[";

            int j=0;
            for(auto& i : nodes) {
                i->print();
                if(j != nodes.size()-1) {
                    std::cout << ",";
                }

                ++j;
            }
            std::cout << "]";

        } else {
            if(value == -1) {
                std::cout << "[]";
            } else {
                std::cout << value;
            }
        }
    }
};

#include "AdventTask.h"

class AdventTask13 : public AdventTask<13> {
  protected:
    virtual void solveSilver(std::ifstream &file) {
        std::string input;
        std::vector<std::shared_ptr<Node>> nodes;

        while(file >> input) {
            auto i = tree(input);
            nodes.push_back(i);
        }

        int index = 1;
        int sum = 0;
        for(int i=0; i<nodes.size()-1; i+=2) {
            if(nodes[i]->isRightOrder(nodes[i+1]) == -1) {
                sum += index;
            }

            index++;
        }

        std::cout << std::endl << sum << std::endl;
    }

    virtual void solveGold(std::ifstream &file) {
        std::string input;
        std::vector<std::shared_ptr<Node>> nodes;

        while(file >> input) {
            auto i = tree(input);
            nodes.push_back(i);
        }

        nodes.push_back(tree("[[6]]"));
        nodes.push_back(tree("[[2]]"));

        std::sort(nodes.begin(), nodes.end(), [](auto&& a, auto&& b) {
            int r = a->isRightOrder(b);
            return r == -1;
        });

        int a = 0;
        int b = 0;
        for(int i=0; i<nodes.size()-1; i++) {
            if(nodes[i]->input == "[[2]]") {
                a = i+1;
            }

            if(nodes[i]->input == "[[6]]") {
                b = i+1;
            }
        }

        std::cout << a * b << std::endl;
    }

    std::shared_ptr<Node> tree(const std::string& input) {

        std::shared_ptr<Node> vector = std::make_shared<Node>();
        auto current = vector;

        int z = -1;
        for(auto& i : input) {

            if(i == '[') {
                auto node = std::make_shared<Node>();
                node->parent = current;

                current->nodes.push_back(node);
                current = node;

            } else if(i == ']') {
                if(z != -1) {
                    auto node = std::make_shared<Node>(z);
                    node->parent = current;
                    current->nodes.push_back(node);
                    z = -1;
                }

                current = current->parent;
            } else if (i == ',') {
                if(z != -1) {
                    auto node = std::make_shared<Node>(z);
                    node->parent = current;
                    current->nodes.push_back(node);
                    z = -1;
                }
            } else {
                int n = (int)i - 48;
                if(z == -1) {
                    z = n;
                } else {
                    z = 10 * z + n;
                }
            }
        }

        vector->nodes[0]->input = input;
        return vector->nodes[0];
    }
};

#endif /* AdventTask13_h */
