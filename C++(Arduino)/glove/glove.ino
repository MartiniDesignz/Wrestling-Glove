/*----------------Description (March 2019)------------------
 *  >This code is written for an arduino nano
 * 
 * The arduino has an nrf module that can either send or recieve, but it cant do  
 * both simultaneously. It uses the nrf to comunicate to the control pannel arduino. This  
 * arduino sends commands like whether to add points to a score and recieves info like 
 * whether time is up or not.  
 * 
 * It can also change its channel: 0 to 9
 * 
 * I wrote this code as a junior in highschool so... yeah(2016~2017).
 * 
 */
#include <SPI.h>
#include<RF24.h>
#include<nRF24L01.h>//nrf connection


//ce, csn pins
RF24 radio(9, 10);


int L1 = 2;//
int L2 = 3;//
int R1 = 4;//
int R2 = 5;//
int M1 = 6;//
int M2 = 7;//
int M3 = 8;//

int sensorPin = A6;    // select the input pin for the potentiometer
int sensorValue = 0;  // variable to store the value coming from the sensor

int  LED1 = 18;//
int LED2 = 19;//

int fingBtn1 = A7;
int fs = 0;
int fingBtn1int = 0;

int funcBtn = 14;
int rawBtn = 0;
int funcBtnInt = 0;

int channel = 0;
int settingsInt = 0;
bool funcBtnWas = false;
bool settingsInit = true;

int Btn1TimeInt = 0;
int dif1 = 0;
int dif1Total = 0;

int Btn2TimeInt = 0;
int dif2 = 0;
int dif2Total = 0;

int setBtnInt = 0;


int btn1State = 0;
int timeGoing;//1 or 0 bassed on data received from pi
int timeOut;
double cycPos;//the step in the cycle that it is in.

int flashInt = 0;

int y = 0;

double radioChannel[] = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

const byte address[][6] = {"00001", "00002"};

void off(){
  digitalWrite(L1, LOW);
  digitalWrite(L2, LOW);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  digitalWrite(M1, LOW);
  digitalWrite(M2, LOW);
  digitalWrite(M3, LOW);
}

//custom function
void connect(){//function that listens untill it receives a signal from the master
  off();
  bool conected = false;
  while(conected != true){
    rawBtn = digitalRead(funcBtn);
    if(rawBtn > 0){
      if(funcBtnWas != true){
        settings();
      }
    }else{
      funcBtnWas = false;
    }
    Serial.println("Conecting");
    radio.startListening();
    char con[32] = {0};
    char mes[32] = {0};
    if(radio.available()){
      radio.read(mes, sizeof(mes));
      Serial.println(mes);
      conected = true;
      cycPos = double(mes[0]) - 48;
    }
    delay(1);
  }
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
        if(channel<=9){
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
  radio.begin();
  Serial.println(radioChannel[channel]);
  radio.setChannel(radioChannel[channel]);
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.setPALevel(RF24_PA_MAX);//can be set to _MIN 
  setBtnInt = 0;
  connect();
}


void setup() {
  while(!Serial);
  Serial.begin(9600);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(fingBtn1, INPUT);
  pinMode(funcBtn, INPUT);
  
  radio.begin();
  radio.setChannel(76);
  radio.openWritingPipe(address[0]);
  radio.openReadingPipe(1, address[1]);
  radio.setPALevel(RF24_PA_MAX);//can be set to _MIN 

  fingBtn1int = 0;
  connect();
  //delay(100);
}

// Loop function
void loop() {
  sensorValue = analogRead(sensorPin);
  fs = analogRead(fingBtn1);

  rawBtn = digitalRead(funcBtn);
    if(rawBtn > 0){
      if(funcBtnWas != true){
        settings();
      }
    }else{
      funcBtnWas = false;
    }
  Serial.println("hello");
  y = 0;
  
  while(fs>10){
    y++;
    fs = fs/1.6;
  }
  //Serial.println(y);

  //Serial.println(cycPos);
  if (cycPos <= 4){
    radio.startListening();
    char receivedMessage[32] = {0};
    if(radio.available()){
      radio.read(receivedMessage, sizeof(receivedMessage));
      //Serial.println("____");
      //Serial.println(receivedMessage);//==============
      //Serial.println("____");
      cycPos = int(receivedMessage[0])-48;// determining the cyc pos num that was sent
      timeGoing = int( receivedMessage[1])-48;// determin if PI btn is timeGoing
      timeOut = int(receivedMessage[4])-48;
     }
     Serial.println("hello");
   //cycPos++;
   //delay(1000);
  }
  if(cycPos >= 5){
    radio.stopListening();
    sensorValue = (sensorValue-200)/100;
    char sending[32] = {char(y+48), char(cycPos+48), char(sensorValue+48) };
        
    radio.write(sending, sizeof(sending));
    //Serial.println(sending);//==============
  }
  
  //Serial.println(timeGoing);
  if(timeGoing == 1){
    digitalWrite(LED1, HIGH);
  }else{
    digitalWrite(LED1, LOW);
  }
  if(timeOut == 1){
    flashInt++;
    if(flashInt%2 == 1){
      digitalWrite(LED2, HIGH);
    }else{
      digitalWrite(LED2, LOW);
    }
    if(flashInt>=30){
      flashInt = 0;
    }
  }else{
    digitalWrite(LED2, LOW);
  }
  cycPos++;
  if(cycPos>9){
    cycPos = 0;
    //Serial.println("reset");
  }
  delay(1);
}
