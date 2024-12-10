// /*
// Name: Group 13
// Class: CPSC223, Fall 2024
// Date: December 8, 2024
// Programming Assignment: Project 2
// Description: 
// */

#ifndef HEADER_HPP
#define HEADER_HPP

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Represents a dam with attributes for its size and year of construction
class Dam {
public:
    string name;    // Name of the dam
    int yearBuilt;  // Year the dam was constructed

    Dam(const string& n, int y);
    void displayInfo() const;
};

// Represents a node in the binary tree, storing information about a water body
struct TreeNode {
    string name;             // Name of the tributary
    string parent;           // Parent tributary
    float flowRate;          // Average flow rate in cubic meters per second
    vector<Dam> dams;        // Dams associated with the tributary
    TreeNode* left;          // Pointer to the left child
    TreeNode* right;         // Pointer to the right child

    TreeNode(const string& n, float f);
    void addDam(const Dam& dam);
    void displayNode() const;
};

TreeNode* insertNode(TreeNode* root, const string& parent, const string& name, float flowRate, const vector<Dam>& dams);
TreeNode* buildTreeFromCSV(const string& filename);
void traverseTree(TreeNode* root);
void exploreTree(TreeNode* root);
void displayTree(TreeNode* root);
#endif // HEADER_HPP

/*
#ifndef HEADER_HPP
#define HEADER_HPP
#endif

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Represents a dam with attributes for its size and year of construction
class Dam {
public:
    string name;     // Name of the dam
    int size;             // Size of the dam (e.g., capacity in cubic feet)
    int yearBuilt;        // Year the dam was constructed

    // Constructor to initialize a dam
    Dam(const string& n, int s, int y) 
        : name(n), size(s), yearBuilt(y) {}

    // Displays information about the dam
    void displayInfo() const {
        cout << "Dam Name: " << name 
                  << ", Size: " << size 
                  << ", Year Built: " << yearBuilt << "\n";
    }
};

// Represents a node in the binary tree, storing information about a water body
struct TreeNode {
    string name;          // Name of the water body (e.g., "Columbia River")
    string type;          // Type of the water body ("River", "Lake", "Stream")
    float flowRate;       // Float of average flow rate in river
    vector<Dam> dams;     // Vector to store dams associated with this water body
    TreeNode* left;            // Pointer to the left child node
    TreeNode* right;           // Pointer to the right child node

    // Constructor to initialize a tree node
    TreeNode(const string& n, const string& t, const float& f) 
        : name(n), type(t), flowRate(f), left(nullptr), right(nullptr) {}

    // Adds a dam to the vector of dams
    void addDam(const Dam& dam) {
        dams.push_back(dam);
    }

    // Displays information about the node and its associated dams
    void displayNode() const {
        cout << "Water Body: " << name << " (" << type << ")\n";
        for (const auto& dam : dams) {
            dam.displayInfo();
        }
    }
};

// Function to move to the right child of the current node
TreeNode* moveToRightChild(TreeNode* current) {
  // Check if the current node is not null
  if (current) {
    // Check if the current node has a right child
    if (current->right) {
      // Move to the right child and return the node
      return current->right;
    } else {
      // Print a message if there is no right child
      cout << "No right child exists for the current node.\n";
      return nullptr;
    }
  } else {
    // Print a message if the current node is null
    cout << "Current node is null, cannot move to right child.\n";
    return nullptr;
  }
}

// Function to print the information of a given node
void printNode(TreeNode* node) {
  // Check if the node is not null
  if (node) {
    // Call the displayNode function to print water body and dam information
    node->displayNode();
  } else {
    // Print a message if the node is null
    cout << "Node is null. No information to display.\n";
  }

// Inserts a new node into the binary tree based on the parent water body
TreeNode* insertNode(TreeNode* root, const string& parent, 
                     const string& name, const float& flowRate, const string& type) {
    if (root == nullptr) {
        // Create a new node if the tree or subtree is empty
        return new TreeNode(name, type, flowRate);
    }

    if (root->name == parent) {
        // Check if the current node matches the parent
        if (!root->left) {
            root->left = new TreeNode(name, type, flowRate);  // Add as the left child if empty
        } else if (!root->right) {
            root->right = new TreeNode(name, type, flowRate); // Add as the right child if empty
        } else {
            // If both children exist, print a warning
            cout << "Parent node already has two children.\n";
        }
    } else {
        // Recursively traverse left and right subtrees to find the parent
        root->left = insertNode(root->left, parent, name, flowRate, type);
        root->right = insertNode(root->right, parent, name, flowRate, type);
    }

    return root; // Return the root of the updated tree
}
*/
