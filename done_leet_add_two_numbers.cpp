// Given two numbers as linked list in reversed order (lowest digit - head),
// Find their sum.
#include <iostream>


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


void print(ListNode* root) {
    while (root != NULL) {
        std::cout << root->val << " ";
        root = root->next;
    }
    std::cout << std::endl;
}


// Resursive solution
// ListNode* add(ListNode* l1, ListNode* l2, int carry) {
//     if (!l1 && !l2 && carry == 0) {
//         return NULL;
//     }
//
//     int number1 = 0;
//     int number2 = 0;
//     if (l1) {
//         number1 = l1->val;
//         l1 = l1->next;
//     }
//     if (l2) {
//         number2 = l2->val;
//         l2 = l2->next;
//     }
//
//     int sum = number1 + number2 + carry;
//     if (sum >= 10) { sum -= 10; carry = 1; } else carry = 0;
//
//     ListNode* curr = new ListNode(sum);
//     curr->next = add(l1, l2, carry);
//     return curr;
// }
//
// ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
//     return add(l1, l2, 0);
// }


// Best solution
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode* root = new ListNode(-1);
    ListNode* ans_it = root;

    int carry = 0;
    while (l1 || l2 || carry) {
        const int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
        ans_it->next = new ListNode(sum % 10);
        ans_it = ans_it->next;

        carry = sum / 10;
        l1 = l1 ? l1->next : nullptr;
        l2 = l2 ? l2->next : nullptr;
    }

    auto tmp = root;
    delete tmp;
    root = root->next;

    return root;
}


int main() {
    ListNode a1(1);
    ListNode a2(4);
    a1.next = &a2;
    ListNode a3(5);
    a2.next = &a3;
    ListNode b1(9);
    ListNode b2(9);
    b1.next = &b2;

    print(&a1);
    print(&b1);
    print(addTwoNumbers(&a1, &b1));

    return 0;
}
