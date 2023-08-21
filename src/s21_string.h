#ifndef SRC_S21_STRING_H_
#define SRC_S21_STRING_H_
#include <ctype.h>
#include <math.h>
#include <stdarg.h>
#include <stdint.h>

#define s21_size_t unsigned long long
#define s21_NULL (void *)0
#define SIZE 2560

// struct to contain flags
typedef struct {
  int minus;
  int plus;
  int space;
  int dot;
  int precision;
  int width;
  char length;
  char specifier;
} flags;

// s21_sprintf
int s21_sprintf(char *str, const char *format, ...);
// scan between % and specifier
const char *scan_for_flags(const char *format, flags *f);
const char *scan_for_width(const char *format, flags *f);
const char *scan_for_precision(const char *format, flags *f);
const char *scan_for_length(const char *format, flags *f);
// deliver scepifier into struct and write case into buffer
void work_with_specifier(flags f, char *buffer, va_list va);
void int_case(flags, char *buffer, va_list va);
void unsigned_case(flags f, char *buffer, va_list va);
void char_case(flags f, char *buffer, va_list va);
void string_case(flags f, char *buffer, va_list va);
void float_case(flags f, char *buffer, va_list va);
// make adjustments to buffer
void process_precision(char *buffer, flags f);
void process_flags(char *buffer, flags f);

// 1
void *s21_memchr(const void *str, int c, s21_size_t n);
// 2
int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
// 3
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
// 4
void *s21_memmove(void *dest, const void *src, s21_size_t n);
// 5
void *s21_memset(void *str, int c, s21_size_t n);
// 6
char *s21_strcat(char *dest, const char *src);
// 7
char *s21_strncat(char *dest, const char *src, s21_size_t n);
// 8
char *s21_strchr(const char *str, int c);
// 9
int s21_strcmp(const char *cs, const char *ct);
// 10
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
// 11
char *s21_strcpy(char *dest, const char *src);
// 12
char *s21_strncpy(char *dest, const char *src, s21_size_t n);
// 13
s21_size_t s21_strcspn(const char *str1, const char *str2);
// 14
char *s21_strerror(int errnum);
// 15
s21_size_t s21_strlen(const char *str);
// 16
char *s21_strpbrk(const char *str1, const char *str2);
// 17
char *s21_strrchr(const char *str, int c);
// 18
s21_size_t s21_strspn(const char *str1, const char *str2);
// 19
char *s21_strstr(const char *s1, const char *s2);
// 20
char *s21_strtok(char *str, const char *delim);
// to upper and to lower
void *s21_to_upper(const char *str);
void *s21_to_lower(const char *str);
// to insert
void *s21_insert(const char *src, const char *str, s21_size_t start_index);
// trim
void *s21_trim(const char *src, const char *trim_chars);
void rtrim(char *temp_str, const char *trim_chars);
void ltrim(char *temp_str, const char *trim_chars);
// atoi
int s21_atoi(char *str);
// itoa
void swap(char *x, char *y);
char *reverse(char *buffer, int i, int j);
void s21_itoa(int64_t value, char *buffer, int base);
void s21_uitoa(uint64_t value, char *buffer, int base);
// ftoa
int s21_itoa_with_counter(int64_t x, char *buffer, int precision, int neg_flag);
void s21_ftoa(long double n, char *buffer, int precision);

#endif  //  SRC_S21_STRING_H_
