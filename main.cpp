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
        Node(int value, Node* left, Node* right) : value(value), left(left), right(right) {}
};


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

    return 0;
}
