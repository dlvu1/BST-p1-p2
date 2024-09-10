/*
Name: Duyen Vu
Date: 10/22/2023
Description: Homework 3
*/
#include <iostream>
using namespace std;

class Node {
public:
    Node* left;
    Node* right;
    int data;
    
    // Node constructor
    Node(int d) : data(d), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
public:
    Node* root;
    
    // BinarySearchTree constructor
    BinarySearchTree() : root(nullptr) {}
    
    // Insert function
    Node* insert(Node* node, int data) {
        // Create a new node if the node is null
        if (node == nullptr) {
            node = new Node(data);
        } 
        // Recursive case go left or right
        else if (data < node->data) {
            node->left = insert(node->left, data);
        } else {
            node->right = insert(node->right, data);
        }
        return node;
    }
    
    void insert(int data) {
        root = insert(root, data);
    }
    
    // Print preOrder
    void preOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        cout << node->data << " ";
        preOrder(node->left);
        preOrder(node->right);
    }
    
    void preOrder() {
        preOrder(root);
        cout << endl;
    }
    
    // Print postOrder
    void postOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        postOrder(node->left);
        postOrder(node->right);
        cout << node->data << " ";
    }
    
    void postOrder() {
        postOrder(root);
        cout << endl;
    }
    
    // Print inOrder
    void inOrder(Node* node) {
        if (node == nullptr) {
            return;
        }
        
        inOrder(node->left);
        cout << node->data << " ";
        inOrder(node->right);
    }
    
    void inOrder() {
        inOrder(root);
        cout << endl;
    }
    
    // Function to find maximum value 
    Node* findMax(Node* node) {
        if (node == nullptr) {
            node = nullptr;
        }
        Node* temp = node;
        while (temp->right != nullptr) {
            temp = temp->right;
        }
        return temp;
    }
    
    // Find and display the player with the max value
    void findMax() {
        Node* maxNode = findMax(root);
        if (maxNode == nullptr) {
            cout << endl;
        } else {
            cout << maxNode->data << endl;
        }
    }
    
    // Function to remove max value
    Node* removeMax(Node* node) {
        if (node == nullptr) {
            node = nullptr;
        }
        
        if (node->right == nullptr) {
            Node* temp = node->left;
            delete node;
            return temp;
        }
        node->right = removeMax(node->right);
        return node;
    }
    
    void removeMax() {
        root = removeMax(root);
        cout << endl;
    }
    
    // Function to find successor
    Node* findSuccessor(Node* node, int data) {
        Node* temp = findVal(node, data);
        
        if (temp == nullptr) {
            return nullptr;
        } 
        else if (temp->right != nullptr) {
            return findMin(temp->right);
        } 
        else {
            Node* successor = nullptr;
            Node* current = node;

            while (current != nullptr) {
                if (data < current->data) {
                    successor = current;
                    current = current->left;
                } else if (data > current->data) {
                    current = current->right;
                } else {
                    break;
                }
            }
        
        return successor;
        }
    }
    
    // Function to search for node
    Node* findVal(Node* node, int data) {
	    if (node == nullptr) {
            return nullptr;
        }
        
	    if(node->data == data) {
	        return node;
	    } else if(node->data > data) {
	        return findVal(node->left, data);
	    } else {
	        return findVal(node->right, data);
	    }
    }
    
    // Function to find min value
    Node* findMin(Node* node) {
        if (node == nullptr) {
            node = nullptr;
        }
        Node* temp = node;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }
    
    // Remove function 
    Node* remove(Node* node, int data) {
        // Return null if the node is null
        if (node == nullptr) {
            return node;
        }
        // Recursive case go left or right
        if (data < node->data) {
            node->left = remove(node->left, data);
        } 
        else if (data > node->data) {
            node->right = remove(node->right, data);
        } 
        else {
            // Case 1: no child
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            // Case 2: 1 child
            } else if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            } else if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            // case 3: 2 children
            } else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }
        return node;
    }
    
    void remove(int data) {
        root = remove(root, data);
    }
};

int main() {
    BinarySearchTree bst;
    Node* node;
    int choice, value;
    
    do {
        // Menu for user choices
        cout << "Binary Search Tree" << endl;
        cout << "1. Insert a Node" << endl;
        cout << "2. Pre-Order Traversal" << endl;
        cout << "3. Post-Order Traversal" << endl;
        cout << "4. In-Order Traversal" << endl;
        cout << "5. Find Max" << endl;
        cout << "6. Remove Max" << endl;
        cout << "7. Successor" << endl;
        cout << "8. Delete a Node" << endl;
        cout << "9. Exit" << endl;
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1: // Insert a value
                cout << "Enter Value To Insert: ";
                cin >> value;
                bst.insert(value);
                cout << "Node With Value " << value << " Inserted." << endl;
                break;
            case 2: // Print pre-order
                cout << "Pre-Order Traversal: ";
                bst.preOrder();
                break;
            case 3: // Print post-order
                cout << "Post-Order Traversal: ";
                bst.postOrder();
                break;
            case 4: // Print in-order
                cout << "In-Order Traversal: ";
                bst.inOrder();
                break;
            case 5: // Print max value
                cout << "Max Value: ";
                bst.findMax();
                break;
            case 6: // Remove max value
                cout << "Max Value Removed.";
                bst.removeMax();
                break;
            case 7: // Find successor
                cout << "Enter Value To Find Successor: ";
                cin >> value;
                
                node = bst.findVal(bst.root, value);
                if(node == NULL) {
                    cout << "Value Not Found" << endl;
                } else {
                    Node* successor = bst.findSuccessor(bst.root, value);
                    if(successor == NULL) {
                        cout << "No Successor Found" << endl;
                    } else {
                        cout << "Successor Of " << value <<" Is " << successor->data << endl; 
                    }
                }
            break;
            case 8: // Delete a node
                cout << "Enter Value To Delete: ";
                cin >> value;
                bst.remove(value);
                cout << "Node " << value << " Deleted" << endl; 
                break;
            case 9: // Exist program
                cout << "Exiting Program." << endl;
                break;
            default: // Print invalid if the user enter an invalid choice
                cout << "Invalid Choice. Please Try Again." << endl;
        }
    } while (choice != 9);

    return 0;
}




