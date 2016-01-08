/*
Arduino Table Lamp
 */

#include <IRSendRev.h>

#define BIT_LEN         0
#define BIT_START_H     1
#define BIT_START_L     2
#define BIT_DATA_H      3
#define BIT_DATA_L      4
#define BIT_DATA_LEN    5
#define BIT_DATA        6

#define OnOff          0x48
#define Forward        0xD8
#define Back           0x58
#define Left           0x20
#define Right          0x60
#define MENU           0xA0

#define RelayPin       5
#define pushButton     3

const int pinRecv = 2;              // ir receiver connect to D2
uint8_t FlagOnOff = 0;
void setup()
{
    Serial.begin(115200);
    IR.Init(pinRecv);
    Serial.println("init over");
    
    pinMode(RelayPin,OUTPUT);
    pinMode(pushButton,INPUT);
}

unsigned char dta[20];

void loop()
{
    if(IR.IsDta() || (digitalRead(pushButton) == 1))                  // get IR data
    {
      
        
        IR.Recv(dta);               // receive data to dta
        Serial.println(dta[2+BIT_DATA]);
        if (digitalRead(pushButton) == 1) {
            delay(200);
            dta[2+BIT_DATA] = OnOff;
        }
        switch(dta[2+BIT_DATA]){
        case OnOff:
            if(FlagOnOff == 0) {
                FlagOnOff = 1;
                digitalWrite(RelayPin,HIGH);
            } else {
                FlagOnOff = 0;
                digitalWrite(RelayPin,LOW);
            }
            while(digitalRead(pushButton) == 1);
            delay(500);
            
            break;
        case Forward:
            break;
        case Back:
            break;
        case Left:
            break;
        case Right:
            break;
        default:
            break;
        }
        
        for(int i=0; i<dta[BIT_DATA_LEN]; i++)
        {
            Serial.print("0x");
            Serial.print(dta[i+BIT_DATA], HEX);
            Serial.print("\t");
        }
        Serial.println();
    
    Serial.print("DATA: ");
        for(int i=0; i<dta[BIT_DATA_LEN]; i++)
        {
            Serial.print(dta[i+BIT_DATA], DEC);
            Serial.print("\t");
        }
        Serial.println();
        Serial.println("+------------------------------------------------------+\r\n\r\n");
    }
}
