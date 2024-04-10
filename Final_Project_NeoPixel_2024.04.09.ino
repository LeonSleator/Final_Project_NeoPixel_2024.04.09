#include <Adafruit_NeoPixel.h>

int ledPin1 = 25;
int ledPin2 = 26;
int ledPin3 = 27;
int notes[7] = { 60, 61, 62, 63, 64, 65, 66 };
int numPixels = 8;
int pixelPin = 33;

// unsigned long lastStepTime = 0;
// int stepLength = 10;
// int currentStep = 0;
int velocityMapped;
int delayTime;


Adafruit_NeoPixel neopixel = Adafruit_NeoPixel(numPixels, pixelPin, NEO_GRB);

void OnNoteOn(byte channel, byte note, byte velocity) {
  velocityMapped = map(velocity, 0, 127, 0, 255);
  //Serial.println(velocity);
  for (int i = 0; i < 8; i++) {
    if (note == notes[0]) {
      neopixel.setPixelColor(i, velocityMapped, 0, 0);  //C3 = red
    } else if (note == notes[1]) {
      neopixel.setPixelColor(i, velocityMapped / 2, velocityMapped / 2, 0);  //C#3 = yellow
    } else if (note == notes[2]) {
      neopixel.setPixelColor(i, 0, velocityMapped, 0);  //D3 = green
    } else if (note == notes[3]) {
      neopixel.setPixelColor(i, 0, velocityMapped / 2, velocityMapped / 2);  //D#3 = cyan
    } else if (note == notes[4]) {
      neopixel.setPixelColor(i, 0, 0, velocityMapped);  //E3 = blue
    } else if (note == notes[5]) {
      neopixel.setPixelColor(i, velocityMapped / 2, 0, velocityMapped / 2);  //F3 = purple
    } else if (note == notes[6]) {
      neopixel.setPixelColor(i, velocityMapped / 2, velocityMapped / 2, velocityMapped / 2);  //F#3 = white
    }
    neopixel.show();
  }
}
void OnNoteOff(byte channel, byte note, byte velocity) {
  velocityMapped = map(velocity, 0, 127, 0, 255);
  if (note == 60) {
    for (int j = velocityMapped; j >= 0; j--) {
      for (int i = 0; i < 8; i++) {
        neopixel.setPixelColor(i, j, 0, 0);
      }
      neopixel.show();
      delay(delayTime);
    }
  }
  // neopixel.clear();
}

void myControlChange(byte channel, byte control, byte value) {
  delayTime = map(value, 0, 127, 1, 14);
  Serial.println(delayTime);
}

void setup() {
  Serial.begin(9600);
  neopixel.begin();
  pinMode(ledPin1, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  pinMode(ledPin3, OUTPUT);
  usbMIDI.setHandleNoteOff(OnNoteOff);
  usbMIDI.setHandleNoteOn(OnNoteOn);
  usbMIDI.setHandleControlChange(myControlChange);
}

void loop() {
  usbMIDI.read();
  // if(millis() > lastStepTime + stepLength)
  // {
  //   lastStepTime = millis();
  //   currentStep = currentStep +1;
  //   Serial.println(currentStep);
  // }
}

// void noteOffFunction(int noteVal){
//   if (note == noteVal) {
//     for (int j = velocityMapped; j >= 0; j--) {
//       for (int i = 0; i < 8; i++) {
//         neopixel.setPixelColor(i, j, 0, 0);
//       }
//       neopixel.show();
//       delay(10);
//     }
//   }
// }
