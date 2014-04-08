//Alanna Predko, 2439008

const int speaker = 2;
const int eyeLeft = 11;
const int eyeRight = 12;
const int numTentacles = 8;

// the pins that each tentacle reads from
int tentaclePins[] = {
  3,4,5,6,7,8,9,10};

// the note (in Hz) to play when a tentacle is pressed
int tentacleNotes[] = {
  1046,1175,1319,1397,1568,1760,1976,2093};

// timings for the blink animation
int timeBlinkIgnore = 5;
int timeBlinkOpen = 100;
int timeBlinkClosed = 45;

// the current step of the blink animation we are on
int blinkStep = 0;

void setup() {
  Serial.begin(9600);
  // setup speaker to be output
  pinMode(speaker, OUTPUT);   

  // setup eyes to be output
  pinMode(eyeLeft, OUTPUT);
  pinMode(eyeRight, OUTPUT);

  // setup each tentacle to be an input
  for (int i = 0; i < numTentacles; i++) {
    pinMode(tentaclePins[i], INPUT);
  }
}

void loop(){
  // if any of the tentacles were pressed
  boolean tentaclePressed = false;
  int tentacleState = 0;

  for (int i = 0; i < numTentacles; i++) {
    // read the state of each tentacle
    tentacleState = digitalRead(tentaclePins[i]);
    Serial.print(tentacleState);
    Serial.print(", ");
    // if this tentacle is on play its note
    if (tentacleState == HIGH) {
      tentaclePressed = true;
      tone(speaker, tentacleNotes[i]);
      
      // found a tentacle that was one, stop checking other tentacles
      break;
    }
  }
  Serial.println();

  if (tentaclePressed) {
    blinkPattern();
  } 
  else {
    // stop playing a tone
    noTone(speaker);

    // open the eyes and reset the blink pattern
    eyesOpen();
    blinkStep = 0;
  }
}

// do one step of the blink pattern.
void blinkPattern() {
  if (blinkStep < timeBlinkIgnore) {
    // Ignore the first few milliseconds the button is pressed as a lazy way 
    // to do debounce. Without this sometimes the LED flickers.
  } 
  else if (blinkStep < timeBlinkOpen) {
    eyesClosed();
  } 
  else if (blinkStep < (timeBlinkOpen + timeBlinkClosed)) {
    eyesOpen(); 
  } 
  else {
    // start the blink animation from the beginning
    blinkStep = 0;
  }

  // go to the next step of the blink
  blinkStep++;
}

// open the eyes
void eyesOpen() {
  digitalWrite(eyeLeft, HIGH);
  digitalWrite(eyeRight, HIGH);
}

// close the eyes
void eyesClosed() {
  digitalWrite(eyeLeft, LOW);
  digitalWrite(eyeRight, LOW);
}
