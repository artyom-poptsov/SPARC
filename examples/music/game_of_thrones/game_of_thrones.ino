/* game_of_thrones.ino -- "Game of Thrones" theme.

   The score for this program is based on "Game of Thrones"
   theme composed by Ramin Djawadi.

   The arrangement is done by lucky37:
   <https://musescore.com/user/158751/scores/2163051>

   You need one Arduino board and two speakers to play this song.

   Copyright (C) 2025 Artyom V. Poptsov <poptsov.artyom@gmail.com>

   This file is a part of SPARC book supplimentary material:
   <https://github.com/artyom-poptsov/SPARC>

   This program is free software: you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation, either version 3 of the
   License, or (at your option) any later version.

   This program is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with This program.  If not, see <http://www.gnu.org/licenses/>.
*/

#define MELODY1 right_hand
#define MELODY2 left_hand

#include "notes.h"
#include "melody.h"
#include "ports.h"

const long CPU_FREQ = 16000000;
const long CPU_PRESCALER = 8.0;
const float DELAY_PERCENT = 0.05;
const int BPM = 180; // Beats per minute.
const long MINUTE = 60000000; // One minute in microseconds.
const long TAKT = (MINUTE / BPM) * 4; // Measure length.

typedef struct {
  int  note_index;
  long note_start_time;
  long note_length;
  long note_delay;
  long current_time;
  long time_diff;
  long increment;
  byte speaker_pin_value;
} track_t;

volatile track_t track1;
volatile track_t track2;

long frequency_to_timer(float f) {
  const double T = 1000000.0 / f;
  return (T * CPU_FREQ) / (CPU_PRESCALER * 1000000.0) / 2;
}

void setup() {
  delay(100);
  pinMode(SPEAKER_1, OUTPUT);
  pinMode(SPEAKER_2, OUTPUT);
  pinMode(4, INPUT_PULLUP);

  track1.note_index = 0;
  track1.note_start_time = micros();
  track1.note_length = TAKT / MELODY1[0][1];
  track1.note_delay = track1.note_length * DELAY_PERCENT;
  track1.current_time = micros();
  track1.time_diff = 0;
  track1.increment = frequency_to_timer(MELODY1[0][0]);
  track1.speaker_pin_value = HIGH;

  track2.note_index = 0;
  track2.note_start_time = micros();
  track2.note_length = TAKT / MELODY2[0][1];
  track2.note_delay = track2.note_length * DELAY_PERCENT;
  track2.current_time = micros();
  track2.time_diff = 0;
  track2.increment = frequency_to_timer(MELODY2[0][0]);
  track2.speaker_pin_value = HIGH;
  
  //Serial.begin(9600);
  //cli(); // Disable global interrupts

  TCCR1A = 0;
  TCCR1B = 0;

  TCCR1B |= B00000010;
  OCR1A = frequency_to_timer(b4);
  OCR1B = frequency_to_timer(b4);
  TIMSK1 |= B00000110;
}

ISR(TIMER1_COMPA_vect) {
  if (track1.increment > 65535) {
    OCR1A = 65535;
    track1.increment -= 65535;
    return;
  } else {
    OCR1A += track1.increment;
  }
  track1.current_time = micros();
  track1.time_diff = track1.current_time - track1.note_start_time;
  
  if ((track1.note_length > 0) 
      && (track1.time_diff < track1.note_length)) {
    digitalWrite(SPEAKER_1, track1.speaker_pin_value);
    track1.speaker_pin_value = ! track1.speaker_pin_value;
  }

  if (track1.time_diff >= track1.note_length + track1.note_delay) {
    track1.note_index = (track1.note_index + 1) % MELODY1_LENGTH;
    track1.note_start_time = track1.current_time;
    if (MELODY1[track1.note_index][0] > 0) {
      track1.increment = frequency_to_timer(MELODY1[track1.note_index][0]);
      track1.note_length = TAKT / MELODY1[track1.note_index][1];
      track1.note_delay = track1.note_length * DELAY_PERCENT;
    } else {
      track1.increment = 100;
      track1.note_delay = TAKT / MELODY1[track1.note_index][1];
      track1.note_delay += track1.note_delay * DELAY_PERCENT;
      track1.note_length = 0;
    }
  }
}

ISR(TIMER1_COMPB_vect) {
  if (track2.increment > 65535) {
    OCR1B = 65535;
    track2.increment -= 65535;
    return;
  } else {
    OCR1B += track2.increment;
  }
  track2.current_time = micros();
  track2.time_diff = track2.current_time - track2.note_start_time;
  
  if ((track2.note_length > 0) 
      && (track2.time_diff < track2.note_length)) {
    digitalWrite(SPEAKER_2, track2.speaker_pin_value);
    track2.speaker_pin_value = ! track2.speaker_pin_value;
  }

  if (track2.time_diff >= track2.note_length + track2.note_delay) {
    track2.note_index = (track2.note_index + 1) % MELODY2_LENGTH;
    track2.note_start_time = track2.current_time;
    if (MELODY2[track2.note_index][0] > 0) {
      track2.increment = frequency_to_timer(MELODY2[track2.note_index][0]);
      track2.note_length = TAKT / MELODY2[track2.note_index][1];
      track2.note_delay = track2.note_length * DELAY_PERCENT;
    } else {
      track2.increment = 100;
      track2.note_delay = TAKT / MELODY2[track2.note_index][1];
      track2.note_delay += track2.note_delay * DELAY_PERCENT;
      track2.note_length = 0;
    }
  }
}

void loop() {
  delay(100);
}
