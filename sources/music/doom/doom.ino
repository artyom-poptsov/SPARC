/* doom.ino -- Doom Theme.
 *  
 * The score for this program is based on "Doom Theme Easy"
 * by Ms Weinert:
 * <https://musescore.com/weinert/doom-theme-easy>
 *
 * You need two Arduino boards to play this song.
 *
 * Copyright (C) 2023 Artyom V. Poptsov <poptsov.artyom@gmail.com>
 *
 * This file is a part of SPARC book supplimentary material:
 * <https://github.com/artyom-poptsov/SPARC>
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation, either version 3 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with This program.  If not, see <http://www.gnu.org/licenses/>.
 */

// The port where a speaker is connected (it's the same for both
// of two Arduino boards.)
const int SPEAKER = 2;

// This port controls which part of the melody 
// the Arduino would play (left hand or right hand.)
// If this digital port is pulled to LOW value then
// the Arduino will play the right "hand" of the song.
const int SONG_PART_SWITCH = 3;

// Notes.
float c0 = 16.352;
float d0 = 18.354;
float e0 = 20.602;
float f0 = 21.827;
float g0 = 24.500;
float a0 = 27.500;
float b0 = 30.868;

float c1 = c0 * 2;
float c2 = c0 * 4;
float a2 = a0 * 4;
float b2 = b0 * 4;
float a2s = (a2 + b2) / 2; // A2#
float c3 = c0 * 8;
float e3 = e0 * 8;
float f3 = f0 * 8;
float g3 = g0 * 8;
float f3s = (f3 + g3) / 2;
float d3 = d0 * 8;
float d3s = (d3 + e3) / 2;
float a3 = a0 * 8;
float b3 = b0 * 8;
float b3b = (b3 + a3) / 2; // b3b (B3 Бемоль)

float c4 = c0 * 16;
float d4 = 293.66;
float e4 = 329.63;
float f4 = 349.23;
float g4 = 392.00;
float f4s = (f4 + g4) / 2; // F4#, F4 Диез, F4 Sharp (Острая нота)
float a4 = 440.00;
float g4s = (g4 + a4) / 2; // G4#
float b4 = 493.88;

float d5 = d0 * 32;

float R = 0; // Rest -- Покой, Пауза

void setup() {
  pinMode(SPEAKER, OUTPUT);
  pinMode(SONG_PART_SWITCH, INPUT_PULLUP);
}

// This is the procedure to play a sound with frequency "f"
// for "t" microseconds on a "port".
void play_tone(int port, float f, long t) {
  if (f > 0) {
    const long T = 1000000 / f;
    long d = T / 2;
    int count = t / T;
    for (int i = 0; i < count; i++) {
      digitalWrite(port, HIGH);
      delayMicroseconds(d);
      digitalWrite(port, LOW);
      delayMicroseconds(d);
    }
  } else {
    delay(t / 1000);
  }
  // Add a gap between the notes based on the
  // note length.
  delayMicroseconds(t * 0.05);
}


// Right "Hand".
float doom1[][2] = {
  {R, 4}, {e3, 8}, {R, 4}, {d3, 8}, {R, 4},  // 1
  {c3, 8}, {R, 4}, {a2s, 8}, {R, 4}, {b2, 8}, {c3, 8},  // 2
  {R, 4}, {e3, 8}, {R, 4}, {d3, 8}, {R, 4}, // 3
  {c3, 8}, {R, 4}, {a2s, (8.0 / 5.0)}, // 4

  {R, 4}, {e3, 8}, {R, 4}, {d3, 8}, {R, 4},  // 5
  {c3, 8}, {R, 4}, {a2s, 8}, {R, 4}, {b2, 8}, {c3, 8},  // 6
  {R, 4}, {e3, 8}, {R, 4}, {d3, 8}, {R, 4}, // 7
  {c3, 8}, {R, 4}, {a2s, (8.0 / 5.0)}, // 8

  {R, 4}, {e3, 8}, {R, 4}, {d3, 8}, {R, 4},  // 9
  {c3, 8}, {R, 4}, {a2s, 8}, {R, 4}, {b2, 8}, {c3, 8},  // 10
  {R, 4}, {e3, 8}, {R, 4}, {d3, 8}, {R, 4}, // 11
  {R, 8}, {b3, 16}, {e4, 16}, {R, 8}, {b3, 16}, {e4, 16}, {R, 8}, {b3, 16}, {e4, 16}, {R, 8}, {b3, 16}, {e4, 16}, {R, 8},  // 12

  {R, 4}, {a3, 8}, {R, 4}, {g3, 8}, {R, 4}, // 13
  {f3, 8}, {R, 4}, {d3s, 8}, {R, 4}, {e3, 8}, {f3s, 8}, // 14
  {R, 4}, {a3, 8}, {R, 4}, {g3, 8}, {R, 4}, // 15
  {f3, 8}, {R, 4}, {d3s, (8.0 / 5.0)}, // 16
};

// Right "Hand".
float doom2[][2] = {
  {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, // 1
  {R, 8},  {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, {R, 4},    // 2
  {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, // 3
  {R, 8},  {c2, 8}, {c2, 8}, {c2, (8.0 / 5.0)}, // 4

  {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, // 5
  {R, 8},  {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, {R, 4},    // 6
  {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, // 7
  {R, 8},  {c2, 8}, {c2, 8}, {c2, (8.0 / 5.0)}, // 8

  {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, // 9
  {R, 8},  {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, {R, 4},    // 10
  {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, {R, 8}, {c2, 8}, {c2, 8}, // 11
  {e3, 16}, {g3, 16}, {R, 8},  {e3, 16}, {g3, 16}, {R, 8},  {e3, 16}, {g3, 16}, {R, 8},  {e3, 16}, {g3, 16}, {R, 8},  // 12

  {a2, 8}, {a2, 8}, {R, 8}, {a2, 8}, {a2, 8}, {R, 8}, {a2, 8}, {a2, 8}, // 13
  {R, 8},  {a2, 8}, {a2, 8}, {R, 8}, {a2, 8}, {a2, 8}, {R, 4}, // 14
  {a2, 8}, {a2, 8}, {R, 8}, {a2, 8}, {a2, 8}, {R, 8}, {a2, 8}, {a2, 8}, // 15
  {R, 8}, {a2, 8}, {a2, 8}, {a2, 8}, {a2, 8}, {a2, 8}, {a2, 8}, {a2, 8}, // 16
};

void loop() {
  const int BPM = 240; // Удары в минуту (скорость композиции)
  const long MINUTE = 60000000; // Минута в микросекундах
  const long TAKT = (MINUTE / BPM) * 4; // Рассчёт длительности такта
  if (digitalRead(SONG_PART_SWITCH) == LOW) {
    int count = sizeof(doom1) / sizeof(doom1[0]);
    for (int i = 0; i < count; i++) {
      play_tone(SPEAKER, doom1[i][0], TAKT / doom1[i][1] );
    }
  } else {
    int count = sizeof(doom1) / sizeof(doom1[0]);
    for (int i = 0; i < count; i++) {
      play_tone(SPEAKER, doom2[i][0], TAKT / doom2[i][1] );
    }
  }
}
