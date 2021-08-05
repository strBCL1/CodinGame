//Link to the puzzle: https://www.codingame.com/training/easy/order-of-succession
#include <iostream>
#include <vector> //Vectors are needed to store children of nodes in tree;
#include <queue> //Queue is needed for BFS traversal;
using namespace std;

//Structure to initialize a tree;
struct Tree {
    string nodesName, parentName;
    int birthYear;
    bool isAlive;
    bool isNotCatholic;
    char gender;
    vector<Tree*> children;

    //Constructor to initialize a new node in tree;
    Tree(string& nodesName, string& parentName, int& birthYear, string& deathYear, string& religion, char& gender) {
        this->nodesName = nodesName;
        this->parentName = parentName;
        this->birthYear = birthYear;
        this->isAlive = deathYear == "-";
        this->isNotCatholic = religion != "Catholic";
        this->gender = gender;
    }
};

//Function to find a parent of 'newNode' in tree using BFS traversal;
//https://www.geeksforgeeks.org/generic-tree-level-order-traversal/
Tree* findParent (Tree*& newNode, Tree*& root) {
    queue<Tree*> q; //Create a queue;
    q.push(root); //Push root to queue;

    //BFS traversal of general tree:
    while (!q.empty()) { //While queue isn't empty:
        int n = q.size(); //Get amount of nodes, whose children have to be checked to find a parent of 'newNode';

        for (int count = 0; count < n; ++count) { //For each node in queue:
            Tree* curNode = q.front(); //Get current node; 
            vector<Tree*>& children = curNode->children; //Get reference to the children of 'curNode';
            q.pop(); //Erase 'curNode' from queue;

            for (int i = 0; i < children.size(); ++i) { //For each child of 'curNode':
                if (children[i]->nodesName == newNode->parentName) //If name of current child equals to the parent's name of 'newNode', return curChild;
                    return children[i];

                q.push(children[i]); //Else push curChild to queue to check its children;
            }
        }
    }

    return root; //If no parent found, return 'root' as a parent of 'newNode';
}

//Function to print DFS/Inorder tree traversal;
void printAnswer (Tree*& root) {
    if (root->isAlive && root->isNotCatholic)
        cout << root->nodesName << "\n";

    for (auto& curChild : root->children)
        printAnswer(curChild);
}

int main()
{
    int nodesAmount; cin >> nodesAmount; cin.ignore();
    Tree* root = nullptr; //Initialize empty root node;

    for (int count = 0; count < nodesAmount; ++count) {
        //Declarations:
        string nodesName, parentName; //Name of current node and its parent's name;
        int birthYear;
        string deathYear; //Deathyear is a number or "-"; 
        string religion;
        char gender; //Gender is 'M' or 'F';

        cin >> nodesName >> parentName >> birthYear >> deathYear >> religion >> gender; cin.ignore();

        Tree* newNode = new Tree(nodesName, parentName, birthYear, deathYear, religion, gender); //Create a new node;

        if (root == nullptr) { //If root is NULL - initialize root and continue data inputting;
            root = newNode; 
            continue;
        }

        //Else: find a parent of newly created node;
        Tree* newNodesParent = findParent(newNode, root);
        vector<Tree*>& children = newNodesParent->children; //Initialize 'children' vector as a reference to the successors vector of new node's parent;

        if (children.empty()) { //If curParent has no children, add newNode to vector and continue data inputting;
            children.push_back(newNode); 
            continue; 
        }

        //If newNode's gender is 'M' (male), then start searching for insertion position of 'newNode' into 'curParent children' vector from the leftmost index; else from the rightmost index;
        bool fromBeginning = newNode->gender == 'M';
        int curIndex = fromBeginning ? 0 : children.size() - 1;

        //Start searching from the leftmost position; "M" gender;
        //While curIndex isn't last && curChild.gender == newNode.gender && curChild.birthYear < newNode.birthYear: increment curIndex;
        while (fromBeginning && curIndex < children.size() && children[curIndex]->gender == newNode->gender && children[curIndex]->birthYear < newNode->birthYear) {
            curIndex++;
        }

        //Start searching from the rightmost position; "F" gender;
        //While curIndex isn't first && curChild.gender == newNode.gender && curChild.birthYear > newNode.birthYear: decrement curIndex;
        while (!fromBeginning && curIndex >= 0 && children[curIndex]->gender == newNode->gender && children[curIndex]->birthYear > newNode->birthYear) {
            curIndex--;
        }

        //Insert 'newNode' to 'curIndex' position in 'children' if newNode.gender == "M"; else insert 'newNode' to 'curIndex + 1' position;
        children.insert(children.begin() + curIndex + (fromBeginning ? 0 : 1), newNode);
    }

    printAnswer(root); //Perform DFS/Inorder tree traversal;
    delete root; //Delete the whole tree;
}
