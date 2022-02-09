/*
  Titre      : Prototype Systeme de ventillation
  Auteur     : Crepin Vardin Fouelefack
  Date       : 09/02/2021
  Description: Deplacement du sevomoteur de 0 a 90 degre en fonction de la position du sensor rotation
  Droits     : Reproduction permise pour usage pédagogique
  Source     : Partie de code de     https://docs.arduino.cc/learn/electronics/servo-motors
                                     https://wiki.dfrobot.com/Analog_Rotation_Sensor_V2__SKU__DFR0058_

  Version    : 0.0.1
*/


#include <Arduino.h>
#include "WIFI_NINA_Connector.h"
#include "MQTTConnector.h"
#include <Servo.h>

Servo myservo;  // create servo object to control a servo

int pos = 0;    // variable to store the servo position

const int analogInPin = A1;   // Analog input pin that the potentiometer is attached to
int sensorValue = 0;         //  value read from the AnalogInPin
const int DIG_MOTEUR   = 2; //   Broche digital pour le servomoteur


void setup() {
  // initialize serial communications at 9600 bps:
  Serial.begin(9600);
  myservo.attach(2);                  // attaches the servo on pin 2 to the servo object

  //Initialisation des broches
  pinMode(analogInPin, INPUT);

}

void loop() {
  // read the analog in value:
  sensorValue = analogRead(analogInPin);

  // map it to the range of the analog out:
  pos = map(sensorValue, 0, 1023, 0, 255);
  // change the analog out value if value is in (0-90)
  if (pos >=0 && pos <=90)
  {
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(20);                       // waits 20ms for the servo to reach the position

  }

 appendPayload("CapteurRotation", sensorValue);  //Ajout de la valeur de la position du Capteur de rotation au message MQTT
  appendPayload("PosServoMoteur", pos);  //Ajout de la valeur de la position du servomoteur au message MQTT

  sendPayload();                                   //Envoie du message via le protocole MQTT

  // wait 2 milliseconds before the next loop
  // for the analog-to-digital converter to settle
  // after the last reading:
  delay(1000);
}

