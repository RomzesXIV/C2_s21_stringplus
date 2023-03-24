//
//  s21_sprintf.h
//  21_test
//
//  Created by mcbk on 09.11.2022.
//

#ifndef s21_sprintf_h
#define s21_sprintf_h
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#if defined(__APPLE__) || defined(__MACH__)
#define sys 1
#elif defined(__linux__)
#define sys 2
#endif

typedef struct {
  int align;  // -
  int sign;   // +
  int dot;    // .
  int zero;   // 0
  int width;
  int acc;
  int space;
  int h;
  int L;
  int l;
  int hash;  // #
} flags;

typedef struct {
  char* buffer;
  int pos;
  int size;
} _string;

typedef struct {
  int* buffer;
  int pos;
  int size;
} _vector;

int s21_sprintf(char* str, const char* format, ...);
void flag_init(flags* flags);
void sprint_d(flags* flags, int* counter, int flag_zero, char** str,
              _string* data);
void sprint_f(flags* flags, int* counter, int flag_zero, char** str,
              _string* data);
void sprint_e(flags* flags, int* counter, char** str, _string* data,
              long double val, int zero_flag, char specifier);
void sprint_g(flags* flags, int* counter, int flag_zero, char** str,
              _string* data, long double val, char specifier);
void get_int_from_char(const char** begin, flags* flags);
void my_itoa(long int value, _string* result, int base);
void my_itoa_u(long long unsigned int value, _string* result, int base);
void read_flags(flags* flags, const char** format);
void _string_init(_string* data);
void _vector_init(_vector* data);
void round_acc(_vector* vec);
void shuffle_str(_string* data);
void apply_acc_d(flags* flags, _string* data, int zero_flag);
void apply_width_d(flags* flags, _string* data, int zero_flag, int flag_d_f);
void my_dtos(long double val, _string* data, flags* flags, char specifier);
int my_dtoe(long double* val, int zero_flag);
int check_inf_nan(long double val, _string* data, flags* flags, char specifier);
void check_flags(long double val, flags* flags);
void update_acc(long double val, flags* flags, char specifier, char e_or_f,
                int zero_flag);
void sprint_o(flags* flags, int* counter, int flag_zero, char** str,
              _string* data);
void sprint_x(flags* flags, int* counter, int flag_zero, char** str,
              _string* data, char specifier);
void sprint_s(flags* flags, int* counter, char** str, va_list param);
void supp_d(flags* flags, va_list param, char** str, int* counter);
void supp_u(flags* flags, va_list param, char** str, int* counter);
void supp_f(flags* flags, va_list param, char** str, int* counter);
void supp_e(flags* flags, va_list param, char** str, int* counter,
            const char* format);
void supp_g(flags* flags, va_list param, char** str, int* counter,
            const char* format);
void supp_o(flags* flags, va_list param, char** str, int* counter);
void supp_x(flags* flags, va_list param, char** str, int* counter,
            const char* format);

void supp_p(flags* flags, va_list param, char** str, int* counter,
            const char* format);
#endif /* s21_sprintf_h */
