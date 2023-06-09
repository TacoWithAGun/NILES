// Button 

int buttonPin = 34; 

 
 

// startbutton 

int startButtonPin = 25; 

int endButtonPin = 24; 

 
 

// Motor DC 

int motor1Pin1 = 27;  

int motor1Pin2 = 26;  

int enable1Pin = 14; 

 
 

// Servo Motor 

//const int hoch 
//
//const int runter 
//
//#include <Servo.h> 
//
//#define SERVO_PIN 33 
//
//Servo servoMotor; 

 
 
 

// Setting PWM properties 

const int freq = 30000; 

const int pwmChannel = 0; 

const int resolution = 8; 

int dutyCycle = 200; 

 
 

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

 
 

//Variable zum Speichern ob und welcher Cocktail hergestellt werden soll 

String Cocktail = ""; 

bool Zubereitung = false; 

 
 

//spezielle RFID´s 

String Zuruecksetzen = " 9b 58 36 3b"; 

String Startstring = " 3b c1 40 3b"; 

 
 

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

 
 

//Variablen zum hinterlegen der RFID´s der Cocktails 

String SOTBRFID = " 5b f9 8d 3b"; 

String CosmopolitanRFID = " 4b ab 60 3b"; 

String BloodyMaryRFID = " 3b e4 e3 3b"; 

String PinaColadaRFID = " 9b bd 29 3b"; 

String LadySunshineRFID = " 9b 3d f9 3b"; 

String SwimmingpoolRFID = " 3b 92 60 3b"; 

String MaiTaiRFID = " aa a7 a4 d3"; 

String WhiteRussionRFID = " 1e 18 20 3f"; 

//Variable ob man am Start ist oder nicht 

bool Startbool = false; 

bool End = false; 

 
 

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

 
 

void setup() { 

  // put your setup code here, to run once: 

 
 

  Serial.begin(115200); 

  //begin der SPI Kommunikation 

  SPI.begin(); 

  // sets the pins as outputs: 

  pinMode(motor1Pin1, OUTPUT); 

  pinMode(motor1Pin2, OUTPUT); 

  pinMode(enable1Pin, OUTPUT); 

  //set the Button as input sign 

  pinMode(buttonPin, INPUT_PULLUP); 

  pinMode(startButtonPin, INPUT_PULLUP); 

  pinMode(endButtonPin, INPUT_PULLUP); 

 
 

  // attaches the servo on ESP32 pin 

  //servoMotor.attach(SERVO_PIN);   

   

  //initialisieren der Kommunikation mit dem RFID Modul 

  mfrc522.PCD_Init(); 

   

  // configure LED PWM functionalitites 

  ledcSetup(pwmChannel, freq, resolution); 

   

  // attach the channel to the GPIO to be controlled 

  ledcAttachPin(enable1Pin, pwmChannel); 

 
 
 

} 

 
 

void loop() { 

  // put your main code here, to run repeatedly: 

 
 

//Wenn ein Button gedrückt wird soll der Motor gestoppt werden 

 
 

  int buttonValue = digitalRead(buttonPin); 

  int StartButtonValue = digitalRead(startButtonPin); 

  int EndButtonValue = digitalRead(endButtonPin); 

 
 

    if (StartButtonValue == 1) 

  { 

    Startbool = true; 

  } 

 
 

    if (EndButtonValue == 1) 

  { 

    End = true; 

  } 

 
 

  if (Zubereitung == true && SouthernComfortMAss == 0 && MaracujasirupMAss == 0 && GingeraleMAss == 0 && WodkaMAss == 0 && SahneMAss == 0 && BlueCuracaoMAss == 0 && KokossirupMAss == 0 && RumMAss == 0 && AnanassaftMAss == 0 && MandelsirupMAss == 0 && ZuckersirupMAss == 0 && OrangensaftMAss == 0 && KaffeelikoerMAss == 0 && TomatensaftMAss == 0 && LimettensaftMAss == 0 && CointreuMAss == 0 && CranberrynektarMAss == 0 && GrenadineMAss == 0 && PfirsichlikoerMAss == 0) 

  { 

    while (Startbool == false) 

    { 

        //Move DC motor backwards at maximum speed 

        Serial.println("Moving Backwards"); 

        digitalWrite(motor1Pin1, HIGH); 

        digitalWrite(motor1Pin2, LOW);  

        delay(5); 

 
 

        if (StartButtonValue == 1) 

        { 

          Startbool = true; 

          // Stop the DC motor 

          Serial.println("Motor stopped"); 

          digitalWrite(motor1Pin1, LOW); 

          digitalWrite(motor1Pin2, LOW); 

          delay(5); 

        } 

 
 

    } 

  } 

 
 
 
 

  if (buttonValue == 1) 

  { 

    // Stop the DC motor 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, LOW); 

      delay(5); 

  } 

 
 

  if (!mfrc522.PICC_IsNewCardPresent() || !mfrc522.PICC_ReadCardSerial()) 

      { 

          return; 

      } 

    String newRfidId = ""; 

  for (byte i = 0; i < mfrc522.uid.size; i++) 

    { 

        // !! Achtung es wird ein Leerzeichen vor der ID gesetzt !! 

        newRfidId.concat(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "); 

        newRfidId.concat(String(mfrc522.uid.uidByte[i], HEX)); 

    } 

    //alle Buchstaben in kleinbuchstaben umwandeln 

    newRfidId.toLowerCase(); 

 
 

  //Was soll passieren, wenn Southern Comfort gelesen wird? 

  if (newRfidId.equals(SouthernComfortRFID) && SouthernComfortMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotoren temporär auskommentiert, da hardware noch nicht vorhanden. Dafür Serial Print. 

    Serial.println("Servomotor hoch"); 

    delay (30); 

    SouthernComfortMAss -= 1; 

    Serial.println("SouthernComfortMAss = " + SouthernComfortMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (SouthernComfortMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5);

    } 

 
 
 

  } 

 
 

  if (newRfidId.equals(SouthernComfortRFID)) 

  { 

    SouthernComfort = true; 

  } 

  if (newRfidId.equals(SouthernComfortRFID) && SouthernComfortMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5);

  } 

 
 

  //Was soll passieren, wenn Maracujasirup gelesen wird? 

  if (newRfidId.equals(MaracujasirupRFID) && MaracujasirupMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert, da hardware nicht vorhanden. 

    Serial.println("Servomotor hoch");

    delay (30); 

    MaracujasirupMAss -= 1; 

    Serial.println("MaracujasirupMAss = " + MaracujasirupMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (MaracujasirupMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5);

    } 

     

  } 

 
 

  if (newRfidId.equals(MaracujasirupRFID)) 

  { 

    Maracujasirup = true; 

  } 

 
 

  if (newRfidId.equals(MaracujasirupRFID) && MaracujasirupMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

  //Was soll passieren, wenn Gingerale gelesen wird? 

  if (newRfidId.equals(GingeraleRFID) && GingeraleMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temprotär auskommentiert. 

    Serial.println("Servomotor hoch");

    delay (30); 

    GingeraleMAss -= 1; 

    Serial.println("GingeraleMAss = " + GingeraleMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (GingeraleMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

  } 

 
 

  if (newRfidId.equals(GingeraleRFID)) 

  { 

    Gingerale = true; 

  } 

 
 

  if (newRfidId.equals(GingeraleRFID) && GingeraleMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

  //Was soll passieren, wenn Wodka gelesen wird? 

  if (newRfidId.equals(WodkaRFID) && WodkaMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temprotär auskommentiert  

    Serial.println("Servomotor hoch");

    delay (30); 

    WodkaMAss -= 1; 

    Serial.println("WodkaMAss = " + WodkaMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (WodkaMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

  } 

 
 

  if (newRfidId.equals(WodkaRFID)) 

  { 

    Wodka = true; 

  } 

  if (newRfidId.equals(WodkaRFID) && WodkaMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn Sahne gelesen wird? 

  if (newRfidId.equals(SahneRFID) && SahneMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temprorär auskommentiert  

    Serial.println("Servomotor hoch");

    delay (30); 

    SahneMAss -= 1; 

    Serial.println("SahneMAss = " + SahneMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (SahneMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

  } 

  if (newRfidId.equals(SahneRFID)) 

  { 

    Sahne = true; 

  } 

  if (newRfidId.equals(SahneRFID) && SahneMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn Blue Curacao gelesen wird? 

  if (newRfidId.equals(BlueCuracaoRFID) && BlueCuracaoMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert  

    Serial.println("Servomotor hoch");

    delay (30); 

    BlueCuracaoMAss -= 1; 

    Serial.println("BlueCuracaoMAss = " + BlueCuracaoMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (BlueCuracaoMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

  } 

  if (newRfidId.equals(BlueCuracaoRFID)) 

  { 

    BlueCuracao = true; 

  } 

  if (newRfidId.equals(BlueCuracaoRFID) && BlueCuracaoMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 
 

  //Was soll passieren, wenn Kokossirup gelesen wird? 

  if (newRfidId.equals(KokossirupRFID) && KokossirupMAss  && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert 

    Serial.println("Servomotor hoch"); 

    delay (30); 

    KokossirupMAss -= 1; 

    Serial.println("KokossirupMAss= " + KokossirupMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (KokossirupMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

  } 

  if (newRfidId.equals(KokossirupRFID)) 

  { 

    Kokossirup = true; 

  } 

  if (newRfidId.equals(KokossirupRFID) && KokossirupMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn Rum gelesen wird? 

  if (newRfidId.equals(RumRFID) && RumMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert  

    Serial.println("Servomotor hoch"); 

    delay (30); 

    RumMAss -= 1; 

    Serial.println("RumMAss= " + RumMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (RumMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5);

    } 

     

  } 

  if (newRfidId.equals(RumRFID)) 

  { 

    Rum = true; 

  } 

  if (newRfidId.equals(RumRFID) && RumMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn AnanassaftRFID gelesen wird? 

  if (newRfidId.equals(AnanassaftRFID) && AnanassaftMAss  && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    AnanassaftMAss -= 1; 

    Serial.println("AnanassaftMAss= " + AnanassaftMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (AnanassaftMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

  } 

  if (newRfidId.equals(AnanassaftRFID)) 

  { 

    Ananassaft = true; 

  } 

  if (newRfidId.equals(AnanassaftRFID) && AnanassaftMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5);

  } 

 
 

  //Was soll passieren, wenn Mandelsirup gelesen wird? 

  if (newRfidId.equals(MandelsirupRFID) && MandelsirupMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert  

    Serial.println("Servomotor hoch");

    delay (30); 

    MandelsirupMAss -= 1; 

    Serial.println("MandelsirupMAss= " + MandelsirupMAss); 

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (MandelsirupMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5);

    } 

     

  } 

  if (newRfidId.equals(MandelsirupRFID)) 

  { 

    Mandelsirup = true; 

  } 

 
 

  if (newRfidId.equals(MandelsirupRFID) && MandelsirupMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn Zuckersirup gelesen wird? 

  if (newRfidId.equals(ZuckersirupRFID) && ZuckersirupMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    ZuckersirupMAss -= 1; 

    Serial.println("ZuckersirupMAss = " + ZuckersirupMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (ZuckersirupMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

  } 

  if (newRfidId.equals(ZuckersirupRFID)) 

  { 

    Zuckersirup = true; 

  } 

  if (newRfidId.equals(ZuckersirupRFID) && ZuckersirupMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn Orangensaft gelesen wird? 

  if (newRfidId.equals(OrangensaftRFID) && OrangensaftMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    OrangensaftMAss -= 1; 

    Serial.println("OrangensaftMAss= " + OrangensaftMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (OrangensaftMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

     

  } 

  if (newRfidId.equals(OrangensaftRFID)) 

  { 

    Orangensaft = true; 

  } 

 
 

  if (newRfidId.equals(OrangensaftRFID) && OrangensaftMAss == 0 && Zubereitung == true)

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5);

  } 

 
 

  //Was soll passieren, wenn Kaffeelikoer gelesen wird? 

  if (newRfidId.equals(KaffeelikoerRFID) && KaffeelikoerMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    KaffeelikoerMAss -= 1; 

    Serial.println("KaffeelikoerMAss= " + KaffeelikoerMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (KaffeelikoerMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

  } 

  if (newRfidId.equals(KaffeelikoerRFID)) 

  { 

    Kaffeelikoer = true; 

  } 

 
 

  if (newRfidId.equals(KaffeelikoerRFID) && KaffeelikoerMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5);

  } 

 
 

  //Was soll passieren, wenn Tomatensaft gelesen wird? 

  if (newRfidId.equals(TomatensaftRFID) && TomatensaftMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär sukommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    TomatensaftMAss -= 1; 

    Serial.println("TomatensaftMAss= " + TomatensaftMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (TomatensaftMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

 
 

  } 

  if (newRfidId.equals(TomatensaftRFID)) 

  { 

    Tomatensaft = true; 

  } 

  if (newRfidId.equals(TomatensaftRFID) && TomatensaftMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn Limettensaft gelesen wird? 

  if (newRfidId.equals(LimettensaftRFID) && LimettensaftMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotot temporär auskommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    LimettensaftMAss -= 1; 

    Serial.println("LimettensaftMAss= " + LimettensaftMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (LimettensaftMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

     

  } 

  if (newRfidId.equals(LimettensaftRFID)) 

  { 

    Limettensaft = true; 

  } 

  if (newRfidId.equals(LimettensaftRFID) && LimettensaftMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5);

  } 

  //Was soll passieren, wenn Cointreu gelesen wird? 

  if (newRfidId.equals(CointreuRFID) && CointreuMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    CointreuMAss -= 1; 

    Serial.println("CointreuMAss= " + CointreuMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (CointreuMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5);

    } 

     

  } 

  if (newRfidId.equals(CointreuRFID)) 

  { 

   Cointreu = true;  

  } 

   

  if (newRfidId.equals(CointreuRFID) && CointreuMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn Cranberrynektar gelesen wird? 

  if (newRfidId.equals(CranberrynektarRFID) && CranberrynektarMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    CranberrynektarMAss -= 1; 

    Serial.println("CranberrynektarMAss= " + CranberrynektarMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter"); 

    delay (15); 

    if (CranberrynektarMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5);

    } 

     

  } 

  if (newRfidId.equals(CranberrynektarRFID)) 

  { 

    Cranberrynektar = true; 

  } 

 
 

    if (newRfidId.equals(CranberrynektarRFID) && CranberrynektarMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn Grenadine gelesen wird? 

  if (newRfidId.equals(GrenadineRFID) && GrenadineMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotot temporär auskommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    GrenadineMAss -= 1; 

    Serial.println("GrenadineMAss= " + GrenadineMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15);     

    if (GrenadineMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

  } 

  if (newRfidId.equals(GrenadineRFID)) 

  { 

    Grenadine = true; 

  } 

 
 

  if (newRfidId.equals(GrenadineRFID) && GrenadineMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5); 

  } 

 
 

  //Was soll passieren, wenn Pfirsichlikoer gelesen wird? 

  if (newRfidId.equals(PfirsichlikoerRFID) && PfirsichlikoerMAss != 0 && Zubereitung == true) 

  { 

    //servoMotor.write(hoch); Servomotor temporär auskommentiert 

    Serial.println("Servomotor hoch");

    delay (30); 

    PfirsichlikoerMAss -= 1; 

    Serial.println("PfirsichlikoerMAss= "+ PfirsichlikoerMAss);

    //servoMotor.write(runter); 

    Serial.println("Servomotor runter");

    delay (15); 

    if (PfirsichlikoerMAss == 0) 

    { 

      // Move the DC motor forward at maximum speed 

      Serial.println("Moving Forward"); 

      digitalWrite(motor1Pin1, LOW); 

      digitalWrite(motor1Pin2, HIGH); 

      delay (5); 

    } 

  } 

 
 

  if (newRfidId.equals(PfirsichlikoerRFID) && Zubereitung == false) 

  { 

    Pfirsichlikoer = true; 

  } 

 
 

  if (newRfidId.equals(PfirsichlikoerRFID) && PfirsichlikoerMAss == 0 && Zubereitung == true) 

  { 

    // Move the DC motor forward at maximum speed 

     Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

    delay (5);

  } 

  if (newRfidId.equals(Startstring)) 

  { 

    Zubereitung = true; 

    // Move the DC motor forward at maximum speed 

    Serial.println("Moving Forward"); 

    digitalWrite(motor1Pin1, LOW); 

    digitalWrite(motor1Pin2, HIGH); 

  } 

  //Was soll passieren, wenn Zurücksetzen gelesen wird? 

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

 
} 


