// Button
int buttonPin = 34;

// startbutton
int startBututtonPin = 25;
int endButtonPin = 24;

// Motor DC
int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14;

// Servo Motor
const int hoch
const int runter
#include <Servo.h>
#define SERVO_PIN 33
Servo servoMotor;


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
String Zurücksetzen = " 9b 58 36 3b";
String Start = " 3b c1 40 3b";

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
bool Start = false;
bool End == false;

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
int SouthernComfortMAß = 0;
int MaracujasirupMAß = 0;
int GingeraleMAß = 0;
int WodkaMAß = 0;
int SahneMAß = 0;
int BlueCuracaoMAß = 0;
int KokossirupMAß = 0;
int RumMAß = 0;
int AnanassaftMAß = 0;
int MandelsirupMAß = 0;
int ZuckersirupMAß = 0;
int OrangensaftMAß = 0;
int KaffeelikoerMAß = 0;
int TomatensaftMAß = 0;
int LimettensaftMAß = 0;
int CointreuMAß = 0;
int CranberrynektarMAß = 0;
int GrenadineMAß = 0;
int PfirsichlikoerMAß = 0;

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
    Start = true;
  }

    if (EndButtonValue == 1)
  {
    End = true;
  }

  if (Zubereitung == true && SouthernComfortMAß == 0 && MaracujasirupMAß == 0 && GingeraleMAß == 0 && WodkaMAß == 0 && SahneMAß == 0 && BlueCuracaoMAß == 0 && KokossirupMAß == 0 && RumMAß == 0 && AnanassaftMAß == 0 && MandelsirupMAß == 0 && ZuckersirupMAß == 0 && OrangensaftMAß == 0 && KaffeelikoerMAß == 0 && TomatensaftMAß == 0 && LimettensaftMAß == 0 && CointreuMAß == 0 && CranberrynektarMAß == 0 && GrenadineMAß == 0 && PfirsichlikoerMAß == 0)
  {
    while (Start == false)
    {
        //Move DC motor backwards at maximum speed
        Serial.println("Moving Backwards");
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW); 
        delay(5);

        if (StartButtonValue == 1)
        {
          Start = true;
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
  if (newRfid.equals(SouthernComfortRFID) && SouthernComfortMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotoren temporär auskommentiert, da hardware noch nicht vorhanden. Dafür Serial Print.
    serial.println("Servomotor hoch");
    delay (30);
    SouthernComfortMAß -= 1;
    serial.println("SouthernComfortMAß = " + SouthernComfortMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (SouthernComfortMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }


  }

  if (newRfid.equals(SouthernComfortRFID))
  {
    SouthernComfort = true;
  }
  if (newRfid.equals(SouthernComfortRFID) && SouthernComfortMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Maracujasirup gelesen wird?
  if (newRfid.equals(MaracujasirupRFID) && MaracujasirupMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert, da hardware nicht vorhanden.
    serial.println("Servomotor hoch")
    delay (30);
    MaracujasirupMAß -= 1;
    serial.println("MaracujasirupMAß = " + MaracujasirupMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (MaracujasirupMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }

  if (newRfid.equals(MaracujasirupRFID))
  {
    Maracujasirup = true;
  }

  if (newRfid.equals(MaracujasirupRFID) && MaracujasirupMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }
  //Was soll passieren, wenn Gingerale gelesen wird?
  if (newRfid.equals(GingeraleRFID) && GingeraleMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temprotär auskommentiert.
    serial.println("Servomotor hoch")
    delay (30);
    GingeraleMAß -= 1;
    serial.println("GingeraleMAß = " + GingeraleMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (GingeraleMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }

  if (newRfid.equals(GingeraleRFID))
  {
    Gingerale = true;
  }

  if (newRfid.equals(GingeraleRFID) && GingeraleMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }
  //Was soll passieren, wenn Wodka gelesen wird?
  if (newRfid.equals(WodkaRFID) && WodkaMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temprotär auskommentiert 
    serial.println("Servomotor hoch")
    delay (30);
    WodkaMAß -= 1;
    serial.println("WodkaMAß = " + WodkaMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (WodkaMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }

  if (newRfid.equals(WodkaRFID))
  {
    Wodka = true;
  }
  if (newRfid.equals(WodkaRFID) && WodkaMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Sahne gelesen wird?
  if (newRfid.equals(SahneRFID) && SahneMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temprorär auskommentiert 
    serial.println("Servomotor hoch")
    delay (30);
    SahneMAß -= 1;
    serial.println("SahneMAß = " + SahneMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (SahneMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(SahneRFID))
  {
    Sahne = true;
  }
  if (newRfid.equals(SahneRFID) && SahneMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Blue Curacao gelesen wird?
  if (newRfid.equals(BlueCuracaoRFID) && BlueCuracaoMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert 
    serial.println("Servomotor hoch")
    delay (30);
    BlueCuracaoMAß -= 1;
    serial.println("BlueCuracaoMAß = " + BlueCuracaoMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (BlueCuracaoMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(BlueCuracaoRFID))
  {
    BlueCuracao = true;
  }
  if (newRfid.equals(BlueCuracaoRFID) && BlueCuracaoMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }


  //Was soll passieren, wenn Kokossirup gelesen wird?
  if (newRfid.equals(KokossirupRFID) && KokossirupMAß  && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    KokossirupMAß -= 1;
    serial.println("KokossirupMAß= " + KokossirupMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (KokossirupMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(KokossirupRFID))
  {
    Kokossirup = true;
  }
  if (newRfid.equals(KokossirupRFID) && KokossirupMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Rum gelesen wird?
  if (newRfid.equals(RumRFID) && RumMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert 
    serial.println("Servomotor hoch")
    delay (30);
    RumMAß -= 1;
    serial.println("RumMAß= " + RumMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (RumMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(RumRFID))
  {
    Rum = true;
  }
  if (newRfid.equals(RumRFID) && RumMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn AnanassaftRFID gelesen wird?
  if (newRfid.equals(AnanassaftRFID) && AnanassaftMAß  && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    AnanassaftMAß -= 1;
    serial.println("AnanassaftMAß= " + AnanassaftMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (AnanassaftMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(AnanassaftRFID))
  {
    Ananassaft = true;
  }
  if (newRfid.equals(AnanassaftRFID) && AnanassaftMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Mandelsirup gelesen wird?
  if (newRfid.equals(MandelsirupRFID) && MandelsirupMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert 
    serial.println("Servomotor hoch")
    delay (30);
    MandelsirupMAß -= 1;
    serial.println("MandelsirupMAß= " + MandelsirupMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (MandelsirupMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(MandelsirupRFID))
  {
    Mandelsirup = true;
  }

  if (newRfid.equals(MandelsirupRFID) && MandelsirupMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Zuckersirup gelesen wird?
  if (newRfid.equals(ZuckersirupRFID) && ZuckersirupMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    ZuckersirupMAß -= 1;
    serial.println("ZuckersirupMAß = " + ZuckersirupMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (ZuckersirupMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(ZuckersirupRFID))
  {
    Zuckersirup = true;
  }
  if (newRfid.equals(ZuckersirupRFID) && ZuckersirupMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Orangensaft gelesen wird?
  if (newRfid.equals(OrangensaftRFID) && OrangensaftMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    OrangensaftMAß -= 1;
    serial.println("OrangensaftMAß= " + OrangensaftMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (OrangensaftMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
    
  }
  if (newRfid.equals(OrangensaftRFID))
  {
    Orangensaft = true;
  }

  if (newRfid.equals(OrangensaftRFID) && OrangensaftMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Kaffeelikoer gelesen wird?
  if (newRfid.equals(KaffeelikoerRFID) && KaffeelikoerMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    KaffeelikoerMAß -= 1;
    serial.println("KaffeelikoerMAß= " + KaffeelikoerMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (KaffeelikoerMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(KaffeelikoerRFID))
  {
    Kaffeelikoer = true;
  }

  if (newRfid.equals(KaffeelikoerRFID) && KaffeelikoerMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Tomatensaft gelesen wird?
  if (newRfid.equals(TomatensaftRFID) && TomatensaftMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär sukommentiert
    serial.println("Servomotor hoch")
    delay (30);
    TomatensaftMAß -= 1;
    serial.println("TomatensaftMAß= " + TomatensaftMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (TomatensaftMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }

  }
  if (newRfid.equals(TomatensaftRFID))
  {
    Tomatensaft = true;
  }
  if (newRfid.equals(TomatensaftRFID) && TomatensaftMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Limettensaft gelesen wird?
  if (newRfid.equals(LimettensaftRFID) && LimettensaftMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotot temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    LimettensaftMAß -= 1;
    serial.println("LimettensaftMAß= " + LimettensaftMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (LimettensaftMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(LimettensaftRFID))
  {
    Limettensaft = true;
  }
  if (newRfid.equals(LimettensaftRFID) && LimettensaftMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }
  //Was soll passieren, wenn Cointreu gelesen wird?
  if (newRfid.equals(CointreuRFID) && CointreuMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    CointreuMAß -= 1;
    serial.println("CointreuMAß= " + CointreuMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (CointreuMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(CointreuRFID))
  {
   Cointreu = true; 
  }
  
  if (newRfid.equals(CointreuRFID) && CointreuMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Cranberrynektar gelesen wird?
  if (newRfid.equals(CranberrynektarRFID) && CranberrynektarMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    CranberrynektarMAß -= 1;
    serial.println("CranberrynektarMAß= " + CranberrynektarMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (CranberrynektarMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
    
  }
  if (newRfid.equals(CranberrynektarRFID))
  {
    Cranberrynektar = true;
  }

    if (newRfid.equals(CranberrynektarRFID) && CranberrynektarMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Grenadine gelesen wird?
  if (newRfid.equals(GrenadineRFID) && GrenadineMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotot temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    GrenadineMAß -= 1;
    serial.println("GrenadineMAß= " + GrenadineMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);    
    if (GrenadineMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
  }
  if (newRfid.equals(GrenadineRFID))
  {
    Grenadine = true;
  }

  if (newRfid.equals(GrenadineRFID) && GrenadineMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }

  //Was soll passieren, wenn Pfirsichlikoer gelesen wird?
  if (newRfid.equals(PfirsichlikoerRFID) && PfirsichlikoerMAß != 0 && Zubereitung == true)
  {
    //servoMotor.write(hoch); Servomotor temporär auskommentiert
    serial.println("Servomotor hoch")
    delay (30);
    PfirsichlikoerMAß -= 1;
    serial.println("PfirsichlikoerMAß= "+ PfirsichlikoerMAß)
    //servoMotor.write(runter);
    serial.println("Servomotor runter")
    delay (15);
    if (PfirsichlikoerMAß == 0)
    {
      // Move the DC motor forward at maximum speed
      Serial.println("Moving Forward");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      delay (5)
    }
  }

  if (newRfid.equals(PfirsichlikoerRFID) && Zubereitung == false)
  {
    Pfirsichlikoer = true;
  }

  if (newRfid.equals(PfirsichlikoerRFID) && PfirsichlikoerMAß == 0 && Zubereitung == true)
  {
    // Move the DC motor forward at maximum speed
     Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    delay (5)
  }
  if (newRfid.equals(Start))
  {
    Zubereitung = true;
    // Move the DC motor forward at maximum speed
    Serial.println("Moving Forward");
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
  }
  //Was soll passieren, wenn Zurücksetzen gelesen wird?
  if (newRfid.equals(Zurücksetzen))
    {
        SouthernComfort = false;
        LadySunshine = false;
        Maracujasirup = false;
        Gingerale = false;
        Wodka = false;
        Swimmingpool = false;
        Sahne = false;
        BlueCuracao = false;
        Kokossirup = false;
        Rum = false;
        Ananassaft = false;
        Maitai = false;
        Mandelsirup = false;
        Zuckersirup = false;
        Orangensaft = false;
        WhiteRussion = false;
        Kaffeelikoer = false;
        PinaColada = false;
        BloodyMary = false;
        Tomatensaft = false;
        Cosmopolitan = false;
        Limettensaft = false;
        Cointreu = false;
        Cranberrynektar = false;
        Grenadine = false;
        Zombie = false;
        SOTB = false;
        Pfirsichlikoer = false;

        SouthernComfortMAß = 0;
        MaracujasirupMAß = 0;
        GingeraleMAß = 0;
        WodkaMAß = 0;
        SahneMAß = 0;
        BlueCuracaoMAß = 0;
        KokossirupMAß = 0;
        RumMAß = 0;
        AnanassaftMAß = 0;
        MandelsirupMAß = 0;
        ZuckersirupMAß = 0;
        OrangensaftMAß = 0;
        KaffeelikoerMAß = 0;
        TomatensaftMAß = 0;
        LimettensaftMAß = 0;
        CointreuMAß = 0;
        CranberrynektarMAß = 0;
        GrenadineMAß = 0;
        PfirsichlikoerMAß = 0;

        Zubereitung = false;

    }

	if (newRfid.equals(SOTBRFID) && Pfirsichlikoer == true && Cranberrynektar == true && Orangensaft == true && Wodka == true)
    {
       Cocktail = "SOTB";
       PfirsichlikoerMAß = 1;
       CranberrynektarMAß = 3;
       OrangensaftMAß = 4;
       WodkaMAß = 2;
    }
  if (newRfid.equals(SOTBRFID) && Pfirsichlikoer == false)
  {
    Serial.println("Pfirsichlikoer fehlt");
  }
  if (newRfid.equals(SOTBRFID) && Cranberrynektar == false)
  {
    Serial.println("Cranberrynektar fehlt");
  }
  if (newRfid.equals(SOTBRFID) && Orangensaft == false)
  {
    Serial.println("Orangensaft fehlt");
  }
  if (newRfid.equals(SOTBRFID) && Wodka == false)
  {
    Serial.println("Wodka fehlt");
  }
  
  if (newRfid.equals(CosmopolitanRFID) && Limettensaft == true && Cointreu == true && Cranberranektar == true && Wodka == true)
    {
      Cocktail = "Cosmopolitan";
      LimettensaftMAß = 1;
      CointreuMAß = 1;
      CranberrynektarMAß = 1;
      WodkaMAß = 2;
    }
  if (newRfid.equals(CosmopolitanRFID) && Limettensaft == false)
  {
    Serial.println("Limettensaft fehlt");
  }
  if (newRfid.equals(CosmopolitanRFID) && Cointreu == false)
  {
    Serial.println("Cointreu fehlt");
  }
  if (newRfid.equals(CosmopolitanRFID) && Cranberranektar == false)
  {
    Serial.println("Cranberranektar fehlt");
  }
  if (newRfid.equals(CosmopolitanRFID) && Wodka == false)
  {
    Serial.println("Wodka fehlt");
  }
  
  if (newRfid.equals(BloodyMaryRFID) && tomatensaft == true && Limettensaft == true && Wodka == true)
    {
      Cocktail = "BloodyMary";
      TomatensaftMAß = 2;
      LimettensaftMAß = 1;
      WodkaMAß = 1;
    }
  if (newRfid.equals(BloodyMaryRFID) && tomatensaft == false)
  {
    Serial.println("Tomatensaft fehlt");
  }
  if (newRfid.equals(BloodyMaryRFID) && Limettensaft == false)
  {
    Serial.println("Limettensaft fehlt");
  }
  if (newRfid.equals(BloodyMaryRFID) && Wodka == false)
  {
    Serial.println("Wodka fehlt");
  }
  
  if (newRfid.equals(PinaColadaRFID) && Kokossirup == true && Rum == true && Ananassaft == true)
    {
      Cocktail = "PinaColada";
      KokossirupMAß = 1;
      RumMAß = 1;
      AnanassaftMAß = 2;
    }
  if (newRfid.equals(PinaColadaRFID) && Kokossirup == false)
  {
    Serial.println("Kokossirup fehlt");
  }
  if (newRfid.equals(PinaColadaRFID) && Rum == false)
  {
    Serial.println("Rum fehlt");
  }
  if (newRfid.equals(PinaColadaRFID) && Ananassaft == false)
  {
    Serial.println("Ananassaft fehlt");
  }
  
  if (newRfid.equals(LadySunshineRFID) && Maracujasirup == true && Gingerale == true && Wodka == true && SouthernComfort == true)
    {
      Cocktail = "LadySunshine";
      MaracujasirupMAß = 1;
      GingeraleMAß = 2;
      WodkaMAß = 2;
      SouthernComfortMAß = 1;
    }
  if (newRfid.equals(LadySunshineRFID) && Maracujasirup == false)
  {
    Serial.println("Maracujasirup fehlt");
  }
  if (newRfid.equals(LadySunshineRFID) && Gingerale == false)
  {
    Serial.println("Gingerale fehlt");
  }
  if (newRfid.equals(LadySunshineRFID) && Wodka == false)
  {
    Serial.println("Wodka fehlt");
  }
  if (newRfid.equals(LadySunshineRFID) && SouthernComfort == false)
  {
    Serial.println("SouthernComfort fehlt");
  }
  
  if (newRfid.equals(SwimmingpoolRFID) && Sahne == true && BlueCuracao == true && Kokossirup == true && Ananassaft == true && Wodka == true)
    {
      Cocktail = "Swimmingpool";
      SahneMAß = 1;
      BlueCuracaoMAß = 1;
      KokossirupMAß = 2;
      AnanassaftMAß = 6;
      WodkaMAß = 2;
    }
  if (newRfid.equals(SwimmingpoolRFID) && Sahne == false)
  {
    Serial.println("Sahne fehlt");
  }
  if (newRfid.equals(SwimmingpoolRFID) && BlueCuracao == false)
  {
    Serial.println("BlueCuracao fehlt");
  }
  if (newRfid.equals(SwimmingpoolRFID) && Kokossirup == false)
  {
    Serial.println("Kokossirup fehlt");
  }
  if (newRfid.equals(SwimmingpoolRFID) && Ananassaft == false)
  {
    Serial.println("Ananassaft fehlt");
  }
  if (newRfid.equals(SwimmingpoolRFID) && Wodka == false)
  {
    Serial.println("Wodka fehlt");
  }
  
  if (newRfid.equals(MaiTaiRFID) && Mandelsirup == true && Zuckersirup == true && Ananassaft == true && Orangensaft == true && Rum == true)
    {
      Cocktail = "MaiTai";
      MandelsirupMAß = 1;
      ZuckersirupMAß = 1;
      AnanassaftMAß = 2;
      OrangensaftMAß = 2;
      RumMAß = 2;
    }
  if (newRfid.equals(MaiTaiRFID) && Mandelsirup == false)
  {
    Serial.println("Mandelsirup fehlt");
  }
  if (newRfid.equals(MaiTaiRFID) && Zuckersirup == false)
  {
    Serial.println("Zuckersirup fehlt");
  }
  if (newRfid.equals(MaiTaiRFID) && Ananassaft == false)
  {
    Serial.println("Ananassaft fehlt");
  }
  if (newRfid.equals(MaiTaiRFID) && Orangensaft == false)
  {
    Serial.println("Orangensaft fehlt");
  }
  if (newRfid.equals(MaiTaiRFID) && Rum == false)
  {
    Serial.println("Rum fehlt");
  }
  
  if (newRfid.equals(WhiteRussionRFID) && Sahne == true && Wodka == true && Kaffeelikoer == true)
    {
      Cocktail = "WhiteRussion";
      SahneMAß = 1;
      WodkaMAß = 1;
      KaffeelikoerMAß = 1;
    }
  if (newRfid.equals(WhiteRussionRFID) && Sahne == false)
  {
    Serial.println("Sahne fehlt");
  }
  if (newRfid.equals(WhiteRussionRFID) && Wodka == false)
  {
    Serial.println("Wodka fehlt");
  }
  if (newRfid.equals(WhiteRussionRFID) && Kaffeelikoer == false)
  {
    Serial.println("Kaffeelikoer fehlt");
  }

  



}
