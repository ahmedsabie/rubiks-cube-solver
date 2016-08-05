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

    int bidirectionalBFS();

    void tryLeftClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                              RubiksCube &currentCube, int &moves);

    void tryLeftAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                  RubiksCube &currentCube, int &moves);

    void tryRightClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                               RubiksCube &currentCube, int &moves);

    void tryRightAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                   RubiksCube &currentCube, int &moves);

    void tryFrontClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                               RubiksCube &currentCube, int &moves);

    void tryFrontAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                   RubiksCube &currentCube, int &moves);

    void tryBackClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                              RubiksCube &currentCube, int &moves);

    void tryBackAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                  RubiksCube &currentCube, int &moves);

    void tryUpClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                            RubiksCube &currentCube, int &moves);

    void tryUpAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                RubiksCube &currentCube, int &moves);

    void tryDownClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                              RubiksCube &currentCube, int &moves);

    void tryDownAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                  RubiksCube &currentCube, int &moves);

public:
    RubiksCubeSolver(RubiksCube cube);
    int findMinNumberOfMoves();

};




RubiksCubeSolver::RubiksCubeSolver(RubiksCube cube) {
    this -> cube = cube;
    solvedState = RubiksCube(solvedCubeArray);

}

int RubiksCubeSolver::findMinNumberOfMoves() {
    return bidirectionalBFS();
}


int RubiksCubeSolver::bidirectionalBFS() {
    Trie cubesSeenFwd, cubesSeenBkwd;
    std::queue<std::pair<RubiksCube,int> > activeCubesFwd, activeCubesBkwd;

    cubesSeenFwd.insertString(cube.toString(), 0);
    activeCubesFwd.push(std::make_pair(cube, 0));

    cubesSeenBkwd.insertString(solvedState.toString(), 0);
    activeCubesBkwd.push(std::make_pair(solvedState, 0));

    int movesFwd, movesBkwd;
    RubiksCube currentCube, nextCube;

    int ans = -1;

    while (!activeCubesFwd.empty() && !activeCubesBkwd.empty())
    {
        currentCube = activeCubesFwd.front().first;
        movesFwd = activeCubesFwd.front().second;
        activeCubesFwd.pop();


        if (movesFwd < MAX_MOVES / 2) {

            tryLeftClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryLeftAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryRightClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryRightAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryFrontClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryFrontAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryBackClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryBackAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryUpClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryUpAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryDownClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);

            tryDownAntiClockwiseTurn(cubesSeenFwd, activeCubesFwd, currentCube, movesFwd);
        }


        if (cubesSeenBkwd.isStringPresent(currentCube.toString())) {
            movesBkwd = cubesSeenBkwd.getNumMoves(currentCube.toString());
            ans = movesFwd + movesBkwd;
            break;
        }



        currentCube = activeCubesBkwd.front().first;
        movesBkwd = activeCubesBkwd.front().second;
        activeCubesBkwd.pop();

        if (movesBkwd < MAX_MOVES / 2) {

            tryLeftClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryLeftAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryRightClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryRightAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryFrontClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryFrontAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryBackClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryBackAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryUpClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryUpAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryDownClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);

            tryDownAntiClockwiseTurn(cubesSeenBkwd, activeCubesBkwd, currentCube, movesBkwd);
        }
        
        
        if (cubesSeenFwd.isStringPresent(currentCube.toString())) {
            movesFwd = cubesSeenFwd.getNumMoves(currentCube.toString());
            ans = movesFwd + movesBkwd;
            break;
        }
    }
    return ans;
}

void RubiksCubeSolver::tryLeftClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                            RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnLeftClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryLeftAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnLeftAntiClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryRightClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                             RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnRightClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryRightAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                 RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnRightAntiClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryFrontClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                             RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnFrontClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryFrontAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                 RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnFrontAntiClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryBackClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                            RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnBackClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryBackAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnBackAntiClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryUpClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                          RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnUpClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryUpAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                              RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnUpAntiClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryDownClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                            RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnDownClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}

void RubiksCubeSolver::tryDownAntiClockwiseTurn(Trie &cubesSeen, std::queue<std::pair<RubiksCube,int> > &activeCubes,
                                                RubiksCube &currentCube, int &moves) {
    RubiksCube nextCube = currentCube;

    nextCube.turnDownAntiClockwise();

    std::string cubeString = nextCube.toString();

    if (!cubesSeen.isStringPresent(cubeString)) {
        cubesSeen.insertString(cubeString, moves+1);
        activeCubes.push(std::make_pair(nextCube, moves+1));
    }
}
