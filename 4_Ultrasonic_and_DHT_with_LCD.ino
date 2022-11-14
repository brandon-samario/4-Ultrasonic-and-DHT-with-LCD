/*
  The purpose of this program is to use an lcd in combination with 2 sensors.
  A temperature and humidity sensor DHT11 as well as an ultrasonic sensor HC-SR04.
  This program provides the ability to read the temperature in either celsius or fahrenheit,
  the value of humidity, and the distance in cm.
  All which is then displayed on the lcd showing each of the sensor's values.
  The LCD will "T" for temperature in celsius, "H" for humidity, and "D" for distance.
*/

#include <DHT.h>
#define Type DHT11
#include <LiquidCrystal.h>

#define echoPin 4 // attach pin D4 Arduino to pin Echo of HC-SR04 (Ultrasonic)
#define trigPin 5 //attach pin D5 Arduino to pin Trig of HC-SR04 (Ultrasonic)


// define pins between lcd and ardunio uno
int rs = 7;
int en = 8;
int d4 = 9;
int d5 = 10;
int d6 = 11;
int d7 = 12;

// sensor setup
int sensePin = 2;
DHT HT(sensePin, Type);
float humidity;
float tempC;
float tempF;
int setTime = 500;
int dt = 1000;

// defines variables
long duration; // variable for the duration of sound wave travel
int distance_cm; // variable for centimeters measurement

// lcd pins
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);


// the loop function runs over and over again forever
void setup()
{

  Serial.begin(9600); // opens serial port, sets data rate to 9600 bps
  lcd.begin(16, 2); // set up the LCD's number of columns and rows
  HT.begin(); // establishes a connection with using sensor DHT11

  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT

}

// the loop function runs over and over again forever
void loop()
{

  humidity = HT.readHumidity();
  tempC = HT.readTemperature(true); // Celsius is set as the unit of temperature to be used
  tempF = HT.readTemperature(); // Fahrenheit can be set as the unit of temperature if set to true

  lcd.setCursor(0, 0); // position of text on lcd (will show on 1st column)
  lcd.print("T= "); // print text on lcd
  lcd.print(tempC); // print temperature value in celsius on lcd

  lcd.setCursor(9, 0); // position of text on lcd (will show on position 9 on 1st column)
  lcd.print("H= "); // print text on lcd
  lcd.print(humidity); // print humidity value on lcd
  lcd.print(" %"); // print text on lcd

  lcd.setCursor(0, 1); // position of text on lcd (will show on 2nd column)
  lcd.print("D= "); // print text on lcd
  lcd.print(distance_cm); // print distance value in cm on lcd
  lcd.println("cm"); // print text on lcd

  delay(setTime); // wait time (setime = 500ms)


  // Clears the trigPin condition
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // Sets the trigPin HIGH - ACTIVE
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);

  // Formula for calculating the distance
  distance_cm = duration * 0.034 / 2; // Speed of sound wave divided by 2 (travel and back)


  Serial.print("H: "); // print text in serial monitor
  Serial.print(humidity); // print humidity value in serial monitor
  Serial.print(" % Temperature "); // print text in serial monitor

  Serial.print(tempC); // print celsius value in serial monitor
  Serial.print(" C "); // print text in serial monitor

  Serial.print(tempF); // print fahrenheit value in serial monitor
  Serial.println(" F "); // print text in serial monitor


  Serial.print("D= "); // print text in serial monitor
  Serial.print(distance_cm); // displays the distance on the Serial Monitor
  Serial.println("cm"); // print text in serial monitor

}

