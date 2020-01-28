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
Servo ESC;
/* ATTENTION:
 * la valeur gazVal doit bien être entre 0 et 255!
 */
int angleX, angleY, gazVal; //de meme que le tx
int rc[4] = {angleX, angleY, gazVal, rudVal}; //en attente de recevoir le paquet
vitesseBrushless(0); //on arme le brushless (procédure de démarrage)

void setup() {
  leftWing.attach(9);
  rightWing.attach(10);
  ESC.attach(6);
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
      vitesseBrushless(rc[2]); //contrôleur
        if(rc[0] > 0) {
            //on braque à droite en plus de monter/descendre
            leftWing.write(map(rc[0], 0, 180, 180, 0)); //on baisse l'elevon gauche
            rightWing.write(rc[1]); //on leve le droit
        }
        
        else if(rc[0] < 0) {
            //on vire à gauche monter/descendre
            rightWing.write(rc[0]); //on baisse l'elevon droit
            leftWing.write(rc[1]); //on lève l'autre
        }
        
      else {
        //pitch: on va chercher angleY dans le tableau
        leftWing.write(rc[1]);
        rightWing.write(rc[1]);
        }
       delay(15); //attend que les servo se mettent en place
      //a tester si double elevon braqués = plus maniable ou pas
      
    }
    //perte de connexion: on fait clignoter la LED à éclats
     
  }
    //pas de télécommande à proximité: on fait clignoter la LED à occultations    
    rx.write(&rc, sizeof(rc)); //on envoie un paquet test toutes les 750ms
    delay(750);
}

void vitesseBrushless(int gaz) {
    int commandeEsc = map(gaz, 0, 255, 0, 180); //applique les positions de joysticks ► Servos à différentes vitesses
    ESC.write(commandeEsc);
}