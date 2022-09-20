/*Arduino Uno TX FPV
 * using 2.4GHz
 * 2.4: Smaller antenna, multichannel so less interferences
 */
//PROTOS
void musique(int pitch);
void musiqueConnect(int pitch);
int mapExp(float valeur, float min, float max, float nMin, float nMax);
//end PROTOS 
#define C 523
#define G 784
#define GS 831
#define DS 622
#define F 698
#include <SPI.h>
#include <RF24.h>
RF24 tx (7, 8);
byte adresses[][6] = {"0"}; //fonction d'adressage: sorte de code couleur entre les modules
//initialisation générale
const int ledExpo = 9;
const int xPin = A0; //axe horizontal
const int yPin = A1; //vertical
const int gazPin = A4; //manette des gaz
const int rudPin = A5; //gouverne de direction
int x0, y0, x, y;
int buzz = 3; //pour affecter au digit 3
struct Package {
  int gazVal;
  //char aprs[60];
  int steerVal;
};
struct Package rc;

void setup() {
  pinMode(gazPin, INPUT); //la gestion des gaz se fait uniquement via tx
  //conditions initiales joystick
  pinMode(ledExpo, OUTPUT); //la led d'alerte expo
  digitalWrite(ledExpo, HIGH); /*la led expo est utilisée pour montrer que
  * le TX est en train de s'allumer */
  pinMode(swPin, INPUT); //déclatartion du poussoir
  x0 = analogRead(xPin);
  y0 = analogRead(yPin);
  digitalWrite(ledExpo, LOW);
  //paramètres du TX
  digitalWrite(ledExpo, HIGH);
  SPI.begin();
  tx.begin();
  tx.setChannel(69); /*le module a 125 canaux (0-124)
  de 2400 à 2525 MHz
  */
  tx.setPALevel(RF24_PA_MAX); //puissance tx au max
  tx.setDataRate(RF24_250KBPS); //vitesse de transmission la plus lente pour plus de portée
  tx.openWritingPipe(adresses[0]); //on demande à l'appareil d'utiliser le code couleur souhaité
  tx.openReadingPipe(1, adresses[0]); //on lui permet d'écouter
  digitalWrite(ledExpo, LOW); /*tout va bien l'utilisateur confirme que le TX
  est correctement allumé */
  musique(0); //c'est parti pour la SNCF!
  delay(1000);
  //tentavtive de connexion
  for(int i=0; i<3; i++) {
    //on fait clignoter la LED expo
    if(tx.available()) break;
    digitalWrite(ledExpo, HIGH);
    musiqueConnect(0);
    digitalWrite(ledExpo, LOW);
    if(tx.available()) break;
    delay(250);
  }
  //on émet un son pour dire qu'on est connecté
  tone(buzz, C);
  digitalWrite(ledExpo, HIGH);
  delay(500);
  noTone(buzz);
}

void loop() {
  //récupération données joystick: need cal?
  x = analogRead(xPin); /*- x0*/
  y = analogRead(yPin); /*- y0*/
  digitalWrite(ledExpo, LOW); //on allume la led expo
  //sinon on laisse les paramètres linéaires
  rc.steerVal = map(x, 0, 1023, 0, 180); //en degrés

  rc.gazVal = analogRead(gazPin); //récupération de la tension induite par la manette
  //écriture des données sur le port SPI
  tx.write(&rc, sizeof(rc)); //on envoie le paquet
  delay(15);
}

void musique(int pitch) {
  //fonction de musique de démarrage    
  tone(buzz, C+pitch);
  delay(500);
  tone(buzz, G+pitch);
  delay(500);
  tone(buzz, GS+pitch);
  delay(275);
  tone(buzz, DS+pitch);
  delay(500);
  noTone(buzz);
}

void musiqueConnect(int pitch) {
  //fonction de musique de connection    
  tone(buzz, DS+pitch);
  delay(125);
  tone(buzz, F+pitch);
  delay(125);
  tone(buzz, G+pitch);
  delay(250);
  noTone(buzz);
  delay(125);
}
