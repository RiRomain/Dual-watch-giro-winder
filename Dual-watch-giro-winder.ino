//**************************************************************
//Commande de moteur pas-à-pas unipolaire 4 fils
//tiptopboards.com 05/12/2013
// Driver ULN2003 et moteur réducté au 1:64
//
//**************************************************************
//Inclure la librairie stepper.h
 #include <Stepper.h>
 #define STEPS 100

const int bouton1 = 2;     // Numéro de la broche à laquelle est connecté le bouton poussoir 1
const int bouton2 = 3;      // Numéro de la broche à laquelle est connectée le bouton poussoir 2

  // Déclaration des variables :
int etatBouton1 = 0;         // variable qui sera utilisée pour stocker l'état du bouton 1
int etatBouton2 = 0;         // variable qui sera utilisée pour stocker l'état du bouton 2

  //Créer une instance de la classe stepper
  //Le moteur (fils 1 2 3 4) est branché sur les sorties 9 10 11 12 de l'Arduino (et sur GND, +V)
  Stepper small_stepper1(STEPS, 9, 11, 10, 12);     // Sens horaire
  Stepper small_stepper2(STEPS, 5, 7, 6, 8);     // Sens horaire


  //Stepper small_stepper(STEPS, 11, 10, 9, 8);  // Sens anti-horaire en inversant 8 et 11 (si on préfère)
  int  Steps2Take = 0;  //Nombre de pas de rotation demandé au moteur
  long temps =0;          //Durée de rotation pour un tour
  //************************************************************
  // Pour un moteur de ce type : http://tiptopboards.com/151-moteur-pas-%C3%A0-pas-r%C3%A9duct%C3%A9-de-5v-4-fils-driver-.html
  // 64 pas par tour, 4 phases, angle de 5.625° selon les spécifications du moteur
  // Démultiplication 1:64 pour ce moteur réducté mécaniquement
  //   360° / 5.625° * 64 = 4096 angles avec la démultiplication
  //   360° / 5.625° * 64  * 4 bobines / 2 bipolaire = 2048 step / tour

int Compteur;
void setup()
 {
  Serial.begin(9600);     // 9600 bps
  Serial.println("Test de moteur pas a pas");
  pinMode(4, OUTPUT); // Declare le Pin 5 comme sortie pour la LED
  // indique que la broche led est une sortie :
  pinMode(bouton1, INPUT);      
  // indique que la broche bouton est une entrée :
  pinMode(bouton2, INPUT);
  }

void loop()
  {
  digitalWrite(4, HIGH);
  delay(100);
  // lit l'état du bouton et stocke le résultat dans etatBouton
  etatBouton1 = digitalRead(bouton1);
  etatBouton2 = digitalRead(bouton2);
  Serial.println("Moteur en marche ");
  //Faire tourner le moteur
  small_stepper1.setSpeed(300); //Vitesse de 300 (max) réduire ce chiffre pour un mouvement plus lent
  small_stepper2.setSpeed(300); //Vitesse de 300 (max) réduire ce chiffre pour un mouvement plus lent
  //100 permet d'avoir un couple élevé >300 le moteur vibre sans tourner

if (Compteur<=30 && etatBouton1 == HIGH && etatBouton2 == LOW){
  Serial.println("LOOP1 ");

  Steps2Take  = -4096;  // Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
  //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
  // Exemple  Steps2Take  = -6*2048/30;
  //temps = millis();
  small_stepper1.step(Steps2Take);  //Ca tourne
  //temps =  millis()- temps ;  //Chronomètre un rour complet  6.236 sec par tour à vitesse 200
  //Serial.println(temps);      //Affiche le temps (en ms) pour un tour complet
  delay(2000);  //pause

  Steps2Take  = 4096;  // Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
  //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
  // Exemple  Steps2Take  = -6*2048/30;
  //temps = millis();
  small_stepper1.step(Steps2Take);  //Ca tourne
  //temps =  millis()- temps ;  //Chronomètre un rour complet  6.236 sec par tour à vitesse 200
  //Serial.println(temps);      //Affiche le temps (en ms) pour un tour complet
  delay(2000);  //pause

// Glignotement de la LED
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  delay(100); 
  Compteur++; //Ajoute 1 au Compteur
 }
else if (Compteur<=30 && etatBouton1 == LOW && etatBouton2 == HIGH){
  Serial.println("LOOP2 ");
  Steps2Take  = -4096;  // Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
  //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
  // Exemple  Steps2Take  = -6*2048/30;
  //temps = millis();
  small_stepper2.step(Steps2Take);  //Ca tourne
  //temps =  millis()- temps ;  //Chronomètre un rour complet  6.236 sec par tour à vitesse 200
  //Serial.println(temps);      //Affiche le temps (en ms) pour un tour complet
  delay(2000);  //pause

  Steps2Take  = 4096;  // Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
  //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
  // Exemple  Steps2Take  = -6*2048/30;
  //temps = millis();
  small_stepper2.step(Steps2Take);  //Ca tourne
  //temps =  millis()- temps ;  //Chronomètre un rour complet  6.236 sec par tour à vitesse 200
  //Serial.println(temps);      //Affiche le temps (en ms) pour un tour complet
  delay(2000);  //pause

// Glignotement de la LED
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  delay(100); 
  Compteur++; //Ajoute 1 au Compteur
 }
 else if (Compteur<=30 && etatBouton1 == LOW && etatBouton2 == LOW){
  Serial.println("LOOP1&2 ");
  Steps2Take  = -4096;  // Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
  //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
  // Exemple  Steps2Take  = -6*2048/30;
  //temps = millis();
  small_stepper1.step(Steps2Take);  //Ca tourne
  small_stepper2.step(Steps2Take);  //Ca tourne
  //temps =  millis()- temps ;  //Chronomètre un rour complet  6.236 sec par tour à vitesse 200
  //Serial.println(temps);      //Affiche le temps (en ms) pour un tour complet
  delay(0);  //pause

  Steps2Take  = 4096;  // Une rotation complète avec 2048 pas (1 tour environ 4.5sec)
  //Pour tourner à l'envers de 6 fois 1/30eme de tour, simplement multiplier Steps2Take par 6/30 et mettre un moins pour inverser le sens
  // Exemple  Steps2Take  = -6*2048/30;
  //temps = millis();
  small_stepper1.step(Steps2Take);  //Ca tourne
  small_stepper2.step(Steps2Take);  //Ca tourne
  //temps =  millis()- temps ;  //Chronomètre un rour complet  6.236 sec par tour à vitesse 200
  //Serial.println(temps);      //Affiche le temps (en ms) pour un tour complet
  delay(0);  //pause

// Glignotement de la LED
  digitalWrite(4, LOW);
  delay(100);
  digitalWrite(4, HIGH);
  delay(100); 
  Compteur++; //Ajoute 1 au Compteur
 }
 
 else if (Compteur<=30 && etatBouton1 == HIGH && etatBouton2 == HIGH){
  Serial.println("BUGINTER ");
  Compteur++; //Ajoute 1 au Compteur
  }
  
else if (Compteur <=180){
  Serial.println("PAUSE ");
  digitalWrite(4, LOW);
  delay(1000);
  digitalWrite(4, HIGH);
  delay(1000);
// 10 sec Ecoulé
  Compteur++; //Ajoute 1 au Compteur
}
else {
  Compteur=0; //Réinitialise le Compteur
  }
  }
