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
    if(estadoDect==LOW){ //Deteccion primera palmada
      Serial.println("A");
      tiempo=millis();
      estadoDect=HIGH;
    }else{ //Deteccion segunda palmada
      long tiempo_trans = millis()-tiempo;
      if(tiempo_trans>200 && tiempo_trans<420){ //Comprobacion de tiempo entre palmadas
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
  if(estadoDect==HIGH){ //Volver al estado inicial si solo se ha detectado 1 palmada
    long tiempo_trans = millis()-tiempo;
    if(tiempo_trans>450){
      estadoDect=LOW;
    }
  }
    
  digitalWrite(13,estadoOut);
  digitalWrite(pinRelay,estadoOut);
}
