let ambientSound, blinkSound;
let eyelidOpen = true;
let isBlinking = false;

function preload() {
ambientSound = loadSound('/Assets/ArturKordas_Baba.mp3')
blinkSound = loadSound('/Assets/Blink.mp3')
}

function setup() {

  createCanvas(600, 600);
  
  angleBig = 0;
  angleSmall= 0;

  ambientSound.play()
  ambientSound.loop()
}

function draw() {

  background('black');
  translate(width/2, height/2);
  strokeCap(ROUND);

  //reset del parpadeo
  if (!eyelidOpen && !isBlinking) {
    eyelidOpen = true; 
  }

  //crear lineas y movimientos con cos y sin
  let radius = 280;
  for (let i = 0; i < 16; i++) {
    let a = angleBig + i * 0.4;
    let x = cos(a) * radius;
    let y = sin(a) * radius;
    stroke('white');
    strokeWeight(7);
    line(0, 0, x, y);
  }

  let radiusSmall = 230;
  for (let i = 0; i < 16; i++) { 
    let a = angleSmall + i * 0.4; 
    let x = cos(a) * radiusSmall; 
    let y = sin(a) * radiusSmall; 
    stroke('red');
    strokeWeight(7)
    line(0, 0, x, y);
  }

  //circulo negro en medio
  fill('black')
  noStroke()
  ellipse(0,0,200);

  //Ojo con curvas de bezier
  stroke('white');
  fill('white')
  beginShape();
  vertex(-80, 0);
  bezierVertex(-30, -50, 30, -50, 80, 0);
  bezierVertex(30,50,-30,50,-80,0)
  ;
  endShape();

  //Pupilas
  fill('black');
  stroke('black');
  ellipse(0, 0, 50, 50);
  fill('white');
  noStroke()
  ellipse(-15, -10, 15, 15);
  
  stroke('white');
  fill('black');
  noStroke()

  //Parpados abiertos y cerrados
  if (eyelidOpen) {
  beginShape();
  vertex(-80, 0);
  bezierVertex(-30, -50, 30, -50, 80, 0);
  bezierVertex(-15, -25, 15, -25, -80, 0);
  endShape(CLOSE);
  }
  else {
    beginShape();
    vertex(-80, 0);
    bezierVertex(-30, -50, 30, -50, 80, 0);
    bezierVertex(30,50,-30,50,-80,0)
    endShape(CLOSE);
  }

  //update movimiento de lineas
  angleSmall -= 0.003;
  angleBig += 0.003;
}
//parpadeo del ojo
function mouseClicked() {
  if (!isBlinking) {
    eyelidOpen = false;
    isBlinking = true;
    blinkSound.play();
    setTimeout(function() {
      isBlinking = false;  //delay
    }, 200);
  }

  //eyelidOpen = !eyelidOpen; //cambiar estado del parpadeo
}