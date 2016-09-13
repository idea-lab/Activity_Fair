var canvas = document.getElementById("myCanvas");
var ctx = canvas.getContext("2d");
var width=480;
var height=320;
var state=0;
var score=0;
var keys={left:false, right:false};
var ballPos=[100, 100];
var ballV = [-1, -1];
var playerX=0;
$(document).keypress(function(e){
	if(state == 0){
		state++;
	}
	else if(state==1){
		if(e.keyCode==97){ //a
			keys.left=true;			
		}
		if(e.keyCode == 100){ //d
			keys.right=true;
		}
	}
})
$(document).keyup(function(e){
	if(state==1){
		if(e.keyCode==65){ //a
			keys.left=false;			
		}
		if(e.keyCode == 68){ //d
			keys.right=false;
		}
	}
})
function title(){
	ctx.font = "30px Roboto-Thin";
	ctx.fillText("Press a key to start", width/2-75, height/2);
}
function game(){
	if(keys.left) playerX=playerX-5>=0?playerX-5:0;
	if(keys.right) playerX=playerX+5<width-50?playerX+5:width-50;
	var r={x:playerX,y:0,width:50,height:10};
	var eR={x:r.x-10,y:-10,width:70,height:30};
	var intersection={x:-1,y:-1};
	if (cohenSutherlandIntersection(ballPos[0], ballPos[1], ballPos[0]+ballV[0], ballPos[1]+ballV[1], eR, intersection)) {
		var isLeft = intersection.x < r.x;
		var isRight = intersection.x > r.x + r.width;
		var isTop = intersection.y > r.y + r.height;
		if(isLeft||isRight) {
			ballV[0]=-ballV[0];
			ballPos[0]+=ballV[0];
		}
		else if(isTop) {
			ballV[1]=-ballV[1]+0.5;
			ballPos[1]+=ballV[1];
			score++;
		}
	}
	if(ballPos[0]<=10||ballPos[0]>width-10) ballV[0]=-ballV[0];
	if(ballPos[1]<0)state++;
	if(ballPos[1]>height-10)ballV[1]=-ballV[1];
	ballPos[0]+=ballV[0];
	ballPos[1]+=ballV[1];
	drawPaddle(playerX,0);
	drawBall(ballPos[0], ballPos[1]);
	displayScore();
}
function end(){
	ctx.font ="30px Roboto-Thin"
	ctx.fillStyle ="black"
	ctx.fillText("Game over", 100, 100)
}
function displayScore(){
	ctx.fillStyle="black";
	ctx.fillText("Score: "+score, 300, 50);
}
function drawBall(x, y){
	ctx.beginPath();
	ctx.arc(x, y, 10, 0, Math.PI*2, false);
	ctx.fillStyle="white";
	ctx.strokeStyle = "black";
	ctx.stroke();
	ctx.fill();
	ctx.closePath();
}
function drawPaddle(x, y){
	ctx.beginPath();
	ctx.rect(x, y, 50, 10);
	ctx.fillStyle="black";
	ctx.fill();
	ctx.closePath();
}
setInterval(function(){ //draw
	ctx.clearRect(0, 0, width, height);
	if(state==0){
		title();
	}
	else if(state == 1){
		game();
	}
	else if(state == 2){
		end();
	}
}, 1000/60)

var INSIDE = 0x0000;
var LEFT = 0x0001;
var RIGHT = 0x0010;
var BOTTOM = 0x0100;
var TOP = 0x1000;
function cohenSutherlandIntersection(x1, y1, x2, y2, r, intersection) { //r=rectangle, intersection=vector
	var regionCode1 = calculateRegionCode(x1, y1, r);
	var regionCode2 = calculateRegionCode(x2, y2, r);
	var xMin = r.x;
	var xMax = r.x + r.width;
	var yMin = r.y;
	var yMax = r.y + r.height;
	while (true) {
		if (regionCode1 == INSIDE) {
			intersection.x = x1;
			intersection.y = y1;
			return true;
		} else if ((regionCode1 & regionCode2) != 0) {
			return false;
		} else {
			var x = 0.0;
			var y = 0.0;
			if ((regionCode1 & TOP) != 0) {
				x = x1 + (x2 - x1) / (y2 - y1) * (yMax - y1);
				y = yMax;
			} else if ((regionCode1 & BOTTOM) != 0) {
				x = x1 + (x2 - x1) / (y2 - y1) * (yMin - y1);
				y = yMin;
			} else if ((regionCode1 & RIGHT) != 0) {
				y = y1 + (y2 - y1) / (x2 - x1) * (xMax - x1);
				x = xMax;
			} else if ((regionCode1 & LEFT) != 0) {
				y = y1 + (y2 - y1) / (x2 - x1) * (xMin - x1);
				x = xMin;
			}
			x1 = x;
			y1 = y;
			regionCode1 = calculateRegionCode(x1, y1, r);
		}
	}
}

function calculateRegionCode( x,  y, r) {
	var code = INSIDE;

	if (x < r.x) {
		code |= LEFT;
	} else if (x > r.x + r.width) {
		code |= RIGHT;
	}

	if (y < r.y) {
		code |= BOTTOM;
	} else if (y > r.y + r.height) {
		code |= TOP;
	}

	return code;
}