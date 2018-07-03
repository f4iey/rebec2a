/* Arduino Uno RX FPV
 *  to control motors & servos
 *  compatible with AtTiny85
 */
#include <SPI.h>
#include <RF24.h> 
#include <Servo.h>
RF24 rx (7, 8);
byte adresses[6] = {"0"}; //meme code couleur que pur le tx
Servo leftWing; //on déclare l'aileron gauche
Servo rightWing; //et le droit
int angleX;
int angleY;
byte taille_message = sizeof(int);
int rc[3] = {angleX, angleY}; //en attent de recevoir le paquet

void setup() {
  leftWing.attach(9);
  rightWing.attach(10);
  //réglages radio
  rx.begin();
  rx.setChannel(115); //meme canal que rx
  rx.setPALevel(RF24_PA_MAX); //puissance max
  rx.setDataRate(RF24_250KBPS); //vitesse lente
  rx.openReadingPipe(1, adresses[0]); //on lui donne le code couleur à utiliser
  rx.startListening(); //c'est parti

}

void loop() {
  if(rx.available()) {
    while(rx.available()) {
      rx.read(&rc, sizeof(rc)); //on utilise les données recues pour les ailerons
      if((rc[0] == 0) and (rc[1] != 0)) {
        //pitch: on va chercher angleY dans le tableau
        leftWing.write(rc[1]);
        rightWing.write(rc[1]);
      }

      else if((rc[1] == 0) and (rc[0] !=0)) {
        //roll: on va chercher angleX dans le tableau
        rightWing.write(rc[0]);
        leftWing.write(-1*rc[0]);
      }
      delay(15);
      //reste les directions intermédiaires...
      
    }
    //perte de connexion
     
  }
    //pas de télécommande à proximité    

}
