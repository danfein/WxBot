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

#include <glcd.h>                // include the graphics LCD library
#include <fonts/SystemFont5x7.h> // include the standard character fonts for it

#include <Wire.h>                // Barometer is an i2c device, this is needed to chat with it
#include <Adafruit_Sensor.h>     // sensor foundation library
#include <Adafruit_BMP085_U.h>   // library for barometer

/* This driver uses the Adafruit unified sensor library (Adafruit_Sensor),
   which provides a common 'type' for sensor data and some helper functions.
   
   To use this driver you will also need to download the Adafruit_Sensor
   library and include it in your libraries folder.

   You should also assign a unique ID to this sensor for use with
   the Adafruit Sensor API so that you can identify this particular
   sensor in any data logs, etc.  To assign a unique ID, simply
   provide an appropriate value in the constructor below (12345
   is used by default in this example).
   
   Connections
   ===========
   Connect SCL to analog 5
   Connect SDA to analog 4
   Connect VDD to 3.3V DC
   Connect GROUND to common ground
    
   History
   =======
   2013/JUN/17  - Updated altitude calculations (KTOWN)
   2013/FEB/13  - First version (KTOWN)
*/   
Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);


#include <DHT.h>          // Library for humidity sensor
#include <DHT_U.h>        // and it's pal
#define  DHTTYPE DHT22    // tell the library what I am workin with - DHT 22 (AM2302)
#define DHTPIN 3          // Humidity sensor is on pin 2

DHT_Unified dht(DHTPIN, DHTTYPE);
uint32_t delayMS;

int tcurrent;
int tempArray[100];         //For the temp graph data

float hcurrent;
float humidArray[100];      //for humidity graph

float pcurrent;
float pressArray[100];      //For barometric pressure graph

void setup()
{
  GLCD.Init(NON_INVERTED);  // configure GLCD
  GLCD.ClearScreen();       // turn off all GLCD pixels
  GLCD.SelectFont(System5x7);
  
  Serial.begin(9600); 
  // Initialize device.
  
  //DHT22 setup
  dht.begin();
  Serial.println("DHTxx Unified Sensor Example");
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Temperature");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" *C");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" *C");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" *C");  
  Serial.println("------------------------------------");
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.println("Humidity");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println("%");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println("%");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println("%");  
  Serial.println("------------------------------------");
  // Set delay between sensor readings based on sensor details.
  delayMS = sensor.min_delay / 1000;
  
  
  //BMP180 setup
  Serial.println("Pressure Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bmp.begin())
  {
    /* There was a problem detecting the BMP085 ... check your connections */
    Serial.print("Ooops, no BMP085 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
}

void getTemp()           //Read from DHT22
{
  sensors_event_t event;  
  dht.temperature().getEvent(&event);
  tcurrent = event.temperature;
  // insert the new temperature at the start of the array of past temperatures
  for (int a = 99 ; a >= 0 ; --a )
  {
    tempArray[a] = tempArray[a-1];
  }
  tempArray[0] = tcurrent;
}


void getHumid()           //Read from DHT22 
{

  sensors_event_t event;  
  dht.humidity().getEvent(&event);
  hcurrent = event.relative_humidity;
  // insert the new temperature at the start of the array of past values
  for (int a = 99 ; a >= 0 ; --a )
  {
    humidArray[a] = humidArray[a-1];
  }
  humidArray[0] = hcurrent;
  
}


void getPressure()              //Read from BMP180 humidity sensor
{
  /* Get a new sensor event */ 
  sensors_event_t event;
  bmp.getEvent(&event);
  pcurrent = event.pressure;
  
  Serial.print(event.pressure); //for testing
  
  GLCD.ClearScreen();
  GLCD.CursorTo(1,2);
  GLCD.print("Barometric Pressure");
  GLCD.CursorTo(4,3);
  GLCD.print(pcurrent);
  GLCD.print(" hPa");
  
  delay(2000);
}

void drawTemp()                 // generate Temp graph
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
  delay(2000);
}

void drawHumid()                // generate Humidity graph
{
  int q;
  GLCD.ClearScreen();
  GLCD.CursorTo(0, 0);
  GLCD.Puts("Current:");
  GLCD.PrintNumber(hcurrent);
  GLCD.Puts(" % Humidity");
  GLCD.CursorTo(0, 1);
  GLCD.PrintNumber(80);
  GLCD.CursorTo(0, 2);
  GLCD.PrintNumber(60);
  GLCD.CursorTo(0, 3);
  GLCD.PrintNumber(40);
  GLCD.CursorTo(0, 4);
  GLCD.PrintNumber(20);
  GLCD.CursorTo(0, 5);
  GLCD.PrintNumber(10);
  GLCD.CursorTo(0, 6);
  GLCD.PrintNumber(0);
  for (int a = 28 ; a < 127 ; a++)
  {
    q = (55 - (humidArray[a-28]/2) );
    GLCD.SetDot(a, q, BLACK);
  }
  delay(2000);
}

void face()                        //Face animation
{
  
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

void sweat()                      //Humidity Face
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
  
delay(1500);

/*
GLCD.ClearScreen();
GLCD.CursorTo(6, 3); 
GLCD.print("It is hot");
GLCD.CursorTo(7, 4); 
GLCD.print("as cuss.");

delay(4000);
*/
}

void shifty()
{
  for (int a = 0 ; a < 2 ; a++) // eyes back and for this many times
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
}

void loop()
{
  getTemp();                     // Get temperature into memory
  face();                        // whistling face
  drawTemp();                    // display temp graph
  sweat();                       // sweaty hot face
  getHumid();                    // put humidity into array
  drawHumid();                   // display humidity graph
  shifty();                      // shifty face
  getPressure();                 // Display pressure
}


