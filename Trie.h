#include <iostream>
#include <vector>
#include <unordered_map>
struct Node {
    char letter;
    int index;
    Node(char letter, int index){
        this -> letter = letter;
        this -> index = index;
    }
};
struct Trie {
public:

    int nodeCount;
    std::vector<std::vector<Node> > treeChildren;
    std::unordered_map<int,int> numMoves;

    Trie() {
        //setup root node
        nodeCount = 1;
        treeChildren.push_back(std::vector<Node>());
    }

    void insertString(std::string s,int numMove) {
        int nodeIndex = 0;
        int letterIndex;
        for (char letter : s) {
            std::vector<Node> &nodeChildren = treeChildren[nodeIndex];
            letterIndex = findLetter(nodeChildren, letter);
            if (letterIndex == -1) {
                nodeIndex = insertNode(nodeChildren, letter);
            } else {
                nodeIndex = nodeChildren[letterIndex].index;
            }
        }
        numMoves[nodeIndex] = numMove;
    }
    bool isStringPresent(std::string s) {
        int nodeIndex = 0;
        int letterIndex;
        bool present = true;
        for (char letter : s) {
            std::vector<Node> &nodeChildren = treeChildren[nodeIndex];
            letterIndex = findLetter(nodeChildren, letter);
            if (letterIndex == -1) {
                present = false;
                break;
            } else {
                nodeIndex = nodeChildren[letterIndex].index;
            }
        }
        return present;
    }
    int getNumMoves(std::string s) {
        int nodeIndex = 0;
        int letterIndex;
        for (char letter : s) {
            std::vector<Node> &nodeChildren = treeChildren[nodeIndex];
            letterIndex = findLetter(nodeChildren, letter);
            if (letterIndex == -1) {
                return -1;
            } else {
                nodeIndex = nodeChildren[letterIndex].index;
            }
        }
        return numMoves[nodeIndex];
    }

private:
    int findLetter(std::vector<Node> &nodeChildren, char &letter){
        int index = -1;
        for (int i = 0; i < nodeChildren.size(); i++) {
            if (nodeChildren[i].letter == letter){
                index = i;
                break;
            }
        }
        return index;
    }
    int insertNode(std::vector<Node> &nodeChildren, char &letter){
        nodeChildren.push_back(Node(letter, nodeCount));
        treeChildren.push_back(std::vector<Node>());
        nodeCount++;
        return nodeCount-1;
    }
};
