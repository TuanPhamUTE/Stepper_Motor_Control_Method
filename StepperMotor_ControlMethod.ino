#define enA 9
#define enB 10
const unsigned char FullStep1PhaOn[4] = {0x20, 0x80, 0x10, 0x40};
const unsigned char FullStep2PhaOn[4] = {0xA0, 0x90, 0x50, 0x60};
const unsigned char HalfStep[8]  = {0x20, 0xA0,0x80, 0x90, 0x10, 0x50, 0x40, 0x60};
const unsigned char MicroStepLui[4]  =  {0xA0, 0x90, 0x50,0x60};
const unsigned char MicroStepTien[4]  = {0x50, 0x90, 0xA0,0x60};
const unsigned char MicroStep1st[8] = {49.73, 97.56, 141.68, 180.31, 212.08, 235.59, 250.08, 255};
const unsigned char MicroStep2nd[8] = {250.08, 235.59, 212.08, 180.31, 141.68, 97.56, 49.73, 0};
void setup() {
  Serial.begin(9600);
  DDRD = 0xf0; 
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
}
//*******************FULLSTEP 2 PHA ON**********************//
void FullStep2PhaOnFunction(int a){
      digitalWrite(enB, HIGH);
      digitalWrite(enA, HIGH); 
      PORTD = FullStep2PhaOn[a%4];
}
void FullStep2(float pos, int rpm, int pulse){
  int t2 = 300000/rpm;
  if(pos>0){
    for(int i=pulse; i>0; i--){
      FullStep2PhaOnFunction(i);
      delayMicroseconds(t2);
    }
  }
  else if(pos<0){
    for(int j=0; j<pulse; j++){
      FullStep2PhaOnFunction(j);
      delayMicroseconds(t2);
    }    
  }
}
//*******************FULLSTEP 1 PHA ON*********************//
void FullStep1PhaOnFunction(int a){
    if(((a%4)%2)==0){
      digitalWrite(enB,HIGH);
      digitalWrite(enA,LOW);
      PORTD = FullStep1PhaOn[a%4];       
    }
    else if(((a%4)%2)!=0){
      digitalWrite(enB,LOW);
      digitalWrite(enA,HIGH);
      PORTD = FullStep1PhaOn[a%4];
    }
}
void FullStep1(float pos, int rpm, int pulse){
  int t2 = 300000/rpm;
  if(pos>0){
    for(int i=pulse; i>0; i--){
      FullStep1PhaOnFunction(i);
      delayMicroseconds(t2);
    }
  }
  else if(pos<0){
    for(int j=0; j<pulse; j++){
      FullStep1PhaOnFunction(j);
      delayMicroseconds(t2);
    }    
  }
}
//**********************HALFSTEP***********************//
void HalfStepFunction(int a){
    digitalWrite(enB,HIGH);
    digitalWrite(enA,HIGH);
    PORTD = HalfStep[a%8];
}
void HalfStep1(float pos, int rpm, int pulse){
  int t1 = 150000/rpm;
  if(pos>0){
    for(int i=pulse; i>0; i--){
      HalfStepFunction(i);
      delayMicroseconds(t1);
    }
  }
  else if(pos<0){
    for(int j=0; j<pulse; j++){
      HalfStepFunction(j);
      delayMicroseconds(t1);
    }    
  }
}
//*********************MICROSTEP*****************************//

//**********Tien************************//
void MicroStepFunctionTien(int a, int rpm2){
  int t3 = (37500/rpm2);
  //lan 1
  if((a%4)==0){
    analogWrite(enA, 255);
    analogWrite(enB, 0);
    PORTD = MicroStepTien[a%4];
    for(int i=0; i<8; i++){
      analogWrite(enB, MicroStep1st[i]);
      delayMicroseconds(t3);
    } 
    analogWrite(enB, 255);
    for(int i=0; i<8; i++){
      analogWrite(enA, MicroStep2nd[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enA, 0);    
  }
  //Lan 2
  else if((a%4)==1){
    analogWrite(enB, 255);
    analogWrite(enA, 0); 
    PORTD = MicroStepTien[a%4];
    for(int i=0; i<8; i++){
      analogWrite(enA, MicroStep1st[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enA, 255);
    for(int i=0; i<8; i++){
      analogWrite(enB, MicroStep2nd[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enB, 0);  
  }
  //Lan 3
  else if((a%4)==2){
    analogWrite(enA, 255);
    analogWrite(enB, 0);
    PORTD = MicroStepTien[a%4];
    for(int i=0; i<8; i++){
      analogWrite(enB, MicroStep1st[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enB, 255);
    for(int i=0; i<8; i++){
      analogWrite(enA, MicroStep2nd[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enA, 0);    
  }
  //Lan 4
  else if((a%4)==3){
    analogWrite(enB, 255);
    analogWrite(enA, 0); 
    PORTD = MicroStepTien[a%4];
    analogWrite(enB, 255);
    for(int i=0; i<8; i++){
      analogWrite(enA, MicroStep1st[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enA, 255);
    for(int i=0; i<8; i++){
      analogWrite(enB, MicroStep2nd[i]);
      delayMicroseconds(t3);
    }
  }
}
//**********Lui************************//
void MicroStepFunctionLui(int a, int rpm2){
  int t3 = (37500/rpm2);
  //lan 1
  if((a%4)==0){
    analogWrite(enB, 255);
    analogWrite(enA, 0);
    PORTD = MicroStepLui[a%4];
    for(int i=0; i<8; i++){
      analogWrite(enA, MicroStep1st[i]);
      delayMicroseconds(t3);
    } 
    analogWrite(enA, 255);
    for(int i=0; i<8; i++){
      analogWrite(enB, MicroStep2nd[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enB, 0);    
  }
  //Lan 2
  else if((a%4)==1){
    analogWrite(enA, 255);
    analogWrite(enB, 0); 
    PORTD = MicroStepLui[a%4];
    for(int i=0; i<8; i++){
      analogWrite(enB, MicroStep1st[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enB, 255);
    for(int i=0; i<8; i++){
      analogWrite(enA, MicroStep2nd[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enA, 0);  
  }
  //Lan 3
  else if((a%4)==2){
    analogWrite(enB, 255);
    analogWrite(enA, 0);
    PORTD = MicroStepLui[a%4];
    for(int i=0; i<8; i++){
      analogWrite(enA, MicroStep1st[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enA, 255);
    for(int i=0; i<8; i++){
      analogWrite(enB, MicroStep2nd[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enB, 0);    
  }
  //Lan 4
  else if((a%4)==3){
    analogWrite(enA, 255);
    analogWrite(enB, 0); 
    PORTD = MicroStepLui[a%4];
    analogWrite(enA, 255);
    for(int i=0; i<8; i++){
      analogWrite(enB, MicroStep1st[i]);
      delayMicroseconds(t3);
    }
    analogWrite(enB, 255);
    for(int i=0; i<8; i++){
      analogWrite(enA, MicroStep2nd[i]);
      delayMicroseconds(t3);
    }
  }
}
void MicroStep1(float pos, int rpm, int pulse){
  if(pos>0){
    for(int m = 0; m<pulse; m++){
      MicroStepFunctionTien(m, rpm);    
    }
  }
  else if(pos<0){
    for(int n = 0; n<pulse; n++){
      MicroStepFunctionLui(n, rpm);    
    }
  }
}

int tocdo, soxung, chedo;
float vitri;
String NhapViTri = "Vitri(mm): ";
String NhapTocDo = "Tocdo(rpm): ";
String CheDoDieuKhien = "1 là HalfStep; 2 là FullStep1PhaOn; 3 là FullStep2PhaOn; 4 là MicroStep: ";
void loop(){
  Serial.println("ĐÂY LÀ PROJECT CUỐI KỲ CỦA NHÓM 13");
  Serial.println(CheDoDieuKhien);
  Serial.print("Hãy nhập chế độ điều khiển theo những số như trên: ");
  do{chedo = Serial.parseInt();} while(chedo==0); Serial.println(chedo); //Nhap Che do dieu khien
  
  Serial.print(NhapViTri); do{vitri = Serial.parseFloat();} while(vitri==0); Serial.println(vitri); //Nhap vitri dich chuyen

  Serial.print(NhapTocDo); do{tocdo = Serial.parseInt();}   while(tocdo==0); Serial.println(tocdo); //Nhap Tocdo dich chuyen

  if(vitri>0)  soxung = (200*vitri)/8; 
  else         soxung = (200*(-vitri))/8; 
  
  if(chedo == 1)       HalfStep1(vitri, tocdo, soxung*2);
  else if(chedo == 2)  FullStep1(vitri, tocdo, soxung);
  else if(chedo == 3)  FullStep2(vitri, tocdo, soxung);
  else if(chedo == 4)  MicroStep1(vitri, tocdo, soxung);  
}
