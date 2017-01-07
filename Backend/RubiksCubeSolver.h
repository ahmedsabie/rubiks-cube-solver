#ifndef RubiksCubeSolver_h
#define RubiksCubeSolver_h

#include <iostream>
#include <queue>
#include <algorithm>
#include "Trie.h"
#include "RubiksCube.h"

struct RubiksCubeSolver {
    
private:
    char solvedCubeArray[6][3][3] = {
        {
            {
                'R','R','R',
            },
            {
                'R','R','R',
            },
            {
                'R','R','R',
            },
        },
        {
            {
                'G','G','G',
            },
            {
                'G','G','G',
            },
            {
                'G','G','G',
            },
        },
        {
            {
                'B','B','B',
            },
            {
                'B','B','B',
            },
            {
                'B','B','B',
            },
        },
        {
            {
                'W','W','W',
            },
            {
                'W','W','W',
            },
            {
                'W','W','W',
            },
        },
        {
            {
                'Y','Y','Y',
            },
            {
                'Y','Y','Y',
            },
            {
                'Y','Y','Y',
            },
        },
        {
            {
                'O','O','O',
            },
            {
                'O','O','O',
            },
            {
                'O','O','O',
            },
        },
    };
    RubiksCube cube;
    RubiksCube solvedState;
    const int MAX_MOVES = 26;
    
    int bidirectionalBFS();
    
    void tryLeftClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                              RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryLeftAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                  RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryRightClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                               RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryRightAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                   RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryFrontClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                               RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryFrontAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                   RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryBackClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                              RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryBackAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                  RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryUpClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                            RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryUpAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryDownClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                              RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    void tryDownAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                  RubiksCube &currentCube, int moves, int currentCubeIndex);
    
    std::string fwdPath, bkwdPath;
    std::string retraceHalfPath (Trie &cubesSeen, std::string &currentCubeString);
    
public:
    RubiksCubeSolver(char cube[6][3][3]);
    int findMinNumberOfMoves();
    std::string getPath();
};




RubiksCubeSolver::RubiksCubeSolver(char cube[6][3][3]) {
    this -> cube = RubiksCube(cube);
    solvedState = RubiksCube(solvedCubeArray);
    fwdPath = "";
    bkwdPath = "";
    
}

int RubiksCubeSolver::findMinNumberOfMoves() {
    return bidirectionalBFS();
}


int RubiksCubeSolver::bidirectionalBFS() {
    Trie cubesSeenFwd, cubesSeenBkwd;
    std::queue<std::pair<RubiksCube,int> > activeCubesFwd, activeCubesBkwd;
    
    std::string cubeString = cube.toString();
    std::string solvedStateCubeString = solvedState.toString();
    
    int trieNodeIndex = cubesSeenFwd.insertCube(cubeString, 0, 0, true, -1);
    activeCubesFwd.push(std::make_pair(cube, trieNodeIndex));
    
    trieNodeIndex = cubesSeenBkwd.insertCube(solvedStateCubeString, 0, 0, true, -1);
    activeCubesBkwd.push(std::make_pair(solvedState, trieNodeIndex));
    
    int currentCubeIndex, movesFwd, movesBkwd;
    RubiksCube currentCube, nextCube;
    std::string currentCubeString;
    
    int ans = -1;
    
    while (!activeCubesFwd.empty() && !activeCubesBkwd.empty())
    {
        currentCube = activeCubesFwd.front().first;
        currentCubeIndex = activeCubesFwd.front().second;
        activeCubesFwd.pop();
        
        movesFwd = cubesSeenFwd.getNumMoves(currentCubeIndex);
        
        //std::cout << currentCube.toString() << std::endl;
        
        if (movesFwd < MAX_MOVES / 2) {
            
            tryLeftClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryLeftAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryRightClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryRightAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryFrontClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryFrontAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryBackClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryBackAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryUpClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryUpAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryDownClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
            
            tryDownAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd, currentCubeIndex);
        }
        
        //std::cout << currentCube.toString() << std::endl;
        
        currentCubeString = currentCube.toString();
        
        if (cubesSeenBkwd.isCubePresent(currentCubeString)) {
            movesBkwd = cubesSeenBkwd.getNumMoves(currentCubeString);
            ans = movesFwd + movesBkwd;
            break;
        }
        
        
        
        currentCube = activeCubesBkwd.front().first;
        currentCubeIndex = activeCubesBkwd.front().second;
        activeCubesBkwd.pop();
        
        movesBkwd = cubesSeenBkwd.getNumMoves(currentCubeIndex);
        
        
        if (movesBkwd < MAX_MOVES / 2) {
            
            tryLeftClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryLeftAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryRightClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryRightAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryFrontClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryFrontAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryBackClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryBackAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryUpClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryUpAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryDownClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
            
            tryDownAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd, currentCubeIndex);
        }
        
        currentCubeString = currentCube.toString();
        
        
        if (cubesSeenFwd.isCubePresent(currentCubeString)) {
            movesFwd = cubesSeenFwd.getNumMoves(currentCubeString);
            ans = movesFwd + movesBkwd;
            break;
        }
    }
    
    fwdPath = retraceHalfPath(cubesSeenFwd, currentCubeString);
    //std::cout << fwdPath << std::endl;
    bkwdPath = retraceHalfPath(cubesSeenBkwd, currentCubeString);
    //std::cout << bkwdPath << std::endl;
    
    return ans;
}

std::string RubiksCubeSolver::retraceHalfPath(Trie &cubesSeen, std::string &currentCubeString) {
    int currentCubeIndex = cubesSeen.getCubeIndex(currentCubeString);
    
    std::string halfPath = "";
    
    while (currentCubeIndex != -1) {
        halfPath.append(cubesSeen.getLastMove(currentCubeIndex));
        //std::cout << halfPath << " " << currentCubeIndex << std::endl;
        
        currentCubeIndex = cubesSeen.getParentIndex(currentCubeIndex);
    }
    
    return halfPath;
}

std::string RubiksCubeSolver::getPath() {
	findMinNumberOfMoves();
	
    std::string newFwdPath = "", newBkwdPath = "";
    
    // reverse order of fwdPath
    reverse(fwdPath.begin(), fwdPath.end());
    
    // skip nonexistent move of initial cube
    for (int i = 2; i < (int)fwdPath.size(); i+=2){
        newFwdPath += fwdPath[i+1];
        newFwdPath += fwdPath[i];
    }
    
    //std::cout << newFwdPath << std::endl;
    
    // use opposite moves of bkwdPath
    for (int i = 0; i < (int)bkwdPath.size()-2; i+=2){
        newBkwdPath += bkwdPath[i];
        
        if (bkwdPath[i+1] == ' '){
            newBkwdPath += '\'';
        } else {
            newBkwdPath += ' ';
        }
    }
    
    //std::cout << newBkwdPath << std::endl;

    // return concatenation of fwdPath and bkwdPath
    return newFwdPath.append(newBkwdPath);
}

void RubiksCubeSolver::tryLeftClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                            RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnLeftClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'L', true, currentCubeIndex); 
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryLeftAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnLeftAntiClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'L', false, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryRightClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                             RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnRightClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'R', true, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryRightAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                 RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnRightAntiClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'R', false, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryFrontClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                             RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnFrontClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'F', true, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryFrontAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                 RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnFrontAntiClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'F', false, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryBackClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                            RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnBackClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'B', true, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryBackAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnBackAntiClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'B', false, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryUpClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                          RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnUpClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'U', true, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryUpAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                              RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnUpAntiClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'U', false, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryDownClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                            RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnDownClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'D', true, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

void RubiksCubeSolver::tryDownAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                RubiksCube &currentCube, int moves, int currentCubeIndex) {
    int nextCubeIndex;
    
    RubiksCube nextCube = currentCube;
    
    nextCube.turnDownAntiClockwise();
    
    std::string cubeString = nextCube.toString();
    
    if (!cubesSeen.isCubePresent(cubeString)) {
        nextCubeIndex = cubesSeen.insertCube(cubeString, moves+1, 'D', false, currentCubeIndex);
        activeCubes.push(std::make_pair(nextCube, nextCubeIndex));
    }
}

#endif //RubiksCubeSolver_h