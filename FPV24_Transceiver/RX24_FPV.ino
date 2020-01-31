/* Arduino Uno RX FPV
 *  to control motors & servos
 *  compatible with AtTiny85
 */
#include <SPI.h>
#include <RF24.h> 
#include <Servo.h>
RF24 rx (7, 8);
byte adresses[][6] = {"0"}; //meme code couleur que pour le tx
Servo leftWing; //on déclare l'aileron gauche
Servo rightWing; //et le droit
Servo ESC;

struct Package{
  int angleX;
  int angleY;
  int gazVal;
  int rudVal; //de meme que le tx
};
struct Package rc;

/* ATTENTION:
 * la valeur gazVal doit bien être entre 0 et 1023!
 */

void setup() {
  leftWing.attach(9);
  rightWing.attach(10);
  ESC.attach(6);
  //réglages radio
  SPI.begin;
  rx.begin();
  Serial.begin(115200);
  rx.setChannel(69); //meme canal que rx
  rx.setPALevel(RF24_PA_MAX); //puissance max
  rx.setDataRate(RF24_250KBPS); //vitesse lente
  rx.openReadingPipe(1, adresses[0]); //on lui donne le code couleur à utiliser
  rx.openWritingPipe(adresses[0]); //on lui permet d'ecrire
  //rx.startListening(); //c'est parti
  ESC.write(0); //on arme le brushless (procédure de démarrage)
  delay(15);
}

void loop() {
    //on met la LED en constant si on en a une
    rx.startListening();
    
   if(rx.available()) {
    while(rx.available()) {
      rx.read(&rc, sizeof(rc)); //on utilise les données recues pour les ailerons
      vitesseBrushless(rc.gazVal); //contrôleur
        if(rc.angleX > 90) { //valeur médiane à check sur les vrais sticks
            //on braque à droite en plus de monter/descendre
            leftWing.write(map(rc.angleX, 0, 180, 180, 0)); //on baisse l'elevon gauche
            rightWing.write(rc.angleY); //on leve le droit
        }
        
        else if(rc.angleX < 85) {
            //on vire à gauche monter/descendre
            rightWing.write(rc.angleX); //on baisse l'elevon droit
            leftWing.write(rc.angleY); //on lève l'autre
        }
        
      else {
        //pitch: on va chercher angleY dans le tableau
        leftWing.write(rc.angleY);
        rightWing.write(rc.angleY);
        }
        
       delay(15); //attend que les servo se mettent en place
      //a tester si double elevon braqués = plus maniable ou pas
      
    }
    //perte de connexion: on fait clignoter la LED à éclats
   }   
    //pas de télécommande à proximité: on fait clignoter la LED à occultations
  /*  rx.stopListening();
    rx.write(&rc, sizeof(rc)); //on envoie un paquet test toutes les 750ms
    delay(750);
    rx.startListening();*/
}

void vitesseBrushless(int gaz) {
    int commandeEsc = map(gaz, 0, 1023, 55, 135);
    Serial.println(commandeEsc);//applique les positions de joysticks ► Servos à différentes vitesses
    ESC.write(commandeEsc);
}
