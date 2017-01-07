//Note that a cubelet refers to one side (one color) of a single cube in the rubiks cube

//Faces : 0 = Front, 1 = Left, 2 = Right, 3 = Up, 4 = Down, 5 = Back
//Rows : 0 = Top, 1 = Middle, 2 = Bottom
//Cols : 0 = Left, 1 = Middle, 2 = Right
faces = ["front", "left", "right", "up", "down", "back"];
rows = ["top", "middle", "bottom"];
cols = ["left", "middle", "right"];

//these arrays map each face to the actual index value
faceToId = {"F" : 0, "L" : 1, "R" : 2, "U" : 3, "D" : 4, "B" : 5};
rowToId = {"T" : 0, "M" : 1, "B" : 2};
colToId = {"L" : 0, "M" : 1, "R" : 2};

//The initial orientation of each face
faceRotations = ["rotateY(0deg)", "rotateY(-90deg)", "rotateY(90deg)", "rotateX(90deg)", "rotateX(-90deg)", "rotateY(180deg)"];

//The delay in milliseconds for a 1 degree rotation in a cubelet to occur
CUBELET_DELAY_MS = 8;

//constructors for the Cubelet class

//id is the html id of the cubelet, and transform is the current transformation style string 
//of the cubelet
function Cubelet() {
  this.id = null;
  this.transform = null;
}
function Cubelet(id, transformStr) {
  this.id = id;
  this.transform = transformStr;
}

//cubelets will be stored in this 3D array, with the 3 indices representing face, row, and col respectively
cubelets = [];

function mainAnimation(colorArray) {
  addEventListeners();
  setUpCubeletInfo();
  assignTransformStrs();
  colorCube(colorArray);
}


//keeps track of the (x,y) position of the cursor while it is being held down,
//set to (-1,-1) when the cursor is not held down
x = y = -1;

//current orientation of the WHOLE cube
cubeOrientation = "rotateY(30deg)";



function addEventListeners() {

  document.addEventListener("mousedown", function(event) {
    x = event.clientX;
    y = event.clientY;
  });

  document.addEventListener("mouseup", function(event) {
    x = y = -1;
  });

  document.addEventListener("mousemove", function(event) {

    //mouse is presssed down
    if (x != -1 && y != -1) {

      var newX, newY, deltaX, deltaY;

      newX = event.clientX;
      newY = event.clientY;
      
      deltaX = newX - x;
      deltaY = newY - y;

      if (deltaX > 0) {
        rotateCube("Y", true);
      } else if (deltaX < 0) {
        rotateCube("Y", false);
      }

      if (deltaY > 0) {
        rotateCube("X", false);
      } else if (deltaY < 0) {
        rotateCube("X", true);
      }

      x = newX;
      y = newY;

    }

  });
}

/*generates the styles.css cubelet ids, and their default transforms

the transform strings are stored in javascript rather than being accessed
by getComputedStyle as the latter returns the matrix3d representation, 
which is difficult to work with */

function setUpCubeletInfo() {
  var translateZ = 150;

  for (var i = 0; i < faces.length; i++) {
    var faceCubelets = [];
    var translateY = 0;
    for (var j = 0; j < rows.length; j++) {
      var rowCubelets = [];
      var translateX = 0;
      for (var k = 0; k < cols.length; k++) {
        var cubeletId = faces[i] + "-face-" + rows[j] + "-row-" + cols[k] + "-col";
        var transformStr = faceRotations[i] + " translate3d(" + translateX + "px, " + translateY + "px, " + translateZ + "px)";

        var cubelet = new Cubelet(cubeletId, transformStr);

        rowCubelets.push(cubelet);

        translateX += 100;
      }
      faceCubelets.push(rowCubelets);

      translateY += 100;
    }
    cubelets.push(faceCubelets);
  }
}

//reassigns the original transformation strings (called after cubelets are swapped)
function updateCubeletInfo() {
  var translateZ = 150;

  for (var i = 0; i < faces.length; i++) {
    var translateY = 0;
    for (var j = 0; j < rows.length; j++) {
      var translateX = 0;
      for (var k = 0; k < cols.length; k++) {
        var transformStr = faceRotations[i] + " translate3d(" + translateX + "px, " + translateY + "px, " + translateZ + "px)";
        var cubelet = cubelets[i][j][k];

        cubelet.transform = transformStr;

        var element = document.getElementById(cubelet.id);
        element.offsetHeight;
        element.style.transform = transformStr;

        translateX += 100;
      }

      translateY += 100;
    }
  }
}

function assignTransformStrs() {
  for (var i = 0; i < cubelets.length; i++) {
    for (var j = 0; j < cubelets[i].length; j++) {
      for (var k = 0; k < cubelets[i][j].length; k++) {
        var element = document.getElementById(cubelets[i][j][k].id);
        element.style.transform = cubelets[i][j][k].transform;
      }
    }
  }
}

function colorCube(colorArray) {
  for (var i = 0; i < cubelets.length; i++) {
    for (var j = 0; j < cubelets[i].length; j++) {
      for (var k = 0; k < cubelets[i][j].length; k++) {
        var element = document.getElementById(cubelets[i][j][k].id);
        element.style.backgroundColor = colorArray[i][j][k];
      }
    }
  }
}


//rotates the whole cube across the dimension by one degree
function rotateCube(dimension, isClockwise) {

  var unitDegree;
  if (isClockwise) {
    unitDegree = 1;
  }
  else {
    unitDegree = -1;
  }

  var newTransformStr = addDegrees(cubeOrientation, dimension, unitDegree);

  cubeOrientation = newTransformStr;

  var element = document.getElementById("cube");
  element.offsetHeight;
  element.style.transform = newTransformStr;

}

function rotateFrontFace(isClockwise) {
  visualRotateFrontFace(isClockwise);

  //update the array after animation is done, hence the delay 
  setTimeout(function(){ 
    if (isClockwise) {
      arrayRotateFrontClockwise();
    } else {
      arrayRotateFrontAntiClockwise();
    }

    updateCubeletInfo();
  }, CUBELET_DELAY_MS*200);
  
}

function rotateBackFace(isClockwise) {
  visualRotateBackFace(!isClockwise);

  //update the array after animation is done, hence the delay 
  setTimeout(function(){ 
    if (isClockwise) {
      arrayRotateBackClockwise();
    } else {
      arrayRotateBackAntiClockwise();
    }

    updateCubeletInfo();
  }, CUBELET_DELAY_MS*200);
}

function rotateLeftFace(isClockwise) {
  visualRotateLeftFace(!isClockwise);

  //update the array after animation is done, hence the delay 
  setTimeout(function(){ 
    if (isClockwise) {
      arrayRotateLeftClockwise();
    } else {
      arrayRotateLeftAntiClockwise();
    }

    updateCubeletInfo();
  }, CUBELET_DELAY_MS*200);

}

function rotateRightFace(isClockwise) {
  visualRotateRightFace(isClockwise);

  //update the array after animation is done, hence the delay 
  setTimeout(function(){ 
    if (isClockwise) {
      arrayRotateRightClockwise();
    } else {
      arrayRotateRightAntiClockwise();
    }

    updateCubeletInfo();
  }, CUBELET_DELAY_MS*200);

}

function rotateUpFace(isClockwise) {
  visualRotateUpFace(!isClockwise);

  //update the array after animation is done, hence the delay 
  setTimeout(function(){ 
    if (isClockwise) {
      arrayRotateUpClockwise();
    } else {
      arrayRotateUpAntiClockwise();
    }

    updateCubeletInfo();
  }, CUBELET_DELAY_MS*200);

}

function rotateDownFace(isClockwise) {
  visualRotateDownFace(isClockwise);

  //update the array after animation is done, hence the delay 
  setTimeout(function(){ 
    if (isClockwise) {
      arrayRotateDownClockwise();
    } else {
      arrayRotateDownAntiClockwise();
    }

    updateCubeletInfo();
  }, CUBELET_DELAY_MS*200);

}

//all functions that start with "visual" change the cube's CSS code

function visualRotateFrontFace(isClockwise) {
  visualRotateFace("F", "Z", isClockwise);

  visualRotateRow("U", "B", "Z", isClockwise);
  visualRotateRow("D", "T", "Z", isClockwise);
  visualRotateCol("L", "R", "Z", isClockwise);
  visualRotateCol("R", "L", "Z", isClockwise);
}

function visualRotateBackFace(isClockwise) {
  visualRotateFace("B", "Z", isClockwise);

  visualRotateRow("U", "T", "Z", isClockwise);
  visualRotateRow("D", "B", "Z", isClockwise);
  visualRotateCol("L", "L", "Z", isClockwise);
  visualRotateCol("R", "R", "Z", isClockwise);
}

function visualRotateLeftFace(isClockwise) {
  visualRotateFace("L", "X", isClockwise);

  visualRotateCol("U", "L", "X", isClockwise);
  visualRotateCol("B", "R", "X", isClockwise);
  visualRotateCol("D", "L", "X", isClockwise);
  visualRotateCol("F", "L", "X", isClockwise);
}

function visualRotateRightFace(isClockwise) {
  visualRotateFace("R", "X", isClockwise);

  visualRotateCol("U", "R", "X", isClockwise);
  visualRotateCol("B", "L", "X", isClockwise);
  visualRotateCol("D", "R", "X", isClockwise);
  visualRotateCol("F", "R", "X", isClockwise);
}

function visualRotateUpFace(isClockwise) {
  visualRotateFace("U", "Y", isClockwise);

  visualRotateRow("L", "T", "Y", isClockwise);
  visualRotateRow("F", "T", "Y", isClockwise);
  visualRotateRow("R", "T", "Y", isClockwise);
  visualRotateRow("B", "T", "Y", isClockwise);
}

function visualRotateDownFace(isClockwise) {
  visualRotateFace("D", "Y", isClockwise);

  visualRotateRow("L", "B", "Y", isClockwise);
  visualRotateRow("F", "B", "Y", isClockwise);
  visualRotateRow("R", "B", "Y", isClockwise);
  visualRotateRow("B", "B", "Y", isClockwise);
}

/*dimension in all the following functions must be given as
"X", "Y", or "Z" */

function visualRotateFace(face, dimension, isClockwise) {
  var faceId = faceToId[face];
  for (var i = 0; i < cubelets[faceId].length; i++) {
    for (var j = 0; j < cubelets[faceId][i].length; j++) {
      visualRotateCubelet(faceId, i, j, dimension, 90, isClockwise);
    }
  }
}

function visualRotateRow(face, row, dimension, isClockwise) {
  var faceId = faceToId[face];
  var rowId = rowToId[row];
  for (var i = 0; i < cubelets[faceId][rowId].length; i++) {
    visualRotateCubelet(faceId, rowId, i, dimension, 90, isClockwise);
  }
}

function visualRotateCol(face, col, dimension, isClockwise) {
  var faceId = faceToId[face];
  var colId = colToId[col];
  for (var i = 0; i < cubelets[faceId].length; i++) {
    visualRotateCubelet(faceId, i, colId, dimension, 90, isClockwise);
  }
}

/*rotates the cubelet with face id i, row id j, and col id k,
across the dimension*/

function visualRotateCubelet(i, j, k, dimension, degrees, isClockwise) {

  var unitDegree;
  if (isClockwise) {
    unitDegree = 1;
  } else {
    unitDegree = -1;
  }

  if (degrees > 0) {
    var cubelet = cubelets[i][j][k];

    var element = document.getElementById(cubelet.id);

    var newTransformStr = addDegrees(cubelet.transform, dimension, unitDegree);

    cubelet.transform = newTransformStr;

    element.offsetHeight;
    element.style.transform = newTransformStr;

    setTimeout(function (){
      visualRotateCubelet(i, j, k, dimension, degrees - 1, isClockwise)
    }, CUBELET_DELAY_MS);
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

//all functions that start with "array" change the cubelet positions
//in our cubelet array. They are all adapted from the C++ backend code

/** Replaces a row on a face of the cube using data from another row/column */
function arrayShiftRow(faceId, rowId, a, b, c){
  var a2 = new Cubelet(), b2 = new Cubelet(), c2 = new Cubelet();

    createDeepCopy(a2, cubelets[faceId][rowId][0]);
    createDeepCopy(b2, cubelets[faceId][rowId][1]);
    createDeepCopy(c2, cubelets[faceId][rowId][2]);
    
    createDeepCopy(cubelets[faceId][rowId][0], a);
    createDeepCopy(cubelets[faceId][rowId][1], b);
    createDeepCopy(cubelets[faceId][rowId][2], c);

    createDeepCopy(a, a2);
    createDeepCopy(b, b2);
    createDeepCopy(c, c2);
}

/** Replaces a row on a face of the cube using data from another row/column in reverse order */
function arrayShiftRowReverse(faceId, rowId, a, b, c){
    var a2 = new Cubelet(), b2 = new Cubelet(), c2 = new Cubelet();

    createDeepCopy(a2, cubelets[faceId][rowId][0]);
    createDeepCopy(b2, cubelets[faceId][rowId][1]);
    createDeepCopy(c2, cubelets[faceId][rowId][2]);
    
    createDeepCopy(cubelets[faceId][rowId][0], c);
    createDeepCopy(cubelets[faceId][rowId][1], b);
    createDeepCopy(cubelets[faceId][rowId][2], a);

    createDeepCopy(a, a2);
    createDeepCopy(b, b2);
    createDeepCopy(c, c2);
}

/** Replaces a column on a face of the cube using data from another row/column */
function arrayShiftCol(faceId, colId, a, b, c){
    var a2 = new Cubelet(), b2 = new Cubelet(), c2 = new Cubelet();

    createDeepCopy(a2, cubelets[faceId][0][colId]);
    createDeepCopy(b2, cubelets[faceId][1][colId]);
    createDeepCopy(c2, cubelets[faceId][2][colId]);
    
    createDeepCopy(cubelets[faceId][0][colId], a);
    createDeepCopy(cubelets[faceId][1][colId], b);
    createDeepCopy(cubelets[faceId][2][colId], c);

    createDeepCopy(a, a2);
    createDeepCopy(b, b2);
    createDeepCopy(c, c2);
}

/** Replaces a column on a face of the cube using data from another row/column in reverse order */
function arrayShiftColReverse(faceId, colId, a, b, c){
    var a2 = new Cubelet(), b2 = new Cubelet(), c2 = new Cubelet();

    createDeepCopy(a2, cubelets[faceId][0][colId]);
    createDeepCopy(b2, cubelets[faceId][1][colId]);
    createDeepCopy(c2, cubelets[faceId][2][colId]);
    
    createDeepCopy(cubelets[faceId][0][colId], c);
    createDeepCopy(cubelets[faceId][1][colId], b);
    createDeepCopy(cubelets[faceId][2][colId], a);

    createDeepCopy(a, a2);
    createDeepCopy(b, b2);
    createDeepCopy(c, c2);
}

/** Rotates the squares on a given face on the Rubiks Cube clockwise. */
function arrayRotateFaceClockwise(face) {
  var faceId = faceToId[face];
    var temp, temp2;
    
    // corners
    temp = cubelets[faceId][0][0];
    cubelets[faceId][0][0] = cubelets[faceId][2][0];
    
    temp2 = cubelets[faceId][0][2];
    cubelets[faceId][0][2] = temp;
    
    temp = cubelets[faceId][2][2];
    cubelets[faceId][2][2] = temp2;
    
    cubelets[faceId][2][0] = temp;
    
    
    // edges
    temp = cubelets[faceId][0][1];
    cubelets[faceId][0][1] = cubelets[faceId][1][0];
    
    temp2 = cubelets[faceId][1][2];
    cubelets[faceId][1][2] = temp;
    
    temp = cubelets[faceId][2][1];
    cubelets[faceId][2][1] = temp2;
    
    cubelets[faceId][1][0] = temp;
    
}

/** Rotates the squares on a given face on the Rubiks Cube anticlockwise. */
function arrayRotateFaceAntiClockwise(face) {
  var faceId = faceToId[face];
    var temp, temp2;
    
    // corners
    temp = cubelets[faceId][0][0];
    cubelets[faceId][0][0] = cubelets[faceId][0][2];
    
    temp2 = cubelets[faceId][2][0];
    cubelets[faceId][2][0] = temp;
    
    temp = cubelets[faceId][2][2];
    cubelets[faceId][2][2] = temp2;
    
    cubelets[faceId][0][2] = temp;
    
    
    // edges
    temp = cubelets[faceId][0][1];
    cubelets[faceId][0][1] = cubelets[faceId][1][2];
    
    temp2 = cubelets[faceId][1][0];
    cubelets[faceId][1][0] = temp;
    
    temp = cubelets[faceId][2][1];
    cubelets[faceId][2][1] = temp2;
    
    cubelets[faceId][1][2] = temp;
    
}


// The following functions update the cube to reflect a one quarter rotation
// on the specified face in the specified direction.
// s1, s2, s3 are the first, second and third cubelets in the row
function arrayRotateFrontClockwise() {
    arrayRotateFaceClockwise("F");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[3][2][0]);
    createDeepCopy(s2, cubelets[3][2][1]);
    createDeepCopy(s3, cubelets[3][2][2]);

    arrayShiftCol (2, 0, s1, s2, s3);
    arrayShiftRowReverse(4, 0, s1, s2, s3);
    arrayShiftCol(1, 2, s1, s2, s3);
    arrayShiftRowReverse(3, 2, s1, s2, s3);

}

function arrayRotateFrontAntiClockwise(){
    arrayRotateFaceAntiClockwise("F");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[3][2][0]);
    createDeepCopy(s2, cubelets[3][2][1]);
    createDeepCopy(s3, cubelets[3][2][2]);
    
    arrayShiftColReverse(1, 2, s1, s2, s3);
    arrayShiftRow(4, 0, s1, s2, s3);
    arrayShiftColReverse (2, 0, s1, s2, s3);
    arrayShiftRow(3, 2, s1, s2, s3);
    
}

function arrayRotateLeftClockwise(){
    arrayRotateFaceClockwise("L");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[3][0][0]);
    createDeepCopy(s2, cubelets[3][1][0]);
    createDeepCopy(s3, cubelets[3][2][0]);
    
    arrayShiftCol (0, 0, s1, s2, s3);
    arrayShiftCol(4, 0, s1, s2, s3);
    arrayShiftColReverse(5, 2, s1, s2, s3);
    arrayShiftColReverse(3, 0, s1, s2, s3);
}

function arrayRotateLeftAntiClockwise(){
    arrayRotateFaceAntiClockwise("L");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[3][0][0]);
    createDeepCopy(s2, cubelets[3][1][0]);
    createDeepCopy(s3, cubelets[3][2][0]);
    
    arrayShiftColReverse(5, 2, s1, s2, s3);
    arrayShiftColReverse(4, 0, s1, s2, s3);
    arrayShiftCol (0, 0, s1, s2, s3);
    arrayShiftCol(3, 0, s1, s2, s3);
    
}

function arrayRotateRightClockwise(){
    arrayRotateFaceClockwise("R");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[3][0][2]);
    createDeepCopy(s2, cubelets[3][1][2]);
    createDeepCopy(s3, cubelets[3][2][2]);
    
    arrayShiftColReverse(5, 0, s1, s2, s3);
    arrayShiftColReverse(4, 2, s1, s2, s3);
    arrayShiftCol (0, 2, s1, s2, s3);
    arrayShiftCol(3, 2, s1, s2, s3);
    
}

function arrayRotateRightAntiClockwise(){
    arrayRotateFaceAntiClockwise("R");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[3][0][2]);
    createDeepCopy(s2, cubelets[3][1][2]);
    createDeepCopy(s3, cubelets[3][2][2]);
    
    arrayShiftCol (0, 2, s1, s2, s3);
    arrayShiftCol(4, 2, s1, s2, s3);
    arrayShiftColReverse(5, 0, s1, s2, s3);
    arrayShiftColReverse(3, 2, s1, s2, s3);
    
}

function arrayRotateUpClockwise(){
    arrayRotateFaceClockwise("U");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[5][0][0]);
    createDeepCopy(s2, cubelets[5][0][1]);
    createDeepCopy(s3, cubelets[5][0][2]);

    arrayShiftRow(2, 0, s1, s2, s3);
    arrayShiftRow(0, 0, s1, s2, s3);
    arrayShiftRow (1, 0, s1, s2, s3);
    arrayShiftRow(5, 0, s1, s2, s3);
    
}

function arrayRotateUpAntiClockwise(){
    arrayRotateFaceAntiClockwise("U");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[5][0][0]);
    createDeepCopy(s2, cubelets[5][0][1]);
    createDeepCopy(s3, cubelets[5][0][2]);

    arrayShiftRow(1, 0, s1, s2, s3);
    arrayShiftRow(0, 0, s1, s2, s3);
    arrayShiftRow (2, 0, s1, s2, s3);
    arrayShiftRow(5, 0, s1, s2, s3);
}

function arrayRotateDownClockwise(){
    arrayRotateFaceClockwise("D");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[5][2][0]);
    createDeepCopy(s2, cubelets[5][2][1]);
    createDeepCopy(s3, cubelets[5][2][2]);

    arrayShiftRow(1, 2, s1, s2, s3);
    arrayShiftRow(0, 2, s1, s2, s3);
    arrayShiftRow (2, 2, s1, s2, s3);
    arrayShiftRow(5, 2, s1, s2, s3);
}

function arrayRotateDownAntiClockwise(){
    arrayRotateFaceAntiClockwise("D");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[5][2][0]);
    createDeepCopy(s2, cubelets[5][2][1]);
    createDeepCopy(s3, cubelets[5][2][2]);

    arrayShiftRow(2, 2, s1, s2, s3);
    arrayShiftRow(0, 2, s1, s2, s3);
    arrayShiftRow (1, 2, s1, s2, s3);
    arrayShiftRow(5, 2, s1, s2, s3);
}

function arrayRotateBackClockwise(){
    arrayRotateFaceClockwise("B");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[3][0][0]);
    createDeepCopy(s2, cubelets[3][0][1]);
    createDeepCopy(s3, cubelets[3][0][2]);

    arrayShiftCol(1, 0, s1, s2, s3);
    arrayShiftRowReverse(4, 2, s1, s2, s3);
    arrayShiftColReverse(2, 2, s1, s2, s3);
    arrayShiftRow(3, 0, s1, s2, s3);
}

function arrayRotateBackAntiClockwise(){
    arrayRotateFaceAntiClockwise("B");
    
    var s1 = new Cubelet(), s2 = new Cubelet(), s3 = new Cubelet();

    createDeepCopy(s1, cubelets[3][0][0]);
    createDeepCopy(s2, cubelets[3][0][1]);
    createDeepCopy(s3, cubelets[3][0][2]);
    
    arrayShiftCol(2, 2, s1, s2, s3);
    arrayShiftRow(4, 2, s1, s2, s3);
    arrayShiftColReverse(1, 0, s1, s2, s3);
    arrayShiftRowReverse(3, 0, s1, s2, s3);
}

function createDeepCopy(cubelet1, cubelet2) {
  cubelet1.id = cubelet2.id;
  cubelet1.transform = cubelet2.transform;
}
