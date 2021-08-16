
 //F5 EE F7 C2   blue
 //22 77 FB 0D



#include <SPI.h>
#include <MFRC522.h>
#include <FastLED.h>
#include <Servo.h>




#define RST_PIN         9          // Configurable, see typical pin layout above
#define SS_PIN          10         // Configurable, see typical pin layout above

// leddf defs
#define LED_PIN     3
#define NUM_LEDS    90 
int BRIGHTNESS  = 100  ;                                              //#define BRIGHTNESS  64;
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
int i=0;


unsigned long previousMillis = 0;        // will store last time LED was updated

float interval = 10;  


MFRC522 mfrc522(SS_PIN, RST_PIN);  // Create MFRC522 instance


Servo servo1; 
Servo servo2; 

void setup() {
  
  Serial.begin(9600);   // Initialize serial communications with the PC
  while (!Serial);    // Do nothing if no serial port is opened (added for Arduinos based on ATMEGA32U4)
  SPI.begin();      // Init SPI bus
  mfrc522.PCD_Init();   // Init MFRC522
  delay(4);       // Optional delay. Some board do need more time after init to be ready, see Readme
  

  servo1.attach(5);
  servo2.attach(6);

  servo1.write(60);
  servo2.write(120);

  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(  BRIGHTNESS );

  // FastLED's built-in rainbow generator
  //fill_rainbow( leds, NUM_LEDS, 0, 7);
  //FastLED.show();
  //delay(2000);


  
}

int b=BRIGHTNESS;
bool flip=false;

void loop() {
  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.

 unsigned long currentMillis = millis();

 // Serial.print("Running"); 

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    bluePulse();
    
    }
  
   
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }



//Reading from the card
  String tag = "";
  for (byte i = 0; i < mfrc522.uid.size; i++)
  {
    tag.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
    tag.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tag.toUpperCase();


  
  
  //Checking the card
  if (tag.substring(1) == "22 77 FB 0D") //change here the UID of the card/cards that you want to give access
  {
    FastLED.setBrightness(100);
     
    for(float i=40;i>1;i/=1.02){
      blueRing();
      delay(i);}
      
    for(float i=150;i>1;i--){
      blueRing();} 
      
    for(float i=BRIGHTNESS;i>5;i-=0.6){
      FastLED.setBrightness(i);
      blueRing();}
    
    for(float i=1.0;i<BRIGHTNESS;i+=0.2){
      FastLED.setBrightness(i);
      fill_solid(leds, NUM_LEDS, CRGB::Green);FastLED.show();} 

  servo1.write(170);
  servo2.write(10);
     
     delay(2000);
    
  }

                                                
  else{

    FastLED.setBrightness(100);
    
    for(float i=40;i>1;i/=1.02){
      blueRing();
      delay(i);}
      
    for(float i=150;i>1;i--){
      blueRing();} 
      
    for(float i=BRIGHTNESS;i>5;i-=0.6){
      FastLED.setBrightness(i);
      blueRing();}
    
    for(float i=1.0;i<BRIGHTNESS;i+=0.2){
      FastLED.setBrightness(i);
      fill_solid(leds, NUM_LEDS, CRGB::Red);FastLED.show();} 

    servo1.write(60);
    servo2.write(120);
  
     delay(2000);
    
  }
  
}



void ledRing(){
  
  i = i>=(NUM_LEDS/2) ? i=1 : i+=1;


  if(i>(NUM_LEDS/6)*2){
    fill_solid(leds+i, (NUM_LEDS/6)-i+(NUM_LEDS/6)*2, CRGB::Red); 
    fill_solid(leds,i-((NUM_LEDS/6)*2), CRGB::Red);     
  }
  else{
    fill_solid(leds+i, NUM_LEDS/6, CRGB::Red);
  } 


  if(i>(NUM_LEDS/6) && i<=(NUM_LEDS/6)*2){
  fill_solid(leds+(NUM_LEDS/6)+i, (NUM_LEDS/6)-i+(NUM_LEDS/6), CRGB::Green); 
  fill_solid(leds,i-(NUM_LEDS/6), CRGB::Green);     
  }
  else if(i>(NUM_LEDS/6)*2){
    fill_solid(leds+i-((NUM_LEDS/6)*2), NUM_LEDS/6, CRGB::Green);
  }
  else{
    fill_solid(leds+(NUM_LEDS/6)+i, NUM_LEDS/6, CRGB::Green);
  }


  if(i>0 && i<=NUM_LEDS/6){
    fill_solid(leds+(NUM_LEDS/6)*2+i, (NUM_LEDS/6)-i, CRGB::Yellow); 
    fill_solid(leds,i, CRGB::Yellow);     
  }
  else if(i>NUM_LEDS/6){
    fill_solid(leds+i-NUM_LEDS/6, NUM_LEDS/6, CRGB::Yellow);
  }

  // SECOND SET


  if(i>(NUM_LEDS/6)*2){
    fill_solid(leds+i+(NUM_LEDS/2), (NUM_LEDS/6)-i+(NUM_LEDS/6)*2, CRGB::Red); 
    fill_solid(leds+(NUM_LEDS/2),i-((NUM_LEDS/6)*2), CRGB::Red);     
  }
  else{
    fill_solid(leds+i+(NUM_LEDS/2), NUM_LEDS/6, CRGB::Red);
  } 


  if(i>(NUM_LEDS/6) && i<=(NUM_LEDS/6)*2){
  fill_solid(leds+(NUM_LEDS/6)+i+(NUM_LEDS/2), (NUM_LEDS/6)-i+(NUM_LEDS/6), CRGB::Green); 
  fill_solid(leds+(NUM_LEDS/2),i-(NUM_LEDS/6), CRGB::Green);     
  }
  else if(i>(NUM_LEDS/6)*2){
    fill_solid(leds+i-((NUM_LEDS/6)*2)+(NUM_LEDS/2), NUM_LEDS/6, CRGB::Green);
  }
  else{
    fill_solid(leds+(NUM_LEDS/6)+i+(NUM_LEDS/2), NUM_LEDS/6, CRGB::Green);
  }


  if(i>0 && i<=NUM_LEDS/6){
    fill_solid(leds+(NUM_LEDS/6)*2+i+(NUM_LEDS/2), (NUM_LEDS/6)-i, CRGB::Yellow); 
    fill_solid(leds+(NUM_LEDS/2),i, CRGB::Yellow);     
  }
  else if(i>NUM_LEDS/6){
    fill_solid(leds+i-(NUM_LEDS/6)+(NUM_LEDS/2), NUM_LEDS/6, CRGB::Yellow);
  }
  FastLED.show();

  }
 

void blueRing(){
  
  FastLED.clear();

  i = i>=(NUM_LEDS/2) ? i=1 : i+=1;

  if(i>(NUM_LEDS/6)*2){
    fill_solid(leds+i, (NUM_LEDS/6)-i+(NUM_LEDS/6)*2, CRGB::Blue); 
    fill_solid(leds,i-((NUM_LEDS/6)*2), CRGB::Blue);     
  }
  else{
    fill_solid(leds+i, NUM_LEDS/6, CRGB::Blue);
  } 

  /// Second Stage 
  
  if(i>(NUM_LEDS/6)*2){
    fill_solid(leds+i+(NUM_LEDS/2), (NUM_LEDS/6)-i+(NUM_LEDS/6)*2, CRGB::Blue); 
    fill_solid(leds+(NUM_LEDS/2),i-((NUM_LEDS/6)*2), CRGB::Blue);     
  }
  else{
    fill_solid(leds+i+(NUM_LEDS/2), NUM_LEDS/6, CRGB::Blue);
  } 

    
  FastLED.show();
}

  

void bluePulse(){

  if(flip==false){
    b++;
    flip = b>100 ? true : false;
  }
  if(flip==true){
    b--;
    flip = b<5 ? false : true;
  }
  
  FastLED.setBrightness(b);
  fill_solid(leds,NUM_LEDS, CRGB::Blue);     
  FastLED.show();
  
}



/**
  SEQUENCE 

  when turn on: 1/3 red yellow green and when on 

  card on good : circlese fast from the 3 collors then fades and fades back to red or green.

  charging: 



 */
