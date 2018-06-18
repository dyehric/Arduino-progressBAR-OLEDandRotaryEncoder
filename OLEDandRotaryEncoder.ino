//Download and include the Adafruit_SSD1306 link here:
//https://github.com/adafruit/Adafruit_SSD1306

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#if (SSD1306_LCDHEIGHT != 32)


#endif

int val=-1;
int encoder0PinA = 3;
int encoder0PinB = 4;
int encoder0Pos = 0;
int encoder0PinALast = LOW;
int n = LOW;
int maxValue = 10;
void setup() {
  pinMode (encoder0PinA, INPUT);
  pinMode (encoder0PinB, INPUT);

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3D (for the 128x64)
 
  Serial.begin (9600);
}

void loop() {
 
  n = digitalRead(encoder0PinA);
  if ((encoder0PinALast == LOW) && (n == HIGH)) {
    if (digitalRead(encoder0PinB) == LOW) {
       if( encoder0Pos > 0 ){
           encoder0Pos--;
       }
    } else {
      if( encoder0Pos < maxValue ){
          encoder0Pos++;
      }
    }
    Serial.print (encoder0Pos);
    Serial.println();
  }
  encoder0PinALast = n;

if( val != encoder0Pos ){
    val = encoder0Pos;
   display.clearDisplay();

   display.setTextSize(2);

   display.setCursor(0,1);

   display.setTextColor(WHITE);
   display.print("VOL:");
   display.print(encoder0Pos * 10);
  
   drawProgressbar(0,20,120,10, encoder0Pos * 10 );
   display.display();
}
}

void drawProgressbar(int x,int y, int width,int height, int progress)
{

   progress = progress > 100 ? 100 : progress;
   progress = progress < 0 ? 0 :progress;

   float bar = ((float)(width-1) / 100) * progress;
 
   display.drawRect(x, y, width, height, WHITE);
   display.fillRect(x+2, y+2, bar , height-4, WHITE);


  // Display progress text
  if( height >= 15){
    display.setCursor((width/2) -3, y+5 );
    display.setTextSize(1);
    display.setTextColor(WHITE);
   if( progress >=50)
     display.setTextColor(BLACK, WHITE); // 'inverted' text

     display.print(progress);
     display.print("%");
  }


}
