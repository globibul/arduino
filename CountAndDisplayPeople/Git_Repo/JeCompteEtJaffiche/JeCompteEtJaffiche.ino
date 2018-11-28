//www.elegoo.com
#include <LiquidCrystal.h>
#include "SR04.h"
#include "string.h"

#define TRIG_PIN 6
#define ECHO_PIN 5
#define RED_LED 4

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int position;
long DistanceCurrent;
long DistancePrevious;
long NbPassage;
float RatioDist;
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);
char Text[17] = "Passage         ";
int aff_nb;
int i;

void setup() {
  Serial.begin(9600);
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  DistanceCurrent = 2214;
  DistancePrevious = 2214;
  NbPassage = 0;
  delay(1000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.println(Text);
  lcd.setCursor(0, 1);
  lcd.println("                ");
  lcd.setCursor(0, 1);
}


void loop() {


  DistanceCurrent = sr04.Distance();
  // Vérifier le ratio.
  // Si le ratio est différent de 1 donc il y'a un passage

  RatioDist = DistanceCurrent - DistancePrevious;
  RatioDist = abs (RatioDist);
  if (RatioDist >= 40)
  { 
    NbPassage++;
    aff_nb = NbPassage / 2;  
    lcd.setCursor(0, 1);
    lcd.print(aff_nb);
        for (i=0; i<3;i++)
        {
        digitalWrite(RED_LED, HIGH);
        delay(100);
        digitalWrite(RED_LED, LOW);
      delay(100);
        }
    //serial begin
    Serial.print("Nombre de passage:");
    Serial.println(aff_nb);
    
  }
  DistancePrevious = DistanceCurrent;
}
