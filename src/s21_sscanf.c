#include "s21_sscanf.h"

#include <stdio.h>
#include <stdlib.h>

#include "type.h"

_bool is_digit(char c) { return c <= '9' && c >= '0' ? TRUE : FALSE; }

int s21_skip(const char *string, const char *format, int *str_diss,
             int *form_diss) {
  int skip = 0;
  if (*string != *format) {
    skip = skip_space(format);
    format += skip;
    *form_diss += skip;
  }
  while (*string == *format && *string != '%') {
    string++;
    format++;
    (*form_diss)++;
    (*str_diss)++;
  }
  *str_diss += skip_space(string);
  *form_diss += skip_space(format);
  return 0;
}

int skip_space(const char *str) {
  int count = 0;
  while (*str == ' ' || *str == '\n' || *str == '\t') {
    count++;
    str++;
  }
  return count;
}

int len(const char *str) {
  int count = 0;
  while (*str != '\0') {
    count++;
    str++;
  }
  return count;
}

int get_pattern(const char *format, struct Pattern *patt) {
  int displacement = 0;
  if (*format == '%') {
    format++;
    displacement++;
    if (*format == '%') {
      patt->spec = PERC_SPEC;
      displacement++;
    } else {
      if (*format == '*') {
        patt->recording = FALSE;
        format++;
        displacement++;
      } else {
        patt->recording = TRUE;
      }
      if (is_digit(*format) == TRUE) {
        int size = 0;
        while (is_digit(*format) == TRUE) {
          size = *format - '0' + size * 10;
          format++;
          displacement++;
        }
        patt->width = size;
      } else {
        patt->width = 0;
      }
      switch (*format) {
        case 'l':
          patt->size_var = L_SIZE;
          format++;
          displacement++;
          break;
        case 'L':
          patt->size_var = L_BIG_SIZE;
          format++;
          displacement++;
          break;
        case 'h':
          patt->size_var = H_SIZE;
          format++;
          displacement++;
          break;
        default:
          patt->size_var = NO_SIZE;
          break;
      }
      switch (*format) {
        case 'c':
          patt->spec = C_SPEC;
          displacement++;
          break;
        case 'd':
          patt->spec = D_SPEC;
          displacement++;
          break;
        case 'i':
          patt->spec = I_SPEC;
          displacement++;
          break;
        case 'e':
          patt->spec = E_SPEC;
          displacement++;
          break;
        case 'E':
          patt->spec = E_BIG_SPEC;
          displacement++;
          break;
        case 'f':
          patt->spec = F_SPEC;
          displacement++;
          break;
        case 'g':
          patt->spec = G_SPEC;
          displacement++;
          break;
        case 'G':
          patt->spec = G_BIG_SPEC;
          displacement++;
          break;
        case 'o':
          patt->spec = O_SPEC;
          displacement++;
          break;
        case 's':
          patt->spec = S_SPEC;
          displacement++;
          break;
        case 'u':
          patt->spec = U_SPEC;
          displacement++;
          break;
        case 'x':
          patt->spec = X_SPEC;
          displacement++;
          break;
        case 'X':
          patt->spec = X_BIG_SPEC;
          displacement++;
          break;
        case 'p':
          patt->spec = P_SPEC;
          displacement++;
          break;
        case 'n':
          patt->spec = N_SPEC;
          displacement++;
          break;
        default:
          displacement = 0;
          patt->spec = ERROR_SPEC;
          break;
      }
    }
  }
  return displacement;
}

int s21_sscanf(const char *string, const char *format, ...) {
  int scanf_argc = -1;
  if (len(string) != skip_space(string)) {
    va_list scanf_arg;
    va_start(scanf_arg, format);
    scanf_argc = va_s21_sscanf(string, format, scanf_arg);
    va_end(scanf_arg);
  }
  return scanf_argc;
}

int read_double(const char *string, struct Pattern patt, long double *d) {
  int displacement = 0;
  char *buf;
  char *buf_w = (char *)malloc(sizeof(char) * 100);

  long double ld = 0.;
  if (patt.width != 0) {
    buf_w = (char *)realloc(buf_w, (sizeof(char) * patt.width));
    int i = 0;
    while (i < patt.width && string[i] != '\0') {
      buf_w[i] = string[i];
      i++;
    }
    char *buf_temp = buf_w;
    ld = strtold(buf_w, &buf_w);
    while (*string != *buf_w) {
      displacement++;
      string++;
    }
    buf_w = buf_temp;
  } else {
    ld = strtold(string, &buf);
    while (*string != *buf) {
      displacement++;
      string++;
    }
  }
  *d = ld;
  free(buf_w);
  return displacement;
}

int read_str(const char *string, struct Pattern patt, struct Buffer *buff) {
  int displacement = 0;
  if (*string != '\0') {
    _bool width_flag = FALSE;
    if (patt.width == 0) width_flag = TRUE;
    int size = patt.width != 0 ? patt.width : 100;
    buff->b_string = (char *)realloc(buff->b_string, (sizeof(char) * size));

    while (*string != ' ' && *string != '\n' && *string != '\t' &&
           *string != '\0' &&
           (patt.width > displacement || width_flag == TRUE)) {
      buff->b_string[displacement] = *string;
      string++;
      displacement++;
      if (size < displacement + 1) {
        size *= 1.5;
        buff->b_string = (char *)realloc(buff->b_string, (sizeof(char) * size));
      }
    }
    buff->b_string[displacement] = '\0';
  }
  return displacement;
}

int read_char(const char *string, char *c) {
  int displacement = 1;
  *c = *string;
  return displacement;
}

int read_percent(const char *string) {
  int displacement = 0;
  if (*string == '%') displacement = 1;
  return displacement;
}

int read_int(const char *string, struct Pattern patt, struct Buffer *buff,
             long int *i) {
  int displacement = 0;
  int width = 0;
  char c = *string;
  _bool flag = TRUE, width_flag = FALSE;
  if (patt.width == 0) width_flag = TRUE;
  if (c == '-') flag = FALSE;
  if (c == '-' || c == '+') {
    if (patt.width > width || width_flag == TRUE) {
      string++;
      displacement++;
      width++;
    }
  }
  *i = 0;
  while ((c = *string) <= '9' && c >= '0' &&
         (patt.width > width || width_flag == TRUE)) {
    buff->good_read = TRUE;
    displacement++;
    string++;
    width++;
    *i = c - '0' + *i * 10;
  }
  if (flag == FALSE) *i *= -1;
  return displacement;
}

int read_i_int(const char *string, struct Pattern patt, struct Buffer *buff) {
  int displacement = 0;
  unsigned long int answ = 0;
  char c = *string;
  int width = 0;
  _bool flag_z = TRUE, width_flag = FALSE;
  if (patt.width == 0) width_flag = TRUE;
  if (c == '-') flag_z = FALSE;
  if (c == '-' || c == '+') {
    if (patt.width > width || width_flag == TRUE) {
      string++;
      displacement++;
      width++;
    }
  }
  if (*string == '0' && (*(string + 1) == 'x' || *(string + 1) == 'X') &&
      (patt.width > width || width_flag == TRUE)) {
    if (width_flag == TRUE || patt.width - width > 1) {
      string += 2;
      displacement += 2;
      width += 2;
    } else {
      string++;
      displacement++;
      width++;
    }
    buff->good_read = TRUE;
    if (patt.width != 0) {
      patt.width -= width;
      if (patt.width > 0)
        displacement += read_u_int16(string, patt, buff, &answ);
    } else {
      displacement += read_u_int16(string, patt, buff, &answ);
    }

  } else if ((*string == '0') && (patt.width > width || width_flag == TRUE)) {
    string++;
    displacement++;
    width++;
    buff->good_read = TRUE;
    if (patt.width != 0) {
      patt.width -= width;
      if (patt.width > 0)
        displacement += read_u_int8(string, patt, buff, &answ);
    } else {
      displacement += read_u_int8(string, patt, buff, &answ);
    }
  } else {
    if (patt.width != 0) {
      patt.width -= width;
      if (patt.width > 0)
        displacement += read_u_int10(string, patt, buff, &answ);
    } else {
      displacement += read_u_int10(string, patt, buff, &answ);
    }
  }

  if (flag_z == FALSE) answ *= -1;
  buff->b_long_int = answ;
  return displacement;
}

int read_u_int8(const char *string, struct Pattern patt, struct Buffer *buff,
                unsigned long int *i) {
  int displacement = 0;
  char c = *string;
  int width = 0;
  _bool flag = TRUE, width_flag = FALSE;
  if (patt.width == 0) width_flag = TRUE;
  if (c == '-') flag = FALSE;
  if (c == '-' || c == '+') {
    if (patt.width > width || width_flag == TRUE) {
      string++;
      displacement++;
      width++;
    }
  }
  *i = 0;
  while ((c = *string) <= '7' && c >= '0' &&
         (patt.width > width || width_flag == TRUE)) {
    displacement++;
    string++;
    width++;
    buff->good_read = TRUE;
    *i = c - '0' + *i * 8;
  }
  if (flag == FALSE) *i *= -1;
  return displacement;
}

int read_u_int10(const char *string, struct Pattern patt, struct Buffer *buff,
                 unsigned long int *i) {
  int displacement = 0;
  char c = *string;
  int width = 0;
  _bool flag = TRUE, width_flag = FALSE;
  if (patt.width == 0) width_flag = TRUE;
  if (c == '-') flag = FALSE;
  if (c == '-' || c == '+') {
    if (patt.width > width || width_flag == TRUE) {
      string++;
      displacement++;
      width++;
    }
  }
  *i = 0;
  while ((c = *string) <= '9' && c >= '0' &&
         (patt.width > width || width_flag == TRUE)) {
    displacement++;
    string++;
    width++;
    buff->good_read = TRUE;
    *i = c - '0' + *i * 10;
  }
  if (flag == FALSE) *i *= -1;
  return displacement;
}

int read_u_int16(const char *string, struct Pattern patt, struct Buffer *buff,
                 unsigned long int *i) {
  int displacement = 0;
  int k = 0;
  char c = *string;
  int width = 0;
  _bool flag = TRUE, width_flag = FALSE, flag_z = TRUE;
  if (patt.width == 0) width_flag = TRUE;
  if (c == '-') flag_z = FALSE;
  if (c == '-' || c == '+') {
    if (patt.width > width || width_flag == TRUE) {
      string++;
      displacement++;
      width++;
    }
  }
  if (*string == '0' && (*(string + 1) == 'x' || *(string + 1) == 'X') &&
      (patt.width > width || width_flag == TRUE)) {
    if (width_flag == TRUE || patt.width - width > 1) {
      string += 2;
      displacement += 2;
      width += 2;
    } else {
      string++;
      displacement++;
      width++;
    }
    buff->good_read = TRUE;
  }
  *i = 0;
  while (flag == TRUE && (patt.width > width || width_flag == TRUE)) {
    c = *string;
    switch (c) {
      case 'A':
      case 'a':
        k = 10;
        break;
      case 'B':
      case 'b':
        k = 11;
        break;
      case 'C':
      case 'c':
        k = 12;
        break;
      case 'D':
      case 'd':
        k = 13;
        break;
      case 'E':
      case 'e':
        k = 14;
        break;
      case 'F':
      case 'f':
        k = 15;
        break;
      default:
        if (is_digit(c) == TRUE) {
          k = c - '0';
        } else {
          flag = FALSE;
        }
    }
    if (flag == TRUE) {
      displacement++;
      string++;
      width++;
      *i = k + *i * 16;
      buff->good_read = TRUE;
    }
  }
  if (flag_z == FALSE) *i *= -1;
  return displacement;
}

int read_string(const char *string, struct Pattern patt, struct Buffer *buff) {
  int displacement = 0;
  char c;
  long int li;
  long double ld;
  unsigned long int uli;
  switch (patt.spec) {
    case C_SPEC:
      displacement = read_char(string, &c);
      buff->b_char = c;
      break;
    case S_SPEC:
      displacement = read_str(string, patt, buff);
      break;
    case I_SPEC:
      displacement = read_i_int(string, patt, buff);
      switch (patt.size_var) {
        case H_SIZE:
          buff->b_short_int = buff->b_long_int;
          break;
        case NO_SIZE:
          buff->b_int = buff->b_long_int;
          break;
        default:
          break;
      }
      break;
    case D_SPEC:
      switch (patt.size_var) {
        case L_SIZE:
          displacement = read_int(string, patt, buff, &li);
          buff->b_long_int = li;
          break;
        case H_SIZE:
          displacement = read_int(string, patt, buff, &li);
          buff->b_short_int = li;
          break;
        case NO_SIZE:
          displacement = read_int(string, patt, buff, &li);
          buff->b_int = li;
          break;
        default:
          break;
      }
      break;
    case E_SPEC:
    case E_BIG_SPEC:
    case F_SPEC:
    case G_SPEC:
    case G_BIG_SPEC:
      switch (patt.size_var) {
        case L_SIZE:
          displacement = read_double(string, patt, &ld);
          buff->b_double = ld;
          break;
        case L_BIG_SIZE:
          displacement = read_double(string, patt, &ld);
          buff->b_long_double = ld;
          break;
        default:
          displacement = read_double(string, patt, &ld);
          buff->b_float = ld;
          break;
      }
      break;
    case O_SPEC:
      switch (patt.size_var) {
        case L_SIZE:
          displacement = read_u_int8(string, patt, buff, &uli);
          buff->b_u_long_int = uli;
          break;
        case H_SIZE:
          displacement = read_u_int8(string, patt, buff, &uli);
          buff->b_u_short_int = uli;
          break;
        case NO_SIZE:
          displacement = read_u_int8(string, patt, buff, &uli);
          buff->b_u_int = uli;
          break;
        default:
          break;
      }
      break;
    case U_SPEC:
      switch (patt.size_var) {
        case L_SIZE:
          displacement = read_u_int10(string, patt, buff, &uli);
          buff->b_u_long_int = uli;
          break;
        case H_SIZE:
          displacement = read_u_int10(string, patt, buff, &uli);
          buff->b_u_short_int = uli;
          break;
        case NO_SIZE:
          displacement = read_u_int10(string, patt, buff, &uli);
          buff->b_u_int = uli;
          break;
        default:
          break;
      }
      break;
    case X_SPEC:
    case X_BIG_SPEC:
      switch (patt.size_var) {
        case L_SIZE:
          displacement = read_u_int16(string, patt, buff, &uli);
          buff->b_u_long_int = uli;
          break;
        case H_SIZE:
          displacement = read_u_int16(string, patt, buff, &uli);
          buff->b_u_short_int = uli;
          break;
        case NO_SIZE:
          displacement = read_u_int16(string, patt, buff, &uli);
          buff->b_u_int = uli;
          break;
        default:
          break;
      }
      break;
    case P_SPEC:
      displacement = read_u_int16(string, patt, buff, &uli);
      buff->b_u_long_int = uli;
      break;
    case N_SPEC:

      break;
    case PERC_SPEC:
      displacement = read_percent(string);
      break;
    default:
      break;
  }
  return displacement;
}

int va_s21_sscanf(const char *string, const char *format, va_list scanf_arg) {
  int form_diss = 0;
  int str_diss = 0;
  struct Pattern patt;
  struct Buffer buff;
  buff.good_read = FALSE;
  buff.counter = 0;
  buff.b_string = (char *)malloc(sizeof(char) * 100);
  int form_diss_global = 0;
  int str_diss_global = 0;
  s21_skip(string, format, &str_diss_global, &form_diss_global);
  char *c;
  long int *li;
  short int *si;
  int *i;
  unsigned long int *uli;
  unsigned short int *usi;
  unsigned int *ui;

  double *d;
  long double *ld;
  float *f;

  while (
      (form_diss = get_pattern(format + form_diss_global, &patt)) > 0 &&
      (((str_diss = read_string(string + str_diss_global, patt, &buff)) > 0) ||
       (patt.spec == N_SPEC))) {
    form_diss_global += form_diss;
    str_diss_global += str_diss;
    s21_skip(string + str_diss_global, format + form_diss_global,
             &str_diss_global, &form_diss_global);
    if (patt.recording == TRUE) {
      switch (patt.spec) {
        case C_SPEC:
          c = (char *)va_arg(scanf_arg, char *);
          *c = buff.b_char;
          buff.counter++;
          break;
        case S_SPEC:
          c = (char *)va_arg(scanf_arg, char *);
          int iter = 0;
          while (buff.b_string[iter] != '\0') {
            c[iter] = buff.b_string[iter];
            iter++;
          }
          c[iter] = '\0';
          buff.counter++;
          break;
        case D_SPEC:
        case I_SPEC:
          switch (patt.size_var) {
            case L_SIZE:
              li = (long int *)va_arg(scanf_arg, long int *);
              if (buff.good_read == TRUE) {
                *li = buff.b_long_int;
                buff.counter++;
              }
              break;
            case H_SIZE:
              si = (short int *)va_arg(scanf_arg, short int *);
              if (buff.good_read == TRUE) {
                *si = buff.b_short_int;
                buff.counter++;
              }
              break;
            case NO_SIZE:
              i = (int *)va_arg(scanf_arg, int *);
              if (buff.good_read == TRUE) {
                *i = buff.b_int;
                buff.counter++;
              }
              break;
            default:
              break;
          }
          break;
        case E_SPEC:
        case E_BIG_SPEC:
        case F_SPEC:
        case G_SPEC:
        case G_BIG_SPEC:
          switch (patt.size_var) {
            case L_SIZE:
              d = (double *)va_arg(scanf_arg, double *);
              *d = buff.b_double;
              buff.counter++;
              break;
            case L_BIG_SIZE:
              ld = (long double *)va_arg(scanf_arg, long double *);
              *ld = buff.b_long_double;
              buff.counter++;
              break;
            case NO_SIZE:
              f = (float *)va_arg(scanf_arg, float *);
              *f = buff.b_float;
              buff.counter++;
              break;
            default:
              break;
          }
          break;
        case O_SPEC:
        case U_SPEC:
        case X_SPEC:
        case X_BIG_SPEC:
          switch (patt.size_var) {
            case L_SIZE:
              uli = (unsigned long int *)va_arg(scanf_arg, unsigned long int *);
              if (buff.good_read == TRUE) {
                *uli = buff.b_u_long_int;
                buff.good_read = FALSE;
                buff.counter++;
              }
              break;
            case H_SIZE:
              usi =
                  (unsigned short int *)va_arg(scanf_arg, unsigned short int *);
              if (buff.good_read == TRUE) {
                *usi = buff.b_u_short_int;
                buff.good_read = FALSE;
                buff.counter++;
              }
              break;
            case NO_SIZE:
              ui = (unsigned int *)va_arg(scanf_arg, unsigned int *);
              if (buff.good_read == TRUE) {
                *ui = buff.b_u_int;
                buff.good_read = FALSE;
                buff.counter++;
              }
              break;
            default:
              break;
          }
          break;
        case P_SPEC:
          uli = (unsigned long int *)va_arg(scanf_arg, unsigned long int *);
          if (buff.good_read == TRUE) {
            *uli = buff.b_u_long_int;
            buff.good_read = FALSE;
            buff.counter++;
          }
          break;
        case N_SPEC:
          switch (patt.size_var) {
            case L_SIZE:
              uli = (unsigned long int *)va_arg(scanf_arg, unsigned long int *);
              *uli = str_diss_global;
              break;
            case H_SIZE:
              usi =
                  (unsigned short int *)va_arg(scanf_arg, unsigned short int *);
              *usi = str_diss_global;
              break;
            case NO_SIZE:
              ui = (unsigned int *)va_arg(scanf_arg, unsigned int *);
              *ui = str_diss_global;
              break;
            default:
              break;
          }
          break;
        case PERC_SPEC:
          break;
        default:
          break;
      }
    }
  }
  va_end(scanf_arg);
  if (buff.b_string != s21_NULL) {
    free(buff.b_string);
  }
  return buff.counter;
}
