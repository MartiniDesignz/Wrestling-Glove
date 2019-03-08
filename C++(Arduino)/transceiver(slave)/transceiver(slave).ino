/*----------------Description (March 2019)------------------
 *  >This code is written for an arduino nano
 * 
 * The arduino has an nrf module that can either send or recieve, but it cant do  
 * both simultaneously. It uses the nrf to comunicate to the glove arduino. This  
 * arduino sends if time is up and it recieves commands like whether to add points 
 * to a score.  It then takes that info it recieves and sends it to the master 
 * arduino via a wired i2c connection.
 * 
 * It can also change its channel: 0 to 9
 * 
 * I wrote this code as a junior in highschool so... yeah(2016~2017).
 * 
 */
#include <SPI.h>//nrf stuff
#include<RF24.h>//nrf stuff
#include<nRF24L01.h>//nrf stuff
#include <Wire.h>//i2c stuff


RF24 radio(9, 10);//ce, csn pins

int cycPos = 0;//the step in the cycle that it is in.

//new stuff_______________________________________
int plus = 0;
int notR = 0;
int angleRInt = 0;

int addR = 0;
int scoreR = 0;
int angleR = 0;

int Time = 0;
int TimeLeft;
int TimeLessTen;

int ClockInt = 0;

//i2c stuff ____________________________

int i2cID = 2;
int i2cInt = 0;

int timerGoing = 0;
int TimeOut = 0;
//
//channel changing stuff___________________

int L1 = 2;//
int L2 = 3;//
int R1 = 4;//
int R2 = 5;//
int M1 = 6;//
int M2 = 7;//
int M3 = 8;//

int funcBtn = 14;
int rawBtn = 0;
int funcBtnInt = 0;

int channel = 0;
int settingsInt = 0;
bool funcBtnWas = false;
bool settingsInit = true;
int setBtnInt = 0;

//custom funtions********************

const byte address[][6] = {"00001", "00002" };
double radioChannel[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

void off(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
}

void zero(){
  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, HIGH);
}

void one(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
}

void two(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, LOW);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
}

void three(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
}

void four(){
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, LOW);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, LOW);
}

void five(){
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
}

void six(){
  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, LOW);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
}

void seven(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
}

void eight(){
  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
}

void nine(){
  digitalWrite(L1, HIGH);
  digitalWrite(L2, LOW);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, HIGH);
  digitalWrite(M3, HIGH);
}

void dispChannel(){
  switch(channel){
    case 0 :
      zero();
      break;
    case 1 :
      one();
      break;
    case 2 :
      two();
      break;
    case 3 :
      three();
      break;
    case 4 :
      four();
      break;
    case 5 :
      five();
      break;
    case 6 :
      six();
      break;
    case 7 :
      seven();
      break;
    case 8 :
      eight();
      break;
    case 9 :
      nine();
      break;
  }
}

void settings(){
  funcBtnInt = 0;
  settingsInit = true;
  while( funcBtnInt < 20){
    rawBtn = digitalRead(funcBtn);
    Serial.println(funcBtnInt);
    if(rawBtn == 1){
      if(settingsInit != true){
        funcBtnInt++;
        funcBtnWas = true;
      }
    }else{
      settingsInit = false;
      funcBtnInt = 0;
      if(funcBtnWas == true){
        if(channel<9){
          channel++;
        }else{
          channel = 0;
        }
        
        funcBtnWas = false;
      }
    }
    
    dispChannel();
    delay(100);
  }
//  Serial.println(0x80);
  radio.begin();
  radio.setChannel(radioChannel[channel]);
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);
  radio.setPALevel(RF24_PA_MAX);//can be set to _MIN 
  setBtnInt = 0;
  off();
}


void Radio(){
  //analogTime = analogRead(analogTimePin);
  //Serial.println(analogTime);
  if(Time == 0){
    TimeOut = 1;
  }else{
    TimeOut = 0;
  }
  if(cycPos<=4){
    radio.stopListening();
    //sensorValue = (sensorValue-200)/100;
    char sending[32] = {char(cycPos+48), char(timerGoing+48), char(cycPos+48), char(cycPos+48), char(TimeOut+48)};
    radio.write(sending, sizeof(sending));
    Serial.println(sending);
  }
  if(cycPos>=5){
  radio.startListening();
    char receivedMessage[32] = {0};
    plus = 0;
    if(radio.available()){
      radio.read(receivedMessage, sizeof(receivedMessage));
      Serial.println(receivedMessage);//===================
      cycPos = int(receivedMessage[1])-48;// determining the cyc pos num that was sent
      plus = int(receivedMessage[0])-48;
      angleR = int(receivedMessage[2])-48;
//      timeGoing = int( receivedMessage[1]) - 48;// determin if PI btn is timeGoing
//      timeOut = int(receivedMessage[4]) - 48;
      if(angleR >= 2){
        if(angleRInt<3){
          plus = 0;
        }
        angleRInt++;
        notR = 0;
        if(plus>3){
          addR++;
        }else{
          plus = 0;
        }
        if(addR<2){
          if(plus>7){
            plus = plus-5;
          }else{
            if(plus>=3){
              plus = plus - 4;
            }
          }
          scoreR = scoreR + plus;
          Serial.println("____");
          Serial.println(scoreR);
          Serial.println("____");
        }
      }else{
        angleRInt = 0;
        notR++;
        if(notR>=3){
          addR = 0;
        }
      } 
    }
  }
  cycPos++;
  if(cycPos>=10){
    cycPos = 0;
  }
}

void recEvent(int howMany){
  char c[8] = {0};
  i2cInt = 0;
  while(Wire.available()){
    c[i2cInt] = Wire.read();  
    //Serial.println(c[1]);
    i2cInt++;
  }
  if(c[0] == 'T'){
    Time = int(c[1]);
    timerGoing = int(c[2]);
    Serial.println(Time);
  }
}

void reqEvent(){
  Wire.write(char(scoreR));
  scoreR = 0; 
}

void setup() {
  while(!Serial);
  Serial.begin(9600);
  
  Wire.begin(i2cID);
  Wire.onReceive(recEvent);
  Wire.onRequest(reqEvent);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(funcBtn, INPUT);
  
  radio.begin();
  radio.setChannel(76);
  radio.openWritingPipe(address[1]);
  radio.openReadingPipe(1, address[0]);
  radio.setPALevel(RF24_PA_MAX);//can be set to _MIN 
}


void loop(){
  rawBtn = digitalRead(funcBtn);
    if(rawBtn > 0){
      if(funcBtnWas != true){
        settings();
      }
    }else{
      funcBtnWas = false;
    }
//  if(ClockInt%10 == 0){
//    Serial.println(Time);
//    Radio();
//  }
  Radio();
//  Serial.println(Time);
  
  ClockInt++;
  if(ClockInt>=99){
    ClockInt = 0;
  }
  delay(1);
}
//End of program
