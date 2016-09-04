//Faces : 0 = Front, 1 = Left, 2 = Right, 3 = Up, 4 = Down, 5 = Back

faces = ["front", "left", "right", "up", "down", "back"];
rows = ["top", "middle", "bottom"];
cols = ["left", "middle", "right"];

//these arrays map each face to the actual index value
faceToId = {"F" : 0, "L" : 1, "R" : 2, "U" : 3, "D" : 4, "B" : 5};
rowToId = {"T" : 0, "M" : 1, "B" : 2};
colToId = {"L" : 0, "M" : 1, "R" : 2};

faceRotations = ["rotateY(0deg)", "rotateY(-90deg)", "rotateY(90deg)", "rotateX(90deg)", "rotateX(-90deg)", "rotateY(180deg)"];

//a cubelet in the 2 following 3D arrays is accessed as [face][row][col]
cubeletIds = [];
cubeletTransformStrs = [];

setUpCubeletInfo();
assignTransformStrs();



/*generates the styles.css cubelet ids, and their default transforms

the transform strings are stored in javascript rather than accessed
with getComputedStyle as the latter returns the matrix3d representation, 
rather than the rotates and translates only of the CSS*/

function setUpCubeletInfo() {
	var translateZ = 150;

	for (var i = 0; i < faces.length; i++) {
		var faceIds = [];
		var faceStrs = [];
		var translateY = 0;
		for (var j = 0; j < rows.length; j++) {
			var rowIds = [];
			var rowStrs = [];
			var translateX = 0;
			for (var k = 0; k < cols.length; k++) {
				var cubeletId = faces[i] + "-face-" + rows[j] + "-row-" + cols[k] + "-col";
				rowIds.push(cubeletId);

				var transformStr = faceRotations[i] + " translate3d(" + translateX + "px, " + translateY + "px, " + translateZ + "px)";
				rowStrs.push(transformStr);

				translateX += 100;
			}
			faceIds.push(rowIds);
			faceStrs.push(rowStrs)

			translateY += 100;
		}
		cubeletIds.push(faceIds);
		cubeletTransformStrs.push(faceStrs);
	}
}

function assignTransformStrs() {
	for (var i = 0; i < cubeletIds.length; i++) {
		for (var j = 0; j < cubeletIds[i].length; j++) {
			for (var k = 0; k < cubeletIds[i][j].length; k++) {
				var element = document.getElementById(cubeletIds[i][j][k]);
				element.style.transform = cubeletTransformStrs[i][j][k];
			}
		}
	}
}

function rotateFrontFace(isClockwise) {
	rotateFace("F", "Z", isClockwise);

	rotateRow("U", "B", "Z", isClockwise);
	rotateRow("D", "T", "Z", isClockwise);
	rotateCol("L", "R", "Z", isClockwise);
	rotateCol("R", "L", "Z", isClockwise);

}

function rotateBackFace(isClockwise) {
	isClockwise = !isClockwise;
	rotateFace("B", "Z", isClockwise);

	rotateRow("U", "T", "Z", isClockwise);
	rotateRow("D", "B", "Z", isClockwise);
	rotateCol("L", "L", "Z", isClockwise);
	rotateCol("R", "R", "Z", isClockwise);

}

function rotateLeftFace(isClockwise) {
	isClockwise = !isClockwise;
	rotateFace("L", "X", isClockwise);

	rotateCol("U", "L", "X", isClockwise);
	rotateCol("B", "R", "X", isClockwise);
	rotateCol("D", "L", "X", isClockwise);
	rotateCol("F", "L", "X", isClockwise);

}

function rotateRightFace(isClockwise) {
	rotateFace("R", "X", isClockwise);

	rotateCol("U", "R", "X", isClockwise);
	rotateCol("B", "L", "X", isClockwise);
	rotateCol("D", "R", "X", isClockwise);
	rotateCol("F", "R", "X", isClockwise);

}

function rotateUpFace(isClockwise) {
	isClockwise = !isClockwise;
	rotateFace("U", "Y", isClockwise);

	rotateRow("L", "T", "Y", isClockwise);
	rotateRow("F", "T", "Y", isClockwise);
	rotateRow("R", "T", "Y", isClockwise);
	rotateRow("B", "T", "Y", isClockwise);

}

function rotateDownFace(isClockwise) {
	rotateFace("D", "Y", isClockwise);

	rotateRow("L", "B", "Y", isClockwise);
	rotateRow("F", "B", "Y", isClockwise);
	rotateRow("R", "B", "Y", isClockwise);
	rotateRow("B", "B", "Y", isClockwise);

}

/*dimension in all the following functions must be given as
"X", "Y", or "Z" */

function rotateFace(face, dimension, isClockwise) {
	var faceId = faceToId[face];
	for (var i = 0; i < cubeletIds[faceId].length; i++) {
		for (var j = 0; j < cubeletIds[faceId][i].length; j++) {
			rotateCubelet(faceId, i, j, dimension, 90, isClockwise);
		}
	}
}

function rotateRow(face, row, dimension, isClockwise) {
	var faceId = faceToId[face];
	var rowId = rowToId[row];
	for (var i = 0; i < cubeletIds[faceId][rowId].length; i++) {
		rotateCubelet(faceId, rowId, i, dimension, 90, isClockwise);
	}
}

function rotateCol(face, col, dimension, isClockwise) {
	var faceId = faceToId[face];
	var colId = colToId[col];
	for (var i = 0; i < cubeletIds[faceId].length; i++) {
		rotateCubelet(faceId, i, colId, dimension, 90, isClockwise);
	}
}

/*rotates the cubelet with face id i, row id j, and col id k,
across the dimension*/

function rotateCubelet(i, j, k, dimension, degrees, isClockwise) {
	var unitDegree;
	if (isClockwise) {
		unitDegree = 1;
	} else {
		unitDegree = -1;
	}

	if (degrees > 0) {
		var element = document.getElementById(cubeletIds[i][j][k]);

		var newTransformStr = addDegrees(cubeletTransformStrs[i][j][k], dimension, unitDegree);

		cubeletTransformStrs[i][j][k] = newTransformStr;

		element.offsetHeight;
		element.style.transform = newTransformStr;

		setTimeout(function (){
			rotateCubelet(i, j, k, dimension, degrees - 1, isClockwise)
		}, 10);
	}
}

/*extracts the rotate property of the corresponding dimension in a
transform string, and shifts it by the new angle*/
function addDegrees(transformStr, dimension, degrees) {
	var rotateProperty = "rotate" + dimension;

    var startIndex = transformStr.indexOf(rotateProperty);

	if (startIndex === -1) {
		//rotate property for the dimension has not been assigned before
		transformStr = rotateProperty + "(" + degrees + "deg) " + transformStr;
	} else {
		var endIndex = startIndex + 8;
		var currentAngle = "";
		var negative = false;
		if (transformStr[endIndex] === '-') {
			negative = true;
			endIndex++;
		}
		while ('0' <= transformStr[endIndex] && transformStr[endIndex] <= '9') {
			currentAngle += transformStr[endIndex];
			endIndex++;
		}
		currentAngle = parseInt(currentAngle);

		if (negative) {
			currentAngle = -currentAngle;
		}

		transformStr = transformStr.substring(0,startIndex) + 
		rotateProperty + "(" + (currentAngle + degrees) + "deg)" +
		transformStr.substring(endIndex+4);
	}
	return transformStr;
}
