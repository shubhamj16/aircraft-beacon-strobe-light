// Strobe settings
#define STB_PIN_LIGHT 3 // Pin number for strobe light output   // ------------------------------------------------------------------------Eric Note WORKS!
#define STB_PIN_LIGHTB 4 // Pin number for strobe light output
#define STB_BLINK_INTERVAL 2000000 // Blink interval for strobe light in microseconds

// Anti-collision beacon settings
#define ACB1_PIN_LIGHT 0 // Pin number for anti-collision beacon 1  //------------------------------------------------------------ Eric Note on Digispark 1 is internal LED 
#define ACB2_PIN_LIGHT 1 // Pin number for anti-collision beacon 2
#define ACB_FADE_MIN 0 // Minimum fade level for beacon (0-255)
#define ACB_FADE_MAX 255 // Maximum fade level for beacon (0-255)
#define ACB_FADE_INTERVAL 4000 // Fade step interval, in microseconds (lower numbers = faster fade)

unsigned long lastFadeTime = 0;
unsigned long lastStrobeTime = 0;
int currentFade = ACB_FADE_MIN;
int fadeDirection = 1;

void setup()
{
  // Declare output pins
  pinMode(STB_PIN_LIGHT, OUTPUT);
  pinMode(STB_PIN_LIGHTB, OUTPUT);
  pinMode(ACB1_PIN_LIGHT, OUTPUT);
  pinMode(ACB2_PIN_LIGHT, OUTPUT);
  
  
}

void loop()
{
  unsigned long currentTime = micros();
  // Check if it's time to fade the anti-collision lights
  if ((currentTime - lastFadeTime) > ACB_FADE_INTERVAL) {
    doFade();
    lastFadeTime = currentTime;
  }

  // Check if it's time to blink the strobes
  if ((currentTime - lastStrobeTime) > STB_BLINK_INTERVAL) {
    doStrobe();
    lastStrobeTime = currentTime; 
  }
}

// Fade anti-collision LEDs
void doFade()
{
  currentFade += fadeDirection;
  if (currentFade == ACB_FADE_MAX || currentFade == ACB_FADE_MIN) {
    // If we hit the fade limit, flash the high beacon, and flip the fade direction
    if (fadeDirection == 1) {
      analogWrite(ACB1_PIN_LIGHT, 255);

    } else {
      analogWrite(ACB2_PIN_LIGHT, 255);
    }
    delay(50); 
    fadeDirection *= -1; 
  }

  analogWrite(ACB1_PIN_LIGHT, currentFade);
  analogWrite(ACB2_PIN_LIGHT, ACB_FADE_MAX - currentFade + ACB_FADE_MIN);
}

// Strobe double-blink
void doStrobe()
{
  digitalWrite(STB_PIN_LIGHT, HIGH);
  digitalWrite(STB_PIN_LIGHTB, HIGH);
  delay(50);
  digitalWrite(STB_PIN_LIGHT, LOW);
  digitalWrite(STB_PIN_LIGHTB, LOW);
  delay(50);
  digitalWrite(STB_PIN_LIGHT, HIGH);
  digitalWrite(STB_PIN_LIGHTB, HIGH);
  delay(50);
  digitalWrite(STB_PIN_LIGHT, LOW);
  digitalWrite(STB_PIN_LIGHTB, LOW);
}
