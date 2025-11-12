#ifndef __MUSIC_H__
#define __MUSIC_H__

typedef struct {
  // Количество нот в мелодии.
  int length;

  // Индекс (номер) ноты.
  int  note_index;

  // Время начала воспроизведения ноты.
  long note_start_time;

  // Длина ноты.
  long note_length;

  // Задержка после ноты.
  long note_delay;

  // Текущее время.
  long current_time;

  // Время, прошедшее с начала воспроизведения
  // ноты.
  long time_diff;

  // Виртуальный регистр OCR.
  long ocr;

  // Счётчик для таймера.
  long counter;

  // Цифровой порт для вывода звука.
  byte speaker_pin;

  // Текущее значение на выходном цифровом порту.
  byte speaker_pin_value;
} track_t;

extern float melody_left[][2];
extern float melody_right[][2];
extern const int LENGTH_1;
extern const int LENGTH_2;

#endif /* ifndef __MUSIC_H__ */
