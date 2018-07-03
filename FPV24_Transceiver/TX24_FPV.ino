/*Arduino Uno TX FPV
 * using 2.4GHz
 * 433: long range, FM mode but more interferences because only one channel
 * 2.4: Smaller antenna, multichannel so less interferences
 */
#include <SPI.h>
#include <RF24.h>
RF24 tx (7, 8);
byte adresses[6] = {"0"}; //fonction d'adressage: sorte de code couleur entre les modules
//initialisation générale
const int ledExpo = 9;
int modeExpo = LOW;
byte swState = LOW;
int impulse = HIGH;
const int xPin = 3; //axe horizontal
const int yPin = 4; //vertical
const int swPin = 5; //bouton poussoir du joystick
int x0, y0, sw0, x, y, sw;
int angleX, angleY; //valeurs de fin

void setup() {
  //conditions initiales joystick
  pinMode(ledExpo, OUTPUT); //la led d'alerte expo
  pinMode(swPin, INPUT); //déclatartion du poussoir
  x0 = analogRead(xPin);
  y0 = analogRead(yPin);
  sw0 = analogRead(swPin);
  //paramètres du TX
  tx.begin();
  tx.setChannel(115); /*le module a 125 canaux (0-124)
  de 2400 à 2525 MHz
  */
  tx.setPALevel(RF24_PA_MAX); //puissance tx au max
  tx.setDataRate(RF24_250KBPS); //vitesse de transmission la plus lente pour plus de portée
  tx.openWritingPipe(adresses[0]); //on demande à l'appareil d'utiliser le code couleur souhaité
  tx.stopListening(); //c'est parti
  delay(1000);
}

void loop() {
  //récupération données joystick

  x = analogRead(xPin) - x0;
  y = analogRead(yPin) - y0;
  swState = analogRead(swPin) - sw0;
  if(swState <=-300) {
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
  angleY = -angleY; //on inverse le joystick vericalement
  //codage des valeurs en radio
  int rc[3] = {angleX, angleY}; //on met nos valeurs a envoyer dans le meme pack
  tx.write(&rc, sizeof(rc)); //on envoie le paquet
}

/*fonction pour permettre des variations exponentielles
 * pour permettre au mode expo de fonctionner.
 */
int mapExp(float valeur, float depart, float arrivee, float nDepart, float nArrivee) {
  nDepart = log(nDepart);
  nArrivee = log(nArrivee);
  float sortie = exp(nDepart + (nArrivee - nDepart) * ((valeur - depart) / (arrivee - depart)));
  sortie = round(sortie);
  return sortie;
}


