# MicroMelody 🎵

MicroMelody is an Arduino-based MIDI keyboard and MP3 playback station that we created for the module computer architecture at the university of Basel.

## Features
- **MIDI Keyboard** (Arduino Leonardo)  
  - 7 keys mapped to a major scale  
  - USB-MIDI integration with DAW (tested with FL Studio)  
  - 3 potentiometers for effects (e.g., volume, distortion)  

- **MP3 Playback Station** (Arduino Uno)  
  - Mini MP3 player with SD card storage  
  - LCD display showing song titles  
  - Buttons for play/pause and track switching  

## Hardware
- Arduino Leonardo (MIDI keyboard)  
- Arduino Uno (MP3 player)  
- Buttons, potentiometers, LCD display, mini MP3 module  
- Speaker and SD card for playback  

## Libraries Used
- `MIDIUSB`
- `DFRobotDFPlayerMini`
- `LiquidCrystal_I2C`
- `Control_Surface.h` ([GitHub](https://github.com/tttapa/Control-Surface))  

## How to Use
1. Upload the MIDI code to Arduino Leonardo and connect it to a DAW.  
2. Upload the MP3 playback code to Arduino Uno with an SD card containing songs.
3. Assemble the hardware (based on the documentation)
4. Use the keyboard for live music creation and playback system for background tracks.  

## Authors  
**Dion Ibra, Elton Zijadin Malici, Manuel Buser**  
University of Basel – Computer Architecture (2025)
