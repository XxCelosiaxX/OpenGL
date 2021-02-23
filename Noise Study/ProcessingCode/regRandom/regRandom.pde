void setup()
{
   size(800,500);
   frameRate(10);
}

void draw()
{
  background(0);
  fill(255);
  
  float x = random(width);
  ellipse(x,height/2,40,40);
}
