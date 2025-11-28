#include "tasks_5.h"
#include <iostream>
#include <vector>

static class TreeNode {
private:
    int value;
    TreeNode* root = nullptr;
    std::vector<TreeNode*> children;

public:
    TreeNode(int val) : value(val) {
    }

    TreeNode(const TreeNode&) = delete;
    TreeNode& operator=(const TreeNode&) = delete;

    ~TreeNode() {
        for (auto child : children) {
            delete child;
        }
    }

    TreeNode* AddChild(int child_value) {
        auto node = new TreeNode(child_value);
        node->root = this;
        children.push_back(node);
        return node;
    }

    void Print(int depth = 0) const {
        for (int i = 0; i < depth; ++i) {
            std::cout << " ";
        }
        std::cout << "- " << value << "\n";
        for (const auto& child : children) {
            child->Print(depth + 1);
        }
    }
};

void task_502() {
    TreeNode root(1);

    auto left_son = root.AddChild(10);
    auto middle_son = root.AddChild(20);
    auto right_son = root.AddChild(30);

    left_son->AddChild(100);
    left_son->AddChild(200);

    root.Print();
}
