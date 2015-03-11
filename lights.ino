/* 
 Encoder sim
 -----------
 
 
 K Lawson 2014
 
 Use a pot to control the cycle speed of an encoder simulator.  An A and B channel drive in either direction at speeds from 1-10K Hz.
 A bi-colour LED indiates speed and when we reach 1k and 10kHz.
 
 When in the mid-position the unit is 'off'; this is taken from a dedband.
 
 The encoder SM has 4 states and outputs at 4x lower f than it's called.
 The analog sampling and LED control are done using ms timing.
 
 1-1KHz output frequency
 
 Green LED    0-10Hz
 Red LED      10-.1KHz
 Bi           .1K - 1K
 
 
 Notes on Mini
 -------------
 
 The mini is not pin-pin compatible with the minipro programming header and an adapter
 header needs to e made to program the unit.  This is done using a 5 w 2.54 header strip
 remove a min and bend the last one then either solder or friction fit to program it.
 
          PGMR
 | dtr rx tx vcc cts gnd |
 -------------------------
       |  |  |     __|
       |  |  |    /
 -------------------------
 | x  tx rx vcc gnd  x    |
 
 reset btn just before pgm when the IDE says 'uploading'.  Use 2.54 header to make interface and balance
 in holes.
 
 */
 
 
const byte RD = 10;
const byte YL = 12;
const byte GN = 11;
const byte SW = 14;


// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.

  //BI LED drive
  pinMode(10,OUTPUT); //r
  pinMode(11,OUTPUT); //g
  pinMode(12,OUTPUT); //y
  pinMode(13,OUTPUT); //sw
  pinMode(14,INPUT_PULLUP); //sw ip
 
  //digitalWrite(13, 1); 

  Serial.begin(9600);  
}//END Setup





// the loop routine runs over and over again forever:
void loop() 
{
   static int state=0,msDelay;
   byte swval;
 
   swval = digitalRead(SW);

   msDelay = random(0,10000) + 1000;
  
  if(swval)
    state = 0;
  
  switch(state)
  {
    //@@@@ switch on @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
    case 0:  RAG(1,0,0); //r a g
             break;
              
    //@@@@ normal ops @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@      
    case 1:
    case 2:
    case 3:
    case 4:  RAG(1,0,0);
             delay(msDelay);
             break;

    case 5:  RAG(1,1,0);
             delay(3000);
             break;

    case 6:
    case 7: 
    case 8:  RAG(0,0,1);
             delay(msDelay);
             break;
             
    case 9:
    case 10:  RAG(0,1,0);
             delay(3000);
             break;

    case 11:  state = 0;
              break;
      
    default:
      break;
  }
  state ++;
}//END Loop


void RAG(byte r,byte a,byte g)
{
  digitalWrite(RD, r ^ 1);
  digitalWrite(YL, a ^ 1);
  digitalWrite(GN, g ^ 1); 
}
