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
#define Ff 698
#define N_DATA 3
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
int x, y;
int buzz = 3; //pour affecter au digit 3
struct Package {
  int gazVal;
  //char aprs[60];
  int steerVal;
  uint8_t acc; //accessory trigger
};
struct Package rc;
int ackData[N_DATA] = {15, 15, 0};
bool remote = false;
int remoteData[N_DATA]; 


void setup() {
  pinMode(gazPin, INPUT); //la gestion des gaz se fait uniquement via tx
  //conditions initiales joystick
  pinMode(ledExpo, OUTPUT); //la led d'alerte expo
  digitalWrite(ledExpo, HIGH); /*la led expo est utilisée pour montrer que
  * le TX est en train de s'allumer */
  x = analogRead(xPin);
  y = analogRead(yPin);
  digitalWrite(ledExpo, LOW);
  //paramètres du TX
  digitalWrite(ledExpo, HIGH);
  SPI.begin();
  Serial.begin(115200);
  tx.begin();
  tx.setChannel(69); /*le module a 125 canaux (0-124)
  de 2400 à 2525 MHz
  */
  tx.setPALevel(RF24_PA_MAX); //puissance tx au max
  tx.setDataRate(RF24_250KBPS); //vitesse de transmission la plus lente pour plus de portée
  tx.enableAckPayload();
  tx.setRetries(5,5); //delay,count
  tx.openWritingPipe(adresses[0]); //on demande à l'appareil d'utiliser le code couleur souhaité
 // tx.openReadingPipe(1, adresses[0]); //on lui permet d'écouterh
  digitalWrite(ledExpo, LOW); /*tout va bien l'utilisateur confirme que le TX
  est correctement allumé */
  musique(0); //c'est parti pour la SNCF!
  delay(1000);
  //tentavtive de connexion
//  for(int i=0; i<3; i++) {
//    //on fait clignoter la LED expo
//    if(tx.available()) break;
//    digitalWrite(ledExpo, HIGH);
//    musiqueConnect(0);
//    digitalWrite(ledExpo, LOW);
//    if(tx.available()) break;
//    delay(250);
//  }
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
  if(!remote){
      rc.steerVal = 40; //map(x, 0, 1023, 20, 65); //en degrés: full gauche à full droite
      rc.gazVal = analogRead(gazPin); //récupération de la tension induite par la manette
      rc.acc = 0; //feature, les accesoires ne sont accessible qu'en remote 
  }
  else{
    rc.gazVal = remoteData[0];
    rc.steerVal = remoteData[1];
    rc.acc = remoteData[2];
  }
  //remote control
  if(Serial.available()){ //0x57 = W et 0x52 =R
      remote = true;
      String cmd = Serial.readStringUntil('\n');
      cmd.trim();
      if(cmd.startsWith("R")){
        String ans = "R";
        for(int i=0;i<N_DATA;i++){
          ans += String(ackData[i]);
          if (i<N_DATA - 1) ans += ",";
        }
        Serial.println(ans);
      }
        else if (cmd.startsWith("W")){
          String param = cmd.substring(1);
          param.trim();
          if(param.length() == 0) Serial.println("F");
          else if(param.indexOf(',') == -1){
            //un seul param
            int val1 = param.toInt();
            remoteData[0] = val1;
            Serial.println("R1");
          }
          else if(param.indexOf(',', param.indexOf(',')+1) == -1){
            //deux param
            int val1 = cmd.substring(1, cmd.indexOf(',', 1)).toInt();
            String vals2 = cmd.substring(cmd.indexOf(',', 1)+1);
            vals2.trim();
            int val2 = vals2.toInt();
            remoteData[0] = val1;
            remoteData[1] = val2;
            Serial.println("R2");
          }
          else{
            //trois param
            int val1 = cmd.substring(1, cmd.indexOf(',', 1)).toInt();
            String vals2 = cmd.substring(cmd.indexOf(',', 1)+1);
            String vals3 = cmd.substring(cmd.indexOf(',', cmd.indexOf(',', 1)+1)+1);
            vals2.trim();
            vals3.trim();
            int val2 = vals2.toInt();
            int val3 = vals3.toInt();
            remoteData[0] = val1;
            remoteData[1] = val2;
            remoteData[2] = val3;
            Serial.println("R3");
          }
        }
        else if(cmd.startsWith("X")){
         remote = false; // deconnexion
         Serial.println("R");
      }
      else Serial.println("E"); //commande inconnue
    }
  //écriture des données sur le port SPI
  if(tx.write(&rc, sizeof(rc)) && tx.isAckPayloadAvailable()){
    //on envoie le paquet et on acquitte
    tx.read(&ackData, sizeof(ackData));
    //Serial.println(ackData[0]);
  }
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
  tone(buzz, Ff+pitch);
  delay(125);
  tone(buzz, G+pitch);
  delay(250);
  noTone(buzz);
  delay(125);
}
