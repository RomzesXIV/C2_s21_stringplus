//
//  s21_sprintf.c
//  21_test
//
//  Created by mcbk on 09.11.2022.
//

#include "s21_sprintf.h"

#include <math.h>

#include "type.h"
#ifdef NAN
/* NAN is supported */
#endif
#ifdef INFINITY
/* INFINITY is supported */
#endif
#define SIZE 1024

int s21_sprintf(char* str, const char* format, ...) {
  int counter = 0;
  int flag;
  flags flags;
  flag_init(&flags);
  va_list param;
  va_start(param, format);
  while (*format) {
    if (*format != '%') {
      *(str++) = *(format++);
      ++counter;
    } else {
      flag = 1;
      while (flag) {
        ++format;
        read_flags(&flags, &format);
        if (*format == '*') {
          if (!flags.dot)
            flags.width = va_arg(param, int);
          else
            flags.acc = va_arg(param, int);
        } else if (*(format) == 'c') {
          int tmp = va_arg(param, int);
          if (!flags.align && flags.width > 1) {
            for (int i = 0; i < flags.width - 1; ++i) {
              *(str++) = ' ';
              ++counter;
            }
          }
          *(str++) = (char)tmp;
          ++counter;
          if (flags.align && flags.width > 1) {
            for (int i = 0; i < flags.width - 1; ++i) {
              *(str++) = ' ';
              ++counter;
            }
          }
          flag = 0;
          flag_init(&flags);
          ++format;
        } else if (*(format) == 's') {
          sprint_s(&flags, &counter, &str, param);
          flag_init(&flags);
          flag = 0;
          ++format;
        } else if (*(format) == 'd' || *(format) == 'i') {
          supp_d(&flags, param, &str, &counter);
          flag = 0;
          ++format;
        } else if (*(format) == 'u') {
          supp_u(&flags, param, &str, &counter);
          flag = 0;
          ++format;
        } else if (*(format) == 'f') {
          supp_f(&flags, param, &str, &counter);
          flag = 0;
          ++format;
        } else if (*(format) == 'e' || *(format) == 'E') {
          supp_e(&flags, param, &str, &counter, format);
          flag = 0;
          ++format;
        } else if (*(format) == 'g' || *(format) == 'G') {
          supp_g(&flags, param, &str, &counter, format);
          flag = 0;
          ++format;

        } else if (*(format) == 'o') {
          supp_o(&flags, param, &str, &counter);
          flag = 0;
          ++format;

        } else if (*(format) == 'X' || *(format) == 'x') {
          supp_x(&flags, param, &str, &counter, format);
          flag = 0;
          ++format;

        } else if (*(format) == 'p') {
          supp_p(&flags, param, &str, &counter, format);
          flag = 0;
          ++format;

        } else if (*(format) == 'n') {
          int* ptr;
          ptr = va_arg(param, int*);
          *ptr = counter;
          ++format;
          flag = 0;
          flag_init(&flags);
        } else if (*(format) == '%') {
          *(str++) = '%';
          ++counter;
          ++format;
          flag = 0;
          flag_init(&flags);
        }
      }
    }
  }
  va_end(param);
  *str = '\0';
  return counter;
}

void flag_init(flags* flags) {
  flags->align = 0;
  flags->sign = 0;
  flags->dot = 0;
  flags->zero = 0;
  flags->width = -1;
  flags->acc = -1;
  flags->space = 0;
  flags->h = 0;
  flags->l = 0;
  flags->L = 0;
  flags->hash = 0;
}

void _string_init(_string* data) {
  data->buffer = (char*)calloc(SIZE, sizeof(char));
  data->pos = 0;
  data->size = SIZE;
}

void _vector_init(_vector* data) {
  data->buffer = (int*)calloc(SIZE, sizeof(int));
  data->pos = 0;
  data->size = SIZE;
}

void get_int_from_char(const char** begin, flags* flags) {
  const char* ptr = *begin;
  while (*ptr >= '0' && *ptr <= '9') ++ptr;
  int counter = 0, temp = 0;
  do {
    temp += (*(--ptr) - 48) * pow(10, counter++);
  } while (ptr != *begin);
  if (flags->dot == 0)
    flags->width = temp;
  else
    flags->acc = temp;
  (*begin) += counter - 1;
}

void sprint_d(flags* flags, int* counter, int flag_zero, char** str,
              _string* data) {
  if (flags->zero == 1 && flags->align == 1) flags->zero = 0;
  if (flags->acc < 0 && flags->dot) flags->acc = 0;

  apply_acc_d(flags, data, flag_zero);
  if (data->pos < flags->width) apply_width_d(flags, data, flag_zero, 0);

  for (int i = 0; i < data->pos; ++i) {
    *((*str)++) = data->buffer[i];
    ++(*counter);
  }
}

void sprint_f(flags* flags, int* counter, int flag_zero, char** str,
              _string* data) {
  apply_width_d(flags, data, flag_zero, 1);

  for (int i = 0; i < data->pos; ++i) {
    *((*str)++) = data->buffer[i];
    ++(*counter);
  }
}
void sprint_e(flags* flags, int* counter, char** str, _string* data,
              long double val, int zero_flag, char specifier) {
  int exp = 0;
  if (val != INFINITY && val != -INFINITY) exp = my_dtoe(&val, zero_flag);

  my_dtos(val, data, flags, specifier);
  if (data->buffer[0] != 'n' && data->buffer[0] != 'i' &&
      data->buffer[1] != 'i' && data->buffer[0] != 'N' &&
      data->buffer[0] != 'I' && data->buffer[1] != 'I') {
    data->buffer[data->pos++] = specifier;
    if (exp < 0) {
      exp *= -1;
      data->buffer[data->pos++] = '-';
    } else {
      data->buffer[data->pos++] = '+';
    }
    if (exp < 10) data->buffer[data->pos++] = '0';
    _string temp;
    _string_init(&temp);
    my_itoa((long long)exp, &temp, 10);
    for (int i = 0; i < temp.pos; ++i) {
      data->buffer[data->pos++] = temp.buffer[i];
    }
    free(temp.buffer);
  }
  apply_width_d(flags, data, zero_flag, 1);

  for (int i = 0; i < data->pos; ++i) {
    *((*str)++) = data->buffer[i];
    ++(*counter);
  }
}

void sprint_g(flags* flags, int* counter, int flag_zero, char** str,
              _string* data, long double val, char specifier) {
  long double val_cp = val;
  int exp = my_dtoe(&val_cp, flag_zero);
  check_flags(val, flags);
  if (flags->acc == 0) flags->acc = 1;
  if (flags->acc > exp && exp >= -4) {
    flags->acc -= (exp + 1);
    update_acc(val, flags, specifier, 'f', flag_zero);
    my_dtos(val, data, flags, specifier);

    sprint_f(flags, counter, flag_zero, str, data);
  } else {
    flags->acc -= 1;
    update_acc(val, flags, specifier, 'e', flag_zero);
    sprint_e(flags, counter, str, data, val, flag_zero, specifier);
  }
}

void sprint_o(flags* flags, int* counter, int flag_zero, char** str,
              _string* data) {
  flags->sign = 0;
  flags->zero = 0;
  flags->space = 0;
  if (flags->acc < 0 && flags->dot) flags->acc = 0;
  if (flags->hash) {
    shuffle_str(data);
    data->buffer[data->pos++] = '0';
    shuffle_str(data);
  }
  apply_acc_d(flags, data, flag_zero);
  if (data->pos < flags->width) apply_width_d(flags, data, flag_zero, 0);

  for (int i = 0; i < data->pos; ++i) {
    *((*str)++) = data->buffer[i];
    ++(*counter);
  }
}

void sprint_x(flags* flags, int* counter, int flag_zero, char** str,
              _string* data, char specifier) {
  flags->sign = 0;
  flags->zero = 0;
  flags->space = 0;
  if (flags->acc < 0 && flags->dot) flags->acc = 0;

  apply_acc_d(flags, data, flag_zero);
  if (flags->hash || specifier == 'p') {
    shuffle_str(data);
    if (specifier == 'x' || specifier == 'X' || specifier == 'p')
      data->buffer[data->pos++] = 'x';
    data->buffer[data->pos++] = '0';
    if (specifier == 'X') {
      for (int i = 0; i < data->pos; ++i) {
        if (data->buffer[i] >= 'a' && data->buffer[i] <= 'z')
          data->buffer[i] -= 32;
      }
    }
    shuffle_str(data);
  }
  if (data->pos < flags->width) apply_width_d(flags, data, flag_zero, 0);

  for (int i = 0; i < data->pos; ++i) {
    *((*str)++) = data->buffer[i];
    ++(*counter);
  }
}

void sprint_s(flags* flags, int* counter, char** str, va_list param) {
  char* data = s21_NULL;
  wchar_t* data_t = s21_NULL;
  if (flags->l)
    data_t = va_arg(param, wchar_t*);
  else
    data = va_arg(param, char*);
  _string tmp;
  _string_init(&tmp);
  int i = 0;
  if (flags->dot && flags->acc < 0) flags->acc = 0;

  if (!flags->l) {
    while (*data != '\0' && (flags->acc < 0 || tmp.pos < flags->acc)) {
      tmp.buffer[tmp.pos++] = *(data++);
    }
  } else {
    while (*data_t != L'\0' && (flags->acc < 0 || tmp.pos < flags->acc)) {
      tmp.buffer[tmp.pos++] = (char)*(data_t++);
    }
  }
  if (!flags->align) {
    shuffle_str(&tmp);
  }
  for (; tmp.pos < flags->width;) tmp.buffer[tmp.pos++] = ' ';
  if (!flags->align) {
    shuffle_str(&tmp);
  }
  while (tmp.buffer[i] != '\0') {
    *((*str)++) = tmp.buffer[i++];
    ++(*counter);
  }

  free(tmp.buffer);
}

void shuffle_str(_string* data) {
  char *ptr1 = data->buffer, *ptr = &(data->buffer[data->pos - 1]);

  while (ptr1 < ptr) {
    char tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
}

void my_itoa(long int value, _string* result, int base) {
  char *ptr = result->buffer, *ptr1 = result->buffer;
  long int tmp_value;
  do {
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[35 + (tmp_value - value * base)];
    ++result->pos;
  } while (value);
  if (tmp_value < 0) {
    *ptr++ = '-';
    ++result->pos;
  }
  ptr--;
  while (ptr1 < ptr) {
    char tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
}
void my_itoa_u(long long unsigned int value, _string* result, int base) {
  char *ptr = result->buffer, *ptr1 = result->buffer;

  do {
    long long unsigned int tmp_value;
    tmp_value = value;
    value /= base;
    *ptr++ =
        "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxy"
        "z"[35 + (tmp_value - value * base)];
    ++result->pos;
  } while (value);

  ptr--;
  while (ptr1 < ptr) {
    char tmp_char = *ptr;
    *ptr-- = *ptr1;
    *ptr1++ = tmp_char;
  }
}

void read_flags(flags* flags, const char** format) {
  if ((**format >= '1' && **format <= '9') ||
      (flags->dot && **format >= '0' && **format <= '9')) {
    get_int_from_char(format, flags);
  } else if (**(format) == '-')
    flags->align = 1;
  else if (**(format) == '+')
    flags->sign = 1;
  else if (**(format) == ' ')
    flags->space = 1;
  else if (**(format) == '.')
    flags->dot = 1;
  else if (**(format) == '0')
    flags->zero = 1;
  else if (**(format) == 'l')
    flags->l = 1;
  else if (**(format) == 'h')
    flags->h = 1;
  else if (**(format) == 'L')
    flags->L = 1;
  else if (**(format) == '#')
    flags->hash = 1;
}

void apply_acc_d(flags* flags, _string* data, int zero_flag) {
  shuffle_str(data);
  if ((zero_flag < 0)) {
    --data->pos;
  }
  for (; data->pos < flags->acc;) data->buffer[data->pos++] = '0';
  if (flags->sign && zero_flag >= 0)
    data->buffer[data->pos++] = '+';
  else if (zero_flag < 0)
    data->buffer[data->pos++] = '-';
  else if (flags->space)
    data->buffer[data->pos++] = ' ';
  shuffle_str(data);
  if (flags->acc == 0 && zero_flag == 0 && flags->sign)
    data->pos = 1;
  else if (flags->acc == 0 && zero_flag == 0 && !flags->sign) {
    data->pos = 0;
  }
}

void apply_width_d(flags* flags, _string* data, int zero_flag, int flag_d_f) {
  if (!flags->align) shuffle_str(data);
  if (flags->zero && (flags->sign || zero_flag < 0 || flags->space) &&
      ((flags->acc < 0 && !flag_d_f) || flag_d_f)) {
    --data->pos;
    --flags->width;
  }
  for (; data->pos < flags->width;) {
    if (flags->zero && flags->acc <= 0)
      data->buffer[data->pos++] = '0';
    else
      data->buffer[data->pos++] = ' ';
  }
  if (flags->zero && flags->sign &&
      ((flags->acc < 0 && !flag_d_f) || flag_d_f) && zero_flag >= 0)
    data->buffer[data->pos++] = '+';
  else if (flags->zero && ((flags->acc < 0 && !flag_d_f) || flag_d_f) &&
           zero_flag < 0)
    data->buffer[data->pos++] = '-';
  else if (flags->zero && ((flags->acc < 0 && !flag_d_f) || flag_d_f) &&
           flags->space)
    data->buffer[data->pos++] = ' ';
  if (!flags->align) shuffle_str(data);
}

void round_acc(_vector* vec) {
  int flag = 1;
  int temp = vec->pos;
  while (flag && temp >= 1) {
    --temp;
    vec->buffer[temp] += 1;
    if (vec->buffer[temp] == 10)
      vec->buffer[temp] = 0;
    else
      flag = 0;
  }
}

void my_dtos(long double val, _string* data, flags* flags, char specifier) {
  if (flags->acc < 0 && flags->dot) flags->acc = 0;
  if (flags->acc < 0 && !flags->dot) flags->acc = 6;
  double int_part = 0;
  _vector vec;
  _vector_init(&vec);
  if (!check_inf_nan(val, data, flags, specifier)) {
    if (flags->acc > 0) {
      double float_part = modf(val, &int_part);
      if (float_part < 0) float_part *= -1;
      vec.buffer[vec.pos++] = 0;
      for (int i = 0; i < flags->acc; ++i) {
        float_part *= 10;
        vec.buffer[vec.pos++] = (int)float_part;
        float_part -= vec.buffer[vec.pos - 1];
      }
      int temp = ((int)(float_part * 10));
      if (temp >= 5) round_acc(&vec);
      if (vec.buffer[0] == 1) int_part += 1;
    } else {
      int_part = lround(val);
    }
    my_itoa((long long)int_part, data, 10);
    shuffle_str(data);
    if (1 / val == -INFINITY || (int_part == 0 && val < 0)) {
      data->buffer[data->pos++] = '-';
    } else if (flags->sign && val >= 0)
      data->buffer[data->pos++] = '+';
    else if (flags->space && val >= 0)
      data->buffer[data->pos++] = ' ';
    shuffle_str(data);
    if (flags->acc > 0 || flags->hash) {
      data->buffer[data->pos++] = '.';
      for (int i = 0; i < flags->acc; ++i) {
        int temp = vec.buffer[i + 1];
        temp += 48;
        data->buffer[data->pos++] = (char)temp;
      }
    }
  }
  free(vec.buffer);
}

int check_inf_nan(long double val, _string* data, flags* flags,
                  char specifier) {
  int result = 1;
  if (isnan(val) && specifier != 'E') {
    if (sys == 2) data->buffer[data->pos++] = '-';
    data->buffer[data->pos++] = 'n';
    data->buffer[data->pos++] = 'a';
    data->buffer[data->pos++] = 'n';
  } else if (isnan(val) && specifier == 'E') {
    data->buffer[data->pos++] = 'N';
    data->buffer[data->pos++] = 'A';
    data->buffer[data->pos++] = 'N';
  } else if (val == INFINITY && specifier != 'E') {
    flags->sign == 1 ? data->buffer[data->pos++] = '+' : 1;
    flags->space == 1 ? data->buffer[data->pos++] = ' ' : 1;
    data->buffer[data->pos++] = 'i';
    data->buffer[data->pos++] = 'n';
    data->buffer[data->pos++] = 'f';
  } else if (val == INFINITY && specifier == 'E') {
    flags->sign == 1 ? data->buffer[data->pos++] = '+' : 1;
    flags->space == 1 ? data->buffer[data->pos++] = ' ' : 1;
    data->buffer[data->pos++] = 'I';
    data->buffer[data->pos++] = 'N';
    data->buffer[data->pos++] = 'F';
  } else if (val == -INFINITY && specifier != 'E') {
    data->buffer[data->pos++] = '-';
    data->buffer[data->pos++] = 'i';
    data->buffer[data->pos++] = 'n';
    data->buffer[data->pos++] = 'f';
  } else if (val == -INFINITY && specifier == 'E') {
    data->buffer[data->pos++] = '-';
    data->buffer[data->pos++] = 'I';
    data->buffer[data->pos++] = 'N';
    data->buffer[data->pos++] = 'F';
  } else {
    result = 0;
  }
  return result;
}

void check_flags(long double val, flags* flags) {
  if (isnan(val)) {
    flags->sign = 0;
    flags->zero = 0;
  }
  if (val == INFINITY || val == -INFINITY) {
    flags->zero = 0;
  }
  if (flags->zero == 1 && flags->align == 1) flags->zero = 0;
  if (flags->acc < 0 && flags->dot) flags->acc = 0;
  if (flags->acc < 0 && !flags->dot) flags->acc = 6;
}

int my_dtoe(long double* val, int zero_flag) {
  int exp = 0;
  zero_flag < 0 ? * val *= -1.0 : 1;
  if (*val < 1 && *val > 0.0) {
    while (*val < 1) {
      *val *= 10.0;
      --exp;
    }
  } else if (*val >= 10 && *val != INFINITY && *val != -INFINITY) {
    while (*val >= 10) {
      *val /= 10;
      ++exp;
    }
  }
  zero_flag < 0 ? * val *= -1.0 : 1;

  return exp;
}

void update_acc(long double val, flags* flags, char specifier, char e_or_f,
                int zero_flag) {
  _string temp;
  _string_init(&temp);
  if (e_or_f == 'f')
    my_dtos(val, &temp, flags, specifier);
  else if (e_or_f == 'e')
    my_dtoe(&val, zero_flag);
  if (!flags->hash && temp.pos > 0) {
    int i = temp.pos - 1;
    while (i > 0 && temp.buffer[i] == '0') {
      flags->acc -= 1;
      --i;
    }
  }
  free(temp.buffer);
}
void type_conversion_d(long long* val, flags* flags) {
  if (flags->h && (*val > 32767 || *val < -32767)) {
    if (*val > 0) {
      while (*val > 32767 || *val < -32768) {
        *val -= 65536;
      }
    } else {
      while (*val > 32767 || *val < -32768) {
        *val += 65536;
      }
    }
  }
}

void supp_d(flags* flags, va_list param, char** str, int* counter) {
  long long val = 0;
  int flag_zero;  //=1 если val > 0, = 0 если val = 0, = -1 если val < 0
  if (flags->l)
    val = va_arg(param, long long);
  else
    val = (long long)va_arg(param, int);
  type_conversion_d(&val, flags);
  if (val > 0)
    flag_zero = 1;
  else if (val == 0)
    flag_zero = 0;
  else
    flag_zero = -1;
  _string data;
  _string_init(&data);
  my_itoa(val, &data, 10);
  sprint_d(flags, counter, flag_zero, str, &data);
  flag_init(flags);
  free(data.buffer);
}

void type_conversion_u(unsigned long long int* val, flags* flags) {
  if (flags->h && (*val > 65535)) {
    while (*val > 65535) {
      *val -= 65536;
    }
  }
}

void supp_u(flags* flags, va_list param, char** str, int* counter) {
  unsigned long long int val = 0;
  int flag_zero;  //=1 если val > 0, = 0 если val = 0, = -1 если val < 0
  if (flags->l)
    val = va_arg(param, unsigned long long int);
  else
    val = va_arg(param, unsigned int);
  type_conversion_u(&val, flags);
  if (val > 0)
    flag_zero = 1;
  else
    flag_zero = 0;
  flags->space = 0;
  flags->sign = 0;
  _string data;
  _string_init(&data);
  my_itoa_u(val, &data, 10);
  sprint_d(flags, counter, flag_zero, str, &data);
  flag_init(flags);
  free(data.buffer);
}

void supp_f(flags* flags, va_list param, char** str, int* counter) {
  long double val = 0;
  int flag_zero = 0;
  if (flags->L)
    val = va_arg(param, long double);
  else
    val = (long double)va_arg(param, double);
  _string data;
  _string_init(&data);
  my_dtos(val, &data, flags, 'f');
  if (val > 0)
    flag_zero = 1;
  else if (val == 0.0 && 1 / val != -INFINITY)
    flag_zero = 0;
  else
    flag_zero = -1;
  check_flags(val, flags);
  sprint_f(flags, counter, flag_zero, str, &data);
  flag_init(flags);
  free(data.buffer);
}

void supp_e(flags* flags, va_list param, char** str, int* counter,
            const char* format) {
  long double val = 0;
  char specifier = *(format);
  int flag_zero = 0;
  if (flags->L)
    val = va_arg(param, long double);
  else
    val = (long double)va_arg(param, double);
  _string data;
  _string_init(&data);
  if (val > 0)
    flag_zero = 1;
  else if (val == 0.0 && 1 / val != -INFINITY)
    flag_zero = 0;
  else if (val < 0.0) {
    flag_zero = -1;
  }
  check_flags(val, flags);
  sprint_e(flags, counter, str, &data, val, flag_zero, specifier);
  flag_init(flags);
  free(data.buffer);
}

void supp_g(flags* flags, va_list param, char** str, int* counter,
            const char* format) {
  long double val = 0;
  char specifier = *(format);
  if (specifier == 'g')
    specifier = 'e';
  else
    specifier = 'E';
  int flag_zero = 0;
  if (flags->L)
    val = va_arg(param, long double);
  else
    val = (long double)va_arg(param, double);
  _string data;
  _string_init(&data);
  if (val > 0)
    flag_zero = 1;
  else if (val == 0.0)
    flag_zero = 0;
  else if (val < 0.0) {
    flag_zero = -1;
  }
  check_flags(val, flags);
  sprint_g(flags, counter, flag_zero, str, &data, val, specifier);
  flag_init(flags);
  free(data.buffer);
}

void supp_o(flags* flags, va_list param, char** str, int* counter) {
  long long val = 0;
  int flag_zero = 0;
  val = va_arg(param, long long);
  _string data;
  _string_init(&data);
  my_itoa(val, &data, 8);
  if (val > 0)
    flag_zero = 1;
  else if (val == 0)
    flag_zero = 0;
  sprint_o(flags, counter, flag_zero, str, &data);
  flag_init(flags);
  free(data.buffer);
}
void supp_x(flags* flags, va_list param, char** str, int* counter,
            const char* format) {
  long long val = 0;
  int flag_zero = 0;
  char specifier = *(format);
  val = va_arg(param, long long);
  _string data;
  _string_init(&data);
  my_itoa(val, &data, 16);
  if (val > 0)
    flag_zero = 1;
  else if (val == 0)
    flag_zero = 0;
  sprint_x(flags, counter, flag_zero, str, &data, specifier);
  flag_init(flags);
  free(data.buffer);
}

void supp_p(flags* flags, va_list param, char** str, int* counter,
            const char* format) {
  long long val = 0;
  int flag_zero = 0;
  char specifier = *(format);
  val = va_arg(param, long long);
  _string data;
  _string_init(&data);
  my_itoa(val, &data, 16);
  if (val > 0)
    flag_zero = 1;
  else if (val == 0)
    flag_zero = 0;
  flags->acc = 0;
  sprint_x(flags, counter, flag_zero, str, &data, specifier);
  flag_init(flags);
  free(data.buffer);
}
