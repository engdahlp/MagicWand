
#include <IRremote.h> //this is a special library that decodes magiwands

const uint16_t LOGANSWAND_SERIAL_NUM = 734992257; //logan's wand serial number
const uint16_t LAURENSWAND_SERIAL_NUM = 116991811; //+Lauren's wand serial number
int magnitude = -33000; //setting up default magnitude for fake wand
int RECV_PIN = 11; //ir receiver pin
IRrecv irrecv(RECV_PIN);
IRsend irsend; //this is always pin 3
decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
}

void loop()
{
  if (irrecv.decode(&results))
    {
   //  Serial.println(results.magiquestMagnitude);
    if (results.decode_type == MAGIQUEST) {
      Serial.println("MagiWand Detected ID: ");
      Serial.println(results.value);
      if ((int)results.value == LOGANSWAND_SERIAL_NUM){
        Serial.println("Logan's Wand Detected");
      }
      else if ((int)results.value == LAURENSWAND_SERIAL_NUM){
       Serial.println("Lauren's Wand Detected"); 
      }
    }
     irrecv.resume(); // Receive the next value
    }
}

void transmitIRCode() {   // I use this function to transmit a fake wand signal to train other devices or test equipment.
  Serial.println(LAURENSWAND_SERIAL_NUM);
  Serial.println(magnitude);
  delay(500);
  irsend.sendMagiQuest(LAURENSWAND_SERIAL_NUM, magnitude); //
}
