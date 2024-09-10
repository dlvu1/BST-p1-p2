/*
Name: Duyen Vu
Date: 10/22/2023
Description: Homework 3
*/
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Player class to store information
class Player {
public:
    string name;
    string team;
    float data;
    
    Player(string n, string t, float d) : name(n), team(t), data(d) {}
};

// Node class for bst
class Node {
public:
    Player* player;
    Node* left;
    Node* right;
    
    Node(Player* p) : player(p), left(nullptr), right(nullptr) {}
};

// Bst class for player statistic
class PlayerBinarySearchTree {
public:
    Node* root;

    PlayerBinarySearchTree() : root(nullptr) {}
    
    ~PlayerBinarySearchTree() {
        deleteTree(root);
        root = nullptr;
    }
    
    // Insert function
    Node* insert(Node* node, string name, string team, float data) {
        // Create a new node if the node is null
        if (node == nullptr) {
            return new Node(new Player(name, team, data));
        }
        // Recursive case go left or right
        else if (data < node->player->data) {
            node->left = insert(node->left, name, team, data);
        } else {
            node->right = insert(node->right, name, team, data);
        } 
        return node;
    }
    
    // Insert a player from outside the class
    void insert(string player, string team, float data) {
        root = insert(root, player, team, data);
        
        if (root) {
            cout << "Player Inserted Successfully.\n";
        } else {
            cout << "No Such Player\n";
        }
        return;
    }

    // Function to remove a node by search for string name
    Node* removeNode(Node* node, string name) {
        // Find the node to remove
        Node* nodeToRemove = findVal(root, name);
        
        // Return null if the node is null
        if (nodeToRemove == nullptr) {
            cout << "Player " << name << " not found." << endl;
            return root;
        }
    
        else {
            cout << "Player " << name << " removed successfully." << endl;
            
            // Case 1: no child
            if (nodeToRemove->left == nullptr && nodeToRemove->right == nullptr) {
                delete nodeToRemove;
                return nullptr;
            }          
            // Case 1: no child or 1 child
            else if (nodeToRemove->left == nullptr) {
                Node* temp = nodeToRemove->right;
                delete nodeToRemove;
                return temp;
            } else if (nodeToRemove->right == nullptr) {
                Node* temp = nodeToRemove->left;
                delete nodeToRemove;
                return temp;
            }

            // Case 2: 2 children
            Node* temp = findMin(nodeToRemove->right);
            nodeToRemove->player = temp->player;
            nodeToRemove->right = removeNode(nodeToRemove->right, temp->player->name);
        }
        return nodeToRemove;
    }
    
    // Remove a player node from outside the class
    void removeNode(string name) {
        root = removeNode(root, name);
    } 
    
    // Function to find maximum value 
    Node* findMax(Node* node) {
        if (node == nullptr) {
            return nullptr;
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
            cout << "No Player Found.\n";
        } else {
            cout << "-----------------------------" << endl;
            cout << std::setw(15) << std::left << "Name: " << maxNode->player->name << "\n";
            cout << std::setw(15) << std::left << "Team: " << maxNode->player->team << "\n";
            cout << std::setw(15) << std::left << "Statistic: " << maxNode->player->data << "\n";
            cout << "-----------------------------" << endl;
        }
    }
    
    // Function to find minimum value 
    Node* findMin(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }
        
        Node* temp = node;
        while (temp->left != nullptr) {
            temp = temp->left;
        }
        return temp;
    }
    
    // Find and display the player with the min value
    void findMin() {
        Node* minNode = findMin(root);
        if (minNode == nullptr) {
            cout << "No Player Found.\n";
        } else {
            cout << "-----------------------------" << endl;
            cout << std::setw(15) << std::left << "Name: " << minNode->player->name << "\n";
            cout << std::setw(15) << std::left << "Team: " << minNode->player->team << "\n";
            cout << std::setw(15) << std::left << "Statistic: " << minNode->player->data << "\n";
            cout << "-----------------------------" << endl;
        }
    }

    // Function to find a player by name
    Node* findVal(Node* node, string name) {
        if (node == nullptr) {
            return nullptr;
        }

        if (node->player->name == name) {
            return node;
        } 
        else if (node->player->name > name) {
            return findVal(node->left, name);
        } 
        else {
            return findVal(node->right, name);
        }
    }

    // Function to display players in descending order 
    void descendingOrder(Node* node) {
        if (node == nullptr) {
            return;
        } else {
        descendingOrder(node->right);
        std::cout << std::setw(20) << std::left << node->player->name << node->player->data << std::endl;
        descendingOrder(node->left);
        }
    }

    void descendingOrder() {
        descendingOrder(root);
    }
    
    // Function to delete the tree and free the memory
    void deleteTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        deleteTree(node->left);
        deleteTree(node->right);

        delete node->player;
        delete node;
    }

};
    
    // Triple doubles function
    void listTripleDoubles(PlayerBinarySearchTree& pointsBST, PlayerBinarySearchTree& assistsBST, PlayerBinarySearchTree& reboundsBST) {
        cout << "Players with Triple Doubles:" << endl;
        
        Node* pointsNode = pointsBST.root;
        
        while (pointsNode != nullptr) {
        string playerName = pointsNode->player->name;

        Node* assistsNode = assistsBST.findVal(assistsBST.root, playerName);
        Node* reboundsNode = reboundsBST.findVal(reboundsBST.root, playerName);

        // Check if the player exists in all three categories and has >= 10 points, assists, and rebounds
            if (assistsNode != nullptr && reboundsNode != nullptr &&
                pointsNode->player->data >= 10 && assistsNode->player->data >= 10 && reboundsNode->player->data >= 10) {
                cout << "-----------------------------" << endl;
                cout << "Name: " << playerName << endl;
                cout << "Team: " << pointsNode->player->team << endl;
                cout << "Points: " << pointsNode->player->data << endl;
                cout << "Assists: " << assistsNode->player->data << endl;
                cout << "Rebounds: " << reboundsNode->player->data << endl;
                cout << "-----------------------------" << endl;
            }

            pointsNode = pointsBST.findVal(pointsNode, playerName)->right;
        }
    }

    void listTripleDoubles(PlayerBinarySearchTree& pointsBST, PlayerBinarySearchTree& assistsBST, PlayerBinarySearchTree& reboundsBST);

int main() {
    // Create 3 bst for points, assists, and rebounds
    PlayerBinarySearchTree pointsBST, assistsBST, reboundsBST;

    int choice;
    do {
        // Menu for user choices
        cout << "Basketball Player Statistics Menu\n";
        cout << "1. Add Player Data\n";
        cout << "2. Delete a Player\n";
        cout << "3. Display Highest Statistics\n";
        cout << "4. Display Lowest Statistics\n";
        cout << "5. List Players with Triple Doubles\n";
        cout << "6. Display Players in Descending Order of Points\n";
        cout << "7. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;
        
        // Check if the user enter a number in range 1 to 7
        if (choice < 1 || choice > 7) {
            cout << "Invalid input. Please enter a number between 1 and 7.\n";
            cin.clear(); 
            cin.ignore(); 
            continue; 
        }
        
        switch (choice) {
            case 1: { 
                int dataType;
                string playerName, playerTeam;
                float dataValue;

                // Check if the user enter a number from 1 to 3
                while (true) {
                    cout << "Enter Data Type (Points (1), Assists (2), Rebounds (3)): ";
                    cin >> dataType;

                    if (cin.fail() || (dataType != 1 && dataType != 2 && dataType != 3)) {
                        cin.clear(); // Clear the error flag
                        cin.ignore(); // Discard invalid input
                        cout << "Invalid Data Type. Please Enter Again!\n";
                    } else {
                        break; // Valid input, exit the loop
                    }
                }

                cout << "Enter Player Name: ";
                cin.ignore(); // Clear newline from the buffer
                getline(cin, playerName);
                cout << "Enter Team Name: ";
                getline(cin, playerTeam);
                cout << "Enter Player Data (points, assists, or rebounds): ";
                cin >> dataValue;

                // Add data based on the type of data
                switch (dataType) {
                    case 1:
                        pointsBST.insert(playerName, playerTeam, dataValue);
                        break;
                    case 2:
                        assistsBST.insert(playerName, playerTeam, dataValue);
                        break;
                    case 3:
                        reboundsBST.insert(playerName, playerTeam, dataValue);
                        break;
                    default:
                        break;
                }
                break;
            }
            case 2: {
                int dataType;
                string playerName;
                
                // Check if the user enter a number from 1 to 3
                while (true) {
                    cout << "Enter Data Type (Points (1), Assists (2), Rebounds (3)): ";
                    cin >> dataType;

                    if (cin.fail() || (dataType != 1 && dataType != 2 && dataType != 3)) {
                        cin.clear(); // Clear the error flag
                        cin.ignore(); // Discard invalid input
                        cout << "Invalid Data Type. Please Enter Again!\n";
                    } else {
                        break; // Valid input, exit the loop
                    }
                }
                                
                cout << "Enter Player Name : ";
                cin.ignore(); // Clear newline from the buffer
                getline(cin, playerName);

                // Remove data based on data type
                switch (dataType) {
                    case 1:
                        pointsBST.removeNode(playerName);
                        break;
                    case 2:
                        assistsBST.removeNode(playerName);
                        break;
                    case 3:
                        reboundsBST.removeNode(playerName);
                        break;
                    default:
                        break;
                }
    
                break;
            }
            case 3: {
                // Find max
                cout << "Player with Highest Points:\n";
                pointsBST.findMax();
                cout << "Player with Highest Assists:\n";
                assistsBST.findMax();
                cout << "Player with Highest Rebounds:\n";
                reboundsBST.findMax();
                break;
            }
            case 4: {
                // Find Min
                cout << "Player with Lowest Points:\n";
                pointsBST.findMin();
                cout << "Player with Lowest Assists:\n";
                assistsBST.findMin();
                cout << "Player with Lowest Rebounds:\n";
                reboundsBST.findMin();
                break;
            }
            case 5: {
                // List triple double
                listTripleDoubles(pointsBST, assistsBST, reboundsBST);
                break;
            }
            case 6: {
                int dataType;
                
                // Check if the user enter a number from 1 to 3
                while (true) {
                    cout << "Enter Data Type (Points (1), Assists (2), Rebounds (3)): ";
                    cin >> dataType;

                    if (cin.fail() || (dataType != 1 && dataType != 2 && dataType != 3)) {
                        cin.clear(); // Clear the error flag
                        cin.ignore(); // Discard invalid input
                        cout << "Invalid Data Type. Please Enter Again!\n";
                    } else {
                        break; // Valid input, exit the loop
                    }
                }
                
                // Display players in descending order based on data type
                switch (dataType) {
                    case 1:
                        cout << "Players in Descending Order of Points:\n";
                            pointsBST.descendingOrder(); 
                        break;
                    case 2:
                        cout << "Players in Descending Order of Assists:\n";
                            assistsBST.descendingOrder(); 
                        break;
                    case 3:
                        cout << "Players in Descending Order of Rebounds:\n";
                            reboundsBST.descendingOrder(); 
                        break;
                    default:
                        break;
                }                
                break;
            }
            case 7:
                // Exit the program
                cout << "Exiting Program.\n";
                break;
            default:
                break;
        }
    } while (choice != 7);

    return 0;
}




