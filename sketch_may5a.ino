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

    bool SouthernComfort;
    bool LadySunshine;
    bool Maracujasirup;
    bool Gingerale;
    bool Wodka;
    bool Swimmingpool;
    bool Sahne;
    bool BlueCuracao;
    bool Kokossirup;
    bool Rum;
    bool Ananassaft;
    bool Maitai;
    bool Mandelsirup;
    bool Zuckersirup;
    bool Orangensaft;
    bool WhiteRussion;
    bool Kaffeelikoer;
    bool PinaColada;
    bool BloodyMary;
    bool Tomatensaft;
    bool Cosmopolitan;
    bool Limettensaft;
    bool Cointreu;
    bool Cranberrynektar;
    bool Grenadine;
    bool Zombie;
    bool SOTB;
    bool Pfirsichlikoer;

void setup()
{
   
    //beginn der seriellen Kommunikation mit 115200 Baud
    Serial.begin(115200);
    //eine kleine Pause von 50ms.
    delay(50);
    //begin der SPI Kommunikation
    SPI.begin();
    //initialisieren der Kommunikation mit dem RFID Modul
    mfrc522.PCD_Init();
    // Variablen zum speichern der momentan eingehängten Flaschen

}
void loop()
{
   
    //Wenn keine neue Karte vorgehalten wurde oder die serielle Kommunikation
    //nicht gegeben ist, dann...
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
    //alle Buchstaben in Großbuchstaben umwandeln
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
		
		
      if (newRfidId == " fe b0 1e 3f")
        {
          SouthernComfort = true;
          Serial.println ("Southern Comfort");
          Serial.println (SouthernComfort);
          Serial.println (Wodka);
          Serial.println (Gingerale);
          Serial.println (Maracujasirup);

        }
      else if (newRfidId ==  " 5b 7f 7f 3b")
        {
          Pfirsichlikoer = true;
          Serial.print ("Pfirsichlikör");
          
        }
      else if (newRfidId ==" 7b 77 2e 3b")
        {
          Grenadine = true;
          Serial.print ("Grenadinensirup");
          
        }
      else if (newRfidId == " 9b b4 45 3b")
        {
          Cointreu = true;
          Serial.print ("Cointreu");
          
        }
      else if (newRfidId == " 6b 0b 77 3b")
        {
          Cranberrynektar = true;
          Serial.print ("Cranberrynektar");
          
        }
      else if (newRfidId == " 9b fb 7b 3b")
        {
          Limettensaft = true;
          Serial.print ("Limettensaft");
          
        }	
      else if (newRfidId == " 7b 55 ff 3b")
        {
          Tomatensaft = true;
          Serial.print ("Tomatensaft");
        
        }	
      else if (newRfidId == " 5e 5a 21 3f")
        {
          Kaffeelikoer = true;
          Serial.print ("Kaffeelikör");
          
        }	
      else if (newRfidId == " fa e6 b3 d3")
        {
          Orangensaft = true;
          Serial.print ("Orangensaft");
          
        }	
      else if (newRfidId == " fe 5f 2b 3f")
        {
          Zuckersirup = true;
          Serial.print ("Zuckersirup");
          
        }
      else if (newRfidId == " 7a 42 b6 d3")
        {
          Mandelsirup = true;
          Serial.print ("Mandelsirup");
          
        }
      else if (newRfidId == " 8a 50 b4 d3")
        {
          Ananassaft = true;
          Serial.print ("Ananassaft");
          
        }
      else if (newRfidId == " ea 00 a9 d3")
        {
          Rum = true;
          Serial.print ("Rum");
          
        }
      else if (newRfidId == " fa bf ae d3")
        {
          Kokossirup = true;
          Serial.print ("Kokossirup");
          
        }
      else if (newRfidId == " 4b 46 be 3b")
        {
          BlueCuracao = true;
          Serial.print ("Blue Curacao");
          
        }
      else if (newRfidId == " 4b 12 5c 3b")
        {
          Sahne = true;
          Serial.print ("Sahne");
          
        }
      else if (newRfidId == " 7b 9d 67 3b")
        {
          Wodka = true;
          Serial.print ("Wodka");
          
        }
      else if (newRfidId == " ee 22 24 3f")
        {
          Maracujasirup = true;
          Serial.print ("Maracujasirup");
          
        }
      else if (newRfidId == " 6b 54 51 3b")
        {
          Gingerale = true;
          Serial.println ("Gingerale");
          Serial.println (Gingerale);
          Serial.println (Wodka);
          Serial.println (SouthernComfort);
          Serial.println (Maracujasirup);

          
        }
      else if (newRfidId == " 5b f9 8d 3b")
        {
          // SOTB:
          if (Pfirsichlikoer == true && Cranberrynektar == true && Orangensaft == true && Wodka == true)
          {
          Serial.print ("Sex on the Beach wird zubereitet");
          }
          else
          {
            if (Pfirsichlikoer == false)
            {
            Serial.println("Pfirsichlikoer fehlt.");
            }
      
            if (Cranberrynektar == false)
            {
            Serial.println("Cranberrynektar fehlt.");
            }
      
            if (Orangensaft == false)
            {
            Serial.println("Orangensaft fehlt.");
            }
      
            if (Wodka == false)
            {
            Serial.println("Wodka fehlt.");
            }
          }
          
          
        }
      else if (newRfidId == " 4b ab 60 3b")
        {
          // Cosmopolitan:
          if (Limettensaft == true && Cointreu == true && Cranberrynektar == true && Wodka == true)
          {
          Serial.print ("Cosmopolitan wird zubereitet");
          }
          else	
            {
              if (Limettensaft == false)
              {
              Serial.println("Limettensaft fehlt.");
              }
      
              if (Cointreu == false)
              {
              Serial.println("Cointreu fehlt.");
              }
      
              if (Cranberrynektar == false)
              {
              Serial.println("Cranberrynektar fehlt.");
              }
        
              if (Wodka == false)
              {
              Serial.println("Wodka fehlt.");
              }
            }
          
        }
      else if (newRfidId == " 3b e4 e3 3b")
        {
          // BloodyMary:
          if (Tomatensaft == true && Wodka == true)
          {
          Serial.print ("Bloody Mary wird zubereitet");
          }
          else
            {
              if (Tomatensaft == false)
              {
              Serial.println("Tomatensaft fehlt.");
              }
        
              if (Wodka == false)
              {
              Serial.println("Wodka fehlt.");
              }
          
        }
          
        }
      else if (newRfidId == " 9b bd 29 3b")
        {
          
          // PinaColada:
          if (Kokossirup == true && Rum == true && Wodka == true)
          {
          Serial.print ("Pina Colada wird zubereitet");
          }
          
          else
            {
              if (Kokossirup == false)
              {
              Serial.println("Kokossirup fehlt.");
              }
      
              if (Rum == false)
              {
              Serial.println("Rum fehlt.");
              }
      
              if (Wodka == false)
              {
              Serial.println("Wodka fehlt.");
              }
            }
          
          
        }
        
      else if (newRfidId == " 9b 3d f9 3b")
        {
          // Lady Sunshine:
          if (SouthernComfort == true && Maracujasirup == true && Gingerale == true && Wodka == true)
          {
          Serial.print ("Lady Sunshine wird zubereitet");
          }	
          else 
          {
            if (SouthernComfort == false)
            {
            Serial.println("Southern Comfort fehlt.");
            Serial.println(SouthernComfort);
            }
      
            if (Maracujasirup == false)
            {
            Serial.println("Maracujasirup fehlt.");
            Serial.println(Maracujasirup);
            }
      
            if (Gingerale == false)
            {
            Serial.println("Gingerale fehlt.");
            Serial.println(Gingerale);
            }
      
            if (Wodka == false)
            {
            Serial.println("Wodka fehlt.");
            Serial.println(Wodka);
            }
          }
            
        }
        
      else if (newRfidId == " 3b 92 60 3b")
        {
        // Swimmingpool:
          if (Sahne == true && BlueCuracao == true && Kokossirup == true && Ananassaft == true && Wodka == true)
          {
          Serial.print ("Swimmingpool wird zubereitet");
          }
          
          else
            {
              if (Sahne == false)
              {
              Serial.println("Sahne fehlt.");
              }
        
              if (BlueCuracao == false)
              {
                Serial.println("BlueCuracao fehlt.");
              }
      
              if (Kokossirup == false)
              {
                Serial.println("Kokossirup fehlt.");
              }
      
              if (Ananassaft == false)
              {
                Serial.println("Ananassaft fehlt.");
              }
      
              if (Wodka == false)
              {
                Serial.println("Wodka fehlt.");
              }
            }
            
        }
        
      else if (newRfidId == " aa a7 a4 d3")
        {
          // Maitai:
          if (Mandelsirup == true && Zuckersirup == true && Ananassaft == true && Orangensaft == true && Rum == true)
          {
          Serial.print ("Mai Tai wird zubereitet");
          }	

          else
          {
            if (Mandelsirup == false)
            {
              Serial.println("Mandelsirup fehlt.");
            }
        
            if (Zuckersirup == false)
            {
              Serial.println("Zuckersirup fehlt.");
            }
      
            if (Kokossirup == false)
            {
              Serial.println("Kokossirup fehlt.");
            }
      
            if (Ananassaft == false)
            {
              Serial.println("Ananassaft fehlt.");
            }
        
            if (Orangensaft == false)
            {
              Serial.println("Orangensaft fehlt.");
            }
      
            if (Rum == false)
            {
              Serial.println("Rum fehlt.");
            }

          }
          
          

        }
      else if (newRfidId == " 1e 18 20 3f")
        {
          // WhiteRussion::
          if (Sahne == true && Kaffeelikoer == true && Wodka == true)
          {
          Serial.print ("White Russion wird zubereitet");
          }	

          else
          {
            if (Sahne == false)
            {
              Serial.println("Sahne fehlt.");
            }
        
            if (Kaffeelikoer == false)
            {
              Serial.println("Kaffeelikoer fehlt.");
            }
      
            if (Wodka == false)
            {
              Serial.println("Wodka fehlt.");
            }

          }
          
          

        }
      else if (newRfidId == " 3b c1 40 3b")
        {
          Serial.print ("Startposition erreicht");
          
        }
      else if (newRfidId == " 9b 58 36 3b")
        {
          Serial.print ("Zielposition erreicht");
          
        }
      else
        {
          Serial.println ("Karte nicht bekannt.");

        }

    }
}