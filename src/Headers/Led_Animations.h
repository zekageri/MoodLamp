#ifndef Animations_h
#define Animations_h

#define AnimationDelay1 100
#define AnimationDelay2 250

void Animation1(){
  for(int i=0;i<NUM;i++){
    pixels.setPixelColor(i, pixels.Color(255,0,0));
    pixels.show();
    vTaskDelay(AnimationDelay1);
  }
  for(int i=NUM;i>=0;i--){
    pixels.setPixelColor(i, pixels.Color(0,255,0));
    pixels.show();
    vTaskDelay(AnimationDelay1);
  }
  for(int i=0;i<NUM;i++){
    pixels.setPixelColor(i, pixels.Color(0,255,255));
    pixels.show();
    vTaskDelay(AnimationDelay1);
  }
  for(int i=NUM;i>=0;i--){
    pixels.setPixelColor(i, pixels.Color(255,255,0));
    pixels.show();
    vTaskDelay(AnimationDelay1);
  }
}

void Animation2(){
    for(int i=0;i<NUM;i++){
    pixels.setPixelColor(i, pixels.Color(255,0,0));
    pixels.show();
    vTaskDelay(AnimationDelay2);
  }

  for(int i=0;i<NUM;i++){
    pixels.setPixelColor(i, pixels.Color(0,255,0));
    pixels.show();
    vTaskDelay(AnimationDelay2);
  }

  for(int i=0;i<NUM;i++){
    pixels.setPixelColor(i, pixels.Color(0,0,255));
    pixels.show();
    vTaskDelay(AnimationDelay2);
  }
}
#endif