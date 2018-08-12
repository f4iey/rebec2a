/*Arduino Uno TX FPV
 * using 2.4GHz
 * 433: long range, FM mode but more interferences because only one channel
 * 2.4: Smaller antenna, multichannel so less interferences
 */
#define C 523
#define G 784
#define G# 831
#define D# 622
#define F 698
#include <SPI.h>
#include <RF24.h>
RF24 tx (7, 8);
byte adresses[6] = {"0"}; //fonction d'adressage: sorte de code couleur entre les modules
//initialisation générale
const int ledExpo = 9;
int modeExpo = LOW;
const int xPin = A3; //axe horizontal
const int yPin = A4; //vertical
const int swPin = 5; //switch digital pour le mode expo
const int gazPin = 6; //manette des gaz
int x0, y0, swEtat, x, y, sw, gazVal;
int angleX, angleY; //valeurs de fin
int buzz = 3; //pour affecter au digit 3

void setup() {
  pinMode(gazPin, INPUT); //la gestion des gaz se fait uniquement via tx
  //conditions initiales joystick
  pinMode(ledExpo, OUTPUT); //la led d'alerte expo
  digitalWrite(ledExpo, HIGH); /*la led expo est utilisée pour montrer que
  * le TX est en train de s'allumer */
  pinMode(swPin, INPUT); //déclatartion du poussoir
  x0 = analogRead(xPin);
  y0 = analogRead(yPin);
  swEtat = digitalRead(swPin);
  digitalWrite(ledExpo, LOW);
  //paramètres du TX
  digitalWrite(ledExpo, HIGH);
  tx.begin();
  tx.setChannel(115); /*le module a 125 canaux (0-124)
  de 2400 à 2525 MHz
  */
  tx.setPALevel(RF24_PA_MAX); //puissance tx au max
  tx.setDataRate(RF24_250KBPS); //vitesse de transmission la plus lente pour plus de portée
  tx.openWritingPipe(adresses[0]); //on demande à l'appareil d'utiliser le code couleur souhaité
  tx.openReadingPipe(1, adresses[0]); //on lui permet d'écouter
  tx.startListening(); //c'est parti
  digitalWrite(ledExpo, LOW); /*tout va bien l'utilisateur confirme que le TX
  est correctement allumé */
  musique(); //c'est parti pour la SNCF!
  delay(1000);
  while(not tx.available()) {
    //en attente de connexion 
    //on fait clignoter la LED expo
    digitalWrite(ledExpo, HIGH);
    musiqueConnect();
    digitalWrite(ledExpo, LOW);
    delay(250);
  }
  //on émet un son pour dire qu'on est connecté
  tone(buzz, C);
  delay(500);
  noTone(buzz);
  tx.stopListening();
}

void loop() {
  //récupération données joystick
  x = analogRead(xPin) - x0;
  y = analogRead(yPin) - y0;
  //pour utiliser le switch expo:
  if(swEtat == HIGH) {
    //si le switch est fermé
      digitalWrite(ledExpo, HIGH); //on allume la led expo
    }
    else {
    digitalWrite(ledExpo, LOW); //on allume la led expo
    }

  modeExpo = digitalRead(ledExpo); //on regarde si la LED verte est allumée
  if(modeExpo == HIGH) {
    //si le mode expo est actif
    angleX = mapExp(x, 0, 1023, 0, 20); //en degrés
    angleY = mapExp(y, 0, 1023, 0, 20);
  }

  else {
    //sinon on laisse les paramètres linéaires
    angleX = map(x, 0, 1023, 0, 20); //en degrés
    angleY = map(y, 0, 1023, 0, 20);
  }
  angleY = -angleY; //on inverse le joystick vericalement
  gazVal = analogRead(gazPin); //récupération de la tension induite par la manette
  gazVal = map(gazVal, 0, 1023, 0, 255); //adaptation en numérique pour le NPN
  //codage des valeurs en radio
  int rc[3] = {angleX, angleY, gazVal}; //on met nos valeurs a envoyer dans le meme pack
  tx.write(&rc, sizeof(rc)); //on envoie le paquet
  delayMicroseconds(500);
}

/*fonction pour permettre des variations exponentielles
 * pour permettre au mode expo de fonctionner.
 * problème de valeurs... à corriger
 */
int mapExp(float valeur, float min, float max, float nMin, float nMax) {
  float p = nMax / exp(max);
  float sortie = p * exp(valeur);
  if(sortie < nMin) {
      sortie = nMin;
  }
  else if(sortie > nMax) {
      sortie = nMax
  }
  sortie = round(sortie);
  return sortie;
}

void musique(int pitch=0) {
  //fonction de musique de démarrage    
  tone(buzz, C+pitch);
  delay(500);
  noTone(buzz)
  delay(600);
  tone(buzz, G+pitch);
  delay(500);
  noTone(buzz);
  delay(650);
  tone(buzz, G#+pitch);
  delay(575);
  tone(buzz, D#+pitch);
  delay(500);
  noTone(buzz);
}

void musiqueConnect(int pitch=0) {
  //fonction de musique de connection    
  tone(buzz, D#+pitch);
  delay(250);
  tone(buzz, F+pitch);
  delay(250);
  tone(buzz, G+pitch);
  delay(250);
  noTone(buzz);
  delay(250);
}
