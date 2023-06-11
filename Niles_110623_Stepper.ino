//steppermotor
#include <Stepper.h> // Hinzufügen der Programmbibliothek.
int SPU = 2048; // Schritte pro Umdrehung.
#define IN1 14
#define IN2 27
#define IN3 26
#define IN4 25

Stepper Motor(SPU, IN1,IN2,IN3,IN4); // Der Schrittmotor erhält die Bezeichnung "Motor" und es wird angegeben an welchen Pins der Motor angeschlossen ist.

// Position des Steppermotors
int Position = 0; // zukuenftige Position
int momPos = 0; // Momentane Positioin
int Bewegung = 2048; // wie viele Umdrehungen werden gebraucht um weier zu kommen ?

//einbinden der Bibliotheken für das
//ansteuern des MFRC522 Moduls
#include <SPI.h>
#include <MFRC522.h>
//definieren der Pins  RST & SDA für den ESP32
#define RST_PIN     22
#define SS_PIN      21
//erzeugen einer Objektinstanz
MFRC522 mfrc522(SS_PIN, RST_PIN);
//Variable zum speichern der bereits gelesenen RFID-ID
String lastRfid = "";

bool Zubereitung;

//Variablen zum hinterlegen der RFID´s der Zutaten 

String SouthernComfortRFID = " fe b0 1e 3f"; 

String MaracujasirupRFID = " ee 22 24 3f"; 

String GingeraleRFID = " 6b 54 51 3b"; 

String WodkaRFID = " 7b 9d 67 3b"; 

String SahneRFID = " 4b 12 5c 3b"; 

String BlueCuracaoRFID = " 4b 46 be 3b"; 

String KokossirupRFID = " fa bf ae d3"; 

String RumRFID = " ea 00 a9 d3"; 

String AnanassaftRFID = " 8a 50 b4 d3"; 

String MandelsirupRFID = " 7a 42 b6 d3"; 

String ZuckersirupRFID = " fe 5f 2b 3f"; 

String OrangensaftRFID = " fa e6 b3 d3"; 

String KaffeelikoerRFID = " 5e 5a 21 3f"; 

String TomatensaftRFID = " 7b 55 ff 3b"; 

String LimettensaftRFID = " 9b fb 7b 3b"; 

String CointreuRFID = " 9b b4 45 3b"; 

String CranberrynektarRFID = " 6b 0b 77 3b"; 

String GrenadineRFID = " 7b 77 2e 3b"; 

String PfirsichlikoerRFID =  " 5b 7f 7f 3b"; 

 
//Welcher Cocktail wird Zubereitet?
String Cocktail ="";

//Variablen zum hinterlegen der RFID´s der Cocktails 

String SOTBRFID = " 5b f9 8d 3b"; 

String CosmopolitanRFID = " 4b ab 60 3b"; 

String BloodyMaryRFID = " 3b e4 e3 3b"; 

String PinaColadaRFID = " 9b bd 29 3b"; 

String LadySunshineRFID = " 9b 3d f9 3b"; 

String SwimmingpoolRFID = " 3b 92 60 3b"; 

String MaiTaiRFID = " aa a7 a4 d3"; 

String WhiteRussionRFID = " 1e 18 20 3f"; 

//Variable zum speichern der eingespannten Zutaten 

bool SouthernComfort; 

bool Maracujasirup; 

bool Gingerale; 

bool Wodka; 

bool Sahne; 

bool BlueCuracao; 

bool Kokossirup; 

bool Rum; 

bool Ananassaft; 

bool Mandelsirup; 

bool Zuckersirup; 

bool Orangensaft; 

bool Kaffeelikoer; 

bool Tomatensaft; 

bool Limettensaft; 

bool Cointreu; 

bool Cranberrynektar; 

bool Grenadine; 

bool Pfirsichlikoer; 

 
 

//Variablen zum speichern wie viel von welcher Zutat benötigt wird 

int SouthernComfortMAss = 0; 

int MaracujasirupMAss = 0; 

int GingeraleMAss = 0; 

int WodkaMAss = 0; 

int SahneMAss = 0; 

int BlueCuracaoMAss = 0; 

int KokossirupMAss = 0; 

int RumMAss = 0; 

int AnanassaftMAss = 0; 

int MandelsirupMAss = 0; 

int ZuckersirupMAss = 0; 

int OrangensaftMAss = 0; 

int KaffeelikoerMAss = 0; 

int TomatensaftMAss = 0; 

int LimettensaftMAss = 0; 

int CointreuMAss = 0; 

int CranberrynektarMAss = 0; 

int GrenadineMAss = 0; 

int PfirsichlikoerMAss = 0; 

String Startstring = " 3b c1 40 3b";
String Zuruecksetzen = " 9b 58 36 3b"; 

#include <ESP32Servo.h>
 
Servo myservo;  // create servo object to control a servo
// 16 servo objects can be created on the ESP32


//Servomotor
int pos = 0;    // variable to store the servo position
int Hoch = 180;
int Tief = 0;

// Recommended PWM GPIO pins on the ESP32 include 2,4,12-19,21-23,25-27,32-33 
int servoPin = 13;
 
void setup() {
	// Allow allocation of all timers
	ESP32PWM::allocateTimer(0);
	ESP32PWM::allocateTimer(1);
	ESP32PWM::allocateTimer(2);
	ESP32PWM::allocateTimer(3);
	myservo.setPeriodHertz(50);    // standard 50 hz servo
	myservo.attach(servoPin, 500, 2400); // attaches the servo on pin 18 to the servo object
	// using default min/max of 1000us and 2000us
	// different servos may require different min/max settings
	// for an accurate 0 to 180 sweep
  //beginn der seriellen Kommunikation mit 115200 Baud
  Serial.begin(115200);
  //eine kleine Pause von 50ms.
  delay(50);
  //begin der SPI Kommunikation
  SPI.begin();
  //initialisieren der Kommunikation mit dem RFID Modul
  mfrc522.PCD_Init();
  //Steppermotor
  Motor.setSpeed(5); // Angabe der Geschwindigkeit in Umdrehungen pro Minute.
}
 
void loop() {
  //Wenn keine neue Karte vorgehalten wurde oder die serielle Kommunikation
  //nicht gegeben ist, dann...
  if ( ! mfrc522.PICC_IsNewCardPresent() || ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }
  String newRfidId = "";
  for (byte i = 0; i < mfrc522.uid.size; i++) {
    // !! Achtung es wird ein Leerzeichen vor der ID gesetzt !!
    newRfidId.concat(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
    newRfidId.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  //alle Buchstaben in Großbuchstaben umwandeln
  newRfidId.toLowerCase();
  //Wenn die neue gelesene RFID-ID ungleich der bereits zuvor gelesenen ist,
  //dann soll diese auf der seriellen Schnittstelle ausgegeben werden.
  if (!newRfidId.equals(lastRfid)) {
    //überschreiben der alten ID mit der neuen
    lastRfid = newRfidId;
    Serial.print(" gelesene RFID-ID :");
    Serial.println(newRfidId);
    Serial.println();
    if (newRfidId.equals(Zuruecksetzen)) 

    { 

        SouthernComfort = false; 

        Maracujasirup = false; 

        Gingerale = false; 

        Wodka = false; 

        Sahne = false; 

        BlueCuracao = false; 

        Kokossirup = false; 

        Rum = false; 

        Ananassaft = false; 

        Mandelsirup = false; 

        Zuckersirup = false; 

        Orangensaft = false; 

        Kaffeelikoer = false; 

        Tomatensaft = false; 

        Limettensaft = false; 

        Cointreu = false; 

        Cranberrynektar = false; 

        Grenadine = false; 

        Pfirsichlikoer = false; 

 
 

        SouthernComfortMAss = 0; 

        MaracujasirupMAss = 0; 

        GingeraleMAss = 0; 

        WodkaMAss = 0; 

        SahneMAss = 0; 

        BlueCuracaoMAss = 0; 

        KokossirupMAss = 0; 

        RumMAss = 0; 

        AnanassaftMAss = 0; 

        MandelsirupMAss = 0; 

        ZuckersirupMAss = 0; 

        OrangensaftMAss = 0; 

        KaffeelikoerMAss = 0; 

        TomatensaftMAss = 0; 

        LimettensaftMAss = 0; 

        CointreuMAss = 0; 

        CranberrynektarMAss = 0; 

        GrenadineMAss = 0; 

        PfirsichlikoerMAss = 0; 

 
 

        Zubereitung = false; 
        Position = 0;

 
 

    } 
    if (newRfidId.equals(Startstring))
    {
      Zubereitung = true;
    }
     while (newRfidId.equals(SouthernComfortRFID) && SouthernComfortMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       SouthernComfortMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(MaracujasirupRFID) && MaracujasirupMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       MaracujasirupMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(GingeraleRFID) && GingeraleMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       GingeraleMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(WodkaRFID) && WodkaMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       WodkaMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(SahneRFID) && SahneMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       SahneMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(BlueCuracaoRFID) && BlueCuracaoMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       BlueCuracaoMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(KokossirupRFID) && KokossirupMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       KokossirupMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(RumRFID) && RumMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       RumMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(AnanassaftRFID) && AnanassaftMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       AnanassaftMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(MandelsirupRFID) && MandelsirupMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       MandelsirupMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(ZuckersirupRFID) && ZuckersirupMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       ZuckersirupMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(OrangensaftRFID) && OrangensaftMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       OrangensaftMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(KaffeelikoerRFID) && KaffeelikoerMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       KaffeelikoerMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(TomatensaftRFID) && TomatensaftMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       TomatensaftMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(LimettensaftRFID) && LimettensaftMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       LimettensaftMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(CointreuRFID) && CointreuMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       CointreuMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(CranberrynektarRFID) && CranberrynektarMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       CranberrynektarMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(GrenadineRFID) && GrenadineMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       GrenadineMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }
     while (newRfidId.equals(PfirsichlikoerRFID) && PfirsichlikoerMAss != 0 && Zubereitung == true)
  {
     for (pos = Tief; pos <= Hoch; pos += 1) { // goes from 0 degrees to 180 degrees
     		// in steps of 1 degree
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
       PfirsichlikoerMAss -= 1;
     	for (pos = Hoch; pos >= Tief; pos -= 1) { // goes from 180 degrees to 0 degrees
     		myservo.write(pos);    // tell servo to go to position in variable 'pos'
     		delay(15);             // waits 15ms for the servo to reach the position
     	}
  }

  if (newRfidId.equals(SouthernComfortRFID))
  {
    Serial.println("Southern Comfort ist gescannt");
    SouthernComfort=true;
  }

  if (newRfidId.equals(MaracujasirupRFID))
  {
    Serial.println("Maracujasirup ist gescannt");
    Maracujasirup=true;
  }

  if (newRfidId.equals(GingeraleRFID))
  {
    Serial.println("Gingerale ist gescannt");
    Gingerale=true;
  }

  if (newRfidId.equals(WodkaRFID))
  {
    Serial.println("Wodka ist gescannt");
    Wodka=true;
  }
  if (newRfidId.equals(SahneRFID))
  {
    Serial.println("Sahne ist gescannt");
    Sahne=true;
  }
  if (newRfidId.equals(BlueCuracaoRFID))
  {
    Serial.println("Blue Curacao ist gescannt");
    BlueCuracao=true;
  }
  if (newRfidId.equals(KokossirupRFID))
  {
    Serial.println("Kokossirup ist gescannt");
    Kokossirup=true;
  }
  if (newRfidId.equals(RumRFID))
  {
    Serial.println("Rum ist gescannt");
    Rum=true;
  }
  if (newRfidId.equals(AnanassaftRFID))
  {
    Serial.println("Ananassaft ist gescannt");
    Ananassaft=true;
  }
  if (newRfidId.equals(MandelsirupRFID))
  {
    Serial.println("Mandelsirup ist gescannt");
    Mandelsirup=true;
  }
  if (newRfidId.equals(ZuckersirupRFID))
  {
    Serial.println("Zuckersirup ist gescannt");
    Zuckersirup=true;
  }
  if (newRfidId.equals(OrangensaftRFID))
  {
    Serial.println("Orangensaft ist gescannt");
    Orangensaft=true;
  }
  if (newRfidId.equals(KaffeelikoerRFID))
  {
    Serial.println("Kaffeelikoer ist gescannt");
    Kaffeelikoer=true;
  }
  if (newRfidId.equals(TomatensaftRFID))
  {
    Serial.println("Tomatensaft ist gescannt");
    Tomatensaft=true;
  }
  if (newRfidId.equals(LimettensaftRFID))
  {
    Serial.println("Limettensaft ist gescannt");
    Limettensaft=true;
  }
  if (newRfidId.equals(CointreuRFID))
  {
    Serial.println("Cointreu ist gescannt");
    Cointreu=true;
  }
  if (newRfidId.equals(CranberrynektarRFID))
  {
    Serial.println("Cranberrynektar ist gescannt");
    Cranberrynektar=true;
  }
  if (newRfidId.equals(GrenadineRFID))
  {
    Serial.println("Grenadine ist gescannt");
    Grenadine=true;
  }
  if (newRfidId.equals(PfirsichlikoerRFID))
  {
    Serial.println("Pfirsichlikoer ist gescannt");
    Pfirsichlikoer=true;
  }

  if (newRfidId.equals(SOTBRFID) && Pfirsichlikoer == true && Cranberrynektar == true && Orangensaft == true && Wodka == true) 

    { 

       Cocktail = "SOTB"; 

       PfirsichlikoerMAss = 1; 

       CranberrynektarMAss = 3; 

       OrangensaftMAss = 4; 

       WodkaMAss = 2; 

    } 

  if (newRfidId.equals(SOTBRFID) && Pfirsichlikoer == false) 

  { 

    Serial.println("Pfirsichlikoer fehlt"); 

  } 

  if (newRfidId.equals(SOTBRFID) && Cranberrynektar == false) 

  { 

    Serial.println("Cranberrynektar fehlt"); 

  } 

  if (newRfidId.equals(SOTBRFID) && Orangensaft == false) 

  { 

    Serial.println("Orangensaft fehlt"); 

  } 

  if (newRfidId.equals(SOTBRFID) && Wodka == false) 

  { 

    Serial.println("Wodka fehlt"); 

  } 

   

  if (newRfidId.equals(CosmopolitanRFID) && Limettensaft == true && Cointreu == true && Cranberrynektar == true && Wodka == true) 

    { 

      Cocktail = "Cosmopolitan"; 

      LimettensaftMAss = 1; 

      CointreuMAss = 1; 

      CranberrynektarMAss = 1; 

      WodkaMAss = 2; 

    } 

  if (newRfidId.equals(CosmopolitanRFID) && Limettensaft == false) 

  { 

    Serial.println("Limettensaft fehlt"); 

  } 

  if (newRfidId.equals(CosmopolitanRFID) && Cointreu == false) 

  { 

    Serial.println("Cointreu fehlt"); 

  } 

  if (newRfidId.equals(CosmopolitanRFID) && Cranberrynektar == false) 

  { 

    Serial.println("Cranberranektar fehlt"); 

  } 

  if (newRfidId.equals(CosmopolitanRFID) && Wodka == false) 

  { 

    Serial.println("Wodka fehlt"); 

  } 

   

  if (newRfidId.equals(BloodyMaryRFID) && Tomatensaft == true && Limettensaft == true && Wodka == true) 

    { 

      Cocktail = "BloodyMary"; 

      TomatensaftMAss = 2; 

      LimettensaftMAss = 1; 

      WodkaMAss = 1; 

    } 

  if (newRfidId.equals(BloodyMaryRFID) && Tomatensaft == false) 

  { 

    Serial.println("Tomatensaft fehlt"); 

  } 

  if (newRfidId.equals(BloodyMaryRFID) && Limettensaft == false) 

  { 

    Serial.println("Limettensaft fehlt"); 

  } 

  if (newRfidId.equals(BloodyMaryRFID) && Wodka == false) 

  { 

    Serial.println("Wodka fehlt"); 

  } 

   

  if (newRfidId.equals(PinaColadaRFID) && Kokossirup == true && Rum == true && Ananassaft == true) 

    { 

      Cocktail = "PinaColada"; 

      KokossirupMAss = 1; 

      RumMAss = 1; 

      AnanassaftMAss = 2; 

    } 

  if (newRfidId.equals(PinaColadaRFID) && Kokossirup == false) 

  { 

    Serial.println("Kokossirup fehlt"); 

  } 

  if (newRfidId.equals(PinaColadaRFID) && Rum == false) 

  { 

    Serial.println("Rum fehlt"); 

  } 

  if (newRfidId.equals(PinaColadaRFID) && Ananassaft == false) 

  { 

    Serial.println("Ananassaft fehlt"); 

  } 

   

  if (newRfidId.equals(LadySunshineRFID) && Maracujasirup == true && Gingerale == true && Wodka == true && SouthernComfort == true) 

    { 

      Cocktail = "LadySunshine"; 

      MaracujasirupMAss = 1; 

      GingeraleMAss = 2; 

      WodkaMAss = 2; 

      SouthernComfortMAss = 1; 

    } 

  if (newRfidId.equals(LadySunshineRFID) && Maracujasirup == false) 

  { 

    Serial.println("Maracujasirup fehlt"); 

  } 

  if (newRfidId.equals(LadySunshineRFID) && Gingerale == false) 

  { 

    Serial.println("Gingerale fehlt"); 

  } 

  if (newRfidId.equals(LadySunshineRFID) && Wodka == false) 

  { 

    Serial.println("Wodka fehlt"); 

  } 

  if (newRfidId.equals(LadySunshineRFID) && SouthernComfort == false) 

  { 

    Serial.println("SouthernComfort fehlt"); 

  } 

   

  if (newRfidId.equals(SwimmingpoolRFID) && Sahne == true && BlueCuracao == true && Kokossirup == true && Ananassaft == true && Wodka == true) 

    { 

      Cocktail = "Swimmingpool"; 

      SahneMAss = 1; 

      BlueCuracaoMAss = 1; 

      KokossirupMAss = 2; 

      AnanassaftMAss = 6; 

      WodkaMAss = 2; 

    } 

  if (newRfidId.equals(SwimmingpoolRFID) && Sahne == false) 

  { 

    Serial.println("Sahne fehlt"); 

  } 

  if (newRfidId.equals(SwimmingpoolRFID) && BlueCuracao == false) 

  { 

    Serial.println("BlueCuracao fehlt"); 

  } 

  if (newRfidId.equals(SwimmingpoolRFID) && Kokossirup == false) 

  { 

    Serial.println("Kokossirup fehlt"); 

  } 

  if (newRfidId.equals(SwimmingpoolRFID) && Ananassaft == false) 

  { 

    Serial.println("Ananassaft fehlt"); 

  } 

  if (newRfidId.equals(SwimmingpoolRFID) && Wodka == false) 

  { 

    Serial.println("Wodka fehlt"); 

  } 

   

  if (newRfidId.equals(MaiTaiRFID) && Mandelsirup == true && Zuckersirup == true && Ananassaft == true && Orangensaft == true && Rum == true) 

    { 

      Cocktail = "MaiTai"; 

      MandelsirupMAss = 1; 

      ZuckersirupMAss = 1; 

      AnanassaftMAss = 2; 

      OrangensaftMAss = 2; 

      RumMAss = 2; 

    } 

  if (newRfidId.equals(MaiTaiRFID) && Mandelsirup == false) 

  { 

    Serial.println("Mandelsirup fehlt"); 

  } 

  if (newRfidId.equals(MaiTaiRFID) && Zuckersirup == false) 

  { 

    Serial.println("Zuckersirup fehlt"); 

  } 

  if (newRfidId.equals(MaiTaiRFID) && Ananassaft == false) 

  { 

    Serial.println("Ananassaft fehlt"); 

  } 

  if (newRfidId.equals(MaiTaiRFID) && Orangensaft == false) 

  { 

    Serial.println("Orangensaft fehlt"); 

  } 

  if (newRfidId.equals(MaiTaiRFID) && Rum == false) 

  { 

    Serial.println("Rum fehlt"); 

  } 

   

  if (newRfidId.equals(WhiteRussionRFID) && Sahne == true && Wodka == true && Kaffeelikoer == true) 

    { 

      Cocktail = "WhiteRussion"; 

      SahneMAss = 1; 

      WodkaMAss = 1; 

      KaffeelikoerMAss = 1; 

    } 

  if (newRfidId.equals(WhiteRussionRFID) && Sahne == false) 

  { 

    Serial.println("Sahne fehlt"); 

  } 

  if (newRfidId.equals(WhiteRussionRFID) && Wodka == false) 

  { 

    Serial.println("Wodka fehlt"); 

  } 

  if (newRfidId.equals(WhiteRussionRFID) && Kaffeelikoer == false) 

  { 

    Serial.println("Kaffeelikoer fehlt"); 

  } 
  //Wenn es in Zubereitung ist und die Zutat nicht gebraucht wird

  if (newRfidId.equals(SouthernComfortRFID) && Zubereitung == true && SouthernComfortMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }

  if (newRfidId.equals(MaracujasirupRFID) && Zubereitung == true && MaracujasirupMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }

  if (newRfidId.equals(GingeraleRFID) && Zubereitung == true && GingeraleMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }

  if (newRfidId.equals(WodkaRFID) && Zubereitung == true && WodkaMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(SahneRFID) && Zubereitung == true && SahneMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(BlueCuracaoRFID) && Zubereitung == true && BlueCuracaoMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(KokossirupRFID) && Zubereitung == true && KokossirupMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(RumRFID) && Zubereitung == true && RumMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(AnanassaftRFID) && Zubereitung == true && AnanassaftMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(MandelsirupRFID) && Zubereitung == true && MandelsirupMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(ZuckersirupRFID) && Zubereitung == true && ZuckersirupMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(OrangensaftRFID) && Zubereitung == true && OrangensaftMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(KaffeelikoerRFID) && Zubereitung == true && KaffeelikoerMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(TomatensaftRFID) && Zubereitung == true && TomatensaftMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(LimettensaftRFID) && Zubereitung == true && LimettensaftMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(CointreuRFID) && Zubereitung == true && CointreuMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(CranberrynektarRFID) && Zubereitung == true && CranberrynektarMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(GrenadineRFID) && Zubereitung == true && GrenadineMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }
  if (newRfidId.equals(PfirsichlikoerRFID) && Zubereitung == true && PfirsichlikoerMAss == 0)
  {
    Position += 1;
    Serial.println(Position);
  }

  if(Position == 1)
  {
    Serial.println("Motor bewegt sich auf Position 1")
    Motor.step(Bewegung)
    momPos = momPos + Bewegung;
  }

  if(Position == 2)
  {
    Serial.println("Motor bewegt sich auf Position 2")
    Motor.step(Bewegung)
    momPos = momPos + Bewegung;
  }

  if(Position == 3)
  {
    Serial.println("Motor bewegt sich auf Position 3")
    Motor.step(Bewegung)
    momPos = momPos + Bewegung;
  }

  if(Position == 4)
  {
    Serial.println("Motor bewegt sich auf Position 4")
    Motor.step(Bewegung)
    momPos = momPos + Bewegung;
  }

  if(Position == 5)
  {
    Serial.println("Motor bewegt sich auf Position 5")
    Motor.step(Bewegung)
    momPos = momPos + Bewegung;
  }

  if(Position == 6)
  {
    Serial.println("Motor bewegt sich auf Position 6")
    Motor.step(Bewegung)
    momPos = momPos + Bewegung;
  }

  if(Position == 0)
  {
    Serial.println("Motor bewegt sich auf Startposition")
    Motor.step(-momPos)
    momPos = 0;
  }

   }
 
	
}