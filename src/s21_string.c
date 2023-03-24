//
//  s21_string.c
//  test
//
//  Created by Spencer Finnigan on 11/26/22.
//

#include "s21_string.h"

#include <stdio.h>

#include "type.h"
#define BUFF_SIZE 256

s21_size_t s21_strlen(const char *str) {
  s21_size_t len = 0;
  for (; str[len]; len++)
    ;
  return len;
}
// naiti simvol (pervoe vxogdenie)
void *s21_memchr(const void *str, int c, s21_size_t n) {
  unsigned char *ch = (unsigned char *)str;
  unsigned char *res = s21_NULL;
  while (n-- > 0) {
    if (*ch == c) {
      res = ch;
      break;
    }
    ch++;
  }
  return res;
}
// sravnenie strok (equals) v diapozone "n"
int s21_memcmp(const void *str1, const void *str2, s21_size_t n) {
  int res = 0;
  const unsigned char *ch1 = str1;
  const unsigned char *ch2 = str2;
  while (n-- > 0) {
    if (*ch1 != *ch2) {
      res = *ch1 - *ch2;
      break;
    }
    ch1++;
    ch2++;
  }
  return res;
}
// kopirovanie n-symvolov iz massiva "src", v massiv "dest"
void *s21_memcpy(void *dest, const void *src, s21_size_t n) {
  unsigned char *ch_dest = dest;
  const unsigned char *ch_src = src;
  while (n-- > 0) {
    *ch_dest++ = *ch_src++;
  }
  *ch_dest = '\0';
  return dest;
}
// bezopasnaa memcpy, isklychaet bagi pri perexleste pamRti
void *s21_memmove(void *dest, const void *src, s21_size_t n) {
  if (dest <= src) {
    s21_memcpy(dest, src, n);
  } else {
    unsigned char *ch_end_dest = dest + (n - 1);
    const unsigned char *ch_end_src = src + (n - 1);
    while (n-- > 0) {
      *ch_end_dest-- = *ch_end_src--;
    }
  }
  return dest;
}
// zapolnRet pervie n-symvolov simvolami "c"
void *s21_memset(void *str, int c, s21_size_t n) {
  char *ch = str;
  while (n-- > 0) {
    *ch++ = c;
  }
  return str;
}
// skleivaem stroki
char *s21_strcat(char *dest, const char *src) {
  s21_size_t len_src = s21_strlen(src);
  char *ch_end_dest = dest + (s21_strlen(dest));
  while (len_src-- > 0) {
    *ch_end_dest++ = *src++;
  }
  *ch_end_dest = '\0';
  return dest;
}
// skleivaem stroki s ogranicheniem kol-va simvolov
char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *ch_end_dest = dest + (s21_strlen(dest));
  while (n-- > 0 && *src != '\0') {
    *ch_end_dest++ = *src++;
  }
  *ch_end_dest = '\0';
  return dest;
}
// pervoe vxogdenie simvola v stroke
char *s21_strchr(const char *str, int c) {
  char *res = s21_NULL;
  while (*str != '\0') {
    if (*str == c) {
      res = (char *)str;
      break;
    }
    str++;
  }
  return res;
}
// sravnenie strok (equals)
int s21_strcmp(const char *str1, const char *str2) {
  for (; *str1 && *str1 == *str2; str1++, str2++)
    ;
  return *str1 - *str2;
}
// sravnenie strok (equals) v diapozone "n"
int s21_strncmp(const char *str1, const char *str2, s21_size_t n) {
  for (; *str1 && *str1 == *str2 && n > 0; str1++, str2++, n--)
    ;
  return *str1 - *str2;
}
// kopirovanie stroki iz "src" v "dest"
char *s21_strcpy(char *dest, const char *src) {
  char *ch_dest = dest;
  while (*src != '\0') {
    *ch_dest++ = *src++;
  }
  *ch_dest = '\0';
  return dest;
}
// kopirovanie stroki iz "src" v "dest" v zadannom diapozone "n"
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  char *ch_dest = dest;
  while (n > 0 && *src != '\0') {
    *ch_dest++ = *src++;
    n--;
  }
  *ch_dest = '\0';
  return dest;
}
// vichislenie dlini segmenta "str1" kyda ne vxodRt simvoli "str2"
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  for (s21_size_t i = 0; i < s21_strlen(str1); i++) {
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) {
        res = i;
        j = s21_strlen(str2);
        i = s21_strlen(str1);
      } else {
        res = s21_strlen(str1);
      }
    }
  }
  return res;
}
// vivod oshibok po ix nomery
char *s21_strerror(int errnum) {
  char *res = s21_NULL;

  // char str[250] = "Unknown error: ";
  if (errnum >= MIN_ERRLIST && errnum < MAX_ERRLIST) {
    res = (char *)s21_errlist[errnum];

  } else {
    static char tmp[250];
    if (MAX_ERRLIST == 134)
      s21_sprintf(tmp, "Unknown error %d", errnum);
    else if (MAX_ERRLIST == 107)
      s21_sprintf(tmp, "Unknown error: %d", errnum);
    res = tmp;
  }
  return res;
}
// ishet pervoe vxogdenie lybogo simvola "str2" v "str1"
char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(str1); i++) {
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if (str1[i] == str2[j]) {
        res = (char *)(str1 + i);
        j = s21_strlen(str2);
        i = s21_strlen(str1);
      }
    }
  }
  return res;
}
// ishet poslednee vxogdenie simvola v stroky
char *s21_strrchr(const char *str, int c) {
  char *res = s21_NULL;
  while (*str++) {
    if (*str == c) {
      res = (char *)str;
    }
  }
  return res;
}
// opredelRet dliny v str1 (pervoe vxogdenie) sootvetstvyyshey lybomy simvoly
// str2
s21_size_t s21_strspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  for (s21_size_t i = 0; i < s21_strlen(str1); i++) {
    res = 0;
    for (s21_size_t j = 0; j < s21_strlen(str2); j++) {
      if ((str1[i] == str2[j]) && i != (s21_strlen(str1) - 1)) {
        break;
      }
      if (str1[i] != str2[j]) {
        res++;
        if (res == s21_strlen(str2)) {
          res = i;
          j = s21_strlen(str2);
          i = s21_strlen(str1);
        }
      }
      if ((str1[i] == str2[j]) && i == (s21_strlen(str1) - 1)) {
        res = s21_strlen(str1) - 1;
      }
    }
  }
  return res;
}
// ishet pervoe vxogdenie "needle" (polnost'Y) v "haystack"
char *s21_strstr(const char *haystack, const char *needle) {
  s21_size_t j = 0;
  s21_size_t in = 0;
  char *start = s21_NULL;
  for (s21_size_t i = 0; i < s21_strlen(haystack); i++) {
    if (haystack[i] == needle[j]) {
      start = (char *)(haystack + i);
      in = i;
      while (haystack[i++] == needle[j++]) {
        if (needle[j] == '\0') {
          i = s21_strlen(haystack);
          break;
        }
        if (haystack[i] != needle[j]) {
          i = in;
          break;
        }
      }
    }
  }
  return start;
}
// parser stroki
char *s21_strtok(char *str, const char *delim) {
  static char *parser_position = s21_NULL;
  if (str) {
    parser_position = str;
    while (*parser_position && s21_strchr(delim, *parser_position)) {
      *parser_position = '\0';
      parser_position++;
    }
  }
  if (parser_position != s21_NULL) {
    if (*parser_position != '\0') {
      str = parser_position;
      while (*parser_position && !s21_strchr(delim, *parser_position))
        parser_position++;
      while (*parser_position && s21_strchr(delim, *parser_position)) {
        *parser_position = '\0';
        parser_position++;
      }
    } else {
      str = s21_NULL;
    }
  } else {
    str = s21_NULL;
  }
  return str;
}

void *to_upper(const char *str) {
  char *str_cp = s21_NULL;
  if (str) {
    str_cp = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
    s21_size_t i = 0;
    while (str[i] != '\0') {
      if (str[i] >= 'a' && str[i] <= 'z')
        str_cp[i] = str[i] - 32;
      else
        str_cp[i] = str[i];
      ++i;
    }
    str_cp[i] = '\0';
  }
  return str_cp;
}

void *to_lower(const char *str) {
  char *str_cp = s21_NULL;
  if (str) {
    str_cp = (char *)calloc(s21_strlen(str) + 1, sizeof(char));
    int i = 0;
    while (str[i] != '\0') {
      if (str[i] >= 'A' && str[i] <= 'Z')
        str_cp[i] = str[i] + 32;
      else
        str_cp[i] = str[i];
      ++i;
    }
    str_cp[i] = '\0';
  }
  return str_cp;
}

void *insert(const char *src, const char *str, s21_size_t start_index) {
  char *str_cp =
      (char *)calloc(s21_strlen(str) + s21_strlen(src) + 1, sizeof(char));

  if (start_index <= s21_strlen(src) && str_cp != s21_NULL) {
    s21_size_t i = 0;
    while (i < start_index) {
      str_cp[i] = src[i];
      ++i;
    }
    s21_size_t i_temp = i, j = 0;
    while (str[j] != '\0') {
      str_cp[i++] = str[j++];
    }
    while (src[i_temp] != '\0') {
      str_cp[i++] = src[i_temp++];
    }
    str_cp[i] = '\0';
  } else {
    if (str_cp != s21_NULL) free(str_cp);
    str_cp = s21_NULL;
  }
  return str_cp;
}

void *trim(const char *src, const char *trim_chars) {
  char *str_cp = s21_NULL;

  if (src != s21_NULL) {
    s21_size_t left_bound = 0, right_bound = 0, flag = 1;
    right_bound = s21_strlen(src) - 1;
    while (flag && left_bound != right_bound) {
      flag = 0;
      for (s21_size_t i = 0; i < s21_strlen(trim_chars); ++i) {
        if (src[left_bound] == trim_chars[i]) flag = 1;
      }
      if (flag) left_bound++;
    }
    flag = 1;
    while (flag && left_bound != right_bound) {
      flag = 0;
      for (s21_size_t i = 0; i < s21_strlen(trim_chars); ++i) {
        if (src[right_bound] == trim_chars[i]) flag = 1;
      }
      if (flag) right_bound--;
    }
    // printf("lb = %zu  rb = %zu", left_bound, right_bound);

    str_cp = calloc(right_bound - left_bound + 2, sizeof(char));
    if (str_cp) {
      int i_temp = 0;

      if (left_bound != right_bound) {
        for (s21_size_t i = left_bound; i <= right_bound; ++i)
          str_cp[i_temp++] = src[i];
      }
      str_cp[i_temp] = '\0';
    }
  }
  return str_cp;
}
