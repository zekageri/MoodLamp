#ifndef Animations_h
#define Animations_h

int ANIMATION = -1;
uint16_t currentBrightness = 50;

#define LED_PIN     27
#define NUM_LEDS    76
#define CHIPSET     WS2812
#define COLOR_ORDER GRB //GBR //RBG //RGB //BRG //BGR
CRGB leds[NUM_LEDS];
/**  TEMPERATURE CHANGE DEFINES **/
#define BRIGHTNESS  128
#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky
#define DISPLAYTIME 50
#define BLACKTIME   3
/** TEMPERATURE CHANGE DEFINES **/

/** FIRE ANIMATION DEFINES **/
#define FRAMES_PER_SECOND 60
bool gReverseDirection = false;
CRGBPalette16 gPal;
#define COOLING  20 // Default 55, suggested range 20-100 
#define SPARKING 55 // Default 120, suggested range 50-200.
#define BASIC_COOLING  70
#define BASIC_SPARKING 55
/** FIRE ANIMATION DEFINES **/

/** NEW ANIMATION DECLARATIONS **/
boolean power = false;
uint8_t autoplay = 0;
uint8_t autoplayDuration = 10;
unsigned long autoPlayTimeout = 0;
CRGB solidColor = CRGB::Blue;
uint8_t cooling = 50;
uint8_t sparking = 120;
uint8_t currentPatternIndex = 0;
uint8_t gHue = 0;
uint8_t speed = 30;
uint8_t currentPaletteIndex = 0;
#define ARRAY_SIZE(A) (sizeof(A) / sizeof((A)[0]))
boolean Can_Set_Static = false;
int Web_R= 0, Web_G= 0, Web_B = 0;
#include <Headers/palettes.h>
#include <Headers/twinkleFox.h>

void Led_Setup(){
  vTaskDelay(100);
  pinMode(LED_PIN, OUTPUT);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  power = false;
}

void Null_Animations(){
  ANIMATION = -1;
}

void Set_Static_From_Web(){
  if(Can_Set_Static){
    fill_solid(leds, NUM_LEDS, CRGB::Black);
    FastLED.show();
    Can_Set_Static = false;
    Null_Animations();
    for(int i = 0; i < NUM_LEDS;i++){
      leds[i] = CRGB( Web_R, Web_G, Web_B);
      FastLED.show();
      vTaskDelay(15);
    }
  }
}

void Fire2012WithPalette(){
  static byte heat[NUM_LEDS];
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((COOLING * 10) / NUM_LEDS) + 2));
    }
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < NUM_LEDS; j++) {
      byte colorindex = scale8( heat[j], 240);
      CRGB color = ColorFromPalette( gPal, colorindex);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}

void Basic_Fire(){
  static byte heat[NUM_LEDS];
    for( int i = 0; i < NUM_LEDS; i++) {
      heat[i] = qsub8( heat[i],  random8(0, ((BASIC_COOLING * 10) / NUM_LEDS) + 2));
    }
    for( int k= NUM_LEDS - 1; k >= 2; k--) {
      heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
    }
    if( random8() < BASIC_SPARKING ) {
      int y = random8(7);
      heat[y] = qadd8( heat[y], random8(160,255) );
    }
    for( int j = 0; j < NUM_LEDS; j++) {
      CRGB color = HeatColor( heat[j]);
      int pixelnumber;
      if( gReverseDirection ) {
        pixelnumber = (NUM_LEDS-1) - j;
      } else {
        pixelnumber = j;
      }
      leds[pixelnumber] = color;
    }
}

void Fire_Loop(){
  random16_add_entropy( esp_random());
  Fire2012WithPalette();
}

void colorwaves( CRGB* ledarray, uint16_t numleds, CRGBPalette16& palette)
{
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;

  // uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);

  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 300, 1500);

  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;

  for ( uint16_t i = 0 ; i < numleds; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    uint16_t h16_128 = hue16 >> 7;
    if ( h16_128 & 0x100) {
      hue8 = 255 - (h16_128 >> 1);
    } else {
      hue8 = h16_128 >> 1;
    }

    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;

    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);

    uint8_t index = hue8;
    //index = triwave8( index);
    index = scale8( index, 240);

    CRGB newcolor = ColorFromPalette( palette, index, bri8);

    uint16_t pixelnumber = i;
    pixelnumber = (numleds - 1) - pixelnumber;

    nblend( ledarray[pixelnumber], newcolor, 128);
  }
}

void colorWaves(){ // we have to investigate the palettes!! palettes[]
  colorwaves(leds, NUM_LEDS, currentPalette);
}

void pride(){
  static uint16_t sPseudotime = 0;
  static uint16_t sLastMillis = 0;
  static uint16_t sHue16 = 0;
  uint8_t sat8 = beatsin88( 87, 220, 250);
  uint8_t brightdepth = beatsin88( 341, 96, 224);
  uint16_t brightnessthetainc16 = beatsin88( 203, (25 * 256), (40 * 256));
  uint8_t msmultiplier = beatsin88(147, 23, 60);
  uint16_t hue16 = sHue16;//gHue * 256;
  uint16_t hueinc16 = beatsin88(113, 1, 3000);
  uint16_t ms = millis();
  uint16_t deltams = ms - sLastMillis ;
  sLastMillis  = ms;
  sPseudotime += deltams * msmultiplier;
  sHue16 += deltams * beatsin88( 400, 5, 9);
  uint16_t brightnesstheta16 = sPseudotime;
  for ( uint16_t i = 0 ; i < NUM_LEDS; i++) {
    hue16 += hueinc16;
    uint8_t hue8 = hue16 / 256;
    brightnesstheta16  += brightnessthetainc16;
    uint16_t b16 = sin16( brightnesstheta16  ) + 32768;
    uint16_t bri16 = (uint32_t)((uint32_t)b16 * (uint32_t)b16) / 65536;
    uint8_t bri8 = (uint32_t)(((uint32_t)bri16) * brightdepth) / 65536;
    bri8 += (255 - brightdepth);
    CRGB newcolor = CHSV( hue8, sat8, bri8);
    uint16_t pixelnumber = i;
    pixelnumber = (NUM_LEDS - 1) - pixelnumber;
    nblend( leds[pixelnumber], newcolor, 64);
  }
}

void rainbow(){
  fill_rainbow( leds, NUM_LEDS, gHue, speed);
}

void addGlitter( fract8 chanceOfGlitter){
  if ( random8() < chanceOfGlitter) {
    leds[ random16(NUM_LEDS) ] += CRGB::White;
  }
}

void rainbowWithGlitter(){
  rainbow();
  addGlitter(80);
}

void confetti(){
  fadeToBlackBy( leds, NUM_LEDS, 10);
  int pos = random16(NUM_LEDS);
  leds[pos] += CHSV( gHue + random8(64), 200, 255);
}


void sinelon(){
  fadeToBlackBy( leds, NUM_LEDS, 20);
  int pos = beatsin16(speed, 0, NUM_LEDS - 1);
  static int prevpos = 0;
  CRGB color = ColorFromPalette(palettes[currentPaletteIndex], gHue, 255);
  if ( pos < prevpos ) {
    fill_solid( leds + pos, (prevpos - pos) + 1, color);
  } else {
    fill_solid( leds + prevpos, (pos - prevpos) + 1, color);
  }
  prevpos = pos;
}

void bpm(){
  uint8_t beat = beatsin8( speed, 64, 255);
  CRGBPalette16 palette = palettes[currentPaletteIndex];
  for ( int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(palette, gHue + (i * 2), beat - gHue + (i * 10));
  }
}

void Temperature_Loop(){
  static uint8_t starthue = 0;
  fill_rainbow( leds, NUM_LEDS, --starthue, 20);
  uint8_t secs = (millis() / 1000) % (DISPLAYTIME * 2);
  if( secs < DISPLAYTIME) {
    FastLED.setTemperature( TEMPERATURE_1 );
    leds[0] = TEMPERATURE_1;
  } else {
    FastLED.setTemperature( TEMPERATURE_2 );
    leds[0] = TEMPERATURE_2;
  }
  if( (secs % DISPLAYTIME) < BLACKTIME) {
    memset8( leds, 0, NUM_LEDS * sizeof(CRGB));
  }
}

void juggle() {
  fadeToBlackBy( leds, NUM_LEDS, 20);
  byte dothue = 0;
  for ( int i = 0; i < 8; i++) {
    leds[beatsin16( i + speed, 0, NUM_LEDS - 1 )] |= CHSV(dothue, 200, 255);
    dothue += 32;
  }
}

void showSolidColor(){
  fill_solid(leds, NUM_LEDS, solidColor);
}


void heatMap(CRGBPalette16 palette, bool up){
  fill_solid(leds, NUM_LEDS, CRGB::Black);
  random16_add_entropy(random(256));
  static byte heat[NUM_LEDS];
  byte colorindex;
  for ( uint16_t i = 0; i < NUM_LEDS; i++) {
    heat[i] = qsub8( heat[i],  random8(0, ((cooling * 10) / NUM_LEDS) + 2));
  }
  for ( uint16_t k = NUM_LEDS - 1; k >= 2; k--) {
    heat[k] = (heat[k - 1] + heat[k - 2] + heat[k - 2] ) / 3;
  }
  if ( random8() < sparking ) {
    int y = random8(7);
    heat[y] = qadd8( heat[y], random8(160, 255) );
  }
  for ( uint16_t j = 0; j < NUM_LEDS; j++) {
    colorindex = scale8(heat[j], 190);
    CRGB color = ColorFromPalette(palette, colorindex);
    if (up) {
      leds[j] = color;
    }
    else {
      leds[(NUM_LEDS - 1) - j] = color;
    }
  }
}

void fire(){
  heatMap(HeatColors_p, false);
}
void water(){
  heatMap(IceColors_p, true);
}
void PartyHeatMap(){
  heatMap(PartyColors_p, false);
}
void ForestHeatMap(){
  heatMap(ForestColors_p, false);
}
void LavaHeatMap(){
  heatMap(LavaColors_p, false);
}
void CloudHeatMap(){
  heatMap(CloudColors_p, false);
}
void OceanHeatMap(){
  heatMap(OceanColors_p, false);
}
void RainbowStripeHeatMap(){
  heatMap(RainbowStripeColors_p, false);
}
void FairyHeatMap(){
  heatMap(FairyLight_p, false);
}
void HolyHeatMap(){
  heatMap(Holly_p, false);
}
void RetroC9_pHeatMap(){
  heatMap(RetroC9_p, false);
}
void TestAnim(){
  CRGB color1 = CRGB( 252, 186, 3 );
  CRGB color2 = CRGB( 252, 3, 177 );
  fill_gradient_RGB(leds,NUM_LEDS,color1,color2);
}

  static const inline void Get_Animation(int ANIM){
    Null_Animations();
    ANIMATION = ANIM;
    //bitSet(ANIMATION,ANIM);
    power = true;
    Can_Set_Static = false;
    Serial.print("Starting Animation: ");
    Serial.println(ANIM);
    Save_Current_Animation(ANIM);
  }

  void Animation( void * parameter ){
    Led_Setup();
    int lastAnim = Get_Current_Animation();
    if(lastAnim != -1){Get_Animation(lastAnim);}
    for ever{
      if ( !power ) {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
        vTaskDelay(100);
      }else {
        Set_Static_From_Web();
        if(ANIMATION == 0){
          Temperature_Loop();
        }else if( ANIMATION == 1 ){
          Fire_Loop();
        }else if( ANIMATION == 2 ){
          PartyHeatMap();
        }else if(ANIMATION == 3){
          confetti();
        }else if(ANIMATION == 4){
          rainbow();
        }else if(ANIMATION == 5){
          rainbowWithGlitter();
        }else if(ANIMATION == 6){
          juggle();
        }else if(ANIMATION == 7){
          water();
        }else if(ANIMATION == 8){
          fire();
        }else if(ANIMATION == 9){
          pride();
        }else if(ANIMATION == 10){
          sinelon();
        }else if(ANIMATION == 11){
          bpm();
        }else if(ANIMATION == 12){
          ForestHeatMap();
        }else if(ANIMATION == 13){
          LavaHeatMap();
        }else if(ANIMATION == 14){
          CloudHeatMap();
        }else if(ANIMATION == 15){
          OceanHeatMap();
        }else if(ANIMATION == 16){
          RainbowStripeHeatMap();
        }else if(ANIMATION == 17){
          FairyHeatMap();
        }else if(ANIMATION == 18){
          HolyHeatMap();
        }else if(ANIMATION == 19){
          RetroC9_pHeatMap();
        }else if(ANIMATION == 20){
          TestAnim();
        }
        FastLED.show();
        FastLED.setBrightness(currentBrightness);
        vTaskDelay(1000 / FRAMES_PER_SECOND);
      }
    }
  }

#endif