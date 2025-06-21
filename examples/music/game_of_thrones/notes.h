/*
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

// Notes.

const float c0 = 16.352;
float d0 = 18.354;
float e0 = 20.602;
float f0 = 21.827;
float g0 = 24.500;
float a0 = 27.500;
float b0 = 30.868;

float c2 = c0 * 4;
float f2 = f0 * 4;
float g2 = g0 * 4;
float a2 = a0 * 4;
float b2 = b0 * 4;
float b2f = (b2 + a2) / 2;

float c3 = c0 * 8;
float d3 = d0 * 8;
float e3 = e0 * 8;
float e3f = (e3 + d3) / 2;
float f3 = f0 * 8;
float g3 = g0 * 8;
float g3f = (g3 + f3) / 2;
float a3 = a0 * 8;
float a3f = (a3 + g3) / 2;
float b3 = b0 * 8;
float b3f = (b3 + a3) / 2;

float c4 = c0 * 16;
float d4 = d0 * 16;
float e4 = e0 * 16;
float e4f = (e4 + d4) / 2; // E4 Бемоль (Flat)
float f4 = f0 * 16;
float g4 = g0 * 16;
float f4s = (f4 + g4) / 2;  // F4 Диез (Sharp)
float a4 = a0 * 16;
float a4f = (a4 + g4) / 2;
float b4 = b0 * 16;
float b4f = (b4 + a4) / 2;

float c5 = c0 * 32;
float d5 = d0 * 32;

float R = 0;
