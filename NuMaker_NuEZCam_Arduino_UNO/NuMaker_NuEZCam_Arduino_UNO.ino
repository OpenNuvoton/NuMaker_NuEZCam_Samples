/*
  Serial Call and Response in ASCII
 Language: Wiring/Arduino

 This program sends an ASCII A (byte of value 65) on startup
 and repeats that until it gets some data in.
 Then it waits for a byte in the serial port, and
 sends three ASCII-encoded, comma-separated sensor values,
 truncated by a linefeed and carriage return,
 whenever it gets a byte in.

 Thanks to Greg Shakar and Scott Fitzgerald for the improvements

  The circuit:
 * potentiometers attached to analog inputs 0 and 1
 * pushbutton attached to digital I/O 2



 Created 26 Sept. 2005
 by Tom Igoe
 modified 24 Apr 2012
 by Tom Igoe and Scott Fitzgerald

 This example code is in the public domain.

 http://www.arduino.cc/en/Tutorial/SerialCallResponseASCII

 */

int inByte = 0;         // incoming serial byte
// set pin numbers:
const int buttonPin = 2;     // the number of the pushbutton pin
int buttonState = 0;         // variable for reading the pushbutton status
int ledPin = 13;
int ifound;
int sendnum;
int special;
void setup() {
  // start serial port at 9600 bps and wait for port to open:
  Serial.begin(115200);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }
     pinMode(buttonPin, INPUT_PULLUP);
     pinMode(ledPin, OUTPUT);
     inByte= 0;
    digitalWrite(ledPin, LOW);
	ifound = 0;
	sendnum =0;
  special = 0;
}

void loop() {
  // if we get a valid byte, read analog ins:
  if ( special == 0 )
  {
    delay(1500);
    Serial.write(0xA5);
    special = 1;
  }
	buttonState = digitalRead(buttonPin);

  // check if the pushbutton is pressed.
  // if it is, the buttonState is HIGH:
	if (buttonState == HIGH) {
    // turn LED on:
		if ( ifound == 1 )
		{
			sendnum++;
			setupCommand(inByte);
			ifound = 0;
			inByte = 0;
  	}
	} else {
      // turn LED off:
		digitalWrite(ledPin,HIGH);
		inByte++;
		ifound=1;
		delay(200);
		digitalWrite(ledPin, LOW);
  }
  delay(500);

 
}
// number is the number of LED flash.
void setupCommand(int number) {
	int no, readByte,i, CmdStatus;
// Send ID 0x8D, 0x7C, 0x6B, 0x5C 
  if ( number == 1 )
  { // AVI start
    Serial.write(0x8D);
    Serial.write(0x7C);
    Serial.write(0x6B);    
    Serial.write(0x5A);    
    Serial.write(0xA0);
    Serial.write(0x01);
    CmdStatus = 0xA1;
  }
  else if ( number == 2 )
  { // UVC+UAC start
    Serial.write(0x8D);
    Serial.write(0x7C);
    Serial.write(0x6B);    
    Serial.write(0x5A);       
    Serial.write(0xB0);
    Serial.write(0x01);    
    CmdStatus = 0xB1;
  }
  else if ( number == 3 )
  { // USB MSC start
    Serial.write(0x8D);
    Serial.write(0x7C);
    Serial.write(0x6B);    
    Serial.write(0x5A);         
    Serial.write(0xC0);
    Serial.write(0x01);    
    CmdStatus = 0xC1;
  }
  else if ( number == 4 )
  {  // AVI stop
    Serial.write(0x8D);
    Serial.write(0x7C);
    Serial.write(0x6B);    
    Serial.write(0x5A);       
    Serial.write(0xA0);
    Serial.write(0x03);    
    CmdStatus = 0xA3;
  }  
  else if ( number == 5 )
  { //AVI capture
    Serial.write(0x8D);
    Serial.write(0x7C);
    Serial.write(0x6B);    
    Serial.write(0x5A);      
    Serial.write(0xA0);
    Serial.write(0x02);        
    CmdStatus = 0xA2;
  }  
#if 0  
// Send ID 0x8D, 0x7C, 0x6B, 0x5C 
  if ( number == 1 )
  { // AVI start
    Serial.write(0x4F);
    Serial.write(0x38);
    Serial.write(0x5A);    
    Serial.write(0x29);    
    Serial.write(0x40);
    Serial.write(0x01);
    CmdStatus = 0x41;
  }
  else if ( number == 2 )
  { // UVC+UAC start
    Serial.write(0x4F);
    Serial.write(0x38);
    Serial.write(0x5A);    
    Serial.write(0x29);       
    Serial.write(0x50);
    Serial.write(0x01);    
    CmdStatus = 0x51;
  }
  else if ( number == 3 )
  { // USB MSC start
    Serial.write(0x4F);
    Serial.write(0x38);
    Serial.write(0x5A);    
    Serial.write(0x29);     
    Serial.write(0x60);
    Serial.write(0x01);    
    CmdStatus = 0x61;
  }
  else if ( number == 4 )
  {  // AVI stop
    Serial.write(0x4F);
    Serial.write(0x38);
    Serial.write(0x5A);    
    Serial.write(0x29);   
    Serial.write(0x40);
    Serial.write(0x03);    
    CmdStatus = 0x43;
  }  
  else if ( number == 5 )
  { //AVI capture
    Serial.write(0x4F);
    Serial.write(0x38);
    Serial.write(0x5A);    
    Serial.write(0x29);   
    Serial.write(0x40);
    Serial.write(0x02);        
    CmdStatus = 0x42;
  }
#endif

//	no = '0'+ number;
//	Serial.write(no);
#if 0
 delay(1000);
 while (1)
 {
  no = Serial.available();
  if ( no > 0 )
  {
    readByte = Serial.read();  
    if ( readByte == 0x4F )
    {
      
    }
    Serial.write(readByte);
  }
  else
     break;
 }
#endif
#if 0
  delay(3000);
	while (1)
	{
		no = Serial.available(); 
		if ( no > 0 )
		{
      if ( Serial.read() == 0x4F )
      {
        if ( Serial.read()== 0x38 )
        {
          if ( Serial.read() == 0x5A )
          {
            if ( Serial.read() == 0x29 )
            {
               readByte = Serial.read();
               if ( readByte == CmdStatus )
               {
                readByte = Serial.read();
                if ( readByte == 0x70 )
                {
                  LED_Success();
                  break;
                }
               }
               LED_Fail();
            }
          }
        }
      }
		}
    else
     break;
	}
#endif
#if 1
  delay(3000);
  while (1)
  {
    no = Serial.available(); 
    if ( no > 0 )
    {
      if ( Serial.read() == 0x8D )
      {
        if ( Serial.read()== 0x7C )
        {
          if ( Serial.read() == 0x6B )
          {
            if ( Serial.read() == 0x5A )
            {
               readByte = Serial.read();
               if ( readByte == CmdStatus )
               {
                readByte = Serial.read();
                if ( readByte == 0x80 )
                {
                  LED_Success();
                  break;
                }
               }
               LED_Fail();
            }
          }
        }
      }
    }
    else
     break;
  }
#endif
} 

void LED_Success()
{
  int i;
        for (i=0; i<3; i++)
         { 
            digitalWrite(ledPin,HIGH);
            delay(200);
            digitalWrite(ledPin, LOW); 
            delay(200);
         }
}

void LED_Fail()
{
  int i;
        for (i=0; i<10; i++)
         { 
            digitalWrite(ledPin,HIGH);
            delay(200);
            digitalWrite(ledPin, LOW); 
            delay(200);
         }
}










