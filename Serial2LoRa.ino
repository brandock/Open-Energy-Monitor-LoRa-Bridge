/*Brandon Baldock 2022
 * This is the Rocket Scream rf95_client sketch configured for Low Power Lab's Moteino, and
 * updated to repeat any inbound serial data as an outbound LoRa radio packet.
 */


//*********************************************************************************************
#include <RH_RF95.h>
#include <SPI.h>      //comes with Arduino IDE (www.arduino.cc)

//*********************************************************************************************
#define NODEID        1  //unique for each node on same network
#define NETWORKID     100  //the same on all nodes that talk to each other
#define FREQUENCY     RF69_433MHZ

//*********************************************************************************************
#define SERIAL_BAUD   115200

#ifdef __AVR_ATmega1284P__
  #define LED           15 // Moteino MEGAs have LEDs on D15
  #define FLASH_SS      23 // and FLASH SS on D23
#else
  #define LED           9 // Moteinos have LEDs on D9
  #define FLASH_SS      8 // and FLASH SS on D8
#endif

// Singleton instance of the radio driver
RH_RF95 rf95;

//*********************************************************************************************
void setup() {
  Serial.begin(SERIAL_BAUD);
  delay(10);

  if (!rf95.init())
    Blink(LED,5);
  // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

  // You can change the modulation parameters with eg
  // rf95.setModemConfig(RH_RF95::Bw500Cr45Sf128);

// The default transmitter power is 13dBm, using PA_BOOST.
  // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
  // you can set transmitter powers from 2 to 20 dBm:
//  driver.setTxPower(20, false);
  // If you are using Modtronix inAir4 or inAir9, or any other module which uses the
  // transmitter RFO pins and not the PA_BOOST pins
  // then you can configure the power transmitter power for 0 to 15 dBm and with useRFO true. 
  // Failure to do that will result in extremely low transmit powers.
//  driver.setTxPower(14, true);
}

const unsigned int MAX_MESSAGE_LENGTH = RH_RF95_MAX_MESSAGE_LEN;
//*********************************************************************************************
void loop() {
  if (Serial.available()) {      // If anything comes in Serial (USB),
   //Create a place to hold the incoming message
   static char message[MAX_MESSAGE_LENGTH];
   static unsigned int message_pos = 0;

   //Read the next available byte in the serial receive buffer
   char inByte = Serial.read();

   //Message coming in (check not terminating character) and guard for over message size
   if ( inByte != '\n' && (message_pos < MAX_MESSAGE_LENGTH - 1) ) {
      //Add the incoming byte to our message
      message[message_pos] = inByte;
      message_pos++;
     }
     //Full message received...
     else {
      //Add null character to string
      message[message_pos] = '\0';
  
      //Send the message
      //Serial.println(message);
      rf95.send(message, sizeof(message));
      rf95.waitPacketSent();
      Blink(LED,3);
    
      //Reset for the next message
      message_pos = 0;    
    }
  }
}

//*********************************************************************************************
void Blink(byte PIN, int DELAY_MS)
{
  pinMode(PIN, OUTPUT);
  digitalWrite(PIN,HIGH);
  delay(DELAY_MS);
  digitalWrite(PIN,LOW);
}
