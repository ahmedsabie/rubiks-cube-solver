#include "RubiksCubeSolver.h"
#include <emscripten/bind.h>

using namespace emscripten;

std::string getMoves(std::string stringCube) {
	char cube[6][3][3];
	int index = 0;

	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				cube[i][j][k] = stringCube[index++];
			}
		}
	}

    RubiksCubeSolver solved(cube);
    return solved.getPath();
}

EMSCRIPTEN_BINDINGS(my_module) {
    function("getMoves", &getMoves);
}
