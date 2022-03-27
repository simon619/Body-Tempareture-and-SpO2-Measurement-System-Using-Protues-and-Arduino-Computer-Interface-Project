#include <LiquidCrystal.h>
LiquidCrystal lcd(3,4,10,11,12,13);
const int sensor=A3;
int pulse = 0;
int lr = 0;
int li = 0;
void setup() {
  // put your setup code here, to run once:
  pinMode(A0,INPUT);  //define pin as input
  pinMode(A1,INPUT);  //define pin as input
  pinMode(A2,INPUT);  //define pin as input
  pinMode(5,OUTPUT);  //define pin as output 
  pinMode(6,OUTPUT);  //define pin as output 
  pinMode(7,OUTPUT);  //define pin as output 
  
  lcd.begin(16,2); //Sets the screen dimensions
  lcd.setCursor(0,0); //starts the cursor at position 0,0
  lcd.print("Instrumentation"); //Print the word instrumentation
  lcd.setCursor(3,1); //starts the cursor at position 3,1
  lcd.print("Medic"); //Print the word medic
  delay(2000); //delay 500ms
  lcd.clear(); //clears the screen
  lcd.setCursor(0,0); ////starts the cursor at position 0,0
  lcd.print("PulseOximeter"); //Print the word pulseOximeter
  lcd.setCursor(0,1); //starts the cursor at position 0,1
  lcd.print("Patient"); //Print the word patient
  delay(2000); //delay 500ms
  lcd.clear(); //clears the screen
  Serial.begin(9600); //passes the value 9600 to the speed parameter. This tells the Arduino to get ready to exchange messages with the Serial Monitor at a data rate of 9600 bits per second
  Serial.println("Tempareture Sensor");
  Serial.println();
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  pulse=analogRead(A0); //assign the value of input a0 to the varial
  lr=analogRead(A1); //assign the value of input a1 to the varial
  li=analogRead(A2); //assign the value of input a1 to the varial
  lr=map(lr,0,1023,00,150); //map takes the value of ir and converts to to the new range
  li=map(lr,0,1023,00,100); //maps the mean values ​​and gives it a value
  lcd.clear(); //clears the screen
  lcd.setCursor(0,0); //starts the cursor at position 0,0 
  lcd.print("PPM: "); //Print the word "PPM"
  lcd.setCursor(4,0); //starts the cursor at position 4,0
  lcd.print(lr);  //Print value of l
  lcd.setCursor(8,0); //starts the cursor at position 8,0
  lcd.print("SPO2: "); //Print the word "SPO2"
  lcd.setCursor(13,0); //starts the cursor at position 13,0
  lcd.print(li); //Print value of li
  lcd.setCursor(15,0); //starts the cursor at position 15,0
  lcd.print("%"); 
  if(li<90) { // Compare that li is less than 90
    digitalWrite(7,HIGH); //put a high value on pin 7
    digitalWrite(5,HIGH); //put a high value on pin 7
    lcd.setCursor(3,1); //starts the cursor at position 3,1
    lcd.print("Sick"); //Print sick
  }
  else {
    digitalWrite(7,LOW); //put a low value on pin 7
    digitalWrite(5,LOW); //put a low value on pin 5
  }
  if(li>=90&&li<=93) { //Compare that li is greater than or equal to 90 and less than equal to 93
    digitalWrite(6,HIGH); //put a high value on pin 6
    lcd.setCursor(3,1); //starts the cursor at position 3,1
    lcd.print("Alright");  //Print lucky day
  }
  else {
    digitalWrite(6,LOW); //put a high value on pin 6
  }
  delay(150); //delay 150ms 
  int vout=analogRead(sensor); //initialize sensor in varaible
  vout=(vout*4.88)/10;
  int tempc=vout; //convert it into int value
  int tempf=(vout*1.8)+32;
  Serial.print("Temperature in C=");
  Serial.print("\t");
  Serial.print(tempc);
  Serial.print("Temperature in F=");
  Serial.print("\t");
  Serial.print(tempf);
  Serial.println(); 
  delay(1000); 
}
