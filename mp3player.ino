#include "mp3tf16p.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Define Button Pins
const int playPauseButton = 2; // Button for Play/Pause (must be an interrupt pin)
const int nextSongButton = 3;  // Button for Next Song (must be an interrupt pin)

// MP3 Player Instance
MP3Player mp3(10, 11);

// LCD Instance
LiquidCrystal_I2C lcd(0x27, 16, 2); // Adjust I2C address (0x27 is common)

// Flags for button presses
volatile bool playPauseFlag = false;
volatile bool nextSongFlag = false;

// State Variables
bool isPlaying = false;        // Playback state
int currentTrack = 1;          // Current track number
const int totalTracks = 6;     // Total number of tracks (hardcoded)

// Song Names
const char* songNames[] = {
  "Track 1: Epic Theme",
  "Track 2: Sax House",
  "Track 3: Ambient Space",
  "Track 4: Techno 101",
  "Track 5: Classical",
  "Track 6: Jazz Composition"
};

void setup() {
  // Initialize Serial Monitor
  Serial.begin(9600);
  Serial.println("MP3 Player with Button Control");

  // Initialize Button Pins
  pinMode(playPauseButton, INPUT_PULLUP);
  pinMode(nextSongButton, INPUT_PULLUP);

  // Attach Interrupts
  attachInterrupt(digitalPinToInterrupt(playPauseButton), playPauseISR, FALLING);
  attachInterrupt(digitalPinToInterrupt(nextSongButton), nextSongISR, FALLING);

  // Initialize MP3 Player
  mp3.initialize();

  // Initialize LCD
  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("MP3 Player Ready");
  delay(2000); // Show message for 2 seconds
  lcd.clear();

  // Start with the first track paused
  Serial.print("Total Tracks Available: ");
  Serial.println(totalTracks);
  lcd.setCursor(0, 0);
  lcd.print("Press Play to");
  lcd.setCursor(0, 1);
  lcd.print("Start");
}

void loop() {
  // Handle Play/Pause Button Interrupt
  if (playPauseFlag) {
    playPauseFlag = false; // Reset flag
    if (isPlaying) {
      Serial.println("Playback Paused");
      mp3.player.stop(); // Stop playback
      isPlaying = false;
      lcd.setCursor(0, 1);
      lcd.print("Paused          ");
    } else {
      Serial.println("Playback Resumed");
      playTrack(currentTrack); // Resume playback
    }
  }

  // Handle Next Song Button Interrupt
  if (nextSongFlag) {
    nextSongFlag = false; // Reset flag
    currentTrack++;
    if (currentTrack > totalTracks) {
      currentTrack = 1; // Loop back to the first track
    }
    Serial.print("Playing Next Track: ");
    Serial.println(currentTrack);
    playTrack(currentTrack);
  }
}

// Interrupt Service Routine for Play/Pause Button
void playPauseISR() {
  static unsigned long lastInterruptTime = 0; // Track the last interrupt time
  unsigned long currentInterruptTime = millis();
  if (currentInterruptTime - lastInterruptTime > 50) { // Debounce (50ms)
    playPauseFlag = true;
    lastInterruptTime = currentInterruptTime;
  }
}

// Interrupt Service Routine for Next Song Button
void nextSongISR() {
  static unsigned long lastInterruptTime = 0; // Track the last interrupt time
  unsigned long currentInterruptTime = millis();
  if (currentInterruptTime - lastInterruptTime > 50) { // Debounce (50ms)
    nextSongFlag = true;
    lastInterruptTime = currentInterruptTime;
  }
}

// Helper Function to Play a Specific Track
void playTrack(int trackNumber) {
  mp3.playTrackNumber(trackNumber, 15, false); // Non-blocking playback
  isPlaying = true;
  Serial.print("Now Playing Track: ");
  Serial.println(trackNumber);

  // Update LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Now Playing:");
  lcd.setCursor(0, 1);
  lcd.print(songNames[trackNumber - 1]); // Display track name
}
