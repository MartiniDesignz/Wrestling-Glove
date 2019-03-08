/*----------------Description (March 2019)------------------
 * This code is written for an arduino nano, it can controll up to 16 7 segment
 * displays by making a binary counter with 4 of the I/O pins.
 * 
 *    it has a timer, red score, and I think a green score
 *    it also has a few inputs
 * 
 * 
 * 
 * I wrote this code as a junior in highschool so... yeah(2016~2017).
 * 
 */
#include <Wire.h>// i2c comunication

int s = 0;

char StartLet;

int cont1 = 2;//Im pretty sure these are the out put pins to make the binary counter
int cont2 = 3;
int cont3 = 4;
int cont4 = 5;

int L1 = 6;//Display pin
int L2 = 7;//Display pin
int R1 = 8;//Display pin
int R2 = 9;//Display pin
int M1 = 10;//Display pin
int M2 = 11;//Display pin
int M3 = 12;//Display pin


int Btn1 = A6;// pin for btn1, subs from scoreR
int Btn2 = A7;// pin for btn2, adds to ScoreR
int Btn3 = 14;// pin for the start stop and reset btn



int ChangeInt1 = 0;// value of Btn1
int ChangeInt2 = 0;// value of Btn2
int ChangeInt3 = 0;// value of Btn3
int ChangeInt4 = 0;

int scoreR = 0;// red score
int numToDisp = 0;// The number that is going to be displayed at that moment in time

int startTime = 19;// default start time
int Time = 0;// current time var
bool timerGo = false;// bool to tell wether the timer should be going or not 

int Btn1TimeInt = 0;
int dif1 = 0;
int dif1Total = 0;

int Btn2TimeInt = 0;
int dif2 = 0;
int dif2Total = 0;

int timePlusBtn = 15;
int Btn3TimeInt = 0;
int dif3 = 0;
int dif3Total = 0;

int pressed3Int = 0;
bool btn3Stop = false;
bool btn3Pressed = false;
int timeStartStopInt = 0;

int loopCount = 0;

int arduino1ID = 2;// The id of the tranceiver arduino
int i2cInt = 0;// 

int plusRed = 0;// the number that is received from the slave arduino and is added to the Red score

int timerGoInt = 0;

void setup() {
  // put your setup code here, to run once:
  while(!Serial);
  Serial.begin(9600);

  Wire.begin();

  pinMode(cont1, OUTPUT);
  pinMode(cont2, OUTPUT);
  pinMode(cont3, OUTPUT);
  pinMode(cont4, OUTPUT);

  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);


  pinMode(Btn1, INPUT);
  pinMode(Btn2, INPUT);
  pinMode(timePlusBtn, INPUT);
  
  digitalWrite(L1, HIGH);
  digitalWrite(L2, HIGH);
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  digitalWrite(M1, HIGH);
  digitalWrite(M2, LOW);
  digitalWrite(M3, HIGH);

  
  Time = startTime;
}


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


void checkBtns(){
   // code for btns input
  ChangeInt1 = analogRead(Btn1);
  ChangeInt2 = analogRead(Btn2);
  ChangeInt3 = digitalRead(Btn3);
  ChangeInt4 = digitalRead(timePlusBtn);
  
  
  if(ChangeInt1>400){
    if( dif1 == 0){
      scoreR--;
      dif1Total = 0;
    }else{
      dif1Total++;
    }
    if(dif1Total>=10){
      if(dif1Total%2 != 0){
        scoreR--;
      }
    }
    if(dif1Total>=30){
      if(dif1Total%2 != 1){
        scoreR--;
      }
    }
  }
  
  if(ChangeInt1>400){
    Btn1TimeInt = loopCount+1;
  }else{
    Btn1TimeInt = loopCount;
  }

  dif1 = Btn1TimeInt - loopCount;

  Serial.println(scoreR);
  if(ChangeInt2>400){
    if( dif2 == 0){
      scoreR++;
      dif2Total = 0;
    }else{
      dif2Total++;
    }
    if(dif2Total>=10){
      if(dif2Total%2 != 0){
        scoreR++;
      }
    }
    if(dif2Total>=30){
      if(dif2Total%2 != 1){
        scoreR++;
      }
    }
  }

  if(ChangeInt2>400){
    Btn2TimeInt = loopCount+1;
  }else{
    Btn2TimeInt = loopCount;
  }
  
  dif2 = Btn2TimeInt - loopCount;



  if(ChangeInt3 == 1){
    if(btn3Stop == false){
      pressed3Int++;
      if(pressed3Int>10){
        Time = startTime;
        btn3Pressed = false;
        btn3Stop = true;
      }else{
        btn3Pressed = true;
      }
    }
  }else{
    if(btn3Pressed == true){
      timeStartStopInt++;
      if(timeStartStopInt%2 == 0){
        timerGo = false;
        timerGoInt = 0;
      }else{
        timerGo = true;
        timerGoInt = 1;
      }
    }
    btn3Stop = false;
    pressed3Int = 0;
    btn3Pressed = false;
  }

  if(ChangeInt4==1){
    if( dif3 == 0){
      Time++;
      dif3Total = 0;
    }else{
      dif3Total++;
    }
    if(dif3Total>=10){
      if(dif3Total%2 != 0){
        Time++;
      }
    }
    if(dif3Total>=30){
      if(dif3Total%2 != 1){
        Time++;
      }
    }
  }
  
  if(ChangeInt4==1){
    Btn3TimeInt = loopCount+1;
  }else{
    Btn3TimeInt = loopCount;
  }

  dif3 = Btn3TimeInt - loopCount;
  
  //check the score from the traciever arduino
  Wire.requestFrom(arduino1ID, 1);// 1st num is address, 2nd num is how many bytes do you want back

  char c[1] = {0};
  i2cInt = 0;
  while(Wire.available()){
    c[i2cInt] = Wire.read();
      
    //Serial.println(c[1]);
    i2cInt++;
  }
  plusRed = int(c[0]);
  Serial.println(plusRed);
  scoreR = scoreR + plusRed;
}



void loop() {
  if(scoreR>18){
    scoreR = 19;
  }
  if(scoreR<1){
    scoreR = 0;
  }

 //++++++++++++++++++++++++++++++++++++++++
 
 if(loopCount%100 == 0){
  checkBtns();
 }
  
  //timer stuff***************************
  if(loopCount == 999){
    if(timerGo == true){
      if (Time>0){
        Time--;
      }else{
        pressed3Int++;
        timerGoInt = 0;
        timerGo = false;
      }
    }
    
    char mes[8] = {'T', char(Time), char(timerGoInt) };
    Wire.beginTransmission(arduino1ID);
    Wire.write(mes);
    Wire.endTransmission();
  }
  
  // 7 segment display************************
  //if(loopCount%2 == 1){
    //dispBreak();
    //off();
  //}
  if(loopCount%5 == 0){
    off();
    digitalWrite(cont1, LOW);
    digitalWrite(cont2, LOW);
    digitalWrite(cont3, HIGH);
    numToDisp = scoreR%10;
    
  }else{
    off();
    if(loopCount%5 == 1){
      digitalWrite(cont1, HIGH);
      digitalWrite(cont2, HIGH);
      digitalWrite(cont3, LOW);
      numToDisp = Time%10;
    }else{
      if(loopCount%5==2){
        digitalWrite(cont1, LOW);
        digitalWrite(cont2, HIGH);
        digitalWrite(cont3, LOW);
        numToDisp = Time/10;
        numToDisp = numToDisp%6;
      }
      if(loopCount%5==3){
        digitalWrite(cont1, HIGH);
        digitalWrite(cont2, LOW);
        digitalWrite(cont3, LOW);
        numToDisp = Time/60;
      }
    }
    if(loopCount%5==4){
      digitalWrite(cont1, HIGH);
      digitalWrite(cont2, LOW);
      digitalWrite(cont3, HIGH);
      numToDisp = scoreR/10;
    }
  }
  
 
  switch(numToDisp){
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

  
  //End of loop**************************
  //loopCount++;
  if (loopCount <= 1000){
    loopCount++;
  }else{
    loopCount = 0;
  }
  
  delay(1);
}



// end of code
