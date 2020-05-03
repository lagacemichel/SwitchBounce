/*
  Switch Bounce sketch
  Uses four LEDs connected to digital I/O pins 8, 9, 10, and 11 to demonstrate
  the effect of a mechanical switch's bounce by lighting the LEDs in sequence
  everytime the switch's input goes from high to low.

  MIT License

  Copyright (c) 2020, Michel Lagace

  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in all
  copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
  SOFTWARE.
*/

// Switch value will be read from pin 12
#define INPORT 12
static bool switchState = HIGH; // State of the switch

// LED values will be output on pins 8, 9, 10, and 11
#define LED0 11
#define LED1 10
#define LED2 9
#define LED3 8
static unsigned int litLED = 0; // Currently lit LED

// Setup the board.
void setup() {
  // Set Arduino<s input and output ports
  pinMode(INPORT, INPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);

  // Initialize switch state and currently lit LED
  switchState = HIGH;
  litLED = 0;
  digitalWrite(LED0, HIGH);
  digitalWrite(LED1, LOW);
  digitalWrite(LED2, LOW);
  digitalWrite(LED3, LOW);
}

// Wait for an edge and return state
bool waitForEdge() {
  bool newValue = switchState;
  while (newValue == switchState) {
    newValue = digitalRead(INPORT);
  }
  switchState = newValue;
  return newValue;
}

// Repeat forever
void loop() {
  // Wait for a rising or falling edge
  bool value = waitForEdge();

  // Increase output on dropping edge (input is LOW when button is pressed)
  if (!value) {
    litLED++;
    if (litLED > 3) {
      litLED = 0;
    }

    // Light up the appropriate LED
    digitalWrite(LED0, litLED == 0);
    digitalWrite(LED1, litLED == 1);
    digitalWrite(LED2, litLED == 2);
    digitalWrite(LED3, litLED == 3);
  }
}
