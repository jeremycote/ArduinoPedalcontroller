///////////////////////////////////////////////////////////
//  midi_output.ino                                      //
//  Example: MIDI Output                                 //
//  https://github.com/ddiakopoulos/hiduino              //
//  Last Updated: 17 December 2015                       //
//  Next step is to trigger midi on button press         //
///////////////////////////////////////////////////////////

#include <MIDI.h>

const int buttonPin = 2;
const int ledPin =  13;

const int buttons [5] = {2,3,4,5,6};
const int midiNotes [5] = {48,49,50,51,52};

// int buttonState = 0;
bool buttonPressed = false;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() 
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  // initialize the pushbutton pin as an input:
  pinMode(buttonPin, INPUT);
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() 
{
  // buttonState = digitalRead(buttonPin);
  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:

  buttonPressed = false;
  for (int i = 0; i < ((sizeof buttons) / (sizeof buttons[0])); i++){
    if (digitalRead(buttons[i]) == HIGH){
      MIDI.sendNoteOn(midiNotes[i], 50, 1);
      buttonPressed = true;
    } else {
      MIDI.sendNoteOff(midiNotes[i], 50, 1);
    }
  }

  if (buttonPressed == true) {
    digitalWrite(ledPin, HIGH);
  } else {
    digitalWrite(ledPin, LOW);
  }
  /*
  if (buttonState == HIGH) {
    // turn LED on:
    digitalWrite(ledPin, HIGH);
    MIDI.sendNoteOn(48, 50, 1);     
  } else {
    // turn LED off:
    digitalWrite(ledPin, LOW);
    MIDI.sendNoteOff(48,50,1);
  }
  */
  /*
  for (int i = 0; i < 24; i++) 
  {
    MIDI.sendNoteOn(i, i*2, 1); 
    delay(75); 
    MIDI.sendNoteOff(i,i*2,1);
  }
  */

  // Polling rate
  delay(50); 

}
