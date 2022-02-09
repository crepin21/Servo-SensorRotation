/*
  Titre      : ControleSercoMoteur
  Auteur     : Crepin Vardin Fouelefack
  Date       : 01/02/2021
  Description: Alarme sonnore se declenche lorsque le servo moteur est a 0 ou 180 degre
  Droits     : Reproduction permise pour usage pédagogique
  Source     : Partie de code de     https://docs.arduino.cc/learn/electronics/servo-motors
                                     https://wiki.dfrobot.com/DFRobot_Speaker_v1.0_SKU__FIT0449
  Version    : 0.0.1
*/


#include <Arduino.h>
//#include "WIFI_NINA_Connector.h"
//#include "MQTTConnector.h"

const int DIG_BOUTTON  = 3;
const int DIG_TACTILE  = 4;    //Affectation des broches pour les deifferents capteurs
const int DIG_SPEAKER  = 5;
const int DIG_MOTEUR   = 2;

#include <Servo.h>

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  myservo.attach(2);                  // attaches the servo on pin 2 to the servo object
  pinMode(DIG_BOUTTON, INPUT);   
  pinMode(DIG_TACTILE, INPUT);       // pour lire l'etat des broches
}

void loop() {


    // in steps of 1 degree
  if ( digitalRead(DIG_BOUTTON) == 1 )  //Lorsqu'on appuie sur le boutton
  {
     myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(13);                       // waits 15ms for the servo to reach the position
     pos += 1;
  }
    if (digitalRead(DIG_BOUTTON) == 1 && pos >= 180 )   // Si le boutton est appuie et la position du servo moteur est >=180 degre
    {
            tone(5, 1000,800);
            delay(40);                                 // l'alarme se declenche
           noTone(5);
    }
    
  // Le boutton tactile ne fonctionne pas encore correctemenent
    if (digitalRead(DIG_TACTILE) == 1)
    {

      myservo.write(pos);              // tell servo to go to position in variable 'pos'
     delay(15);                       // waits 15ms for the servo to reach the position
     pos -= 1;
    }
      if (digitalRead(DIG_TACTILE) == 1 && pos <= 0)      // Si le boutton est appuie et la position du servo moteur est <=180 degre
    {
          tone(5, 2000,800);
          delay(40);                                     // l'alarme se declenche
          noTone(5);
    }
}
