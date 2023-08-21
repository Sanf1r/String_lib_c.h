#include "s21_string.h"

#include <stdlib.h>

#include "s21_errorlist.h"

// 1 Searches for the first occurrence of the character c
//  (an unsigned char) in the first n bytes of the string pointed to, by the
//  argument str.
void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ptr = (unsigned char *)str;
  void *res = s21_NULL;

  for (s21_size_t i = 0; i < n && ptr; i++) {
    if (*ptr == (unsigned char)c) {
      res = ptr;
      break;
    }
    ptr++;
  }

  return res;
}

// 2 Compares the first n bytes of str1 and str2.
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  unsigned char *s1 = (unsigned char *)str1;
  unsigned char *s2 = (unsigned char *)str2;
  int dif = 0;

  for (s21_size_t i = 0; i < n; i++) {
    dif = *s1 - *s2;
    if (dif != 0) {
      break;
    }
    s1++;
    s2++;
  }

  return dif;
}

// 3 Copies n characters from src to dest.
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *d = (unsigned char *)dest;
  unsigned char *s = (unsigned char *)src;

  for (s21_size_t i = 0; i < n; i++) {
    d[i] = s[i];
  }

  return dest;
}

// 4 Another function to copy n characters from src to dest.
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  char *to = (char *)dest;
  char *from = (char *)src;
  char *tmp = (char *)malloc(sizeof(char) * n);

  if (tmp != s21_NULL) {
    s21_memcpy(tmp, from, n);
    s21_memcpy(to, tmp, n);
    free(tmp);
  }

  return dest;
}

// 5 Copies the character c (an unsigned char) to the first n characters of the
// string pointed to, by the argument str.
void *s21_memset(void *str, int c, s21_size_t n) {
  char *s = (char *)str;

  for (s21_size_t i = 0; i < n; i++) {
    s[i] = c;
  }

  return str;
}

// 6 Appends the string pointed to, by src to the end of the string pointed to
// by dest.
char *s21_strcat(char *dest, const char *src) {
  int lengthSrc = 0, lengthDest = s21_strlen(dest);

  while (1) {
    if (src[lengthSrc] != '\0') {
      dest[lengthSrc + lengthDest] = src[lengthSrc];
      lengthSrc += 1;
      continue;
    }
    dest[lengthSrc + lengthDest] = '\0';
    break;
  }

  return dest;
}

// 7 Appends the string pointed to, by src to the end of the string pointed to,
// by dest up to n characters long.
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ptr = dest + s21_strlen(dest);

  while (*src != '\0' && n--) {
    *ptr++ = *src++;
  }
  *ptr = '\0';

  return dest;
}

// 8 Searches for the first occurrence of the character c (an unsigned char) in
// the string pointed to, by the argument str.
char *s21_strchr(const char *str, int c) {
  char *s = s21_NULL;

  for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
    if (str[i] == c) {
      s = (char *)str + i;
      break;
    }
  }

  return s;
}

// 9 Compares the string pointed to, by str1 to the string pointed to by str2.
int s21_strcmp(const char *str1, const char *str2) {
  unsigned char s1, s2;
  s21_size_t res = 0;

  do {
    s1 = *str1++;
    s2 = *str2++;
    res = s1 - s2;
    if (res != 0) {
      break;
    }
  } while (s1 && s2);

  return res;
}

// 10 Compares at most the first n bytes of str1 and str2.
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  int res = 0;

  if (str1 && str2 && n > 0) {
    for (s21_size_t i = 0; i < n; i++) {
      if (str1[i] == '\0' || str1[i] != str2[i]) {
        res = str1[i] - str2[i];
        break;
      }
    }
  }

  return res;
}

// 11 Copies the string pointed to, by src to dest.
char *s21_strcpy(char *dest, const char *src) {
  int length = 0;

  while (1) {
    if (src[length] != '\0') {
      dest[length] = src[length];
      length += 1;
      continue;
    }
    dest[length] = '\0';
    break;
  }

  return dest;
}

// 12 Copies up to n characters from the string pointed to, by src to dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  s21_memset(dest, '\0', n);

  for (s21_size_t i = 0; i < n && src[i]; i++) {
    dest[i] = src[i];
  }

  return dest;
}

// 13 Calculates the length of the initial segment of str1 which consists
// entirely of characters not in str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t counter = 0;

  for (const char *a = str1; *a; a++) {
    unsigned short flag = 0;
    for (const char *b = str2; *b; b++) {
      if (*a == *b) {
        flag = 1;
        break;
      }
    }
    if (flag == 1) {
      break;
    } else {
      counter++;
    }
  }

  return counter;
}

// 14 Searches an internal array for the error number errnum and returns a
// pointer to an error message string. You need to declare macros containing
// arrays of error messages for mac and linux operating systems. Error
// descriptions are available in the original library. Checking the current OS
// is carried out using directives.
char *s21_strerror(int errnum) {
  static char errorstr[256];
  char *p = errorstr;

#if defined(__APPLE__) || defined(__MACH__)
  s21_sprintf(errorstr, "Unknown error: %d", errnum);
#elif defined(__linux__) || defined(__unix__)
  s21_sprintf(errorstr, "Unknown error %d", errnum);
#endif

  if (errnum >= 0 && errnum < S21_ERRORLIST) {
    p = (char *)s21_errors[errnum];
  }

  return p;
}

// 15 Computes the length of the string str up to but not including the
// terminating null character.
s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;

  for (; str[len]; len++) {
    continue;
  }

  return len;
}

// 16 Finds the first character in the string str1 that matches any character
// specified in str2.
char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;

  for (const char *a = str1; *a; a++) {
    for (const char *b = str2; *b; b++) {
      if (*a == *b) {
        res = (char *)a;
        break;
      }
    }

    if (res != s21_NULL) {
      break;
    }
  }

  return res;
}

// 17 Searches for the last occurrence of the character c (an unsigned char) in
// the string pointed to by the argument str.
char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  s21_size_t len = s21_strlen(str);

  for (int i = len; i >= 0; i--) {
    if (str[i] == c) {
      res = ((char *)str) + i;
      break;
    }
  }

  return res;
}

// 18 Calculates the length of the initial segment of str1 which consists
// entirely of characters in str2.
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t counter = 0;

  for (const char *a = str1; *a; a++) {
    unsigned short flag = 0;
    for (const char *b = str2; *b; b++) {
      if (*a == *b) {
        counter++;
        flag = 1;
        break;
      }
    }
    if (flag != 1) {
      break;
    }
  }

  return counter;
}

// 19 Finds the first occurrence of the entire string needle (not including the
// terminating null character) which appears in the string haystack.
char *s21_strstr(const char *haystack, const char *needle) {
  char *res = s21_NULL;
  s21_size_t l1, l2;

  l1 = s21_strlen(haystack);
  l2 = s21_strlen(needle);

  while (l1 >= l2) {
    l1--;
    if (!s21_memcmp(haystack, needle, l2)) {
      res = (char *)haystack;
      break;
    }
    haystack++;
  }

  return res;
}

// 20 Breaks string str into a series of tokens separated by delim.
char *s21_strtok(char *str, const char *delim) {
  static char *p = s21_NULL;

  while (1) {
    if (str) {
      p = str;
    }
    if (!p) {
      str = s21_NULL;
      break;
    }
    str = p + s21_strspn(p, delim);
    p = str + s21_strcspn(str, delim);
    if (p == str) {
      p = 0;
      str = p;
      break;
    }
    if (*p) {
      *p = 0;
      p = p + 1;
    } else {
      p = 0;
    }
    break;
  }

  return str;
}

// insert
// Returns a new string in which a specified string (str) is inserted at a
// specified index position (start_index) in the given string (src). In case of
// any error, return NULL
void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  char *res = s21_NULL;

  if (src != s21_NULL && str != s21_NULL) {
    s21_size_t src_len = s21_strlen(src);
    s21_size_t str_len = s21_strlen(str);
    s21_size_t new_len = src_len + str_len;

    if (src_len >= start_index) {
      res = (char *)malloc(sizeof(char) * new_len + 1);
    }

    if (res != s21_NULL) {
      for (s21_size_t i = 0, j = 0, m = 0; i < new_len; i++) {
        if (i >= start_index && j < str_len) {
          res[i] = str[j];
          j++;
        } else {
          res[i] = src[m];
          m++;
        }
      }
      res[new_len] = '\0';
    }
  } else if (src && !str) {
    res = (char *)malloc(sizeof(char) * s21_strlen(src) + 1);
    if (res != s21_NULL) {
      s21_strcpy(res, src);
      res[s21_strlen(src)] = '\0';
    }
  }

  return res;
}

// to upper
// Returns a copy of string (str) converted to uppercase. In case of any error,
// return NULL
void *s21_to_upper(const char *str) {
  char *temp_str = s21_NULL;

  if (str != s21_NULL) {
    temp_str = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (temp_str != s21_NULL) {
      s21_strcpy(temp_str, str);
      for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
        if (temp_str[i] >= 97 && temp_str[i] <= 122) {
          temp_str[i] = temp_str[i] - 32;
        }
      }
    }
    temp_str[s21_strlen(str)] = '\0';
  }

  return temp_str;
}

// to lower
// Returns a copy of string (str) converted to lowercase. In case of any error,
// return NULL
void *s21_to_lower(const char *str) {
  char *temp_str = s21_NULL;

  if (str != s21_NULL) {
    temp_str = (char *)malloc((s21_strlen(str) + 1) * sizeof(char));
    if (temp_str != s21_NULL) {
      s21_strcpy(temp_str, str);
      for (s21_size_t i = 0; i <= s21_strlen(str); i++) {
        if (temp_str[i] >= 65 && temp_str[i] <= 90) {
          temp_str[i] = temp_str[i] + 32;
        }
      }
    }
    temp_str[s21_strlen(str)] = '\0';
  }

  return temp_str;
}

// trim
// Returns a new string in which all leading and trailing occurrences of a set
// of specified characters (trim_chars) from the given string (src) are removed.
// In case of any error, return NULL
void *s21_trim(const char *src, const char *trim_chars) {
  char *temp_str = s21_NULL;
  if (src != s21_NULL) {
    if (trim_chars != s21_NULL && *trim_chars) {
      temp_str = (char *)malloc((s21_strlen(src) + 1) * sizeof(char));
      if (temp_str != 0) {
        s21_strcpy(temp_str, src);
        rtrim(temp_str, trim_chars);
        ltrim(temp_str, trim_chars);
      }
    } else {
      temp_str = s21_trim(src, " \t\n\v\f\r");
    }
  }

  return temp_str;
}

void rtrim(char *temp_str, const char *trim_chars) {
  for (int i = s21_strlen(temp_str) - 1;
       i >= 0 && s21_strchr(trim_chars, temp_str[i]) != NULL; i--) {
    temp_str[i] = '\0';
  }
}

void ltrim(char *temp_str, const char *trim_chars) {
  while (temp_str[0] != '\0' && s21_strchr(trim_chars, temp_str[0]) != NULL) {
    s21_memmove(&temp_str[0], &temp_str[1], s21_strlen(temp_str));
  }
}

// atoi String to integer

int s21_atoi(char *str) {
  int res = 0;

  for (int i = 0; str[i] != '\0'; ++i) {
    res = res * 10 + str[i] - '0';
  }

  return res;
}

// itoa Integer to string

void swap(char *x, char *y) {
  char temp = *x;
  *x = *y;
  *y = temp;
}

char *reverse(char *buffer, int i, int j) {
  while (i < j) {
    swap(&buffer[i++], &buffer[j--]);
  }

  return buffer;
}

void s21_itoa(int64_t value, char *buffer, int base) {
  int64_t n = value;
  int i = 0;

  if (n < 0) {
    n *= -1;
  }

  while (n) {
    int64_t right = n % base;

    buffer[i++] = 48 + right;

    n = n / base;
  }

  if (i == 0) {
    buffer[i++] = '0';
  }

  if (value < 0) {
    buffer[i++] = '-';
  }

  buffer[i] = '\0';

  reverse(buffer, 0, i - 1);
}

void s21_uitoa(uint64_t value, char *buffer, int base) {
  uint64_t n = value;
  int i = 0;

  while (n) {
    uint64_t right = n % base;

    buffer[i++] = 48 + right;

    n = n / base;
  }

  if (i == 0) {
    buffer[i++] = '0';
  }

  buffer[i] = '\0';

  reverse(buffer, 0, i - 1);
}

// ftoa float to string
int s21_itoa_with_counter(int64_t x, char *buffer, int precision,
                          int neg_flag) {
  int counter = 0;
  int64_t n = x;

  if (n < 0) {
    n = x * -1;
  }

  while (n) {
    buffer[counter++] = (n % 10) + 48;
    n = n / 10;
  }

  if (counter == 0) {
    buffer[counter++] = '0';
  }

  if (neg_flag) {
    buffer[counter++] = '-';
  }

  while (counter < precision) {
    buffer[counter++] = '0';
  }

  reverse(buffer, 0, counter - 1);
  buffer[counter] = '\0';

  return counter;
}

void s21_ftoa(long double n, char *buffer, int precision) {
  char temp[SIZE];
  int neg_flag = 0;
  long double left = 0, right = modfl(n, &left);
  long double newn = roundl(n);

  if (precision == 0) {
    if (newn < 0) {
      newn *= -1;
    }
    if (newn > left) {
      left = newn;
    }
  }

  if (n < 0) {
    neg_flag = 1;
  }

  if (right < 0) {
    right *= -1;
  }

  int i = s21_itoa_with_counter(left, temp, 0, neg_flag);

  if (precision != 0) {
    if (left < 0) {
      left *= -1;
    }

    right = left * powl(10, precision) + right * powl(10, precision);
    right = roundl(right);
    right = right - left * powl(10, precision);

    if (right == powl(10, precision)) {
      left += 1;
      right = 0;
      s21_itoa_with_counter(left, buffer, 0, neg_flag);
    } else {
      s21_itoa_with_counter(left, buffer, 0, neg_flag);
    }

    neg_flag = 0;
    buffer[i] = '.';

    s21_itoa_with_counter(right, buffer + i + 1, precision, neg_flag);
  } else {
    s21_itoa_with_counter(left, buffer, 0, neg_flag);
  }
}
