#include "header.hpp"
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <stack>

Dam::Dam(const string& n, int y) : name(n), yearBuilt(y) {}

void Dam::displayInfo() const {
    cout << name << " (Built: " << yearBuilt << ")\n";
}

TreeNode::TreeNode(const string& n, float f) : name(n), flowRate(f), left(nullptr), right(nullptr) {}

void TreeNode::addDam(const Dam& dam) {
    dams.push_back(dam);
}

void TreeNode::displayNode() const {
    cout << "Tributary: " << name << " (Flow Rate: " << flowRate << " cubic meters/sec)\n";
    cout << "Dams:\n";
    for (const auto& dam : dams) {
        dam.displayInfo();
    }
}

TreeNode* insertNode(TreeNode* root, const string& parent, const string& name, float flowRate, const vector<Dam>& dams) {
    if (root == nullptr) {
        return nullptr;
    }

    if (root->name == parent) {
        if (!root->left) {
            root->left = new TreeNode(name, flowRate);
            root->left->dams = dams;
        } else if (!root->right) {
            root->right = new TreeNode(name, flowRate);
            root->right->dams = dams;
        } else {
            cerr << "Error: Parent node '" << parent << "' already has two children.\n";
        }
        return root;
    }

    // Recurse into the left and right subtrees
    if (root->left) {
        insertNode(root->left, parent, name, flowRate, dams);
    }
    if (root->right) {
        insertNode(root->right, parent, name, flowRate, dams);
    }

    return root;
}


TreeNode* buildTreeFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Failed to open CSV file. Check the file path or permissions.\n";
        return nullptr;
    }

    string line, name, parent, flowRateStr, damsStr;
    unordered_map<string, TreeNode*> nodes;
    TreeNode* root = nullptr;

    getline(file, line); // Skip header line
    while (getline(file, line)) {
        stringstream ss(line);
        getline(ss, name, ',');
        getline(ss, parent, ',');
        getline(ss, flowRateStr, ',');
        getline(ss, damsStr, ',');

        float flowRate = stof(flowRateStr);
        vector<Dam> dams;
        stringstream damsStream(damsStr);
        string damInfo;
        while (getline(damsStream, damInfo, ';')) {
            size_t openParen = damInfo.find('(');
            size_t closeParen = damInfo.find(')');
            if (openParen != string::npos && closeParen != string::npos) {
                string damName = damInfo.substr(0, openParen - 1);
                int yearBuilt = stoi(damInfo.substr(openParen + 1, closeParen - openParen - 1));
                dams.emplace_back(damName, yearBuilt);
            }
        }

        if (parent.empty()) {
            // Create root node
            root = new TreeNode(name, flowRate);
            root->dams = dams;
            nodes[name] = root;
        } else {
            if (nodes.find(parent) == nodes.end()) {
                cerr << "Parent not found: " << parent << endl;
                continue;
            }

            TreeNode* parentNode = nodes[parent];
            if (!parentNode->left) {
                parentNode->left = new TreeNode(name, flowRate);
                parentNode->left->dams = dams;
                nodes[name] = parentNode->left;
            } else if (!parentNode->right) {
                parentNode->right = new TreeNode(name, flowRate);
                parentNode->right->dams = dams;
                nodes[name] = parentNode->right;
            } else {
                cerr << "Parent node already has two children: " << parent << endl;
            }
        }
    }

    file.close();
    return root;
}


void traverseTree(TreeNode* root) {
    if (!root) return;
    root->displayNode();
    traverseTree(root->left);
    traverseTree(root->right);
}

void displayMenu() {
    cout << "\nOptions:\n";
    cout << "1. View Current Node Details\n";
    cout << "2. Navigate to Left Child\n";
    cout << "3. Navigate to Right Child\n";
    cout << "4. Return to Parent\n";
    cout << "5. Exit\n";
    cout << "Enter your choice: ";
}

void exploreTree(TreeNode* root) {
    if (!root) {
        cout << "Tree is empty. Nothing to explore.\n";
        return;
    }

    TreeNode* current = root;
    TreeNode* parent = nullptr; // To track the parent node
    stack<TreeNode*> parentStack; // To allow navigation back to parents

    while (true) {
        cout << endl << "You are in the tributary: " << current->name;
        displayMenu();
        cout << endl;
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: // View current node details
            if (current) {
                current->displayNode();
            } else {
                cout << "No node selected.\n";
            }
            break;

        case 2: // Navigate to left child
            if (current && current->left) {
                parentStack.push(current);
                current = current->left;
            } else {
                cout << "Left child does not exist.\n";
            }
            break;

        case 3: // Navigate to right child
            if (current && current->right) {
                parentStack.push(current);
                current = current->right;
            } else {
                cout << "Right child does not exist.\n";
            }
            break;

        case 4: // Return to parent
            if (!parentStack.empty()) {
                current = parentStack.top();
                parentStack.pop();
            } else {
                cout << "Already at the root. Cannot return further.\n";
            }
            break;

        case 5: // Exit
            cout << "Exiting tree exploration. Goodbye!\n";
            return;

        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }
}
