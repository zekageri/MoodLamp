#ifndef ADXL_h
#define ADXL_h

#define GYROSINFODISPLAYTIME 1000
#define GYROSEVENTTIME 5
#define POKE_TRESHOLD 3
#define POKE_UPTIME 15
int animPokeCounter = 0;
boolean X_Poke_Started = false,Y_Poke_Started = false,Try_ADXL_Once = false;
long xPokeStartTime = 0,yPokeStartTime = 0,gyrosInfoDisplayLastTime = 0,gyrosCopeLastEventTime = 0;
sensors_event_t event;

static const inline void adxl_Setup(){
  if(!accel.begin()){
    Serial.println("Ooops, no ADXL345 detected ...");
    is_ADXL = false;
    if(!Try_ADXL_Once){
      Try_ADXL_Once = true;
      delay(400);
      adxl_Setup();
    }
  }else{
    Serial.println("ADXL Success!");
    is_ADXL = true;
  }
  if(is_ADXL){
    accel.setRange(ADXL345_RANGE_16_G);
  }
}

static const inline void Display_Gyros_Info(){
  if(millis() - gyrosInfoDisplayLastTime >= GYROSINFODISPLAYTIME){
    gyrosInfoDisplayLastTime = millis();
    Serial.print("X: "); Serial.print(event.acceleration.x); Serial.print(" ");
    Serial.print("Y: "); Serial.print(event.acceleration.y); Serial.print(" ");
    Serial.print("Z: "); Serial.print(event.acceleration.z); Serial.print(" ");
    Serial.println("m/s^2 ");
  }
}

static const inline void handle_X_POKE(int x){
  if(!X_Poke_Started){
    if(x >= POKE_TRESHOLD || x <= -POKE_TRESHOLD){
      X_Poke_Started = true;
      xPokeStartTime = millis();
    }
  }
  if(X_Poke_Started){
    if( (x < POKE_TRESHOLD) && (x > -POKE_TRESHOLD) ){
      if( (millis() - xPokeStartTime) <= POKE_UPTIME){
        if(animPokeCounter < 13){animPokeCounter++;}else{animPokeCounter = 0;}
        Get_Animation(animPokeCounter);
      }
      X_Poke_Started = false;
    }
  }
}

static const inline void handle_Y_POKE(int y){
if(!Y_Poke_Started){
    if(y >= POKE_TRESHOLD || y <= -POKE_TRESHOLD){
      Y_Poke_Started = true;
      yPokeStartTime = millis();
    }
  }
  if(Y_Poke_Started){
    if( (y < POKE_TRESHOLD) && (y > -POKE_TRESHOLD) ){
      if( (millis() - yPokeStartTime) <= POKE_UPTIME){
        if(animPokeCounter > 0){animPokeCounter--;}else{animPokeCounter = 13;}
        Get_Animation(animPokeCounter);
      }
      Y_Poke_Started = false;
    }
  }
}

static const inline void Process_Gyros_Event(){
  if(millis() - gyrosCopeLastEventTime >= GYROSEVENTTIME){
    gyrosCopeLastEventTime = millis();
    accel.getEvent(&event);
    handle_X_POKE(event.acceleration.x);
    handle_Y_POKE(event.acceleration.y);
  }
}

static const inline void adxl_Loop(){
  if(is_ADXL){
    Process_Gyros_Event();
  }
}

#endif