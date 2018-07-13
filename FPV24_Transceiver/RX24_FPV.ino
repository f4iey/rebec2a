/* Arduino Uno RX FPV
 *  to control motors & servos
 *  compatible with AtTiny85
 */
#include <SPI.h>
#include <RF24.h> 
#include <Servo.h>
RF24 rx (7, 8);
byte adresses[6] = {"0"}; //meme code couleur que pour le tx
Servo leftWing; //on déclare l'aileron gauche
Servo rightWing; //et le droit
const int npnMot = 6; //on déclare l'ensemble moteur variateur
/* ATTENTION:
 * la valeur gazVal doit bien être entre 0 et 255!
 */
int angleX, angleY, gazVal; //de meme que le tx
int rc[3] = {angleX, angleY, gazVal}; //en attente de recevoir le paquet

void setup() {
  leftWing.attach(9);
  rightWing.attach(10);
  //réglages radio
  rx.begin();
  rx.setChannel(115); //meme canal que rx
  rx.setPALevel(RF24_PA_MAX); //puissance max
  rx.setDataRate(RF24_250KBPS); //vitesse lente
  rx.openReadingPipe(1, adresses[0]); //on lui donne le code couleur à utiliser
  rx.openWritingPipe(adresses[0]); //on lui permet d'ecrire
  rx.startListening(); //c'est parti

}

void loop() {
  if(rx.available()) {
    //on met la LED en constant si on en a une
    while(rx.available()) {
      rx.read(&rc, sizeof(rc)); //on utilise les données recues pour les ailerons
      analogWrite(npnMot, rc[2]); //variateur
        if(rc[0] > 0) {
            //on braque à droite en plus de monter/descendre
            leftWing(-1*rc[0]); //on baisse l'elevon gauche
            rightWing(rc[1]); //on leve le droit
        }
        
        else if(rc[0] < 0) {
            //on vire à gauche monter/descendre
            rightWing(rc[0]); //on baisse l'elevon droit
            leftWing(rc[1]); //on lève l'autre
        }
        
      else {
        //pitch: on va chercher angleY dans le tableau
        leftWing.write(rc[1]);
        rightWing.write(rc[1]);
        }
       delay(15);
      //a tester si double elevon braqués = plus maniable ou pas
      
    }
    //perte de connexion: on fait clignoter la LED à éclats
     
  }
    //pas de télécommande à proximité: on fait clignoter la LED à occultations    
    rx.write(&rc, sizeof(rc)); //on envoie un paquet test toutes les 750ms
    delay(750);
}
