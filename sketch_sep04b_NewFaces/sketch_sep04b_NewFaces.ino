/*
                                              ________        
                                            ||.     . ||
                                            ||   ‿    ||
_|      _|  _|    _|  _|      _|    _|_|    ||        ||
_|      _|  _|    _|  _|_|  _|_|  _|    _| /||--------||\
_|  _|  _|  _|    _|  _|  _|  _|  _|    _|  ||===   . ||
_|  _|  _|  _|    _|  _|      _|  _|    _|  || +  o  0||
_|_|_|_|_|    _|_|_|  _|      _|    _|_|    ||________||
                                               |    |
WUMO The Weather Robot - Dreamed up by Dan Fein and Amy Fischlin
GLCD is a ks0108 on an Arduino: playground.arduino.cc/Code/GLCDks0108 may help with wiring
GLCD.h library from Michael Margolis and Bill Perry: code.google.com/p/glcd-arduino/
*/

// WxBot Project v.02 - Animated Face and Temperature History Monitor

#include <glcd.h> // include the graphics LCD library
#include <fonts/SystemFont5x7.h> // include the standard character fonts for it
int tcurrent;
int tempArray[100];

void setup()
{
  GLCD.Init(NON_INVERTED); // configure GLCD
  GLCD.ClearScreen(); // turn off all GLCD pixels
  GLCD.SelectFont(System5x7);
}

void getTemp() // function to read temperature from TMP36
{
  float sum = 0;
  float voltage = 0;
  float sensor = 0;
  float celsius;
  // read the temperature sensor and convert the result to degrees C
  sensor = analogRead(5);
  voltage = (sensor * 5000) / 1024;
  voltage = voltage - 500;
  celsius = voltage / 10;
  tcurrent = int(celsius);
  // insert the new temperature at the start of the array of past temperatures
  for (int a = 99 ; a >= 0 ; --a )
  {
    tempArray[a] = tempArray[a-1];
  }
  tempArray[0] = tcurrent;
}
void drawScreen() // generate GLCD display effects
{
  int q;
  GLCD.ClearScreen();
  GLCD.CursorTo(5, 0);
  GLCD.Puts("Current:");
  GLCD.PrintNumber(tcurrent);
  GLCD.Puts(" C");
  GLCD.CursorTo(0, 1);
  GLCD.PrintNumber(40);
  GLCD.CursorTo(0, 2);
  GLCD.PrintNumber(32);
  GLCD.CursorTo(0, 3);
  GLCD.PrintNumber(24);
  GLCD.CursorTo(0, 4);
  GLCD.PrintNumber(16);
  GLCD.CursorTo(1, 5);
  GLCD.PrintNumber(8);
  GLCD.CursorTo(1, 6);
  GLCD.PrintNumber(0);
  for (int a = 28 ; a < 127 ; a++)
  {
    q = (55 - tempArray[a-28]);
    GLCD.SetDot(a, q, BLACK);
  }
}

void face() //Face animation
{
  
  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left

delay(5000);

  GLCD.ClearScreen();
  GLCD.FillRect(19,17,8,10,BLACK); //left eye
  GLCD.DrawRect(15,17,30,1, BLACK); //top line
  GLCD.FillRect(95,17,8,10,BLACK); //right eye
  GLCD.DrawRect(90,17,30,1, BLACK); //top line
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left

delay(100);

  GLCD.ClearScreen();
  GLCD.DrawRect(15,20,30,1, BLACK); //top line
  GLCD.DrawRect(90,20,30,1, BLACK); //top line
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left


delay(100);


  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left

delay(2000);

  GLCD.ClearScreen();
  GLCD.FillRect(19,17,8,10,BLACK); //left eye
  GLCD.DrawRect(15,17,30,1, BLACK); //top line
  GLCD.FillRect(95,17,8,10,BLACK); //right eye
  GLCD.DrawRect(90,17,30,1, BLACK); //top line
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left

delay(100);

  GLCD.ClearScreen();
  GLCD.DrawRect(15,20,30,1, BLACK); //top line
  GLCD.DrawRect(90,20,30,1, BLACK); //top line
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left

delay(100);

  GLCD.ClearScreen();
  GLCD.FillRect(19,17,8,10,BLACK); //left eye
  GLCD.DrawRect(15,17,30,1, BLACK); //top line
  GLCD.FillRect(95,17,8,10,BLACK); //right eye
  GLCD.DrawRect(90,17,30,1, BLACK); //top line
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left

delay(100);

  GLCD.ClearScreen();
  GLCD.FillRect(19,17,8,10,BLACK); //left eye
  GLCD.DrawRect(15,17,30,1, BLACK); //top line
  GLCD.FillRect(95,17,8,10,BLACK); //right eye
  GLCD.DrawRect(90,17,30,1, BLACK); //top line
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left

delay(100);

  GLCD.ClearScreen();
  GLCD.DrawRect(15,20,30,1, BLACK); //top line
  GLCD.DrawRect(90,20,30,1, BLACK); //top line
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left
  
delay(100); 

  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left

delay(5000);

  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.DrawCircle(55,45,2,BLACK); // whistle 1
  GLCD.FillCircle(65,40,2,BLACK); // note circle
  GLCD.FillRect(66,30,1,10,BLACK); //note bar
  GLCD.FillRect(68,30,1,2,BLACK); //note top1
  GLCD.FillRect(70,31,1,2,BLACK); //note top2
  GLCD.FillRect(72,30,1,1,BLACK); //note top3

delay(500);

  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.DrawCircle(50,45,3,BLACK); // whistle 2
  GLCD.FillCircle(65,40,2,BLACK); // note circle
  GLCD.FillRect(66,30,1,10,BLACK); //note bar
  GLCD.FillRect(68,30,1,2,BLACK); //note top1
  GLCD.FillRect(70,31,1,2,BLACK); //note top2
  GLCD.FillRect(72,30,1,1,BLACK); //note top3

delay(500);

  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.DrawCircle(62,45,2,BLACK); // whistle 3
  GLCD.FillCircle(75,45,2,BLACK); // note circle
  GLCD.FillRect(76,35,1,10,BLACK); //note bar
  GLCD.FillRect(78,35,8,1,BLACK); //note top1
  GLCD.FillRect(86,35,1,10,BLACK); //note bar2
  GLCD.FillCircle(85,45,2,BLACK); // note circle

  delay(500);

  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.DrawCircle(60,45,3,BLACK); // whistle 2
  GLCD.FillCircle(105,45,2,BLACK); // note circle
  GLCD.FillRect(106,35,1,10,BLACK); //note bar
  GLCD.FillRect(108,35,1,2,BLACK); //note top1
  GLCD.FillRect(110,36,1,2,BLACK); //note top2
  GLCD.FillRect(112,35,1,1,BLACK); //note top3

  delay(500);

  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.DrawCircle(62,45,2,BLACK); // whistle 3
  GLCD.FillCircle(115,35,2,BLACK); // note circle
  GLCD.FillRect(116,25,1,10,BLACK); //note bar
  GLCD.FillRect(118,25,1,2,BLACK); //note top1
  GLCD.FillRect(120,26,1,2,BLACK); //note top2
  GLCD.FillRect(122,25,1,1,BLACK); //note top3

  delay(500);

  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.DrawCircle(60,45,3,BLACK); // whistle 2

  delay(500);

  GLCD.ClearScreen();
  GLCD.FillRect(19,17,8,10,BLACK); //left eye
    GLCD.DrawRect(15,17,30,1, BLACK); //top line
  GLCD.FillRect(95,17,8,10,BLACK); //right eye
    GLCD.DrawRect(90,17,30,1, BLACK); //top line
  GLCD.DrawCircle(55,45,2,BLACK); // whistle 1

  delay(100);

  GLCD.ClearScreen();
    GLCD.DrawRect(15,20,30,1, BLACK); //top line
    GLCD.DrawRect(90,20,30,1, BLACK); //top line
  GLCD.DrawCircle(55,45,2,BLACK); // whistle 1

  delay(100);

  GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.DrawCircle(55,45,2,BLACK); // whistle 1
  
  delay(500);

}

void sweat()
{
 
 GLCD.ClearScreen();
  GLCD.FillRect(19,15,8,12,BLACK); //left eye
  GLCD.FillRect(95,15,8,12,BLACK); //right eye
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,43,3,1,BLACK); // mouth right
  GLCD.FillRect(72,43,3,1,BLACK); // mouth left

delay(1000);
  
  GLCD.ClearScreen();
  GLCD.FillRect(19,18,8,10,BLACK); //left eye
  GLCD.FillRect(95,18,8,10,BLACK); //right eye
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,45,3,1,BLACK); // mouth right
  GLCD.FillRect(72,45,3,1,BLACK); // mouth left
  
  GLCD.FillRect(78,4,0,3,BLACK); // drip center
  GLCD.FillRect(76,8,0,3,BLACK); // drip right
  GLCD.FillRect(74,12,0,2,BLACK); // drip right2
  GLCD.FillRect(76,14,0,1,BLACK); // drip right2
  GLCD.FillRect(80,8,1,3,BLACK); // drip left
  GLCD.FillRect(82,12,1,2,BLACK); // drip left2
  GLCD.FillRect(80,14,1,1,BLACK); // drip right2
  GLCD.FillRect(77,16,4,0,BLACK); // drip center

delay(1000);

 
  GLCD.ClearScreen();
  GLCD.FillRect(19,22,8,8,BLACK); //left eye
  GLCD.FillRect(95,22,8,8,BLACK); //right eye
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,45,3,1,BLACK); // mouth right
  GLCD.FillRect(72,45,3,1,BLACK); // mouth left
  
  GLCD.FillRect(78,14,0,3,BLACK); // drip center
  GLCD.FillRect(76,18,0,3,BLACK); // drip right
  GLCD.FillRect(74,22,0,2,BLACK); // drip right2
  GLCD.FillRect(76,24,0,1,BLACK); // drip right2
  GLCD.FillRect(80,18,1,3,BLACK); // drip left
  GLCD.FillRect(82,22,1,2,BLACK); // drip left2
  GLCD.FillRect(80,24,1,1,BLACK); // drip right2
  GLCD.FillRect(77,26,4,0,BLACK); // drip center


delay(1000);
 
  GLCD.ClearScreen();
  GLCD.FillRect(19,22,8,8,BLACK); //left eye
  GLCD.FillRect(95,22,8,8,BLACK); //right eye
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,45,3,1,BLACK); // mouth right
  GLCD.FillRect(72,45,3,1,BLACK); // mouth left
  
  GLCD.FillRect(78,24,0,3,BLACK); // drip center
  GLCD.FillRect(76,28,0,3,BLACK); // drip right
  GLCD.FillRect(74,32,0,2,BLACK); // drip right2
  GLCD.FillRect(76,34,0,1,BLACK); // drip right2
  GLCD.FillRect(80,28,1,3,BLACK); // drip left
  GLCD.FillRect(82,32,1,2,BLACK); // drip left2
  GLCD.FillRect(80,34,1,1,BLACK); // drip right2
  GLCD.FillRect(77,36,4,0,BLACK); // drip center
    
  GLCD.FillRect(8,4,0,3,BLACK); // drip2 center
  GLCD.FillRect(6,8,0,3,BLACK); // drip2 right
  GLCD.FillRect(4,12,0,2,BLACK); // drip2 right2
  GLCD.FillRect(6,14,0,1,BLACK); // drip2 right2
  GLCD.FillRect(10,8,1,3,BLACK); // drip2 left
  GLCD.FillRect(12,12,1,2,BLACK); // drip2 left2
  GLCD.FillRect(10,14,1,1,BLACK); // drip2 right2
  GLCD.FillRect(7,16,4,0,BLACK); // drip2 center


delay(1000);

 
  GLCD.ClearScreen();
  GLCD.FillRect(19,22,8,8,BLACK); //left eye
  GLCD.FillRect(95,22,8,8,BLACK); //right eye
  GLCD.FillRect(55,45,17,1,BLACK); // mouth middle
  GLCD.FillRect(52,47,3,1,BLACK); // mouth right
  GLCD.FillRect(72,47,3,1,BLACK); // mouth left
    
  GLCD.FillRect(8,24,0,3,BLACK); // drip2 center
  GLCD.FillRect(6,28,0,3,BLACK); // drip2 right
  GLCD.FillRect(4,32,0,2,BLACK); // drip2 right2
  GLCD.FillRect(6,34,0,1,BLACK); // drip2 right2
  GLCD.FillRect(10,28,1,3,BLACK); // drip2 left
  GLCD.FillRect(12,32,1,2,BLACK); // drip2 left2
  GLCD.FillRect(10,34,1,1,BLACK); // drip2 right2
  GLCD.FillRect(7,36,4,0,BLACK); // drip2 center

delay(1000);

  GLCD.ClearScreen();
  GLCD.FillRect(19,22,8,8,BLACK); //left eye
  GLCD.FillRect(28,22,3,1,BLACK); // left eyebrow
  GLCD.FillRect(15,22,3,1,BLACK); // left eyebrow 2
  GLCD.FillRect(95,22,8,8,BLACK); //right eye
  GLCD.FillRect(91,22,3,1,BLACK); // right eyebrow
  GLCD.FillRect(104,22,3,1,BLACK); // right eyebrow 2
  GLCD.FillRect(50,45,25,1,BLACK); // mouth middle
  GLCD.FillRect(54,47,1,2,BLACK); // tongue right
  GLCD.FillRect(56,50,1,1,BLACK); // tongue right 2
  GLCD.FillRect(62,47,1,2,BLACK); // tongue center 
  GLCD.FillRect(58,52,9,1,BLACK); // tongue center 2
  GLCD.FillRect(70,47,1,2,BLACK); // tongue left
  GLCD.FillRect(68,50,1,1,BLACK); // tongue left 2
  
delay(3000);


GLCD.ClearScreen();
GLCD.CursorTo(6, 3); 
GLCD.print("It is hot");
GLCD.CursorTo(7, 4); 
GLCD.print("as cuss.");

delay(4000);

}


void loop()
{
  getTemp();
  face();
  drawScreen();
  for (int a = 0 ; a < 20 ; a++) // wait 20x delay until the next reading
  {
  delay(100); // wait 
  }
  sweat();
  
}


