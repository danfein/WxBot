#include <glcd.h> //Graphic LCD Library
#include "fonts/SystemFont5x7.h" //std type
int j=7;

void setup()
{
  GLCD.Init(NON_INVERTED); //pixels knockout or not
  GLCD.SelectFont(System5x7); //font to be used in display
  GLCD.ClearScreen(); //clear screen
}

void loop()
{
  GLCD.ClearScreen();
  GLCD.FillRect(19,25,8,8,BLACK); //left eye
    GLCD.DrawRect(15,25,30,1, BLACK); //top line
    GLCD.DrawRect(15,34,30,1, BLACK); //bottom line
  GLCD.FillRect(95,25,8,8,BLACK); //right eye
    GLCD.DrawRect(90,25,30,1, BLACK); //top line
    GLCD.DrawRect(90,34,30,1, BLACK); //bottom line
  GLCD.FillRect(55,50,20,1,BLACK); // mouth

delay(1500);

  GLCD.ClearScreen();
  GLCD.FillRect(32,25,8,8,BLACK); //left eye
    GLCD.DrawRect(15,25,30,1, BLACK); //top line
    GLCD.DrawRect(15,34,30,1, BLACK); //bottom line
  GLCD.FillRect(109,25,8,8,BLACK); //right eye
    GLCD.DrawRect(90,25,30,1, BLACK); //top line
    GLCD.DrawRect(90,34,30,1, BLACK); //bottom line
  GLCD.FillRect(55,50,20,1,BLACK); // mouth

delay(1500);


}
