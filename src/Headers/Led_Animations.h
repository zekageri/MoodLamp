#ifndef Animations_h
#define Animations_h


#define LED_PIN     18
#define NUM_LEDS    16
#define CHIPSET     WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];
/**  TEMPERATURE CHANGE DEFINES **/
#define BRIGHTNESS  128
#define TEMPERATURE_1 Tungsten100W
#define TEMPERATURE_2 OvercastSky
#define DISPLAYTIME 50
#define BLACKTIME   3
/** TEMPERATURE CHANGE DEFINES **/

/** FIRE ANIMATION DEFINES **/
#define FIRE_BRIGHTNESS  100
#define FRAMES_PER_SECOND 40
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

#include <Headers/palettes.h>
#include <Headers/twinkleFox.h>

void Led_Setup(){
  vTaskDelay(1000);
  FastLED.addLeds<CHIPSET, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalSMD5050 );
  FastLED.setBrightness( BRIGHTNESS );
  if(ANIMATION->FIRE || ANIMATION->BASIC_FIRE){
    FastLED.setBrightness( FIRE_BRIGHTNESS );
    gPal = HeatColors_p;
  }
  power = false;
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

void Basic_Fire_Loop(){
  Basic_Fire();
  FastLED.show();
  //FastLED.delay(1000 / FRAMES_PER_SECOND);
}

void Fire_Loop(){
  random16_add_entropy( esp_random());
  Fire2012WithPalette();
  FastLED.show();
  //FastLED.delay(1000 / FRAMES_PER_SECOND);
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

void colorWaves(){
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
  heatMap(HeatColors_p, true);
}

void water(){
  heatMap(IceColors_p, false);
}
/*
void nextPattern(){
  currentPatternIndex = (currentPatternIndex + 1) % patternCount;
}

void nextPalette(){
  currentPaletteIndex = (currentPaletteIndex + 1) % paletteCount;
  targetPalette = palettes[currentPaletteIndex];
}*/

  boolean OnceTurnOff = true;
  void Animation( void * parameter ){
    Led_Setup();
    for ever{
      if ( !power) {
        fill_solid(leds, NUM_LEDS, CRGB::Black);
        FastLED.show();
      }else {
        if(ANIMATION->TYPES[0]){
          Temperature_Loop();
        }else if(ANIMATION->TYPES[1]){
          Fire_Loop();
        }else if(ANIMATION->TYPES[2]){
          Basic_Fire_Loop();
        }else if(STATIC->TYPES[0]){
          showSolidColor();
        }else if(ANIMATION->TYPES[3]){
          confetti();
        }else if(ANIMATION->TYPES[4]){
          rainbow();
        }else if(ANIMATION->TYPES[5]){
          rainbowWithGlitter();
        }else if(ANIMATION->TYPES[6]){
          juggle();
        }else if(ANIMATION->TYPES[7]){
          water();
        }else if(ANIMATION->TYPES[8]){
          fire();
        }else if(ANIMATION->TYPES[9]){
          pride();
        }else if(ANIMATION->TYPES[10]){
          sinelon();
        }else if(ANIMATION->TYPES[11]){
          bpm();
        }
        FastLED.show();
        vTaskDelay(1000 / FRAMES_PER_SECOND);
      }
    }
  }

#endif