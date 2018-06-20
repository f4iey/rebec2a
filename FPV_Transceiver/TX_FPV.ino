/*Arduino Uno TX FPV
 * on 433MHz or 2.4GHz
 * 433: long range, FM mode but more interferences because only one channel
 * 2.4: Smaller antenna, multichannel so less interferences
 */
#include <VirtualWire.h>
const int ledExpo = 9;
int modeExpo = LOW;
byte swState = LOW;
int impulse = HIGH;
const int tx = 6;
const int xPin = 3;
const int yPin = 4;
const int swPin = 5; //possible to use for Expo
int x0, y0, sw0, x, y, sw;
int angleX, angleY;

void setup() {
  //conditions initiales joystick
  pinMode(ledExpo, OUTPUT); //la led d'alerte expo
  pinMode(swPin, INPUT); //déclatartion du switch button
  x0 = analogRead(xPin);
  y0 = analogRead(yPin);
  sw0 = analogRead(swPin);
  //paramètres du TX
  vw_set_tx_pin(tx);
  
}

void loop() {
  //récupération données joystick

  x = analogRead(xPin) - x0;
  y = analogRead(yPin) - y0;
  sw = analogRead(swPin) - sw0;
  swState = digitalRead(swPin);
  if(swState == HIGH) {
    //si on presse le bouton joystick
    if(impulse == LOW) {
      digitalWrite(ledExpo, LOW); //led expo disabled
      impulse = HIGH; //prochain appui, on allume
    }
    else {
    digitalWrite(ledExpo, HIGH); //on allume la led expo
    impulse = LOW; //prochain appui: on l'éteint
    }
  }

  modeExpo = digitalRead(ledExpo);
  if(modeExpo == HIGH) {
    //si le mode expo est actif
    angleX = mapExp(x, 0, 1023, 0, 30); //en degrés
    angleY = mapExp(y, 0, 1023, 0, 30);
  }

  else {
    //sinon on laisse les paramètres linéaires
    angleX = map(x, 0, 1023, 0, 30); //en degrés
    angleY = map(y, 0, 1023, 0, 30);
  }
  //codage des valeurs en radio
  if(angleY != 0) {
    vw_send((byte*) &angleY, sizeof(angleY));
    vw_wait_tx();
  }
  delay(5);
  if(angleX != 0) {
    vw_send((byte*) &angleX, sizeof(angleX));
    vw_wait_tx();
  } 
}

int mapExp(float valeur, float depart, float arrivee, float nDepart, float nArrivee) {
  nDepart = log(nDepart);
  nArrivee = log(nArrivee);
  float sortie = exp(nDepart + (nArrivee - nDepart) * ((valeur - depart) / (arrivee - depart)));
  sortie = round(sortie);
  return sortie;
}


