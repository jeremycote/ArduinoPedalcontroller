///////////////////////////////////////////////////////////
//  midi_output.ino                                      //
//  Example: MIDI Output                                 //
//  https://github.com/ddiakopoulos/hiduino              //
//  Last Updated: 17 December 2015                       //
//  Next step is to trigger midi on button press         //
///////////////////////////////////////////////////////////

#include <MIDI.h>

const int ledPin =  13;

//Buttons, and ButtonsPressed must be same size!
const int buttons [8] = {2, 3, 4, 5, 6, 7, 8, 9};
bool buttonPressed [8] = {false, false, false, false, false, false, false, false};
bool shouldLight = false;
const int nButtons = 8;

MIDI_CREATE_DEFAULT_INSTANCE();

void setup() 
{
  // initialize the LED pin as an output:
  pinMode(ledPin, OUTPUT);
  
  // initialize the pushbutton pins as an inputs:
  for (int i = 0; i < nButtons; i++){
    pinMode(buttons[i], INPUT_PULLUP);
  }
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
}

void loop() 
{
  for (int i = 0; i < nButtons; i++){
    if (digitalRead(buttons[i]) == LOW){
      if (buttonPressed[i] != true) {
        //Not pressed, do action
        MIDI.sendProgramChange(i,1);
        buttonPressed[i] = true;
      }
    } else if (buttonPressed[i] == true) {
      buttonPressed[i] = false;
    }
  }

  shouldLight = false;
  for (int i = 0; i < nButtons; i++){
    if (buttonPressed[i] == true) {
      shouldLight = true;
    }
  }
  
  if (shouldLight == true) {
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
  delay(20); 

}
