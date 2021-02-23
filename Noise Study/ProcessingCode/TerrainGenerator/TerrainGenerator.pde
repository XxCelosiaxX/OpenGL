int cols, rows;
int scale = 20;
int width = 600;
int height = 600;
float flying = 0;

OpenSimplexNoise noise;

float[][] terrain;

float zincrement = 0.02; 

void setup(){
   size(600, 600, P3D);
   cols = width/scale;
   rows = height/scale;
   terrain = new float[cols][rows];
   noise = new OpenSimplexNoise();
}

float xoff = 0.0;
float yoff = 0.0;
float zoff = 0.0;  

void draw(){
  
  flying -= 0.01;
  float yOffset = flying;
   for (int y = 0; y < rows; y++){
     float xOffset = 0;
     for(int x = 0; x < cols; x++)
     {
       //Random:
       //terrain[x][y] = random(-80,80);
       
       //Perlin:
       //terrain[x][y] = map(noise(xOffset, yOffset), 0, 1, -80, 80);
      
      //Simplex:
      float n = (float)noise.eval(xOffset ,yOffset);    
      terrain[x][y] = map(n,-1,1,-80,80);
      
       xOffset += 0.2;
     }
     yOffset += 0.2;
   }
  
  
  background(0);
  stroke(255);
  noFill();
  
  // Rotate the view to be looking down at an angle
  translate(width/2, height/2 + 50);
  rotateX(PI/3);
  translate(-width/2, -height/2);
  
  
  
  for (int y = 0; y < rows - 1; y++){
    beginShape(TRIANGLE_STRIP);
     for(int x = 0; x < cols; x++){
       vertex(x * scale, y * scale, terrain[x][y]);
       vertex(x * scale, (y + 1) * scale, terrain[x][y+1]);
     }
     endShape();
  }
}
