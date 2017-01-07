squareSide = 50;
faces = ["front", "left", "right", "up", "down", "back"];
colorCenter = ["red", "green", "blue", "white", "yellow", "orange"];
squares = [];
button = null;

offsetX = document.body.clientWidth/2 - squareSide*6;
offsetY = document.body.clientHeight/2 - squareSide*4.5;

shiftX = [
squareSide * 3, 
squareSide * 0, 
squareSide * 6, 
squareSide * 3,
squareSide * 3,
squareSide * 9,
];

shiftY = [
squareSide * 3, 
squareSide * 3, 
squareSide * 3, 
squareSide * 6,
squareSide * 0,
squareSide * 3,
];

net = document.getElementById("net");


main();


function main() {
	hideCube();
	createNet();
	createSolveButton();
}

function showCube() {
	var cube = document.getElementById("cube");
	cube.style.display = "inherit";
}
function hideCube() {
	var cube = document.getElementById("cube");
	cube.style.display = "none";
}

function createNet() {
	for (var i = 0; i < faces.length; i++) {
		var face = [];
		for (var j = 0; j < 3; j++) {
			var row = [];
			for (var k = 0; k < 3; k++) {

				var y = offsetY + j*squareSide + shiftY[i];
				var x = offsetX + k*squareSide + shiftX[i];

				var square = document.createElement("div");

				square.style.left = x + "px";
				square.style.top = y + "px";
				square.style.position = "fixed";
				square.style.border = "thin solid black";
				square.style.height = squareSide + "px";
				square.style.width = squareSide + "px";

				square.style.backgroundColor = colorCenter[i];


				//center pieces can never change
				if (!(i === 1 && j === 1)){

					square.addEventListener("click", function() {
							
						var index = colorCenter.indexOf(this.style.backgroundColor);

						index = (index + 1) % colorCenter.length;
						this.style.backgroundColor = colorCenter[index];
						});
				}

				net.appendChild(square);
				row.push(square);
			}
			face.push(row);
		}
		squares.push(face);
	}
}

function createSolveButton() {
	button = document.createElement("button");

	button.addEventListener("click", function() {
		if (cubeIsValid()) {
			startSolving();
		}
	});

	var x = offsetX + squareSide*3;
	var y = offsetY + squareSide*9 + 10;

	button.style.width = squareSide*3 + "px";
	button.style.height = squareSide;
	button.style.left = x;
	button.style.top = y;
	button.style.position = "absolute";

	button.innerHTML = "Solve!";

	var wrapper = document.getElementById("solveButton");
	wrapper.appendChild(button);

}

function cubeIsValid() {
	var countColors = {};

	for (var i = 0; i < colorCenter.length; i++) {
		var color = colorCenter[i];
		countColors[color] = 0;
	}
	for (var i = 0; i < 6; i++) {
		for (var j = 0; j < 3; j++) {
			for (var k = 0; k < 3; k++) {
				var color = squares[i][j][k].style.backgroundColor;
				countColors[color]++;
			}
		}
	}

	var isValid = true;

	for (var color in countColors) {
		if (countColors[color] != 9) {
			isValid = false;
		}
	}
	return isValid;
}

function startSolving() {
	clear();
	showCube();
	mainAnimation();
	return;
}

function clear() {
	for (var i = 0; i < 6; i++) {
		for (var j = 0; j < 3; j++) {
			for (var k = 0; k < 3; k++) {
				squares[i][j][k].style.display = "none";
			}
		}
	}

	button.style.display = "none";
}