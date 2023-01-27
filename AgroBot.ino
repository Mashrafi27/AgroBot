#include<Keypad.h>
#include<LiquidCrystal.h>
#include<Servo.h>

//switches###1.........................................................................
int fertilizer_switch = 48;
int pesticide_switch = 49;
int irrigation_switch = 50;
int screen_switch = 51;
int setup_switch = 52;
int pushbutton_init = 53;
//switches..........................................................................


//parameters###2........................................................................
int lenth;
int width;
int Tlenth;
int Twidth;
int T_p;
int T_s;
//parameters.......................................................................


//Keypad###3...........................................................................
const byte rows =4;
const byte cols =4;
char keys[rows][cols] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowpins[rows] = {7,6,5,4};
byte colpins[cols] = {3,2,1,0};
Keypad keypad = Keypad(makeKeymap(keys), rowpins, colpins, rows, cols);
//keypad................................................................................


//liquid crystal###4.......................................................................
LiquidCrystal lcd(42, 43, 44, 45, 46, 47);
int brightness = 10;


//other parameters###5.....................................................................
int a[10];
int i;
int x,y;
int pos;
//.........................................................

//servo's###6....................................................................................
Servo moisture;
Servo pesticide;
Servo urea;
int pesticide_motor = 29;
//.......................................................................................


//gear motors###7........................................................................................
int In1 = 22;
int In2 = 23;
int In3 = 24;
int In4 = 25;
//......................................................................................................


//sensors##8............................................................................................
int moisture_pin = A0;
int moisture_read;
int moisture_val;
int rain_pin = A1;
int temp_pin = A2;
int temp_read;
float temp_cel;
//.......................................................................................................

void setup()
{

  //switches###1......................................................................................
  pinMode(fertilizer_switch,INPUT);
  pinMode(pesticide_switch,INPUT);
  pinMode(irrigation_switch,INPUT);
  pinMode(screen_switch,INPUT);
  pinMode(setup_switch,INPUT);
  pinMode(pushbutton_init,INPUT);
  //switches


  //###4.....................................................................................
  pinMode(brightness, OUTPUT);
  analogWrite(brightness, 512);
  lcd.begin(16,2);
  Serial.begin(9600);

  lcd.write("initializing...");
  delay(1000);
  lcd.clear();
  lcd.write("plant's gap");
  lcd.setCursor(0,1);

  int i = 0;

  //###6................................................................................................
  moisture.attach(26);
  moisture.write(180);
  pesticide.attach(27);
  pesticide.write(57);
  urea.attach(28);
  urea.write(115);
  pinMode(pesticide_motor, OUTPUT);
  //................................................................................................


  //###7............................................................................................
  pinMode(In1,OUTPUT);
  pinMode(In2,OUTPUT);
  pinMode(In3,OUTPUT);
  pinMode(In4,OUTPUT);
  //..................................................................................................

  //###8...............................................................................................
  pinMode(moisture_pin,INPUT);
  pinMode(temp_pin,INPUT);
  pinMode(rain_pin,INPUT);
  //................................................................................................
}


void loop()
{
  if(digitalRead(setup_switch)==HIGH){  
  char key = keypad.getKey();

  if(int(key) != 0){
    if(key == '1'){
      a[i]=1;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }
    else if(key == '2'){
      a[i]=2;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }
    else if(key == '3'){
      a[i]=3;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }
    else if(key == '4'){
      a[i]=4;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }
    else if(key == '5'){
      a[i]=5;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }
    else if(key == '6'){
      a[i]=6;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }
    else if(key == '7'){
      a[i]=7;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }
    else if(key == '8'){
      a[i]=8;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }
    else if(key == '9'){
      a[i]=9;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }
    else if(key == '0'){
      a[i]=0;
      lcd.write(key);
      Serial.print(a[i]);
      lcd.setCursor((i+1),1);
    }        
    i++;
    if(i==2) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("row gap");
      lcd.setCursor(0,1);
    }
    if(i==4){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("plant's in row");
      lcd.setCursor(0,1);    
    }
    if(i==7){
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.write("number of row");
      lcd.setCursor(0,1);     
    }
  }
  }
  if(digitalRead(pushbutton_init)==HIGH){
    lenth= a[0]*10 + a[1];
    width= a[2]*10 + a[3];
    Tlenth = a[4]*100 + a[5]*10 + a[6];
    Twidth = a[7]*100 + a[8]*10 + a[9];

    T_p = ((lenth*1000)/14); //experimental....................................................................(0)
    T_s = ((width*1000)/14);
      
    
    if(digitalRead(fertilizer_switch) == HIGH && digitalRead(pesticide_switch) == LOW && digitalRead(irrigation_switch) == LOW && digitalRead(screen_switch)==LOW){
      if((Twidth%2)!=0){
        for(y=0;y<((Twidth-1)/2);y++){  
          for(x=0;x<(Tlenth+1);x++){  
            delay(1000);
            digitalWrite(In1,HIGH);
            digitalWrite(In3,HIGH);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            delay(T_p);
            digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            delay(1000);
            urea.write(105);//depends..............................................................(1);
            delay(50);
            urea.write(115);
          }
          digitalWrite(In1,LOW);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,HIGH);
          digitalWrite(In4,LOW);    
          delay(400);  //at 9V, replaceble...............................................................(2)
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(T_s);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,HIGH);
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          
          for(x=0;x<Tlenth+1;x++){
            delay(1000);
            digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,HIGH);
            digitalWrite(In4,HIGH);
            delay(T_p);
            digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            delay(1000);
            urea.write(105);
            delay(50);
            urea.write(115);      
          }
          delay(250);
          digitalWrite(In1,LOW);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,HIGH);
          digitalWrite(In4,LOW); 
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(T_s);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);     
          digitalWrite(In1,HIGH);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,HIGH);
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW); 
        }
      }
      if((Twidth%2)==0){
        for(y=0;y<((Twidth/2)-1);y++){  
          for(x=0;x<Tlenth+1;x++){  
            delay(1000);
            digitalWrite(In1,HIGH);
            digitalWrite(In3,HIGH);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            delay(T_p);
            digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            delay(1000);
            urea.write(105);
            delay(50);
            urea.write(115);
          }
          digitalWrite(In1,LOW);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,HIGH);
          digitalWrite(In4,LOW);    
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(T_s);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,HIGH);
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
        
          for(x=0;x<Tlenth+1;x++){
            delay(1000);
            digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,HIGH);
            digitalWrite(In4,HIGH);
            delay(T_p);
            digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            delay(1000);
            urea.write(105);
            delay(50);
            urea.write(115);      
          }
          delay(250);
          digitalWrite(In1,LOW);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,HIGH);
          digitalWrite(In4,LOW); 
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(T_s);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);     
          digitalWrite(In1,HIGH);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,HIGH);
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);    
        }
      
        for(x=0;x<Tlenth+1;x++){  
          delay(1000);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(T_p);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(1000);
          urea.write(105);
          delay(50);
          urea.write(115);
        }
        digitalWrite(In1,LOW);
        digitalWrite(In3,LOW);
        digitalWrite(In2,HIGH);
        digitalWrite(In4,HIGH);
        delay((T_p)*(Tlenth));
        digitalWrite(In1,LOW);
        digitalWrite(In3,LOW);
        digitalWrite(In2,LOW);
        digitalWrite(In4,LOW);
      }
    }
  if(digitalRead(fertilizer_switch) == LOW && digitalRead(pesticide_switch) == HIGH && digitalRead(irrigation_switch) == LOW && digitalRead(screen_switch)==LOW){
      if((Twidth%2)!=0){
        for(y=0;y<((Twidth-1)/2);y++){  
          for(x=0;x<Tlenth+1;x++){  
            digitalWrite(In1,HIGH);
            digitalWrite(In3,HIGH);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            digitalWrite(pesticide_motor,HIGH);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
          }
          digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            digitalWrite(pesticide_motor,LOW);
            delay(1000);
          digitalWrite(In1,LOW);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,HIGH);
          digitalWrite(In4,LOW);    
          delay(400);  //at 9V, replaceble...............................................................(2)
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(T_s);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,HIGH);
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(1000);
          
          for(x=0;x<Tlenth+1;x++){
           
            digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,HIGH);
            digitalWrite(In4,HIGH);
            digitalWrite(pesticide_motor,HIGH);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);      
          }
          digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            digitalWrite(pesticide_motor,LOW);
          delay(1000);
          digitalWrite(In1,LOW);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,HIGH);
          digitalWrite(In4,LOW); 
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(T_s);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);     
          digitalWrite(In1,HIGH);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,HIGH);
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW); 
          delay(1000);
        }
      }
      if((Twidth%2)==0){
        for(y=0;y<((Twidth/2)-1);y++){  
          for(x=0;x<Tlenth+1;x++){  
            
            digitalWrite(In1,HIGH);
            digitalWrite(In3,HIGH);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            digitalWrite(pesticide_motor,HIGH);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
          }
          digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            digitalWrite(pesticide_motor,LOW);
            delay(1000);
          digitalWrite(In1,LOW);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,HIGH);
          digitalWrite(In4,LOW);    
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,HIGH);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(T_s);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(250);
          digitalWrite(In1,HIGH);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,HIGH);
          delay(400);
          digitalWrite(In1,LOW);
          digitalWrite(In3,LOW);
          digitalWrite(In2,LOW);
          digitalWrite(In4,LOW);
          delay(1000);
        
      for(x=0;x<Tlenth+1;x++){
       
        digitalWrite(In1,LOW);
        digitalWrite(In3,LOW);
        digitalWrite(In2,HIGH);
        digitalWrite(In4,HIGH);
          digitalWrite(pesticide_motor,HIGH);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);      
      }
      digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            digitalWrite(pesticide_motor,LOW);
      delay(1000);
      digitalWrite(In1,LOW);
      digitalWrite(In3,HIGH);
      digitalWrite(In2,HIGH);
      digitalWrite(In4,LOW); 
      delay(400);
      digitalWrite(In1,LOW);
      digitalWrite(In3,LOW);
      digitalWrite(In2,LOW);
      digitalWrite(In4,LOW);
      delay(250);
      digitalWrite(In1,HIGH);
      digitalWrite(In3,HIGH);
      digitalWrite(In2,LOW);
      digitalWrite(In4,LOW);
      delay(T_s);
      digitalWrite(In1,LOW);
      digitalWrite(In3,LOW);
      digitalWrite(In2,LOW);
      digitalWrite(In4,LOW);
      delay(250);     
      digitalWrite(In1,HIGH);
      digitalWrite(In3,LOW);
      digitalWrite(In2,LOW);
      digitalWrite(In4,HIGH);
      delay(400);
      digitalWrite(In1,LOW);
      digitalWrite(In3,LOW);
      digitalWrite(In2,LOW);
      digitalWrite(In4,LOW);
      delay(1000);    
    }
  }
  for(x=0;x<Tlenth+1;x++){  
     
      digitalWrite(In1,HIGH);
      digitalWrite(In3,HIGH);
      digitalWrite(In2,LOW);
      digitalWrite(In4,LOW);
          digitalWrite(pesticide_motor,HIGH);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
            for(pos=53;pos<117;pos++){
              pesticide.write(pos);
              delay(5);
            }
            for(pos=117; pos>53; pos--){
            pesticide.write(pos);
            delay(5);
            }
            delay((T_p/4)-640);
    }
    digitalWrite(In1,LOW);
            digitalWrite(In3,LOW);
            digitalWrite(In2,LOW);
            digitalWrite(In4,LOW);
            digitalWrite(pesticide_motor,LOW);
      digitalWrite(In1,LOW);
      digitalWrite(In3,LOW);
      digitalWrite(In2,HIGH);
      digitalWrite(In4,HIGH);
      delay((T_p)*(Tlenth));
      digitalWrite(In1,LOW);
      digitalWrite(In3,LOW);
      digitalWrite(In2,LOW);
      digitalWrite(In4,LOW);
    }
    
  }
  if(digitalRead(fertilizer_switch) == LOW && digitalRead(pesticide_switch) == LOW && digitalRead(irrigation_switch) == HIGH && digitalRead(screen_switch)==LOW){
    
  }
  
    
}
