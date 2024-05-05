#include <LiquidCrystal.h> //load the libraries
const int rs = 6, en = 8, d4 = 12, d5 = 11, d6 = 10, d7 = 9;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

const int trigPin = 3;  // Trigger pin of the ultrasonic sensor
const int echoPin = 2;  // Echo pin of the ultrasonic sensor
const int pumpPin = 5;  // Relay pin to control the water pump
const int min_level = 50;
bool level_flag;
const int buzzer = 13; 

void setup() {
  lcd.begin (20,4); //start the LCD based on type 20 columns * 4 rows
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(pumpPin, OUTPUT);
  pinMode(buzzer, OUTPUT);
}

void loop() {
  // Trigger ultrasonic sensor to get distance measurement
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the duration of the pulse from the echo pin
  long duration = pulseIn(echoPin, HIGH);

  // Calculate distance in centimeters
  int distance = duration * 0.034 / 2;

  // Calculate percentage based on tank height and adjust as needed
  int tankHeight = 20;  // Adjust this based on the height of your water tank
  int percentage = map(distance, 4, tankHeight, 100, 0);
  if(percentage>100){
  percentage = 100; }

  // Display the distance and percentage in the Serial monitor
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.print(" cm, Percentage: ");
  Serial.print(percentage);
  Serial.println("%");

  lcd.setCursor(0, 0);
  lcd.print("AUTOMATIC WATER PUMP CONTROLLER");
  //lcd.clear();
  
  lcd.setCursor(0, 1);
  lcd.print("Water Level:");
  lcd.print(percentage);
  lcd.print("%");

  lcd.setCursor(0, 2);
  lcd.print("Pump State:");

  lcd.setCursor(0, 3);
  lcd.print("NWANO ISRAEL C.");
  //lcd.print(distance);
  //lcd.print("cm");

 if(percentage <= min_level){
    level_flag = false;
    digitalWrite(pumpPin,HIGH);
    lcd.setCursor(12, 2);
    lcd.print("ON");
  }

   else if (percentage > min_level && percentage <= 99 && level_flag == false) {
//      fla = 1;
 digitalWrite(pumpPin,HIGH);
 digitalWrite(buzzer,LOW);
 lcd.setCursor(12, 2);
 lcd.print("ON");
 level_flag = false;
    }
else if (percentage > min_level && percentage <= 99 &&  level_flag == true) {
//      fla = 0;
 digitalWrite(pumpPin,LOW);
 digitalWrite(buzzer,LOW);
 lcd.setCursor(12, 2);
 lcd.print("OFF");
 lcd.clear();
      level_flag = true;
    }
    else if (percentage == 100 &&  level_flag == false) {
     level_flag = true;
      //delay(90000);
       digitalWrite(pumpPin,LOW);
       digitalWrite(buzzer,LOW);
       digitalWrite(buzzer,HIGH);
       delay(500);
//      fla = 0;
//      full();
    }
      else if (percentage == 100 &&  level_flag == true) {
     level_flag = true;
      //delay(90000);
       digitalWrite(pumpPin,LOW);
      lcd.setCursor(12, 2);
      lcd.print("OFF");
       
//      fla = 0;
//      full();
    }
else{level_flag = false;}

  
}
