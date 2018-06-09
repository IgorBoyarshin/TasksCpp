// BST verification (2 methods).
// std::optional usage.
#include <iostream>
#include <optional>
#include <utility>
#include <climits>


struct Node {
    public:
        Node* left;
        Node* right;
        int value;

        Node() : value(0), left(nullptr), right(nullptr) {}
        Node(int value) : value(value), left(nullptr), right(nullptr) {}
        Node(int value, Node* left, Node* right) :
            value(value), left(left), right(right) {}
};


struct MinMax {
    public:
        int min;
        int max;
        MinMax(int min, int max) : min(min), max(max) {}
};


void printShiftedNode(std::ostream& stream, const Node& node, unsigned int shift);
std::ostream& operator<<(std::ostream& stream, const Node& root);

std::optional<MinMax> getMinMax(const Node& node);
bool verify(const Node& root);

bool isBst(const Node* root, int min, int max);
bool verify2(const Node& root);


int main() {
    Node root(20);
    Node node1(10);
    Node node2(30);
    Node node3(5);
    Node node4(40);
    root.left = &node1;
    root.right = &node2;
    node2.left = &node3;
    node2.right = &node4;

    std::cout << root << std::endl;

    std::cout << (verify(root) ? "true" : "false") << std::endl;
    std::cout << (verify2(root) ? "true" : "false") << std::endl;

    return 0;
}


void printShiftedNode(std::ostream& stream, const Node& node, unsigned int shift) {
    for (unsigned int i = 0; i < shift; i++) {
        stream << " ";
    }

    stream << node.value;
    stream << std::endl;
    if (node.left != nullptr) printShiftedNode(stream, *node.left, shift + 3);
    if (node.right != nullptr) printShiftedNode(stream, *node.right, shift + 3);
}


std::ostream& operator<<(std::ostream& stream, const Node& root) {
    printShiftedNode(stream, root, 0);
    return stream;
}


std::optional<MinMax> getMinMax(const Node& node) {
    const auto mml = (node.left == nullptr) ?
        MinMax(node.value, node.value) :
        getMinMax(*node.left);
    const auto mmr = (node.right == nullptr) ?
        MinMax(node.value, node.value) :
        getMinMax(*node.right);

    // If either branch failed to satisfy BST
    if (!mml.has_value() || !mmr.has_value()) {
        return std::nullopt;
    }

    // If current node satisfies BST
    if ((mml.value().max <= node.value) &&
        (node.value <= mmr.value().min)) {
        // Left is sure to have min, right is sure to have max
        return MinMax(mml.value().min, mmr.value().max);
    }

    return std::nullopt;
}


bool verify(const Node& root) {
    return getMinMax(root).has_value();
}


bool isBst(const Node* root, int min, int max) {
    if (root == nullptr) return true;
    if (root->value < min || root->value > max) return false;

    return (isBst(root->left, min, root->value - 1) &&
            isBst(root->right, root->value + 1, max));
}


bool verify2(const Node& root) {
    return isBst(&root, INT_MIN, INT_MAX);
}
