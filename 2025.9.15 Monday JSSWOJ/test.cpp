#include <stdio.h>
#include <stdlib.h>
struct Node {
    int start, end; // Start and End index of current node
    int data; // Data stored in current node
    struct Node *left, *right; // Pointers to left and right child nodes
};
struct Node* newNode(int start, int end) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->start = start;
    node->end = end;
    node->data = 0;
    node->left = NULL;
    node->right = NULL;
    return node;
}
int gcd(int a, int b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}
// Function to modify the value of a range in Segment Tree
void modifyRange(struct Node* root, int start, int end, int val) {
    if (root == NULL) return;
    if (start > end) return;
    if (start <= root->start && end >= root->end) {
        root->data = val;
        return;
    }
    modifyRange(root->left, start, end, val);
    modifyRange(root->right, start, end, val);
}

// Function to query the GCD of a range in Segment Tree
int queryGCD(struct Node* root, int start, int end) {
    if (root == NULL) return -1;
    if (start > end) return -1;
    if (start <= root->start && end >= root->end) {
        return root->data;
    }
    int leftGCD = queryGCD(root->left, start, end);
    int rightGCD = queryGCD(root->right, start, end);
    if (leftGCD == -1 && rightGCD == -1) {
        return -1;
    } else if (leftGCD == -1) {
        return rightGCD;
    } else if (rightGCD == -1) {
        return leftGCD;
    } else {
        return gcd(leftGCD, rightGCD);
    }
}

// Function to find the GCD of two numbers


int main() {
    struct Node* root = newNode(1, 10);
    modifyRange(root, 3, 6, 2); // Modify the range [3, 6] with value 2
    int gcd = queryGCD(root, 2, 8); // Query GCD of range [2, 8]
    printf("%d\n", gcd); // Output: 2
    return 0;
}

