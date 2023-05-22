/ Button
int buttonPin = 34;

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

  Serial.begin(115200);
  //begin der SPI Kommunikation
  SPI.begin();
  // sets the pins as outputs:
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  //set the Button as input sign
  pinMode(buttonPin, INPUT_PULLUP);

  // attaches the servo on ESP32 pin
  servoMotor.attach(SERVO_PIN);  
  
  //initialisieren der Kommunikation mit dem RFID Modul
  mfrc522.PCD_Init();
  
  // configure LED PWM functionalitites
  ledcSetup(pwmChannel, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(enable1Pin, pwmChannel);

}

void loop() {

  int buttonValue = digitalRead(buttonPin);


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
	
    //Wenn die neue gelesene RFID-ID ungleich der bereits zuvor gelesenen ist,
    //dann soll diese auf der seriellen Schnittstelle ausgegeben werden.
	if (!newRfidId.equals(lastRfid))
    {
        //überschreiben der alten ID mit der neuen
        lastRfid = newRfidId;
        Serial.print(" gelesene RFID-ID :");
        Serial.println(newRfidId);
        Serial.println();
    }

  if (lastRfid.equals(Zurücksetzen))
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

    }

  if (lastRfid.equals(Start))
  {

    
  }

  if (lastRfid.equals(SOTBRFID))
    {
       Cocktail = "SOTB";
       PfirsichlikoerMAß = 1;
       CranberrynektarMAß = 3;
       OrangensaftMAß = 4;
       WodkaMAß = 2;
    }
  
  if (lastRfid.equals(CosmopolitanRFID))
    {
      Cocktail = "Cosmopolitan";
      LimettensaftMAß = 1;
      CointreuMAß = 1;
      CranberrynektarMAß = 1;
      WodkaMAß = 2;
    }
  
  if (lastRfid.equals(BloodyMaryRFID))
    {
      Cocktail = "BloodyMary";
      TomatensaftMAß = 2;
      LimettensaftMAß = 1;
      WodkaMAß = 1;
    }
  
  if (lastRfid.equals(PinaColadaRFID))
    {
      Cocktail = "PinaColada";
      KokossirupMAß = 1;
      RumMAß = 1;
      AnanassaftMAß = 2;
    }
  
  if (lastRfid.equals(LadySunshineRFID))
    {
      Cocktail = "LadySunshine";
      MaracujasirupMAß = 1;
      GingeraleMAß = 2;
      WodkaMAß = 2;
      SouthernComfortMAß = 1;
    }
  
  if (lastRfid.equals(SwimmingpoolRFID))
    {
      Cocktail = "Swimmingpool";
      SahneMAß = 1;
      BlueCuracaoMAß = 1;
      KokossirupMAß = 2;
      AnanassaftMAß = 6;
      WodkaMAß = 2;
    }
  
  if (lastRfid.equals(MaiTaiRFID))
    {
      Cocktail = "MaiTai";
      MandelsirupMAß = 1;
      ZuckersirupMAß = 1;
      AnanassaftMAß = 2;
      OrangensaftMAß = 2;
      RumMAß = 2;
    }
  
  if (lastRfid.equals(WhiteRussionRFID))
    {
      Cocktail = "WhiteRussion";
      SahneMAß = 1;
      WodkaMAß = 1;
      KaffeelikoerMAß = 1;
    }

  if (lastRfid.equals(SouthernComfortRFID))
  {
    SouthernComfort = true;
  }

  if (lastRfid.equals(MaracujasirupRFID))
  {
    Maracujasirup = true;
  }

  if (lastRfid.equals(GingeraleRFID))
  {
    Gingerale = true;
  }

  if (lastRfid.equals(WodkaRFID))
  {
    Wodka = true;
  }

  if (lastRfid.equals(SahneRFID))
  {
    Sahne = true;
  }

  if (lastRfid.equals(BlueCuracaoRFID))
  {
    BlueCuracao = true;
  }

  if (lastRfid.equals(KokossirupRFID))
  {
    Kokossirup = true;
  }

  if (lastRfid.equals(RumRFID))
  {
    Rum = true;
  }

  if (lastRfid.equals(AnanassaftRFID))
  {
    Ananassaft = true;
  }

  if (lastRfid.equals(MandelsirupRFID))
  {
    Mandelsirup = true;
  }

  if (lastRfid.equals(ZuckersirupRFID))
  {
    Zuckersirup = true;
  }

  if (lastRfid.equals(OrangensaftRFID)
  {
    Orangensaft = true;
  }

  if (lastRfid.equals(KaffeelikoerRFID))
  {
    Kaffeelikoer = true;
  }

  if (lastRfid.equals(TomatensaftRFID))
  {
    Tomatensaft = true;
  }

  if (lastRfid.equals(LimettensaftRFID))
  {
    Limettensaft = true;
  }

  if (lastRfid.equals(CointreuRFID))
  {
   Cointreu = true; 
  }

  if (lastRfid.equals(CranberrynektarRFID))
  {
    Cranberrynektar = true;
  }

  if (lastRfid.equals(GrenadineRFID))
  {
    Grenadine = true;
  }

  if (lastRfid.equals(PfirsichlikoerRFID))
  {
    Pfirsichlikoer = true;
  }

if (Cocktail == "SOTB" && Pfirsichlikoer == true && Cranberrynektar == true && Orangensaft == true && Wodka == true)
    {
      if (newRfidID.equals(PfirsichlikoerRFID) && PfirsichlikoerMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        PfirsichlikoerMAß -= 1;
        servoMotor.write(runter);
        delay (15);
      }
      if (newRfidID.equals(CranberrynektarRFID) && CranberrynektarMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        CranberrynektarMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(OrangensaftRFID) && OrangensaftMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        OrangensaftMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(WodkaRFID) && WodkaMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        WodkaMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (PfirsichlikoerMAß == 0 && CranberrynektarMAß == 0 && OrangensaftMAß == 0 && WodkaMAß == 0) 
      {
        // Stop the DC motor
        Serial.println("Cocktail fertig");
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        delay(5);
      }
    }

        if (Cocktail == "SOTB" && Pfirsichlikoer == false)
        {
          Serial.println("Pfirsichlikoer fehlt")
        }
        if (Cocktail == "SOTB fehlt" && Cranberrynektar == false)
        {
          Serial.println("Cranberrynektar fehlt")
        }
        if (Cocktail == "SOTB" && Orangensaft == false)
        {
          Serial.println("Orangensaft fehlt")
        }
        if (Cocktail == "SOTB" && Wodka == false)
        {
          Serial.println("Wodka fehlt")
        }
    
    if (Cocktail == "Cosmopolitan" && Limettensaft == true && Cointreu == true && Cranberranektar == true && Wodka == true)
    {
      
      if (newRfidID.equals(LimettensaftRFID) && LimettensaftMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        LimettensaftMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(CointreuRFID) && CointreuMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        CointreuMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(CranberrynektarRFID) && CranberrynektarMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        CranberrynektarMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(WodkaRFID) && WodkaMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        WodkaMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
    }
        if (Cocktail == "Cosmopolitan" && Limettensaft == false)
        {
          Serial.println("Limettensaft fehlt")
        }
        if (Cocktail == "Cosmopolitan" && Cointreu == false)
        {
          Serial.println("Cointreu fehlt")
        }
        if (Cocktail == "Cosmopolitan" && Cranberranektar == false)
        {
          Serial.println("Cranberranektar fehlt")
        }
        if (Cocktail == "Cosmopolitan" && Wodka == false)
        {
          Serial.println("Wodka fehlt")
        }
    
    if (Cocktail == "BloodyMary" && tomatensaft == true && Limettensaft == true && Wodka == true)
    {
      
      if (newRfidID.equals(TomatensaftRFID) && TomatensaftMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        TomatensaftMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(LimettensaftRFID) && LimettensaftMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        LimettensaftMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(WodkaRFID) && WodkaMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        WodkaMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
    }
        if (Cocktail == "BloodyMary" && tomatensaft == false)
        {
          Serial.println("Tomatensaft fehlt")
        }
        if (Cocktail == "BloodyMary" && Limettensaft == false)
        {
          Serial.println("Limettensaft fehlt")
        }
        if (Cocktail == "BloodyMary" && Wodka == false)
        {
          Serial.println("Wodka fehlt")
        }
    
    if (Cocktail == "PinaColada" && Kokossirup == true && Rum == true && Ananassaft == true)
    {
      
      if (newRfidID.equals(KokossirupRFID) && KokossirupMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        KokossirupMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(RumRFID) && RumMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        RumMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(AnanassaftRFID) && AnanassaftMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        AnanassaftMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
    }
        if (Cocktail == "PinaColada" && Kokossirup == false)
        {
          Serial.println("Kokossirup fehlt")
        }
        if (Cocktail == "PinaColada" && Rum == false)
        {
          Serial.println("Rum fehlt")
        }
        if (Cocktail == "PinaColada" && Ananassaft == false)
        {
          Serial.println("Ananassaft fehlt")
        }
    
    if (Cocktail == "LadySunshine" && Maracujasirup == true && Gingerale == true && Wodka == true && SouthernComfort == true)
    {
      
      if (newRfidID.equals(MaracujasirupRFID) && MaracujasirupMAß> 0)
      {
        servoMotor.write(hoch);
        delay (30);
        MaracujasirupMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(GingeraleRFID) && GingeraleMAß> 0)
      {
        servoMotor.write(hoch);
        delay (30);
        GingeraleMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(WodkaRFID) && WodkaMAß> 0)
      {
        servoMotor.write(hoch);
        delay (30);
        WodkaMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(SouthernComfortRFID) && SouthernComfortMAß> 0)
      {
        servoMotor.write(hoch);
        delay (30);
        SouthernComfortMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
    }
        if (Cocktail == "LadySunshine" && Maracujasirup == false)
        {
          Serial.println("Maracujasirup fehlt")
        }
        if (Cocktail == "LadySunshine" && Gingerale == false)
        {
          Serial.println("Gingerale fehlt")
        }
        if (Cocktail == "LadySunshine" && Wodka == false)
        {
          Serial.println("Wodka fehlt")
        }
        if (Cocktail == "LadySunshine" && SouthernComfort == false)
        {
          Serial.println("SouthernComfort fehlt")
        }
    
    if (Cocktail == "Swimmingpool" && Sahne == true && BlueCuracao == true && Kokossirup == true && Ananassaft == true && Wodka == true)
    {
      
      if (newRfidID.equals(SahneRFID) && SahneMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        SahneMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(BlueCuracaoRFID) && BlueCuracaoMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        BlueCuracaoMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(KokossirupRFID) && KokossirupMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        KokossirupMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(AnanassaftRFID) && AnanassaftMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        AnanassaftMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(WodkaRFID) && WodkaMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        WodkaMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
    }
        if (Cocktail == "Swimmingpool" && Sahne == false)
        {
          Serial.println("Sahne fehlt")
        }
        if (Cocktail == "Swimmingpool" && BlueCuracao == false)
        {
          Serial.println("BlueCuracao fehlt")
        }
        if (Cocktail == "Swimmingpool" && Kokossirup == false)
        {
          Serial.println("Kokossirup fehlt")
        }
        if (Cocktail == "Swimmingpool" && Ananassaft == false)
        {
          Serial.println("Ananassaft fehlt")
        }
        if (Cocktail == "Swimmingpool" && Wodka == false)
        {
          Serial.println("Wodka fehlt")
        }
    
    if (Cocktail == "MaiTai" && Mandelsirup == true && Zuckersirup == true && Ananassaft == true && Orangensaft == true && Rum == true)
    {
      
      if (newRfidID.equals(MandelsirupRFID) && MandelsirupMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        MandelsirupMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(ZuckersirupRFID) && ZuckersirupMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        ZuckersirupMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(AnanassaftRFID) && AnanassaftMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        AnanassaftMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(OrangensaftRFID) && OrangensaftMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        OrangensaftMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(RumRFID) && RumMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        RumMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
    }
        if (Cocktail == "MaiTai" && Mandelsirup == false)
        {
          Serial.println("Mandelsirup fehlt")
        }
        if (Cocktail == "MaiTai" && Zuckersirup == false)
        {
          Serial.println("Zuckersirup fehlt")
        }
        if (Cocktail == "MaiTai" && Ananassaft == false)
        {
          Serial.println("Ananassaft fehlt")
        }
        if (Cocktail == "MaiTai" && Orangensaft == false)
        {
          Serial.println("Orangensaft fehlt")
        }
        if (Cocktail == "MaiTai" && Rum == false)
        {
          Serial.println("Rum fehlt")
        }
    
    if (Cocktail == "WhiteRussion" && Sahne == true && Wodka == true && Kaffeelikoer == true )
    {
      
      if (newRfidID.equals(SahneRFID) && SahneMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        SahneMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(WodkaRFID) && WodkaMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        WodkaMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
      if (newRfidID.equals(KaffeelikoerRFID) && KaffeelikoerMAß > 0)
      {
        servoMotor.write(hoch);
        delay (30);
        KaffeelikoerMAß -= 1;
        servoMotor.write(runter);
        delay (15);

      }
    }
        if (Cocktail == "WhiteRussion" && Sahne == false)
        {
          Serial.println("Sahne fehlt")
        }
        if (Cocktail == "WhiteRussion" && Wodka == false)
        {
          Serial.println("Wodka fehlt")
        }
        if (Cocktail == "WhiteRussion" && Kaffeelikoer == false)
        {
          Serial.println("Kaffeelikoer fehlt")
        }

    else
    {
      Serial.println ("Bitte zuerst alle Zutaten scannen und darauf achten, dass der ausgewählte Cocktail mit den eingespannten zutaten hergestellt werden kann");
    }


}































