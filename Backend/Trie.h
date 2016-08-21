#ifndef Trie_h
#define Trie_h

#include <iostream>
#include <vector>
#include <unordered_map>

struct TrieNode {
    char letter;
    int index;
    TrieNode(char letter, int index){
        this -> letter = letter;
        this -> index = index;
    }
};

struct CubeNode {
    int numMoves;
    char lastMove;
    bool isClockwise;
    int parentIndex;
    
    CubeNode(){
        
    }
    
    CubeNode(int numMoves, char lastMove, bool isClockwise, int parentIndex){
        this -> numMoves = numMoves;
        this -> lastMove = lastMove;
        this -> isClockwise = isClockwise;
        this -> parentIndex = parentIndex;
    }
};

struct Trie {
    
public:
    Trie();
    int insertCube(std::string &cubeString,int numMoves, char lastMove, bool isClockwise, int parentIndex);
    bool isCubePresent(std::string &cubeString);
    int getCubeIndex(std::string &cubeString);
    int getNumMoves(std::string &cubeString);
    int getNumMoves(int trieNodeIndex);
    int getParentIndex(std::string &cubeString);
    int getParentIndex(int cubeNodeIndex);
    std::string getLastMove(int cubeNodeIndex);
    
private:
    int trieNodeCount;
    std::vector<std::vector<TrieNode> > treeChildren;
    std::unordered_map<int,CubeNode> cubeStateData;
    
    int findLetter(std::vector<TrieNode> &nodeChildren, char letter);
    int insertTrieNode(std::vector<TrieNode> &nodeChildren, char letter);
};


Trie::Trie() {
    //setup root node
    trieNodeCount = 1;
    treeChildren.push_back(std::vector<TrieNode>());
}

int Trie::insertCube(std::string &cubeString, int numMoves, char lastMove, bool isClockwise, int parentIndex) {
    int trieNodeIndex = 0;
    int letterIndex;
    for (char letter : cubeString) {
        std::vector<TrieNode> &nodeChildren = treeChildren[trieNodeIndex];
        letterIndex = findLetter(nodeChildren, letter);
        if (letterIndex == -1) {
            trieNodeIndex = insertTrieNode(nodeChildren, letter);
        } else {
            trieNodeIndex = nodeChildren[letterIndex].index;
        }
    }
    //std::cout << trieNodeIndex << std::endl;
    cubeStateData[trieNodeIndex] = CubeNode(numMoves, lastMove, isClockwise, parentIndex);
    //std::cout << "numMoves: " << cubeStateData[trieNodeIndex].numMoves << std::endl;
    //std::cout << "lastMove: " << cubeStateData[trieNodeIndex].lastMove << " " << cubeStateData[trieNodeIndex].isClockwise << std::endl;
    //std::cout << "parentIndex: " << cubeStateData[trieNodeIndex].parentIndex << std::endl;
    
    return trieNodeIndex;
}

bool Trie::isCubePresent(std::string &cubeString) {
    int trieNodeIndex = 0;
    int letterIndex;
    bool present = true;
    for (char letter : cubeString) {
        std::vector<TrieNode> &nodeChildren = treeChildren[trieNodeIndex];
        letterIndex = findLetter(nodeChildren, letter);
        if (letterIndex == -1) {
            present = false;
            break;
        } else {
            trieNodeIndex = nodeChildren[letterIndex].index;
        }
    }
    return present;
}

int Trie::getCubeIndex(std::string &cubeString) {
    int trieNodeIndex = 0;
    int letterIndex;
    for (char letter : cubeString) {
        std::vector<TrieNode> &nodeChildren = treeChildren[trieNodeIndex];
        letterIndex = findLetter(nodeChildren, letter);
        if (letterIndex == -1) {
            return -1;
        } else {
            trieNodeIndex = nodeChildren[letterIndex].index;
        }
    }
    return trieNodeIndex;
}

int Trie::getNumMoves(std::string &cubeString) {
    int trieNodeIndex = 0;
    int letterIndex;
    for (char letter : cubeString) {
        std::vector<TrieNode> &nodeChildren = treeChildren[trieNodeIndex];
        letterIndex = findLetter(nodeChildren, letter);
        if (letterIndex == -1) {
            return -1;
        } else {
            trieNodeIndex = nodeChildren[letterIndex].index;
        }
    }
    return cubeStateData[trieNodeIndex].numMoves;
}

int Trie::getNumMoves(int trieNodeIndex) {
    return cubeStateData[trieNodeIndex].numMoves;
}

int Trie::getParentIndex(std::string &cubeString) {
    int trieNodeIndex = 0;
    int letterIndex;
    for (char letter : cubeString) {
        std::vector<TrieNode> &nodeChildren = treeChildren[trieNodeIndex];
        letterIndex = findLetter(nodeChildren, letter);
        if (letterIndex == -1) {
            return -1;
        } else {
            trieNodeIndex = nodeChildren[letterIndex].index;
        }
    }
    return cubeStateData[trieNodeIndex].parentIndex;
}

int Trie::getParentIndex(int cubeNodeIndex) {
    return cubeStateData[cubeNodeIndex].parentIndex;
}

std::string Trie::getLastMove(int cubeNodeIndex) {
    std::string move = "";
    
    //std::cout << (int)cubeStateData[cubeNodeIndex].lastMove << " ";
    
    move += cubeStateData[cubeNodeIndex].lastMove;
    
    if (cubeStateData[cubeNodeIndex].isClockwise){
        move += ' ';
    } else {
        move += '\'';
    }
    return move;
}

int Trie::findLetter(std::vector<TrieNode> &nodeChildren, char letter) {
    int trieNodeIndex = -1;
    for (int i = 0; i < nodeChildren.size(); i++) {
        if (nodeChildren[i].letter == letter){
            trieNodeIndex = i;
            break;
        }
    }
    return trieNodeIndex;
}

int Trie::insertTrieNode(std::vector<TrieNode> &nodeChildren, char letter) {
    nodeChildren.push_back(TrieNode(letter, trieNodeCount));
    treeChildren.push_back(std::vector<TrieNode>());
    trieNodeCount++;
    return trieNodeCount-1;
}

#endif //Trie_h
