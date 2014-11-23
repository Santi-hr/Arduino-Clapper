//Santiago Hernandez Roman 2014
const int pinMic = 4;
const int pinRelay = 7;
int estadoDect = LOW;
int estadoOut = LOW;

long tiempo;

void setup(){
  pinMode(pinMic,INPUT);
  pinMode(13,OUTPUT);
  pinMode(pinRelay,OUTPUT);  
  Serial.begin(9600);
}

void loop(){
    
  if(digitalRead(pinMic)){
    delay(100); //Filtro para el ruido
    if(estadoDect==LOW){
      Serial.println("A");
      tiempo=millis();
      estadoDect=HIGH;
    }else{
      long tiempo_trans = millis()-tiempo;
      if(tiempo_trans>200 && tiempo_trans<420){
        if(estadoOut){
          estadoOut=LOW;
        }else{
          estadoOut=HIGH;
        }
      }
      Serial.println(tiempo_trans);
      estadoDect=LOW;
    }
  }
  if(estadoDect==HIGH){
    long tiempo_trans = millis()-tiempo;
    if(tiempo_trans>350){
      estadoDect=LOW;
    }
  }
    
  digitalWrite(13,estadoOut);
  digitalWrite(pinRelay,estadoOut);
}
