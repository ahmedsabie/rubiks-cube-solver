#include "RubiksCubeSolver.h"
#include <iostream>
using namespace std;
//#include <emscripten/bind.h>

//using namespace emscripten;

std::string getMoves(std::string stringCube, std::string centerColors) {
	char cube[6][3][3];
	int index = 0;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cube[i][j][k] = stringCube[index++];
			}
		}
	}

    RubiksCubeSolver solved(cube, centerColors);
    return solved.getPath();
}

/*EMSCRIPTEN_BINDINGS(my_module) {
    function("getMoves", &getMoves);
}*/
int main() {
    std::string c = "RRRRRRRRRGGGGGGGGGBBBBBBBBBOOOOOOOOOWWWWWWWWWYYYYYYYYY";
    string k = "RGBOWY";
    cout<<getMoves(c, k)<<endl;
}
