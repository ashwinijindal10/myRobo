class Robo {
    canvas = document.getElementById('myCanvas') as HTMLCanvasElement;
    ctx: CanvasRenderingContext2D = this.canvas.getContext('2d');

    constructor() {
        this.ctx.strokeStyle = 'black';
        this.ctx.lineWidth = 1;
    }

    turnLeft() {
        // trun 90 deg left
    }

    turnRight() {
        // trun 90 deg right
    }

    move(x: number, y: number): boolean {
        // move to one unit forward 
        //TODO: check obstacles in front
        if (x >= 0 && y >= 0 && x < this.canvas.width && y < this.canvas.height) {
           
            this.drawPixel(x, y)
            return true;
        }
        return false;
    }

    clean(): void {
       
    }

    private drawPixel(x: number, y: number) {
        let i = .5;

        this.ctx.beginPath();
            this.ctx.moveTo(x, y);
            this.ctx.lineTo(x + i, y + i);
            this.ctx.stroke();
        
        // setTimeout(()=>{
           
        //  //   console.log('painted')
        // },1000);
    }
}


let cleanedSet:string[] =[];

function doClean(robo: Robo, x: number, y: number, angle: number) {
    let position = `${x}-${y}`;

    // cleaning
    if (cleanedSet.indexOf(position) > -1) return;
    robo.clean();
    cleanedSet.push(position);
    //console.log(cleanedSet);

    // go next depth first search
    for (let i = 0; i < 4; i++) {
        if (robo.move(x, y)) {
            let nextX = x, nextY = y;
            switch (angle) {
                case 0: nextY -= 1; break;
                case 90: nextX += 1; break;
                case 180: nextY += 1; break;
                case 270: nextX -= 1; break;
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

doClean(new Robo(), 0,0,0);