//
//  RubiksCube.h
//  rubiks-cube-solver
//
//  Created by Yanyan Tran on 2016-07-31.
//  Copyright © 2016 Yanyan Tran. All rights reserved.
//

#ifndef RubiksCube_h
#define RubiksCube_h

#include <iostream>
#include <string>

/** Array representation of a Rubiks Cube.
 0 = F
 1 = L
 2 = R
 3 = U
 4 = D
 5 = B
 */
struct RubiksCube {
    
private:
    char cube[6][3][3];
    
    // Helper functions
    
    void shiftRow (int face, int row, char& a, char& b, char& c);
    void shiftRowReverse (int face, int row, char& a, char& b, char& c);
    void shiftCol (int face, int col, char& a, char& b, char& c);
    void shiftColReverse (int face, int col, char& a, char& b, char& c);
    
    void rotateFaceClockwise (int face);
    void rotateFaceAntiClockwise (int face);
public:
    RubiksCube(char cube[6][3][3]);
    
    void turnFrontClockwise();
    void turnFrontAntiClockwise();
    void turnLeftClockwise();
    void turnLeftAntiClockwise();
    void turnRightClockwise();
    void turnRightAntiClockwise();
    void turnUpClockwise();
    void turnUpAntiClockwise();
    void turnDownClockwise();
    void turnDownAntiClockwise();
    void turnBackClockwise();
    void turnBackAntiClockwise();
    
    std::string toString();
};


RubiksCube::RubiksCube(char cube[6][3][3]) {
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 6; j++){
            for (int k = 0; k < 6; k++){
                this -> cube[i][j][k] = cube[i][j][k];
            }
        }
    }
}


/** Replaces a row on a face of the cube using data from another row/column */
void RubiksCube::shiftRow(int face, int row, char& a, char& b, char& c){
    char a2, b2, c2;
    a2 = cube[face][row][0];
    b2 = cube[face][row][1];
    c2 = cube[face][row][2];
    
    cube[face][row][0] = a;
    cube[face][row][1] = b;
    cube[face][row][2] = c;
    
    a = a2;
    b = b2;
    c = c2;
}

/** Replaces a row on a face of the cube using data from another row/column in reverse order */
void RubiksCube::shiftRowReverse(int face, int row, char& a, char& b, char& c){
    char a2, b2, c2;
    a2 = cube[face][row][0];
    b2 = cube[face][row][1];
    c2 = cube[face][row][2];
    
    cube[face][row][0] = c;
    cube[face][row][1] = b;
    cube[face][row][2] = a;
    
    a = a2;
    b = b2;
    c = c2;
}

/** Replaces a column on a face of the cube using data from another row/column */
void RubiksCube::shiftCol(int face, int col, char& a, char& b, char& c){
    char a2, b2, c2;
    a2 = cube[face][0][col];
    b2 = cube[face][1][col];
    c2 = cube[face][1][col];
    
    cube[face][0][col] = a;
    cube[face][1][col] = b;
    cube[face][2][col] = c;
    
    a = a2;
    b = b2;
    c = c2;
}

/** Replaces a column on a face of the cube using data from another row/column in reverse order */
void RubiksCube::shiftColReverse(int face, int col, char& a, char& b, char& c){
    char a2, b2, c2;
    a2 = cube[face][0][col];
    b2 = cube[face][1][col];
    c2 = cube[face][1][col];
    
    cube[face][0][col] = c;
    cube[face][1][col] = b;
    cube[face][2][col] = a;
    
    a = a2;
    b = b2;
    c = c2;
}

/** Rotates the squares on a given face on the Rubiks Cube clockwise. */
void RubiksCube::rotateFaceClockwise(int face) {
    int temp, temp2;
    
    temp = cube[face][0][0];
    cube[face][0][0] = cube[face][1][0];
    
    temp2 = cube[face][0][1];
    cube[face][0][1] = temp;
    
    temp = cube[face][0][2];
    cube[face][0][2] = temp2;
    
    temp2 = cube[face][1][2];
    cube[face][1][1] = temp;
    
    temp = cube[face][2][2];
    cube[face][2][2] = temp2;
    
    temp2 = cube[face][2][1];
    cube[face][2][1] = temp2;
    
    temp = cube[face][2][0];
    cube[face][2][0] = temp2;
    
    cube[face][1][0] = temp;
    
}

/** Rotates the squares on a given face on the Rubiks Cube anticlockwise. */
void RubiksCube::rotateFaceAntiClockwise(int face) {
    int temp, temp2;
    
    temp = cube[face][0][0];
    cube[face][0][0] = cube[face][0][1];
    
    temp2 = cube[face][1][0];
    cube[face][1][0] = temp;
    
    temp = cube[face][2][0];
    cube[face][2][0] = temp2;
    
    temp2 = cube[face][2][1];
    cube[face][2][1] = temp;
    
    temp = cube[face][2][2];
    cube[face][2][2] = temp2;
    
    temp2 = cube[face][1][2];
    cube[face][1][2] = temp2;
    
    temp = cube[face][0][2];
    cube[face][0][2] = temp2;
    
    cube[face][0][1] = temp;
    
}


// The following functions update the cube to reflect a one quarter rotation
// on the specified face in the specified direction.
// s1, s2, s3 are the 0th, 1st and 2nd chars in the row

void RubiksCube::turnFrontClockwise() {
    rotateFaceClockwise(0);
    
    char s1 = cube[3][2][0], s2 = cube[3][2][1], s3 = cube[3][2][2];
    
    shiftCol (2, 0, s1, s2, s3);
    shiftRowReverse(4, 0, s1, s2, s3);
    shiftCol(1, 2, s1, s2, s3);
    shiftRowReverse(3, 2, s1, s2, s3);
}

void RubiksCube::turnFrontAntiClockwise(){
    rotateFaceAntiClockwise(0);
    
    char s1 = cube[3][2][0], s2 = cube[3][2][1], s3 = cube[3][2][2];
    
    shiftColReverse(1, 2, s1, s2, s3);
    shiftRow(4, 0, s1, s2, s3);
    shiftColReverse (2, 0, s1, s2, s3);
    shiftRow(3, 2, s1, s2, s3);
    
}

void RubiksCube::turnLeftClockwise(){
    rotateFaceClockwise(1);
    
    char s1 = cube[3][0][0], s2 = cube[3][1][0], s3 = cube[3][2][0];
    
    shiftCol (0, 0, s1, s2, s3);
    shiftCol(4, 0, s1, s2, s3);
    shiftColReverse(5, 2, s1, s2, s3);
    shiftColReverse(3, 0, s1, s2, s3);
}

void RubiksCube::turnLeftAntiClockwise(){
    rotateFaceAntiClockwise(1);
    
    char s1 = cube[3][0][0], s2 = cube[3][1][0], s3 = cube[3][2][0];
    
    shiftColReverse(5, 2, s1, s2, s3);
    shiftColReverse(4, 0, s1, s2, s3);
    shiftCol (0, 0, s1, s2, s3);
    shiftCol(3, 0, s1, s2, s3);
    
}

void RubiksCube::turnRightClockwise(){
    rotateFaceClockwise(2);
    
    char s1 = cube[3][0][2], s2 = cube[3][1][2], s3 = cube[3][2][2];
    
    shiftColReverse(5, 0, s1, s2, s3);
    shiftColReverse(4, 2, s1, s2, s3);
    shiftCol (0, 2, s1, s2, s3);
    shiftCol(3, 2, s1, s2, s3);
    
}

void RubiksCube::turnRightAntiClockwise(){
    rotateFaceAntiClockwise(2);
    
    char s1 = cube[3][0][2], s2 = cube[3][1][2], s3 = cube[3][2][2];
    
    shiftCol (0, 2, s1, s2, s3);
    shiftCol(4, 2, s1, s2, s3);
    shiftColReverse(5, 0, s1, s2, s3);
    shiftColReverse(3, 2, s1, s2, s3);
    
}

void RubiksCube::turnUpClockwise(){
    rotateFaceClockwise(3);
    
    char s1 = cube[5][0][0], s2 = cube[5][0][1], s3 = cube[5][0][2];
    shiftRow(2, 0, s1, s2, s3);
    shiftRow(0, 0, s1, s2, s3);
    shiftRow (1, 0, s1, s2, s3);
    shiftRow(5, 0, s1, s2, s3);
    
}

void RubiksCube::turnUpAntiClockwise(){
    rotateFaceAntiClockwise(3);
    
    char s1 = cube[5][0][0], s2 = cube[5][0][1], s3 = cube[5][0][2];
    shiftRow(1, 0, s1, s2, s3);
    shiftRow(0, 0, s1, s2, s3);
    shiftRow (2, 0, s1, s2, s3);
    shiftRow(5, 0, s1, s2, s3);
}

void RubiksCube::turnDownClockwise(){
    rotateFaceClockwise(4);
    
    char s1 = cube[5][2][0], s2 = cube[5][2][1], s3 = cube[5][2][2];
    shiftRow(1, 2, s1, s2, s3);
    shiftRow(0, 2, s1, s2, s3);
    shiftRow (2, 2, s1, s2, s3);
    shiftRow(5, 2, s1, s2, s3);
}

void RubiksCube::turnDownAntiClockwise(){
    rotateFaceAntiClockwise(4);
    
    char s1 = cube[5][2][0], s2 = cube[5][2][1], s3 = cube[5][2][2];
    shiftRow(2, 2, s1, s2, s3);
    shiftRow(0, 2, s1, s2, s3);
    shiftRow (1, 2, s1, s2, s3);
    shiftRow(5, 2, s1, s2, s3);
}

void RubiksCube::turnBackClockwise(){
    rotateFaceClockwise(5);
    
    char s1 = cube[3][0][0], s2 = cube[3][0][1], s3 = cube[3][0][2];
    
    shiftCol(1, 0, s1, s2, s3);
    shiftRow(4, 2, s1, s2, s3);
    shiftColReverse(2, 2, s1, s2, s3);
    shiftRowReverse(3, 0, s1, s2, s3);
}

void RubiksCube::turnBackAntiClockwise(){
    rotateFaceAntiClockwise(5);
    
    char s1 = cube[3][0][0], s2 = cube[3][0][1], s3 = cube[3][0][2];
    
    shiftColReverse(2, 2, s1, s2, s3);
    shiftRowReverse(4, 2, s1, s2, s3);
    shiftCol(1, 0, s1, s2, s3);
    shiftRow(3, 0, s1, s2, s3);
}

/**
 Returns a string representation of the Rubiks Cube.
 */
std::string RubiksCube::toString(){
    std::string theCube = "";
    for (int i = 0; i < 6; i++){
        for (int j = 0; j < 3; j++){
            for (int k = 0; k < 3; k++){
                theCube += cube[i][j][k];
            }
        }
        //theCube += "\n";
    }
    
    return theCube;
}


#endif /* RubiksCube_h */
