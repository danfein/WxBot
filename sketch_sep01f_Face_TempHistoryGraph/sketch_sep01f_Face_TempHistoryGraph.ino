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

void setup() //Global setup
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
void drawScreen() // generate graph
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

void face() //Face animation - Whistle and blink ~8 seconds
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


void loop() //execution loop
{
  getTemp(); //pull the temperature into memory
  face(); //run the face animation
  drawScreen(); //show the temp graph
  for (int a = 0 ; a < 20 ; a++) // wait 20x delay until the next reading
  {
  delay(100); // wait 
  }
}
