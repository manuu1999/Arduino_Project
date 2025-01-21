#include <Control_Surface.h>

// MIDI-Interface
USBMIDI_Interface midi;

// Klaviatur-Tasten (Knöpfe)
// MIDI note numbers from low to high
NoteButton button1 {2, {48, CHANNEL_1}};  
NoteButton button2 {3, {50, CHANNEL_1}};  
NoteButton button3 {4, {51, CHANNEL_1}};  
NoteButton button4 {5, {52, CHANNEL_1}};  
NoteButton button5 {6, {53, CHANNEL_1}};  
NoteButton button6 {7, {54, CHANNEL_1}};  
NoteButton button7 {8, {55, CHANNEL_1}};  

// Potentiometer
CCPotentiometer volumePot {A0, MIDI_CC::Channel_Volume};        
CCPotentiometer synthPot1 {A1, MIDI_CC::Modulation_Wheel};      
CCPotentiometer synthPot2 {A2, MIDI_CC::Expression_Controller}; 

void setup() {
  Control_Surface.begin(); // Control Surface initialisieren
}

void loop() {
  Control_Surface.loop(); // Control Surface ausführen
}
