
// Октавная система.
float c0 = 16.352;
float d0 = 18.354;
float e0 = 20.602;
float f0 = 21.827;
float g0 = 24.500;
float a0 = 27.500;
float b0 = 30.868;

float c1 = c0 * 2;

float c2 = c0 * 4;

float c3 = c0 * 8;
float b3 = b0 * 8;

float c4 = c0 * 16;
float d4 = d0 * 16;
float e4 = e0 * 16;
float e4b = (e4 + d4) / 2;
float f4 = f0 * 16;
float g4 = g0 * 16;
float f4s = (f4 + g4) / 2; // F4 Диез (F4#, F4 Sharp)
float a4 = a0 * 16;
float b4 = b0 * 16;

float c5 = c0 * 32;
float d5 = d0 * 32;
float c5s = (c5 + d5) / 2;
float e5 = e0 * 32;
float f5 = f0 * 32;
float g5 = g0 * 32;
float f5s = (f5 + g5) / 2;
float a5 = a0 * 32;
float b5 = b0 * 32;
float a5s = (a5 + b5) / 2;

float c6 = c0 * 64;
float d6 = d0 * 64;
float e6 = e0 * 64;

const float R = 0; // Rest -- Покой, пауза.

// Based on the score by crono23:
// <https://musescore.com/crono23/scores/5491815>
float daisy1[][2] = {
  // 1
  {d5, 4}, {c5s, 4}, {d5, 4},
  // 2
  {b4, 4}, {a4, 4}, {g4, 4},
  // 3
  {a4, 2}, {f5s, 4},
  // 4
  {d5, 2}, {d6, 4},
  // 5
  {b5, 8}, {d5, 8},
  {e5, 8}, {f5s, 8},
  {g5, 8}, {a5, 8},
  // 6
  {a5s, 8}, {b5, 8},
  {e6, 8}, {d6, 8},
  {c6, 8}, {g5, 8},
  // 7
  {a5, 2}, {d5, 4},
  // 8
  {b4, 4.0 / 3.0},
  // 9 (vocals)
  {d5, 4}, {c5s, 4}, {d5, 4},
  // 10
  {b4, 4}, {a4, 4}, {g4, 4},
  // 11
  {a4, 2}, {f4s, 4},
  // 12
  {d4, 2}, {R, 4},
  // 13
  {a4, 4.0 / 3.0},
  // 14
  {d4, 4.0 / 3.0},
  // 15
  {d5, 4.0 / 3.0},
  // 16
  {b4, 2}, {R, 4},
  // 17
  {d5, 4}, {c5s, 4}, {d5, 4},
  // 18
  {b4, 4}, {a4, 4}, {g4, 4},
  // 19
  {a4, 2}, {f4s, 4},
  // 20
  {d4, 2}, {R, 4},
  // 21
  {g4, 4}, {d5, 4}, {g4, 4},
  // 22
  {f4s, 4}, {d4, 4}, {a4, 4},
  // 23
  {g4, 1},
  // 24
  {R, 4}, {R, 4}
};

const int LENGTH = sizeof(daisy1) / sizeof(daisy1[0]);
