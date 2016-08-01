#include <iostream>
#include <queue>
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


public:

    RubiksCubeSolver(RubiksCube cube) {
        this -> cube = cube;
        solvedState = RubiksCube(solvedCubeArray);

    }

    int findNumberMoves() {
        Trie cubesSeenFwd = BFSForwards();
        Trie cubesSeenBkwd = BFSBackwards();
        return matchTries(cubesSeenFwd, cubesSeenBkwd, 0, 0);
    }
    int matchTries(Trie &cubesSeenFwd, Trie &cubesSeenBkwd, int nodeIndexFwd, int nodeIndexBkwd) {
        int best = MAX_MOVES + 1;
        std::unordered_map<int,int> &numMovesFwd = cubesSeenFwd.numMoves;
        std::unordered_map<int,int> &numMovesBkwd = cubesSeenBkwd.numMoves;
        if (numMovesFwd.find(nodeIndexFwd) != numMovesFwd.end() &&
            numMovesBkwd.find(nodeIndexBkwd) != numMovesBkwd.end())
        {
            best = std::min(best, numMovesFwd[nodeIndexFwd] + numMovesBkwd[nodeIndexBkwd]);
        }
        std::vector<Node> &treeChildrenFwd = cubesSeenFwd.treeChildren[nodeIndexFwd];
        std::vector<Node> &treeChildrenBkwd = cubesSeenBkwd.treeChildren[nodeIndexBkwd];
        for (int i = 0; i < treeChildrenFwd.size(); i++) {
            for (int j = 0; j < treeChildrenBkwd.size(); j++) {
                if (treeChildrenFwd[i].letter == treeChildrenBkwd[j].letter) {
                    best = std::min(best, matchTries(cubesSeenFwd, cubesSeenBkwd, treeChildrenFwd[i].index, treeChildrenBkwd[i].index));
                }
            }
        }
    }

    Trie BFSForwards() {

        Trie cubesSeenFwd;
        std::queue<std::pair<RubiksCube,int> > activeCubes;
        cubesSeenFwd.insertString(cube.toString(), 0);
        activeCubes.push(std::make_pair(cube, 0));

        int moves;
        RubiksCube currentCube, nextCube;
        std::string cubeString;

        while (!activeCubes.empty())
        {
            currentCube = activeCubes.front().first;
            moves = activeCubes.front().second;
            activeCubes.pop();

            if (moves <= MAX_MOVES / 2) {

                tryLeftClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryLeftAntiClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryRightClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryRightAntiClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryFrontClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryFrontAntiClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryBackClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryBackAntiClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryUpClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryUpAntiClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryDownClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
                tryDownAntiClockwiseTurn(cubesSeenFwd, activeCubes, currentCube, moves);
            }
        }
        return cubesSeenFwd;
    }
    Trie BFSBackwards() {

        Trie cubesSeenBkwd;
        std::queue<std::pair<RubiksCube,int> > activeCubes;
        cubesSeenBkwd.insertString(solvedState.toString(), 0);
        activeCubes.push(std::make_pair(solvedState, 0));

        int moves;
        RubiksCube currentCube, nextCube;
        std::string cubeString;

        while (!activeCubes.empty())
        {
            currentCube = activeCubes.front().first;
            moves = activeCubes.front().second;
            activeCubes.pop();

            if (moves <= MAX_MOVES / 2) {

                tryLeftClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryLeftAntiClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryRightClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryRightAntiClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryFrontClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryFrontAntiClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryBackClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryBackAntiClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryUpClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryUpAntiClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryDownClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
                tryDownAntiClockwiseTurn(cubesSeenBkwd, activeCubes, currentCube, moves);
            }
        }
        return cubesSeenBkwd;
    }

    void tryLeftClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnLeftClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryLeftAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnLeftAntiClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryRightClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnRightClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryRightAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnRightAntiClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryFrontClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnFrontClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryFrontAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnFrontAntiClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryBackClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnBackClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryBackAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnBackAntiClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryUpClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnUpClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryUpAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnUpAntiClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryDownClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnDownClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }
    void tryDownAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes, RubiksCube &currentCube, int &moves) {
        RubiksCube nextCube = currentCube;

        nextCube.turnDownAntiClockwise();

        std::string cubeString = nextCube.toString();

        if (!cubesSeen.isStringPresent(cubeString)) {
            cubesSeen.insertString(cubeString, moves+1);
            activeCubes.push(std::make_pair(nextCube, moves+1));
        }
    }

};
