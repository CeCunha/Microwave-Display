// Final Project Arduino
//  ## Microwave Display ##

// Author: Cesar, Hyago and Shuhua.
// Class: Internet of things - Arduino COMP1045

#define NOTE_B0 31
#define NOTE_C1 33
#define NOTE_CS1 35
#define NOTE_D1 37
#define NOTE_DS1 39
#define NOTE_E1 41
#define NOTE_F1 44
#define NOTE_FS1 46
#define NOTE_G1 49
#define NOTE_GS1 52
#define NOTE_A1 55
#define NOTE_AS1 58
#define NOTE_B1 62
#define NOTE_C2 65
#define NOTE_CS2 69
#define NOTE_D2 73
#define NOTE_DS2 78
#define NOTE_E2 82
#define NOTE_F2 87
#define NOTE_FS2 93
#define NOTE_G2 98
#define NOTE_GS2 104
#define NOTE_A2 110
#define NOTE_AS2 117
#define NOTE_B2 123
#define NOTE_C3 131
#define NOTE_CS3 139
#define NOTE_D3 147
#define NOTE_DS3 156
#define NOTE_E3 165
#define NOTE_F3 175
#define NOTE_FS3 185
#define NOTE_G3 196
#define NOTE_GS3 208
#define NOTE_A3 220
#define NOTE_AS3 233
#define NOTE_B3 247
#define NOTE_C4 262
#define NOTE_CS4 277
#define NOTE_D4 294
#define NOTE_DS4 311
#define NOTE_E4 330
#define NOTE_F4 349
#define NOTE_FS4 370
#define NOTE_G4 392
#define NOTE_GS4 415
#define NOTE_A4 440
#define NOTE_AS4 466
#define NOTE_B4 494
#define NOTE_C5 523
#define NOTE_CS5 554
#define NOTE_D5 587
#define NOTE_DS5 622
#define NOTE_E5 659
#define NOTE_F5 698
#define NOTE_FS5 740
#define NOTE_G5 784
#define NOTE_GS5 831
#define NOTE_A5 880
#define NOTE_AS5 932
#define NOTE_B5 988
#define NOTE_C6 1047
#define NOTE_CS6 1109
#define NOTE_D6 1175
#define NOTE_DS6 1245
#define NOTE_E6 1319
#define NOTE_F6 1397
#define NOTE_FS6 1480
#define NOTE_G6 1568
#define NOTE_GS6 1661
#define NOTE_A6 1760
#define NOTE_AS6 1865
#define NOTE_B6 1976
#define NOTE_C7 2093
#define NOTE_CS7 2217
#define NOTE_D7 2349
#define NOTE_DS7 2489
#define NOTE_E7 2637
#define NOTE_F7 2794
#define NOTE_FS7 2960
#define NOTE_G7 3136
#define NOTE_GS7 3322
#define NOTE_A7 3520
#define NOTE_AS7 3729
#define NOTE_B7 3951
#define NOTE_C8 4186
#define NOTE_CS8 4435
#define NOTE_D8 4699
#define NOTE_DS8 4978

#include <LiquidCrystal.h>
#include <Servo.h>

Servo myservo;                                              // Create servo object to control a servo
const int rs = 12, en = 11, d4 = 7, d5 = 6, d6 = 5, d7 = 4; // Pins were LCD is connected
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
int LCD_COLS = 16;  // LCD Cols
int LCD_ROWS = 2;   // LCD Rows
int sec = 0;        // Seconds
int buttonPin1 = 3; // Button 1 connected to Arduino pin 3
int buttonPin2 = 2; // Button 2 connected to Arduino pin 2

int BlueRGB = 8;   // RGB_Blue connected to Arduino pin 8
int RedRGB = 1;    // RGB_Red connected to Arduino pin 9
int GreenRGB = 10; // RGB_Green connected to Arduino pin 10

bool flag = false;  // Variable used to set the Buttons value(functions)
bool stop = false;  // Variable to stop the timer if the user press the Button2
int userTime = 0;   // Time thar user input to cook
int buzzerPin = 13; // The buzzerPin is connected to pin 5 of the Arduino.

int pos = 0; // Variable to store the servo position

void setup() // The setup function runs once.
{
    myservo.attach(9);

    Serial.begin(9600);                                                  // // Opens serial port
    lcd.begin(LCD_COLS, LCD_ROWS);                                       // Initializing LCD
    pinMode(buzzerPin, OUTPUT);                                          // Setup Buzzer pin as an output pin.
    pinMode(buttonPin1, INPUT);                                          // Setup button1 pin as an input pin.
    pinMode(buttonPin2, INPUT);                                          // Setup button2 pin as an input pin.
    pinMode(BlueRGB, OUTPUT);                                            // Setup blue RGB LED pin as an output pin.
    pinMode(RedRGB, OUTPUT);                                             // Setup red RGB LED pin as an output pin.
    pinMode(GreenRGB, OUTPUT);                                           // Setup green RGB LED pin as an output pin.
    attachInterrupt(digitalPinToInterrupt(buttonPin1), TurnOn, CHANGE);  // Change the functionality of Button 1 of "keep pressing" to "onclick"
    attachInterrupt(digitalPinToInterrupt(buttonPin2), TurnOff, CHANGE); // Change the functionality of Button 2, to execute the function TurnOff, when it is pressed.
    lcd.begin(16, 2);                                                    // set up the LCD's number of columns and rows:
    lcd.clear();
    lcd.print("Time to cook!");    // Print a message to the LCD.
    lcd.setCursor(0, 1);           // set up the LCD's number of columns and rows:
    lcd.print("Press B1 to cook"); // Print a message to the LCD.
    RGB_color(255, 0, 0);          // Turns on the Green Led to signal that it is ready to start.
    musicA();                      // Play the musicA to signal that it is ready to start
    delay(500);                    // delay time
    lcd.clear();                   // clear the LCD
}

void loop() // The loop function runs forever.
{
    Display(); // Call the function Display.
}

void Display()
{ // function that make Microwave Display work.

    if (flag)
    {                                                     // press button 1 to begin cooking
        Serial.println("##############################"); // Print msg on Serial Monitor
        Serial.println("#                            #"); // Print msg on Serial Monitor
        Serial.println("#   Input the cooking time   #"); // Print msg on Serial Monitor
        RGB_color(0, 255, 0);                             // Turn on the Green Led to signal that it is ready to cook.

        while (Serial.available() == 0)
        {
        }                                          // wait for user input data
        int userTime = Serial.parseInt();          // read the incoming byte:
        Serial.print("#   The cooking time is: "); // print the cooking time
        Serial.print(userTime);                    // Print userTime
        Serial.println("  #");                     // Print msg on Serial Monitor
        RGB_color(0, 0, 0);                        // Turn off Led
        RGB_color(255, 0, 0);                      // Turn on the Red Led to signal that it is cooking

        for (int j = userTime; j >= 0; j--)
        { // This loop will run the userTime times
            if (j == 0)
            {                                                     // Condition to finish the cooking
                lcd.clear();                                      // Clear LCD
                lcd.setCursor(0, 0);                              // Set LCD position
                lcd.print(" Food is ready!");                     // Print msg on LCD
                Serial.println("#       Food is ready!       #"); // Print msg on Serial Monitor
                Serial.println("#                            #"); // Print msg on Serial Monitor
                Serial.println("##############################"); // Print msg on Serial Monitor
                musicB();                                         // Play musicB to signal that food is ready
                lcd.clear();
                stop = false; // back stop to false to be able to run another time
            }                 // Clear LCD
            else              // Condition to start the counter
            {
                if (stop) // If I press button2 this if will run and will stop my microwave
                {
                    j = 1;
                }
                lcd.clear();           // Clear LCD
                lcd.setCursor(0, 0);   // Set LCD position
                lcd.print(j);          // Print the time of loop on LCD
                lcd.print(" seconds"); // Print "seconds" with J

                // Each for loop here will run 5 times, each time will have a delay of 100ms, so at the end of the 2 loops will have a total of 1000ms, or 1s
                for (pos = 0; pos <= 180; pos += 36)
                {
                    myservo.write(pos);
                    delay(100);
                }
                for (pos = 180; pos >= 0; pos -= 36)
                {
                    myservo.write(pos);
                    delay(100);
                }
            }
        }
    }
}

void TurnOn()
{                // Function that makes button works.
    flag = true; // Change Flag value
}

void TurnOff()	//Function that makes cancel button works.
{
    stop = true; 
}

void RGB_color(int RedRGB_value, int GreenRGB_value, int BlueRGB_value)
{ // function that set colors of RGB Led.
    analogWrite(RedRGB, RedRGB_value);
    analogWrite(GreenRGB, GreenRGB_value);
    analogWrite(BlueRGB, BlueRGB_value);
}

void musicA()
{ // function that play music A

    tone(buzzerPin, NOTE_B4, 200);
    delay(200);
    tone(buzzerPin, NOTE_A4, 200);
    delay(200);
    tone(buzzerPin, NOTE_B4, 800);
    delay(3000);
}

void musicB()
{ // function that play music B
    tone(buzzerPin, NOTE_E5, 600);
    delay(400);
    RGB_color(0, 0, 0);
    delay(400);
    RGB_color(0, 255, 0);
    delay(400);
    tone(buzzerPin, NOTE_E5, 600);
    delay(400);
    RGB_color(0, 0, 0);
    delay(400);
    RGB_color(0, 255, 0);
    delay(400);
    tone(buzzerPin, NOTE_E5, 600);
    delay(400);
    RGB_color(0, 0, 0);
    delay(400);
    RGB_color(0, 255, 0);
    delay(400);
}