#include "music.h"

// Порт вывода звука.
const int SPEAKER_1 = 2;
const int SPEAKER_2 = 3;

// Частота процессора.
const long CPU_FREQ = 16000000; // Гц

// Предделитель частоты.
const long CPU_PRESCALER = 8.0;

// Время между нотами, равное проценту от длины ноты.
const float DELAY_PERCENT = 0.05;

// Скорость мелодии "Daisy Bell".
const int BPM = 172; // Beats per minute.

// Одна минута, заданная в микросекундах.
const long MINUTE = 60000000; // мкс

// Длина такта.
const long TAKT = (MINUTE / BPM) * 4; // мкс

volatile track_t track1;
volatile track_t track2;

//   04. Процедура для преобразования частоты звука
//     в значение регистра сравнения "OCR".
long frequency_to_timer(double f) {
  return (CPU_FREQ / (CPU_PRESCALER * f * 2)) - 1;
}

void setup() {
  pinMode(SPEAKER_1, OUTPUT);
  pinMode(SPEAKER_2, OUTPUT);

  track1.length = LENGTH_1;
  track1.note_index = 0;
  track1.note_start_time = micros();
  track1.note_length = TAKT / daisy1[0][1];
  track1.note_delay = track1.note_length * DELAY_PERCENT;
  track1.current_time = micros();
  track1.time_diff = 0;
  track1.ocr = frequency_to_timer(daisy1[0][0]);
  track1.counter = track1.ocr;
  track1.speaker_pin_value = HIGH;

  track2.length = LENGTH_2;
  track2.note_index = 0;
  track2.note_start_time = micros();
  track2.note_length = TAKT / daisy2[0][1];
  track2.note_delay = track2.note_length * DELAY_PERCENT;
  track2.current_time = micros();
  track2.time_diff = 0;
  track2.ocr = frequency_to_timer(daisy2[0][0]);
  track2.counter = track2.ocr;
  track2.speaker_pin_value = HIGH;

  TCCR1A = B00000000;
  TCCR1B = B00000010;
  OCR1A = 1024;
  OCR1B = 1024;
  TIMSK1 |= B00000110;
}

// 10. Обработчик прерывания.
ISR(TIMER1_COMPA_vect) {
  if (track1.counter > 65535) {
    OCR1A = 65535;
    track1.counter -= 65535;
    return;
  } else {
    OCR1A += track1.counter;
    track1.counter = track1.ocr;
  }

  track1.current_time = micros();
  track1.time_diff = track1.current_time - track1.note_start_time;
  if ((track1.note_length > 0)
      && (track1.time_diff < track1.note_length)) {
    digitalWrite(SPEAKER_1, track1.speaker_pin_value);
    track1.speaker_pin_value = ! track1.speaker_pin_value;
  }

  if (track1.time_diff >= track1.note_length + track1.note_delay) {
    track1.note_index = (track1.note_index + 1) % track1.length;
    track1.note_start_time = track1.current_time;
    if (daisy1[track1.note_index][0] > 0) {
      track1.ocr = frequency_to_timer(daisy1[track1.note_index][0]);
      track1.note_length = TAKT / daisy1[track1.note_index][1];
      track1.note_delay = track1.note_length * DELAY_PERCENT;
    } else {
      track1.ocr = 100;
      track1.note_delay = TAKT / daisy1[track1.note_index][1];
      track1.note_delay += track1.note_delay * DELAY_PERCENT;
      track1.note_length = 0;
    }
  }
}


// 10. Обработчик прерывания.
ISR(TIMER1_COMPB_vect) {
  if (track2.counter > 65535) {
    OCR1B = 65535;
    track2.counter -= 65535;
    return;
  } else {
    OCR1B += track2.counter;
    track2.counter = track2.ocr;
  }

  track2.current_time = micros();
  track2.time_diff = track2.current_time - track2.note_start_time;
  if ((track2.note_length > 0)
      && (track2.time_diff < track2.note_length)) {
    digitalWrite(SPEAKER_2, track2.speaker_pin_value);
    track2.speaker_pin_value = ! track2.speaker_pin_value;
  }

  if (track2.time_diff >= track2.note_length + track2.note_delay) {
    track2.note_index = (track2.note_index + 1) % track2.length;
    track2.note_start_time = track2.current_time;
    if (daisy2[track2.note_index][0] > 0) {
      track2.ocr = frequency_to_timer(daisy2[track2.note_index][0]);
      track2.note_length = TAKT / daisy2[track2.note_index][1];
      track2.note_delay = track2.note_length * DELAY_PERCENT;
    } else {
      track2.ocr = 100;
      track2.note_delay = TAKT / daisy2[track2.note_index][1];
      track2.note_delay += track2 .note_delay * DELAY_PERCENT;
      track2.note_length = 0;
    }
  }
}


void loop() {
  delay(100);
}
