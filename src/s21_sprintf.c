#include "s21_string.h"

int s21_sprintf(char *str, const char *format, ...) {
  flags f = {0};
  va_list va;
  va_start(va, format);
  char *str_start = str;
  while (*format) {
    if (*format == '%') {
      format++;
      s21_memset(&f, 0, sizeof(flags));
    } else {
      *str++ = *format++;
      continue;
    }

    format = scan_for_flags(format, &f);
    format = scan_for_width(format, &f);
    format = scan_for_precision(format, &f);
    format = scan_for_length(format, &f);

    f.specifier = *format;
    format++;

    char buffer[SIZE] = {'\0'};
    work_with_specifier(f, buffer, va);
    for (int i = 0; buffer[i]; i++, str++) {
      *str = buffer[i];
    }
  }

  *str = '\0';
  va_end(va);
  return str - str_start;
}

const char *scan_for_flags(const char *format, flags *f) {
  while (*format == '-' || *format == '+' || *format == ' ') {
    switch (*format) {
      case '-':
        f->minus = 1;
        break;
      case '+':
        f->plus = 1;
        break;
      case ' ':
        f->space = 1;
        break;
    }
    format++;
  }
  return format;
}

const char *scan_for_width(const char *format, flags *f) {
  if (isdigit(*format)) {
    char temp[SIZE] = {'\0'};

    for (int i = 0; isdigit(*format); i++, format++) {
      temp[i] = *format;
    }

    f->width = s21_atoi(temp);
  }
  return format;
}

const char *scan_for_precision(const char *format, flags *f) {
  if (*format == '.') {
    f->dot = 1;
    format++;
  }

  if (isdigit(*format)) {
    char temp[SIZE] = {'\0'};

    for (int i = 0; isdigit(*format); i++, format++) {
      temp[i] = *format;
    }

    f->precision = s21_atoi(temp);
  }
  return format;
}

const char *scan_for_length(const char *format, flags *f) {
  switch (*format) {
    case 'h':
      if (*++format == 'h') {
        format++;
      }
      f->length = 'h';
      break;
    case 'l':
      if (*++format == 'l') {
        format++;
      }
      f->length = 'l';
      break;
  }
  return format;
}

void process_precision(char *buffer, flags f) {
  char temp[SIZE] = {'\0'};
  int minus = 0;
  int lenght = s21_strlen(buffer);

  if (buffer[0] == '-') {
    temp[0] = '-';
    lenght--;
    minus = 1;
  }

  if (f.precision > lenght) {
    int index;

    for (index = minus; index < f.precision - lenght + minus; index++) {
      temp[index] = '0';
    }

    for (int i = minus; buffer[i]; i++, index++) {
      temp[index] = buffer[i];
    }

    s21_strcpy(buffer, temp);
  }

  if (f.dot && f.precision == 0 && buffer[0] == '0') {
    buffer[0] = '\0';
  }
}

void process_flags(char *buffer, flags f) {
  char temp[SIZE + 1] = {'\0'};

  if (f.plus && f.specifier != 'u') {
    if (buffer[0] == '-') {
      temp[0] = buffer[0];
    } else {
      temp[0] = '+';
    }

    if (buffer[0] == '-') {
      s21_strcpy(temp + 1, buffer + 1);
    } else {
      s21_strcpy(temp + 1, buffer);
    }
    s21_strcpy(buffer, temp);

  } else if (f.space && buffer[0] != '-' && f.specifier != 'u') {
    temp[0] = ' ';
    s21_strcpy(temp + 1, buffer);
    s21_strcpy(buffer, temp);
  }

  if (f.width > (int)s21_strlen(buffer)) {
    int idx = f.width - s21_strlen(buffer);
    if (f.minus) {
      s21_strcpy(temp, buffer);
      s21_memset(temp + s21_strlen(temp), ' ', idx);
    } else {
      s21_memset(temp, ' ', idx);
      s21_strcpy(temp + idx, buffer);
    }
    s21_strcpy(buffer, temp);
  }
}

void work_with_specifier(flags f, char *buffer, va_list va) {
  if (f.specifier == '%')
    buffer[0] = '%';
  else if (f.specifier == 'c')
    char_case(f, buffer, va);
  else if (f.specifier == 'd' || f.specifier == 'i')
    int_case(f, buffer, va);
  else if (f.specifier == 'u')
    unsigned_case(f, buffer, va);
  else if (f.specifier == 's')
    string_case(f, buffer, va);
  else if (f.specifier == 'f')
    float_case(f, buffer, va);
}

void char_case(flags f, char *buffer, va_list va) {
  char c = va_arg(va, int);

  if (f.minus && f.width) {
    buffer[0] = c;
    for (int i = 1; i < f.width; i++) {
      buffer[i] = ' ';
    }

  } else if (f.width) {
    for (int i = 0; i < f.width; i++) {
      buffer[i] = ' ';
      if (i == f.width - 1) {
        buffer[i] = c;
      }
    }

  } else {
    buffer[0] = c;
  }
}

void int_case(flags f, char *buffer, va_list va) {
  int64_t num = va_arg(va, int64_t);

  switch (f.length) {
    case 'h':
      num = (int16_t)num;
      break;
    case 'l':
      num = (int64_t)num;
      break;
    case 0:
      num = (int32_t)num;
      break;
  }

  s21_itoa(num, buffer, 10);
  process_precision(buffer, f);
  process_flags(buffer, f);
}

void unsigned_case(flags f, char *buffer, va_list va) {
  uint64_t num = va_arg(va, uint64_t);
  switch (f.length) {
    case 'h':
      num = (uint16_t)num;
      break;
    case 'l':
      num = (uint64_t)num;
      break;
    case 0:
      num = (uint32_t)num;
      break;
  }

  s21_uitoa(num, buffer, 10);
  process_precision(buffer, f);
  process_flags(buffer, f);
}

void string_case(flags f, char *buffer, va_list va) {
  char *str = va_arg(va, char *);
  char temp[SIZE] = {'\0'};
  s21_strcpy(temp, str);

  if (f.dot) {
    temp[f.precision] = '\0';
  }

  s21_strcpy(buffer, temp);

  int spaces = f.width - s21_strlen(temp);
  int lenght = s21_strlen(temp);

  if (spaces > 0) {
    if (f.minus && f.width) {
      s21_strcpy(buffer, temp);
      s21_memset(buffer + lenght, ' ', spaces);
    } else if (f.width) {
      s21_memset(buffer, ' ', spaces);
      s21_strcpy(buffer + spaces, temp);
    }
  }
}

void float_case(flags f, char *buffer, va_list va) {
  long double val = va_arg(va, double);

  if (!f.dot) {
    f.precision = 6;
  }

  s21_ftoa(val, buffer, f.precision);
  process_flags(buffer, f);
}
