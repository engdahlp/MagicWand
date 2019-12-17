
#include <IRremote.h> //this is a special library that decodes magiwands
#include <Servo.h>

const uint16_t LOGANSWAND_SERIAL_NUM = 734992257; //logan's wand serial number
const uint16_t LAURENSWAND_SERIAL_NUM = 116991811; //+Lauren's wand serial number
int magnitude = -33000; //setting up default magnitude for fake wand
int RECV_PIN = 11; //ir receiver pin
int SERVO_PIN = 10;
int LIGHT_PIN = 12;
IRrecv irrecv(RECV_PIN);
IRsend irsend; //this is always pin 3
decode_results results;

Servo doorServo;
int doorOpenPosition = 180;
int doorClosedPosition = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(SERVO_PIN, OUTPUT);
  pinMode(LIGHT_PIN, OUTPUT);
  doorServo.attach(SERVO_PIN);
  doorServo.write(doorClosedPosition);
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
        openDoor();
      }
      else if ((int)results.value == LAURENSWAND_SERIAL_NUM){
        Serial.println("Lauren's Wand Detected"); 
        lightOn();
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

void openDoor(){
  Serial.println("Opening Door");
  doorServo.write(doorOpenPosition);
  delay(4000);
  Serial.println("Closing Door");
  doorServo.write(doorClosedPosition);
}

void lightOn(){
  Serial.println("Light On");
  digitalWrite(LIGHT_PIN, HIGH);
  delay(4000);
  Serial.println("Light Off");
  digitalWrite(LIGHT_PIN, LOW);
}
