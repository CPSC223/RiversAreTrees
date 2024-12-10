#include "header.hpp"

int main() {
    string filename = "data.csv";

    TreeNode* root = buildTreeFromCSV(filename);
    if (root) {
        cout << "Tree built successfully.\n";
        exploreTree(root);
    } else {
        cout << "Failed to build tree from the file.\n";
    }

    return 0;
}