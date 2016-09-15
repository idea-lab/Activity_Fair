import processing.video.*;
Capture cam;
int state=0;
void setup() {
  size(640, 480);
  cam = new Capture(this, 640, 480, 30);
  cam.start();
}
void draw() {
  if (cam.available() == true) {
    cam.read();
  }
  
  image(cam, 0, 0);
  loadPixels();
  for (int i=0; i<pixels.length; i++) {
    float r=red(pixels[i]);
    float g=green(pixels[i]);
    float b=blue(pixels[i]);
    if (state == 0) if (r>g&&r>b) pixels[i]=color(255, 0, 0);    
    if (state == 1) if (g>r&&g>b) pixels[i]=color(0, 255, 0);      
    if (state == 2) if (b>g&&b>r) pixels[i]=color(0, 0, 255);
    if (state == 3) {
      if (r>g&&r>b) pixels[i]=color(255, 0, 0);
      else if (g>b&&g>r) pixels[i]=color(0, 255, 0);
      else if (b>g&&b>r) pixels[i]=color(0, 0, 255);
    }
    if(r==b||b==g||g==r){
      pixels[i]=color(255);
    }
  }
  updatePixels();
}
void keyPressed(){
  if(key=='r'){
    state=0;
  }
  else if(key=='g'){
    state=1;
  }
  else if(key=='b'){
    state=2;
  }
  else if(key=='`'){
    state=3;
  }
}