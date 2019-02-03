#include <SoftwareSerial.h>

SoftwareSerial BTserial(0, 1); // RX | TX

// defines pins numbers
const int trigPin = 9;
const int echoPin = 10;
// defines variables
double duration1;
double duration2;
double distance1;
double distance2;
int velocity;
//double distance2;

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
BTserial.begin(9600);
}
void loop() {
// Clears the trigPin
digitalWrite(trigPin, LOW);
delayMicroseconds(2);


// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

// Reads the echoPin, returns the sound wave travel time in microseconds
duration1 = pulseIn(echoPin, HIGH);

// find distance 1
distance1 = duration1*0.034/2;

delay(200);

// Clears the trigPin
//digitalWrite(trigPin, LOW);
//delayMicroseconds(2);

// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);

duration2 = pulseIn(echoPin, HIGH);

// find second distance after the object has moved
distance2 = duration2*0.034/2;


velocity = (distance1 - distance2)/(0.2);

/*
Serial.print("distance1: ");
Serial.println(distance1);
Serial.print("distance2: ");
Serial.println(distance2);
Serial.print("displacement: ");
Serial.println(distance1 - distance2);
Serial.print("velocity: ");
Serial.println(velocity);
*/
if(abs(velocity) <= 3){
  velocity = 0;
  BTserial.println("Not moving");
  BTserial.print(velocity);
  BTserial.println("cm/s");
}
else if(abs(velocity) > 10000){
  BTserial.println("Undetectable");
}
else if(velocity < 0){
  BTserial.println("going away");
  BTserial.print(velocity);
  BTserial.println("cm/s");
}
else if(velocity > 15){
  BTserial.println("Danger!!!");
  BTserial.print(velocity);
  BTserial.println("cm/s");
}
else if(velocity > 0){
  BTserial.println("Approaching");
  BTserial.print(velocity);
  BTserial.println("cm/s");
}

/*
Prints the distance on the Serial Monitor
Serial.print("Distance: ");
Serial.println(distance);
*/

delay(200);

}
