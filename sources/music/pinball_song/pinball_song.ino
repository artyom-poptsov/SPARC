/* pinball_song.ino -- Pinball Number Count theme.

   The score for this program is based on "Pinball Number Count"
   from "Sesame Street" composed by Walt Kraemer.

   The arrangement is done by Phil Kan:
   <https://musescore.com/user/33746706/scores/11901262>

   You need one Arduino board and two speakers to play this song.

   Copyright (C) 2023 Artyom V. Poptsov <poptsov.artyom@gmail.com>

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

// Порты для подключения динамиков.
const int SPEAKER_1 = 2;
const int SPEAKER_2 = 4;

// Ноты.
float c0 = 16.352;
float d0 = 18.354;
float e0 = 20.602;
float f0 = 21.827;
float g0 = 24.500;
float a0 = 27.500;
float b0 = 30.868;

float c1 = c0 * 2;
float c2 = c0 * 4;
float g2 = g0 * 4;
float a2 = a0 * 4;
float b2 = b0 * 4;
float a2b = (a2 + g2) / 2; // A2b
float a2s = (a2 + b2) / 2; // A2#
float c3 = c0 * 8;
float e3 = e0 * 8;
float f3 = f0 * 8;
float g3 = g0 * 8;
float f3s = (f3 + g3) / 2;
float d3 = d0 * 8;
float d3s = (d3 + e3) / 2;
float a3 = a0 * 8;
float a3b = (a3 + g3) / 2;
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

float c5 = c0 * 32;
float d5 = d0 * 32;
float a5 = a0 * 32;

float R = 0; // Rest -- Покой, Пауза

void setup() {
  pinMode(SPEAKER_1, OUTPUT);
  pinMode(SPEAKER_2, OUTPUT);
  randomSeed(analogRead(A0));
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


// Основная тема композиции.
float pinball_1[][2] = {
  {g2, 8}, {g2, 8}, {R, 8}, {g3, 8}, {R, 8}, {f3, 8}, {R, 8}, {d3, 8}, // 1
  {g2, 8}, {g2, 8}, {g3, 8}, {R, 4},  // 2
  {a2b, 8}, {a2b, 8}, {a3b, 8}, {R, 8}, {b2, 8}, {b2, 8}, {c4, 8}, // 3
  {c3, 8}, {c3, 8}, {d4, 8}, {e3, 8},  {e3, 8}, {e4, 8}
};

// "Вокальная" партия.
float pinball_2[][2] = {
  {d5, 4}, {c5, 8}, {a4, 8}, {c4, 8}, {d5, 8}, // 1
  {a4, 4}, {g4, 8}, {e4, 8}, {g4, 8}, {e4, 8}, {g4, 8}, {a4, 4}, // 2
  {g4, 4}, {e4, 8}, {d4, 8}, {c4, 8}, {d4, 8}, {c4, 8}, // 3
  {g4, 8}, {a4, 8}, {a5, 8}, {R, 8}, {R, 4} // 4
};

void loop() {
  const int BPM = 180; // Удары в минуту (скорость композиции)
  const long MINUTE = 60000000; // Минута в микросекундах
  const long TAKT = (MINUTE / BPM) * 4; // Вычисление длительности такта

  // Случайный выбор композиции.
  int n = random(3);

  if ( (n == 0) || (n == 1) ) {
    int count = sizeof(pinball_1) / sizeof(pinball_1[0]);
    for (int i = 0; i < count; i++) {
      play_tone(SPEAKER_1, pinball_1[i][0], TAKT / pinball_1[i][1] );
    }
  } else {
    int count = sizeof(pinball_2) / sizeof(pinball_2[0]);
    for (int i = 0; i < count; i++) {
      play_tone(SPEAKER_2, pinball_2[i][0], TAKT / pinball_2[i][1] );
    }
  }

}
