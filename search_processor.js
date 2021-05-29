var Robo = /** @class */ (function () {
    function Robo() {
        this.canvas = document.getElementById('myCanvas');
        this.ctx = this.canvas.getContext('2d');
        this.ctx.strokeStyle = 'black';
        this.ctx.lineWidth = 1;
    }
    Robo.prototype.turnLeft = function () {
        // trun 90 deg left
    };
    Robo.prototype.turnRight = function () {
        // trun 90 deg right
    };
    Robo.prototype.move = function (x, y) {
        // move to one unit forward 
        if (x >= 0 && y >= 0 && x < this.canvas.width && y < this.canvas.height) {
            this.drawPixel(x, y);
            return true;
        }
        return false;
    };
    Robo.prototype.clean = function () {
    };
    Robo.prototype.drawPixel = function (x, y) {
        var i = .5;
        this.ctx.beginPath();
        this.ctx.moveTo(x, y);
        this.ctx.lineTo(x + i, y + i);
        this.ctx.stroke();
        // setTimeout(()=>{
        //  //   console.log('painted')
        // },1000);
    };
    return Robo;
}());
var cleanedSet = [];
function doClean(robo, x, y, angle) {
    var position = x + "-" + y;
    // cleaning
    if (cleanedSet.indexOf(position) > -1)
        return;
    robo.clean();
    cleanedSet.push(position);
    //console.log(cleanedSet);
    // go next depth first search
    for (var i = 0; i < 3; i++) {
        if (robo.move(x, y)) {
            var nextX = x, nextY = y;
            switch (angle) {
                case 0:
                    nextY -= 1;
                    break;
                case 90:
                    nextX += 1;
                    break;
                case 180:
                    nextY += 1;
                    break;
                case 270:
                    nextX -= 1;
                    break;
            }
            doClean(robo, nextX, nextY, angle);
            robo.turnLeft();
            robo.turnLeft();
            robo.move(nextX, nextY);
            robo.turnRight();
            robo.turnRight();
        }
        angle += 90;
        robo.turnRight();
        angle = angle % 360;
    }
}
//let s = new Robo();
//for(let d= 5 ; d <44 ; d ++)
//    s.move(d,d);
doClean(new Robo(), 0, 0, 0);
