#include<iostream>
#include<queue>

/*
    implementation for binary search tree
    Method:
        search(int value);
        insert(int value);
        deleteNode(int value);
        levelOrderTraversal();

*/

struct Node {
    int value;
    Node* leftChild;
    Node* rightChild;
    
    // Constructor to easily create a new Node with given value
    Node(int val) : value(val), leftChild(nullptr), rightChild(nullptr) {}
};

class BST{
    private:
        Node* root;
        bool insertHelper(Node*& rootNode, int value);
        Node* searchHelper(Node* rootNode, int value);
        Node* deleteNodeHelper(Node* rootNode, int value);
        Node* minValueNode(Node* currNnode);
    
    public:
        BST() : root(nullptr) {} 
    
        Node* search(int value);
        bool insert(int value);
        bool deleteNode(int value); // whether the node is deleted
        void levelOrderTraversal();


};

Node* BST::minValueNode(Node* currNode){
    // find the inorder sucessor
    Node* current = currNode;
    while (current && current -> leftChild != nullptr){
        current = current -> leftChild;
    }
    return current;

}

bool BST::insertHelper(Node*& rootNode, int value){
    //Node*&: reference to a pointer
    // base case: the root is a nullptr, 
    // This allows the function to modify the pointer itself (i.e., change what the pointer points to) and have that modification persist outside the function.
    if (rootNode == nullptr){
        rootNode = new Node(value);
        return true;
    }
    // basecase: there is duplicate value
    if (rootNode -> value == value){
        return false;
    }

    // recursion case: traverse based on the comparison of value
    // link the new node to its parent via the assign (=) notation
    if (value < rootNode -> value){
        return insertHelper(rootNode -> leftChild, value);
    }
    else if (value > rootNode -> value){
        return insertHelper(rootNode -> rightChild, value);
    }

}

bool BST::insert(int value){
    bool rootnode = insertHelper(root, value);
    return rootnode;
}

Node* BST::searchHelper(Node* rootNode, int value){
    // basecase: the value is not found
    if (rootNode == nullptr){
        return nullptr;
    }
    // basecase: the value is found
    if (rootNode -> value == value){
        return rootNode;
    }

    if (value < rootNode -> value){
        return searchHelper(rootNode -> leftChild, value);
    }
    else if(value > rootNode -> value){
        return searchHelper(rootNode -> rightChild, value);
    }

}

Node* BST::search(int value){
    Node* foundNode = searchHelper(root, value);
    return foundNode;
}

Node* BST::deleteNodeHelper(Node* rootNode, int value){
    // base case: tree is empty
    if (rootNode == nullptr) return rootNode;
    
    // recursive case: 
    if (value < rootNode -> value){
        rootNode -> leftChild = deleteNodeHelper(root -> leftChild, value);
    }
    else if(value > rootNode -> value){
        rootNode -> rightChild = deleteNodeHelper(root -> rightChild, value);
    }
    else{
        // case: node with only one child/ no child
        if (rootNode -> leftChild == nullptr){
            Node* temp = rootNode -> rightChild;
            delete rootNode;
            return temp;
        }
        else if (rootNode -> rightChild == nullptr){
            Node* temp = rootNode -> leftChild;
            delete rootNode;
            return temp;
        }
        else{
            // case: node with two children
            // find inorder successor
            Node* temp = minValueNode(rootNode -> rightChild);
            rootNode -> value = temp -> value;
            // delete the inorder successor: back to the 0-1 child case
            rootNode -> rightChild = deleteNodeHelper(rootNode -> rightChild, temp -> value);
        }
    }
    // return the current node
    return rootNode;
}

bool BST::deleteNode(int value){
    // check: if the value in the BST 
    if (search(value) != nullptr){
        root = deleteNodeHelper(root, value);
        // After deletion, check if the value still exists
        if (search(value) == nullptr) {
            // the value no longer exists
            return true; 
        }
    }
    // If the value was not found initially or still exists after deletion attempt
    return false;
}

void BST::levelOrderTraversal(){
    if (root == nullptr){return;}
    // queue is required for level order traversal
    std::queue<Node*> q;
    q.push(root);
    while (!q.empty()){
        // fetch the value from head and pop the value
        Node* popNode = q.front();
        q.pop();
        std::cout << popNode -> value << " ";
        if (popNode -> leftChild != nullptr){
            q.push(popNode -> leftChild);
        }
        if(popNode -> rightChild != nullptr){
            q.push(popNode -> rightChild);
        }
    }
}

int main(){
    // initialize a tree
    BST tree;
    tree.insert(2);
    tree.insert(3);
    tree.insert(7);
    tree.insert(5);
    tree.deleteNode(3);
    tree.levelOrderTraversal();
}