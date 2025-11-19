#include "tasks_4.h"
#include <iostream>
#include <map>
#include <string>
#include <vector>

static struct Node {
    std::map<std::string, Node> children;
};

static class Tree {
private:
    Node root;

public:
    bool Has(const std::vector<std::string>& node) const;
    void Insert(const std::vector<std::string>& node);
    void Delete(const std::vector<std::string>& node);
};

bool Tree::Has(const std::vector<std::string>& node) const {
    const Node* current = &root;

    for (const auto& part : node) {
        auto it = current->children.find(part);
        if (it == current->children.end()) {
            return false;
        }
        current = &(it->second);
    }

    return true;
}

void Tree::Insert(const std::vector<std::string>& node) {
    Node* current = &root;

    for (const auto& part : node) {
        current = &(current->children[part]);
    }
}

void Tree::Delete(const std::vector<std::string>& node) {
    if (node.empty()) return;

    Node* current = &root;

    for (size_t i = 0; i < node.size() - 1; ++i) {
        auto it = current->children.find(node[i]);
        if (it == current->children.end()) {
            return;
        }
        current = &(it->second);
    }

    current->children.erase(node.back());
}

void task_408() {
    Tree tree;
    tree.Insert({"home", "user", "documents"});

    std::cout << tree.Has({"home", "user", "documents"}) << std::endl;
    std::cout << tree.Has({"home", "user"}) << std::endl;
    std::cout << tree.Has({"home", "admin"}) << std::endl;

    tree.Delete({"home", "user", "documents"});
    std::cout << tree.Has({"home", "user", "documents"}) << std::endl;
    std::cout << tree.Has({"home", "user"}) << std::endl;
}
