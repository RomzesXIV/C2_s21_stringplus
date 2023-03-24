//
//  main.c
//  21_test
//
//  Created by mcbk on 09.11.2022.
//

#include <check.h>
#include <stdio.h>

#include "s21_sprintf.h"
#include "s21_sscanf.h"
#include "s21_string.h"
#include "test_data.h"

//----------------------TEST SPRINTF----------------------
START_TEST(s21_chars_f) {
  char s21_buffer[256] = {0};
  char buffer[256] = {0};
  s21_sprintf(s21_buffer, "%%%% %c %s %c%s %c %s %s %s %s %s", 'a', test1, '\n',
              test2, '-', test3, test4, test5, test6, test7);
  sprintf(buffer, "%%%% %c %s %c%s %c %s %s %s %s %s", 'a', test1, '\n', test2,
          '-', test3, test4, test5, test6, test7);
  ck_assert_str_eq(s21_buffer, buffer);
}
END_TEST

START_TEST(s21_nums_f) {
  char s21_buffer[256] = {0};
  char buffer[256] = {0};
  s21_sprintf(s21_buffer,
              "%-2i %+5i % 4i %2i %4d %d %15d %-+15d %22u %5u %4u %3u", 101,
              -210, -0, '0', 101, -210, -0, '0', (unsigned int)101,
              (unsigned int)210, (unsigned int)-0, (unsigned int)'0');
  sprintf(buffer, "%-2i %+5i % 4i %2i %4d %d %15d %-+15d %22u %5u %4u %3u", 101,
          -210, -0, '0', 101, -210, -0, '0', (unsigned int)101,
          (unsigned int)210, (unsigned int)-0, (unsigned int)'0');
  ck_assert_str_eq(s21_buffer, buffer);
}
END_TEST

START_TEST(s21_nums2_f) {
  char s21_buffer[256] = {0};
  char buffer[256] = {0};

  s21_sprintf(s21_buffer, "%- 5li %-5hi %12hu %-4lu %hi %li %hi %li",
              (long int)125123123123, (short int)160, (unsigned short)101,
              (unsigned long)210, (short int)0, (long int)0, (short int)-25,
              (long int)-51);
  sprintf(buffer, "%- 5li %-5hi %12hu %-4lu %hi %li %hi %li",
          (long int)125123123123, (short int)160, (unsigned short)101,
          (unsigned long)210, (short int)0, (long int)0, (short int)-25,
          (long int)-51);
  ck_assert_str_eq(s21_buffer, buffer);
}
END_TEST

START_TEST(s21_nums3_f) {
  char s21_buffer[256] = {0};
  char buffer[256] = {0};
  s21_sprintf(s21_buffer, "%-+6.4f %-2.2lf %5.5f %f %f", 100.0, 0.01, 0.10,
              -12.0, 0.00001);
  sprintf(buffer, "%-+6.4f %-2.2f %5.5f %f %f", 100.0, 0.01, 0.10, -12.0,
          0.00001);
  ck_assert_str_eq(s21_buffer, buffer);

  char s21_buffer2[256] = {0};
  char buffer2[256] = {0};
  s21_sprintf(s21_buffer2, "%f %f %f %f %f %f", 0.0 / 0.0, 1.0 / 0.0, 0.0 / 1.0,
              1.0 / 0.0, -1.0 / 0.0, -0.0 / 1.0);
  sprintf(buffer2, "%f %f %f %f %f %f", 0.0 / 0.0, 1.0 / 0.0, 0.0 / 1.0,
          1.0 / 0.0, -1.0 / 0.0, -0.0 / 1.0);
  ck_assert_str_eq(s21_buffer2, buffer2);

  char s21_buffer3[256] = {0};
  char buffer3[256] = {0};
  s21_sprintf(s21_buffer3, "%lg %lG %#lg %le", 234243.234, 8427348.234, 123.0,
              155.2);
  sprintf(buffer3, "%lg %lG %#lg %le", 234243.234, 8427348.234, 123.0, 155.2);
  ck_assert_str_eq(s21_buffer3, buffer3);
}
END_TEST

START_TEST(test_printf_d) {
  char buff[100];
  char buff2[100];

  int f = s21_sprintf(buff2, "blblbblblc%c%+4d%+.0d", '$', 10000, 0);
  int s = sprintf(buff, "blblbblblc%c%+4d%+.0d", '$', 10000, 0);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "blblbblblc%c%+04d", '$', 10);
  s = sprintf(buff, "blblbblblc%c%+04d", '$', 10);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "blblbblblc%c%+-010d", '$', 10);
  s = sprintf(buff, "blblbblblc%c%+-10d", '$', 10);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "blblbblblc%c%+010d%5d%+5d", '$', 10, 0, -1);
  s = sprintf(buff, "blblbblblc%c%+010d%5d%+5d", '$', 10, 0, -1);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "blblbblblc%c%+2.5d", '$', 10);
  s = sprintf(buff, "blblbblblc%c%+2.5d", '$', 10);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "%+.5d %+6.5d %+.5d %+6.5d %-2d %-2.5d %-4.d", 10, 10,
                  -10, -10, 1, 10, 0);
  s = sprintf(buff, "%+.5d %+6.5d %+.5d %+6.5d %-2d %-2.5d %-4.d", 10, 10, -10,
              -10, 1, 10, 0);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "blblbblblc%c%+*.*d", '$', 2, 5, 10);
  s = sprintf(buff, "blblbblblc%c%+*.*d", '$', 2, 5, 10);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "%hd %hd", 32768, -10000000);
  s = sprintf(buff, "%hd %hd", (short)32768, (short)-10000000);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "%d %d", 2147483648, -21474836480);
  s = sprintf(buff, "%d %d", (int)2147483648, (int)-21474836480);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "%d %d", 2147483648, -21474836480);
  s = sprintf(buff, "%d %d", (int)2147483648, (int)-21474836480);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  f = s21_sprintf(buff2, "%hu %hu", 65536, -65536);
  s = sprintf(buff, "%hu %hu", (unsigned short)65536, (unsigned short)-65536);
  ck_assert_int_eq(f, s);
  ck_assert_str_eq(buff, buff2);
  //    f = s21_sprintf(buff2, "%lu", (long unsigned int) 18446744073709551615);
  //    s = sprintf(buff, "%lu", (long unsigned int) 18446744073709551615);
  //    ck_assert_int_eq(f, s);
  //    ck_assert_str_eq(buff, buff2);
}
END_TEST

START_TEST(test_printf_f) {
  char buff[100];
  char buff2[100];

  int f1 = s21_sprintf(buff2, "blblbblblc%c%+4f", '$', 10000.0);
  int s1 = sprintf(buff, "blblbblblc%c%+4f", '$', 10000.0);
  ck_assert_int_eq(f1, s1);
  ck_assert_str_eq(buff, buff2);
  int f2 = s21_sprintf(buff2, "%+4.f", 10000.0);
  int s2 = sprintf(buff, "%+4.f", 10000.0);
  ck_assert_int_eq(f2, s2);
  ck_assert_str_eq(buff, buff2);
  int f3 = s21_sprintf(buff2, "%+.f % .f %+0.f %- 4.5f %-+5.4f ", -10000.0,
                       -1.0, 5.54454545, 5.54454545, 5.54454545);
  int s3 = sprintf(buff, "%+.f % .f %+0.f %- 4.5f %-+5.4f ", -10000.0, -1.0,
                   5.54454545, 5.54454545, 5.54454545);
  ck_assert_int_eq(f3, s3);
  ck_assert_str_eq(buff, buff2);
  int f5 = s21_sprintf(buff2, "%+010.f % .f %+0.f %- 4.5f %-+5.4f ", -10000.0,
                       -1.0, 5.54454545, 5.9999999999, 5.54454545);
  int s5 = sprintf(buff, "%+010.f % .f %+0.f %- 4.5f %-+5.4f ", -10000.0, -1.0,
                   5.54454545, 5.9999999999, 5.54454545);
  ck_assert_int_eq(f5, s5);
  ck_assert_str_eq(buff, buff2);
}
END_TEST

START_TEST(test_printf_e) {
  char buff[200];
  char buff2[200];

  int f1 = s21_sprintf(buff2, "%4.4e %-3.5e %07e %+-.e ", 1000.0, -0.0000002,
                       0.0, 200e+100);
  int s1 = sprintf(buff, "%4.4e %-3.5e %07e %+-.e ", 1000.0, -0.0000002, 0.0,
                   200e+100);
  ck_assert_int_eq(f1, s1);
  ck_assert_str_eq(buff, buff2);
  int f2 = s21_sprintf(buff2, "%4.4E %-3.5E %07E %+-.E", 1000.0, -0.0000002,
                       0.0, 200e+100);
  int s2 = sprintf(buff, "%4.4E %-3.5E %07E %+-.E", 1000.0, -0.0000002, 0.0,
                   200e+100);
  ck_assert_int_eq(f2, s2);
  ck_assert_str_eq(buff, buff2);

  //   int f3 = s21_sprintf(buff2, "%LE %-E %E % E", (long double)0.0/0.0,
  //   0.0/0.0, -1.0/0.0, 1.0/0.0);
  //  int s3 = sprintf(buff, "%LE %-E %E % E", (long double)0.0/0.0, 0.0/0.0,
  //  -1.0/0.0, 1.0/0.0);
  //   ck_assert_int_eq(f3, s3);
  //   ck_assert_str_eq(buff, buff2);
}
END_TEST

START_TEST(test_printf_g) {
  char buff[200];
  char buff2[200];
  int f3 = s21_sprintf(buff2, "%#.0lg %lG %#lg %lg", 234243.234, 8427348.234,
                       123.0, 155.2);
  int s3 = sprintf(buff, "%#.0lg %lG %#lg %lg", 234243.234, 8427348.234, 123.0,
                   155.2);
  ck_assert_int_eq(f3, s3);
  ck_assert_str_eq(buff, buff2);
}
END_TEST

START_TEST(test_printf_o) {
  char buff[100];
  char buff2[100];

  int f1 = s21_sprintf(buff2, "%o %5o %-20lo %10.20lo %#10.20lo %-#20.10lo",
                       21341324, 0, (long)1234341, (long)123423141,
                       (long)1234123, (long)1234341);
  int s1 =
      sprintf(buff, "%o %5o %-20lo %10.20lo %#10.20lo %-#20.10lo", 21341324, 0,
              (long)1234341, (long)123423141, (long)1234123, (long)1234341);
  ck_assert_int_eq(f1, s1);
  ck_assert_str_eq(buff, buff2);
}
END_TEST

START_TEST(test_printf_x) {
  char buff[200];
  char buff2[200];

  int f1 = s21_sprintf(
      buff2, "%x %5x %-20lx %10.20lx %#10.20lx %-#20.10lx %#10.20lX %-#20.10lX",
      21341324, 0, (long)1234341, (long)123423141, (long)1234123, (long)1234341,
      (long)1234123, (long)1234341);
  int s1 = sprintf(
      buff, "%x %5x %-20lx %10.20lx %#10.20lx %-#20.10lx %#10.20lX %-#20.10lX",
      21341324, 0, (long)1234341, (long)123423141, (long)1234123, (long)1234341,
      (long)1234123, (long)1234341);
  ck_assert_int_eq(f1, s1);
  ck_assert_str_eq(buff, buff2);
}
END_TEST

START_TEST(test_printf_p_n) {
  char buff[200];
  char buff2[200];
  int val1 = 10;
  int val2, val3;
  int f1 = s21_sprintf(buff2, "%-20p %n", &val1, &val2);
  int s1 = sprintf(buff, "%-20p %n", &val1, &val3);
  ck_assert_int_eq(f1, s1);
  ck_assert_int_eq(val2, val3);
  ck_assert_str_eq(buff, buff2);
}
END_TEST

START_TEST(test_printf_s_c) {
  char data[100];
  char data1[100];
  sprintf(data, "|%32s|\n", "111");
  s21_sprintf(data1, "|%32s|\n", "111");
  ck_assert_str_eq(data, data1);
  sprintf(data, "%10c %-10c", 'a', 'b');
  s21_sprintf(data1, "%10c %-10c", 'a', 'b');
  ck_assert_str_eq(data, data1);
  sprintf(data, "|%32s|\n", "abc");
  s21_sprintf(data1, "|%32s|\n", "abc");
  ck_assert_str_eq(data, data1);
  int c = s21_sprintf(data, "|%.03s|\n", "hello");
  int d = sprintf(data1, "|%.03s|\n", "hello");
  ck_assert_int_eq(c, d);
  sprintf(data, "%ls", L"assasdsad");
  s21_sprintf(data1, "%ls", L"assasdsad");
  ck_assert_str_eq(data, data1);
}
END_TEST

Suite* sprintf_suite(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("sprintf");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_printf_d);

  tcase_add_test(tc_core, test_printf_f);

  tcase_add_test(tc_core, test_printf_e);

  tcase_add_test(tc_core, test_printf_g);

  tcase_add_test(tc_core, s21_chars_f);

  tcase_add_test(tc_core, s21_nums_f);

  tcase_add_test(tc_core, s21_nums2_f);

  tcase_add_test(tc_core, test_printf_o);

  tcase_add_test(tc_core, test_printf_x);

  tcase_add_test(tc_core, test_printf_p_n);

  tcase_add_test(tc_core, s21_nums3_f);
  tcase_add_test(tc_core, test_printf_s_c);
  suite_add_tcase(s, tc_core);
  return s;
}
//-----------------TEST to_upper(lower) trim insert---------------
START_TEST(test_upper_lower) {
  char* buff = "ASDFGHJK1234!@#$";
  char* buff2 = "asdfghjk1234!@#$";
  char* buff3 = to_lower(buff);
  ck_assert_str_eq(buff2, buff3);
  free(buff3);
  buff3 = to_upper(buff2);
  ck_assert_str_eq(buff, buff3);
  free(buff3);
  buff2 = s21_NULL;
  buff3 = to_upper(buff2);
  ck_assert_ptr_null(buff3);
  buff2 = s21_NULL;
  buff3 = to_lower(buff2);
  ck_assert_ptr_null(buff3);
  buff3 = to_upper("");
  ck_assert_str_eq("", buff3);
  free(buff3);
  buff3 = to_lower("");
  ck_assert_str_eq("", buff3);
  free(buff3);
}
END_TEST

START_TEST(test_insert) {
  char* buff = "0123456789";
  char* buff2 = "9999";
  char* buff3 = insert(buff, buff2, 0);
  ck_assert_str_eq("99990123456789", buff3);
  free(buff3);
  buff3 = insert(buff, buff2, 2);
  ck_assert_str_eq("01999923456789", buff3);
  free(buff3);
  buff3 = insert(buff, buff2, 25);
  ck_assert_ptr_null(buff3);
}
END_TEST

START_TEST(test_trim) {
  char* buff = "     ''''asdfADASSA5522 ASasdaspqp112212''''";
  char* buff2 = " '2";
  char* buff3 = trim(buff, buff2);
  ck_assert_str_eq("asdfADASSA5522 ASasdaspqp11221", buff3);
  free(buff3);
  buff = "                   ";
  buff2 = " ";
  buff3 = trim(buff, buff2);
  ck_assert_str_eq("", buff3);
  free(buff3);
  buff = s21_NULL;
  buff2 = " ";
  buff3 = trim(buff, buff2);
  ck_assert_ptr_null(buff3);
}
END_TEST

Suite* additional_func_suite(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("additional_func");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_upper_lower);
  tcase_add_test(tc_core, test_insert);
  tcase_add_test(tc_core, test_trim);
  suite_add_tcase(s, tc_core);
  return s;
}

START_TEST(test_memchr) {
  const char* buff = "ASDFGHJK1234!@#$";
  char* buff2 = s21_memchr(buff, 'G', 5);
  char* buff3 = memchr(buff, 'G', 5);
  ck_assert_ptr_eq(buff2, buff3);
  ck_assert_str_eq(buff2, buff3);
  buff2 = s21_memchr(buff, 'G', 4);
  ck_assert_ptr_null(buff2);
  buff2 = s21_memchr("", 'G', 5);
  ck_assert_ptr_null(buff2);
  buff2 = s21_memchr(buff, '\0', 25);
  buff3 = memchr(buff, '\0', 25);
  ck_assert_ptr_eq(buff2, buff3);
  ck_assert_str_eq(buff2, buff3);
}
END_TEST

START_TEST(test_memcmp) {
  const char* buff = "ASDFGHJK1234!@#$";
  const char* buff1 = "ASDFGHJK1234!@#$";
  ck_assert_int_eq(memcmp(buff, buff1, 0), s21_memcmp(buff, buff1, 0));
  ck_assert_int_eq(memcmp(buff, buff1, 10), s21_memcmp(buff, buff1, 10));
  buff = " ";
  buff1 = "ASDFGHJK1234!@#$";
  ck_assert_int_eq(memcmp(buff, buff1, 0), s21_memcmp(buff, buff1, 0));
  ck_assert_int_eq(memcmp(buff, buff1, 10), s21_memcmp(buff, buff1, 10));
  buff = "";
  buff1 = "";
  ck_assert_int_eq(memcmp(buff, buff1, 0), s21_memcmp(buff, buff1, 0));
  ck_assert_int_eq(memcmp(buff, buff1, 10), s21_memcmp(buff, buff1, 10));

  buff = "ASDFGHJK1234!@#$/0asd";
  buff1 = "A/0SDFGHJK1234!@#$";
  ck_assert_int_eq(memcmp(buff, buff1, 100), s21_memcmp(buff, buff1, 100));
}
END_TEST

START_TEST(test_memcpy) {
  char str1[20] = "1112151ergergfg515";
  char str2[20] = "                    ";
  char str3[20] = "%hf*-5";
  char str4[20] = "                    ";
  char str5[30] = "";
  char str6[] = "4444";
  char str7[] = "123\0123";
  ck_assert_str_eq(s21_memcpy(str1, str2, 4), memcpy(str1, str2, 4));
  ck_assert_str_eq(s21_memcpy(str3, str4, 5), memcpy(str3, str4, 5));
  ck_assert_str_eq(s21_memcpy(str5, str6, 4), memcpy(str5, str6, 4));
  ck_assert_str_eq(s21_memcpy(str5, str7, 5), memcpy(str5, str7, 5));
}
END_TEST

START_TEST(test_memmove) {
  char str1[] = "11werwer15";
  char str2[s21_strlen(str1)];
  char str3[] = "s_21\n\t";
  char str4[s21_strlen(str3)];
  ck_assert_str_eq(s21_memmove(str2, str1, s21_strlen(str1)),
                   memmove(str2, str1, s21_strlen(str1)));
  ck_assert_str_eq(s21_memmove(str3, str4, s21_strlen(str3)),
                   memmove(str3, str4, s21_strlen(str3)));
}
END_TEST

START_TEST(test_memset) {
  char str[16] = "ASDFGHJK1234";
  ck_assert_str_eq(memset(str, 'a', 1), s21_memset(str, 'a', 1));
  ck_assert_str_eq(memset(str, '\0', 10), s21_memset(str, '\0', 10));
  ck_assert_str_eq(memset(str, 'k', 5), s21_memset(str, 'k', 5));
}
END_TEST

START_TEST(test_strcat) {
  char str1[30] = "what's go";
  char str11[30] = "ing on";
  char str2[30] = "Car";
  char str12[30] = "aaamba";
  ck_assert_str_eq(strcat(str1, str11), s21_strcat(str1, str11));
  ck_assert_str_eq(strcat(str2, str12), s21_strcat(str2, str12));
  char str001[30] = "opa";
  char str0011[30] = "popa";
  ck_assert_str_eq(strcat(str001, str0011), s21_strcat(str001, str0011));
}
END_TEST

START_TEST(test_strncat) {
  char str14[30] = "what's go";
  char str15[30] = "ing on";
  char str16[30] = "Car";
  char str17[30] = "aaamba";
  ck_assert_str_eq(strncat(str14, str15, 5), s21_strncat(str14, str15, 5));
  ck_assert_str_eq(strncat(str16, str17, 3), s21_strncat(str16, str17, 4));
}
END_TEST

START_TEST(test_strchr) {
  char str24[30] = "what's going on";
  ck_assert_str_eq(strchr(str24, 't'), s21_strchr(str24, 't'));
}
END_TEST

START_TEST(test_strcmp) {
  char str25[50] = "1112151515";
  char str26[50] = "11121sdfsdf";
  char str27[50] = "1112dasdasda12312sdas5";
  char str28[50] = "1112dasdasda12312sdas5";
  ck_assert_int_eq(strcmp(str25, str26), s21_strcmp(str25, str26));
  ck_assert_int_eq(strcmp(str27, str28), s21_strcmp(str27, str28));
}
END_TEST

START_TEST(test_strncmp) {
  char str29[50] = "1112151515";
  char str30[50] = "11121sdfsdf";
  char str31[50] = "1112d&*&a12312sdas5";
  char str32[50] = "1112d&*&a12312sdas5";
  ck_assert_int_eq(strncmp(str29, str30, 10), s21_strncmp(str29, str30, 10));
  ck_assert_int_eq(strncmp(str29, str30, 3), s21_strncmp(str29, str30, 3));
  ck_assert_int_eq(strncmp(str31, str32, 10), s21_strncmp(str31, str32, 10));
}
END_TEST

START_TEST(test_strcpy) {
  char str33[50] = "1112151ergergfg515";
  char str34[s21_strlen(str33)];
  ck_assert_str_eq(strcpy(str34, str33), s21_strcpy(str34, str33));
  char str333[50] = "1112151\0";
  char str344[50] = "ssssdddddfffffggggg1231231231231";
  ck_assert_str_eq(strcpy(str344, str333), s21_strcpy(str344, str333));
}
END_TEST

START_TEST(test_strncpy) {
  char str35[50] = "1112151ergergfg515";
  char str36[s21_strlen(str35)];
  ck_assert_str_eq(strncpy(str36, str35, 5), s21_strncpy(str36, str35, 5));
  char str351[50] = "1112151\0";
  char str361[50] = "ssssdddddfffffggggg1231231231231";
  ck_assert_str_eq(strncpy(str361, str351, 4), s21_strncpy(str361, str351, 4));
}
END_TEST

START_TEST(test_strcspn) {
  char str37[50] = "11121s5151s5";
  char str38[50] = "ddds";
  ck_assert_int_eq(strcspn(str37, str38), s21_strcspn(str37, str38));
  char str39[50] = "11121s5151s5";
  char str40[50] = "ddd";
  ck_assert_int_eq(strcspn(str39, str40), s21_strcspn(str39, str40));
}
END_TEST

START_TEST(test_strerror) {
  ck_assert_str_eq(strerror(0), s21_strerror(0));
  ck_assert_str_eq(strerror(55), s21_strerror(55));
  ck_assert_str_eq(strerror(-55), s21_strerror(-55));
}
END_TEST

START_TEST(test_strpbrk) {
  char str41[50] = "11121s5151s5";
  char str42[50] = "ddds";
  ck_assert_ptr_eq(strpbrk(str41, str42), s21_strpbrk(str41, str42));
  char str43[50] = "11121s5151s5";
  char str44[50] = "ddd";
  ck_assert_ptr_eq(strpbrk(str43, str44), s21_strpbrk(str43, str44));
}
END_TEST

START_TEST(test_strrchr) {
  char str45[50] = "what's going on";
  ck_assert_ptr_eq(strrchr(str45, 't'), s21_strrchr(str45, 't'));
  ck_assert_ptr_eq(strrchr(str45, 'c'), s21_strrchr(str45, 'c'));
}
END_TEST

START_TEST(test_strspn) {
  char str46[50] = "11121sssss1111110000111111111111111111111111111111";
  char str47[50] = "11121s";
  ck_assert_int_eq(strspn(str46, str47), s21_strspn(str46, str47));
  char str48[50] = "11121s5151s5";
  char str49[50] = "1dd";
  ck_assert_int_eq(strspn(str48, str49), s21_strspn(str48, str49));
  char str50[50] = "11121s5151s5";
  char str51[50] = "ddd";
  ck_assert_int_eq(strspn(str50, str51), s21_strspn(str50, str51));
}
END_TEST

START_TEST(test_strlen) {
  char str52[50] = "11121s5151s5";
  ck_assert_int_eq(strlen(str52), s21_strlen(str52));
}
END_TEST

START_TEST(test_strstr) {
  char str53[50] = "11121s5151s5";
  char str54[50] = "5151s";
  ck_assert_ptr_eq(strstr(str53, str54), s21_strstr(str53, str54));
  ck_assert_str_eq(strstr(str53, str54), s21_strstr(str53, str54));
  char str55[50] = "11121s5151s5";
  char str56[50] = "111";
  ck_assert_ptr_eq(strstr(str55, str56), s21_strstr(str55, str56));
  ck_assert_str_eq(strstr(str55, str56), s21_strstr(str55, str56));
}
END_TEST

START_TEST(test_strtok) {
  char str57[100] = "It's       not a     bug, it's a feature.";
  char str58[100] = "It's       not a     bug, it's a feature.";
  char* parser = " ,.";
  char* strOrigin = strtok(str57, parser);
  char* st21 = s21_strtok(str58, parser);
  while (strOrigin != s21_NULL) {
    strOrigin = strtok(s21_NULL, parser);
    st21 = s21_strtok(s21_NULL, parser);
    ck_assert_pstr_eq(strOrigin, st21);
  }
}
END_TEST

Suite* main_func_suite(void) {
  Suite* s;
  TCase* tc_core;
  s = suite_create("main_func");
  tc_core = tcase_create("core");
  tcase_add_test(tc_core, test_memchr);
  tcase_add_test(tc_core, test_memcmp);
  tcase_add_test(tc_core, test_memcpy);
  tcase_add_test(tc_core, test_memmove);
  tcase_add_test(tc_core, test_memset);
  tcase_add_test(tc_core, test_strcat);
  tcase_add_test(tc_core, test_strncat);
  tcase_add_test(tc_core, test_strchr);
  tcase_add_test(tc_core, test_strcmp);
  tcase_add_test(tc_core, test_strncmp);
  tcase_add_test(tc_core, test_strcpy);
  tcase_add_test(tc_core, test_strncpy);
  tcase_add_test(tc_core, test_strcspn);
  tcase_add_test(tc_core, test_strerror);
  tcase_add_test(tc_core, test_strpbrk);
  tcase_add_test(tc_core, test_strrchr);
  tcase_add_test(tc_core, test_strspn);
  tcase_add_test(tc_core, test_strlen);
  tcase_add_test(tc_core, test_strstr);
  tcase_add_test(tc_core, test_strtok);
  suite_add_tcase(s, tc_core);
  return s;
}
//---------------------TEST SSCANF-----------
START_TEST(sscanf_test_e) {
  float e1 = 0, e2 = 0;
  int r1 = 0, r2 = 0;

  r1 = sscanf("123e34", "%e", &e1);
  r2 = s21_sscanf("123e34", "%e", &e2);
  ck_assert_msg(e1 == e2, "float not equals");
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12e34", "%e", &e1);
  r2 = s21_sscanf("12e34", "%e", &e2);
  ck_assert_msg(e1 == e2, "float not equals");
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123.345e-34", "%9e", &e1);
  r2 = s21_sscanf("123.345e-34", "%9e", &e2);
  ck_assert_msg(e1 == e2, "float not equals");
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123.345e34", "%8e", &e1);
  r2 = s21_sscanf("123.345e34", "%8e", &e2);
  ck_assert_msg(e1 == e2, "float not equals");
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_l) {
  int r1 = 0, r2 = 0;
  unsigned long lu1 = 0, lu2 = 0;
  long ld1 = 0, ld2 = 0;

  r1 = sscanf("12345", "%lu", &lu1);
  r2 = s21_sscanf("12345", "%lu", &lu2);
  ck_assert_int_eq(lu1, lu2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12345", "%ld", &ld1);
  r2 = s21_sscanf("12345", "%ld", &ld2);
  ck_assert_int_eq(ld1, ld2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_L) {
  int r1 = 0, r2 = 0;
  long double Lf1 = 0, Lf2 = 0;

  r1 = sscanf("123.45", "%Lf", &Lf1);
  r2 = s21_sscanf("123.45", "%Lf", &Lf2);
  ck_assert_msg((int)Lf1 == (int)Lf2, "floats not equals");
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_u) {
  int r1 = 0, r2 = 0;
  unsigned u1 = 0, u2 = 0;

  r1 = sscanf("", "%u", &u1);
  r2 = s21_sscanf("", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-0x123", "%u", &u1);
  r2 = s21_sscanf("-0x123", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("+0x123", "%2u", &u1);
  r2 = s21_sscanf("+0x123", "%2u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("+123", "%u", &u1);
  r2 = s21_sscanf("+123", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("+z123", "%u", &u1);
  r2 = s21_sscanf("+z123", "%u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x12345", "%2u", &u1);
  r2 = s21_sscanf("0x12345", "%2u", &u2);
  ck_assert_int_eq(u1, u2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123.456", "%u", &u1);
  r2 = s21_sscanf("123.456", "%u", &u2);
  ck_assert_msg(u1 == u2, "floats not equals");
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_h) {
  int r1 = 0, r2 = 0;
  unsigned short hu1 = 0, hu2 = 0;

  r1 = sscanf("12345", "%hu", &hu1);
  r2 = s21_sscanf("12345", "%hu", &hu2);
  ck_assert_int_eq(hu1, hu2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_s) {
  int r1 = 0, r2 = 0;
  char s1[100], s2[100];

  r1 = sscanf("werty kraken", "%*s%2s", s1);
  r2 = s21_sscanf("werty kraken", "%*s%2s", s2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("\nwerty kraken", "%*s%10s", s1);
  r2 = s21_sscanf("\nwerty kraken", "%*s%10s", s2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("   werty kraken", "%*s%s", s1);
  r2 = s21_sscanf("   werty kraken", "%*s%s", s2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("   weartewrsthxffdtsrhdfghdfghdfghdfghdfghdfghfdgпывапывапывапы",
              "%s", s1);
  r2 = s21_sscanf(
      "   weartewrsthxffdtsrhdfghdfghdfghdfghdfghdfghfdgпывапывапывапы", "%s",
      s2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_f) {
  int r1 = 0, r2 = 0;
  float f1 = 0, f2 = 0;
  long double lf1 = 0, lf2 = 0;
  double d1 = 0, d2 = 0;

  r1 = sscanf("12e-3", "%f", &f1);
  r2 = s21_sscanf("12e-3", "%f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12e-3", "%lf", &d1);
  r2 = s21_sscanf("12e-3", "%lf", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12e-3", "%Lf", &lf1);
  r2 = s21_sscanf("12e-3", "%Lf", &lf2);
  ck_assert_int_eq(lf1, lf2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12e11", "%5f", &f1);
  r2 = s21_sscanf("12e11", "%5f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-12e-3", "%f", &f1);
  r2 = s21_sscanf("-12e-3", "%f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-12e-11", "%f", &f1);
  r2 = s21_sscanf("-12e-11", "%f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12e-111", "%5f", &f1);
  r2 = s21_sscanf("12e-111", "%5f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12e-111", "%6f", &f1);
  r2 = s21_sscanf("12e-111", "%6f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("+12e-3", "%f", &f1);
  r2 = s21_sscanf("+12e-3", "%f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12e+3", "%f", &f1);
  r2 = s21_sscanf("12e+3", "%f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12e3", "%4f", &f1);
  r2 = s21_sscanf("12e3", "%f4", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12e3", "%3f", &f1);
  r2 = s21_sscanf("12e3", "%3f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("2 12e3", "1 %4f", &f1);
  r2 = s21_sscanf("2 12e3", "1 %4f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-123.45", "%f", &f1);
  r2 = s21_sscanf("-123.45", "%f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-12.345", "%5f", &f1);
  r2 = s21_sscanf("-12.345", "%5f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("12.345", "%5f", &f1);
  r2 = s21_sscanf("12.345", "%5f", &f2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  int i1 = -1, i2 = -1;
  char c1, c2;
  f1 = 0;
  f2 = 0;
  r1 = sscanf("z 21", "%f%c %i", &f1, &c1, &i1);
  r2 = s21_sscanf("z 21", "%f%c %i", &f2, &c2, &i2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf(".z 21", "%f%c %i", &f1, &c1, &i1);
  r2 = s21_sscanf(".z 21", "%f%c %i", &f2, &c2, &i2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf(".z 21", "%3f%c %i", &f1, &c1, &i1);
  r2 = s21_sscanf(".z 21", "%3f%c %i", &f2, &c2, &i2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0.z 21", "%3f%c %i", &f1, &c1, &i1);
  r2 = s21_sscanf("0.z 21", "%3f%c %i", &f2, &c2, &i2);
  ck_assert_int_eq(f1, f2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_o) {
  int r1 = 0, r2 = 0;
  unsigned o1 = 0, o2 = 0, o3 = 0, o4 = 0, o5 = 0, o6 = 0;
  long unsigned int o7 = 0, o8 = 0, o9 = 0, o10 = 0;
  short unsigned int o11 = 0, o12 = 0;

  r1 = sscanf("12345678", "%3o", &o1);
  r2 = s21_sscanf("12345678", "%3o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("+12345678", "%3o", &o1);
  r2 = s21_sscanf("+12345678", "%3o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("012345678", "%3o", &o1);
  r2 = s21_sscanf("012345678", "%3o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-12345678", "%3o", &o1);
  r2 = s21_sscanf("-12345678", "%3o", &o2);
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123.456", "%o", &o1);
  r2 = s21_sscanf("123.456", "%o", &o2);
  ck_assert_uint_eq(o1, o2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("45 011 000 041", "%o%*o %o%o", &o1, &o3, &o5);
  r2 = s21_sscanf("45 011 000 041", "%o%*o %o%o", &o2, &o4, &o6);
  ck_assert_uint_eq(o1, o2);
  ck_assert_uint_eq(o3, o4);
  ck_assert_uint_eq(o5, o6);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("+36 -0123 -59", "%o %o %o", &o1, &o3, &o5);
  r2 = s21_sscanf("+36 -0123 -59", "%o %o %o", &o2, &o4, &o6);
  ck_assert_uint_eq(o1, o2);
  ck_assert_uint_eq(o3, o4);
  ck_assert_uint_eq(o5, o6);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("34 -123456 055", "%2o -%3o 456%02o", &o1, &o3, &o5);
  r2 = s21_sscanf("34 -123456 055", "%2o -%3o 456%02o", &o2, &o4, &o6);
  ck_assert_uint_eq(o1, o2);
  ck_assert_uint_eq(o3, o4);
  ck_assert_uint_eq(o5, o6);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x9 -0xa2 0xBa1", "%ho %lo %lo", &o11, &o7, &o9);
  r2 = s21_sscanf("0x9 -0xa2 0xBa1", "%ho %lo %lo", &o12, &o8, &o10);
  ck_assert_uint_eq(o11, o12);
  ck_assert_uint_eq(o7, o8);
  ck_assert_uint_eq(o9, o10);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("10 12345678", "%ho %lo", &o11, &o7);
  r2 = s21_sscanf("10 12345678", "%ho %lo", &o12, &o8);
  ck_assert_uint_eq(o11, o12);
  ck_assert_uint_eq(o7, o8);
  ck_assert_uint_eq(o9, o10);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_x) {
  int r1 = 0, r2 = 0;
  unsigned x1 = 0, x2 = 0;
  unsigned x3 = 0, x4 = 0;
  unsigned short x5 = 0, x6 = 0;
  unsigned long x7 = 0, x8 = 0;

  r1 = sscanf("abcdef", "%x", &x1);
  r2 = s21_sscanf("abcdef", "%x", &x2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("abcdef", "%hx", &x5);
  r2 = s21_sscanf("abcdef", "%hx", &x6);
  ck_assert_int_eq(x5, x6);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("abcdef", "%lx", &x7);
  r2 = s21_sscanf("abcdef", "%lx", &x8);
  ck_assert_int_eq(x7, x8);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0gabcdef", "%hx", &x5);
  r2 = s21_sscanf("0gabcdef", "%hx", &x6);
  ck_assert_int_eq(x5, x6);
  ck_assert_int_eq(r1, r2);
  //
  r1 = sscanf("0gabcdef", "%lx", &x7);
  r2 = s21_sscanf("0gabcdef", "%lx", &x8);
  ck_assert_int_eq(x7, x8);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("KRAKEN", "%X", &x1);
  r2 = s21_sscanf("KRAKEN", "%X", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("kraken", "%x", &x1);
  r2 = s21_sscanf("kraken", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x1234567890123456", "%x", &x1);
  r2 = s21_sscanf("0x1234567890123456", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x123", "%x", &x1);
  r2 = s21_sscanf("0x123", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-0x123", "%2x", &x1);
  r2 = s21_sscanf("-0x123", "%2x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);
  //
  char t1 = '0', t2 = '0';
  r1 = sscanf("0y923", "%x%c", &x1, &t1);
  r2 = s21_sscanf("0y923", "%x%c", &x2, &t2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(t1, t2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("y123", "%x", &x1);
  r2 = s21_sscanf("y123", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0xy123", "%x", &x1);
  r2 = s21_sscanf("0xy123", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("+123456", "%x", &x1);
  r2 = s21_sscanf("+123456", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-123456 0x12345", "%X %x", &x1, &x3);
  r2 = s21_sscanf("-123456 0x12345", "%X %x", &x2, &x4);
  ck_assert_uint_eq(x1, x2);
  ck_assert_uint_eq(x3, x4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("bcdef", "      %x", &x1);
  r2 = s21_sscanf("bcdef", "      %x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-bcdef", "%x", &x1);
  r2 = s21_sscanf("-bcdef", "%x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("1 2 3 0123", "1 2 3 %x", &x1);
  r2 = s21_sscanf("1 2 3 0123", "1 2 3 %x", &x2);
  ck_assert_uint_eq(x1, x2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_i) {
  int r1 = 0, r2 = 0;
  int i1 = -1, i2 = -1, i3 = 0, i4 = 0, i5 = 0, i6 = 0;
  short int i7, i8, i9, i10, i11, i12;
  long int i20, i21, i22, i23, i24, i25;

  // short int
  r1 = sscanf("-0x9 001  777", "%hi %hi %hi", &i7, &i9, &i11);
  r2 = s21_sscanf("-0x9 001  777", "%hi %hi %hi", &i8, &i10, &i12);
  ck_assert_int_eq(i7, i8);
  ck_assert_int_eq(i9, i10);
  ck_assert_int_eq(i11, i12);
  ck_assert_int_eq(r1, r2);

  // long int
  r1 = sscanf("-0x80000001 017777777777 2234234234234", "%li %li %li", &i20,
              &i22, &i24);
  r2 = s21_sscanf("-0x80000001 017777777777 2234234234234", "%li %li %li", &i21,
                  &i23, &i25);
  ck_assert_int_eq(i20, i21);
  ck_assert_int_eq(i22, i23);
  ck_assert_int_eq(i24, i25);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0z123", "%hi", &i7);
  r2 = s21_sscanf("0z123", "%hi", &i8);
  ck_assert_int_eq(i7, i8);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0z123", "%li", &i20);
  r2 = s21_sscanf("0z123", "%li", &i21);
  ck_assert_int_eq(i20, i21);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0123", "%i", &i1);
  r2 = s21_sscanf("0123", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("09", "%i", &i1);
  r2 = s21_sscanf("09", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("s0123", "%i", &i1);
  r2 = s21_sscanf("s0123", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0s123", "%i", &i1);
  r2 = s21_sscanf("0s123", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0xs123", "%i", &i1);
  r2 = s21_sscanf("0xs123", "%i", &i2);

  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-0123", "%i", &i1);
  r2 = s21_sscanf("-0123", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x123", "%i", &i1);
  r2 = s21_sscanf("0x123", "%i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x123", "%4i", &i1);
  r2 = s21_sscanf("0x123", "%4i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x123", "%6i", &i1);
  r2 = s21_sscanf("0x123", "%6i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x123", "%2i", &i1);
  r2 = s21_sscanf("0x123", "%2i", &i2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-123 5.     -0", "%i%2i %i", &i1, &i3, &i5);
  r2 = s21_sscanf("-123 5.     -0", "%i%2i %i", &i2, &i4, &i6);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(i5, i6);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-12 -10+3.5", "%3i %*i %i", &i1, &i3);
  r2 = s21_sscanf("-12 -10+3.5", "%3i %*i %i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-21474836481 2147483648", "%i %i", &i1, &i3);
  r2 = s21_sscanf("-21474836481 2147483648", "%i %i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-2147483648 -000", "%i %i", &i1, &i3);
  r2 = s21_sscanf("-2147483648 -000", "%i %i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("077 -034      089", "%i%i%i", &i1, &i3, &i5);
  r2 = s21_sscanf("077 -034      089", "%i%i%i", &i2, &i4, &i6);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(i5, i6);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("077 -0234 01", "%2i 7 %i%*i", &i1, &i3);
  r2 = s21_sscanf("077 -0234 01", "%2i 7 %i%*i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("017777777777 020000000000", "%i %i", &i1, &i3);
  r2 = s21_sscanf("017777777777 020000000000", "%i %i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-020000000000 -020000000001", "%i %i", &i1, &i3);
  r2 = s21_sscanf("-020000000000 -020000000001", "%i %i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x9 -0xa2      0xBa1", "%*i%5i%i", &i1, &i3);
  r2 = s21_sscanf("0x9 -0xa2      0xBa1", "%*i%5i%i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x0 -0x3K0x02", "%i %i K %i", &i1, &i3, &i5);
  r2 = s21_sscanf("0x0 -0x3K0x02", "%i %i K %i", &i2, &i4, &i6);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(i5, i6);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x7fffffff 0x80000000", "%i %i", &i1, &i3);
  r2 = s21_sscanf("0x7fffffff 0x80000000", "%i %i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-0x80000000 -0x80000001", "%i %i", &i1, &i3);
  r2 = s21_sscanf("-0x80000000 -0x80000001", "%i %i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("056 y 67", "%i %i %i", &i1, &i3, &i5);
  r2 = s21_sscanf("056 y 67", "%i %i %i", &i2, &i4, &i6);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(i5, i6);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-0xa2 y 02", "%i %*i %i", &i1, &i3);
  r2 = s21_sscanf("-0xa2 y 02", "%i %*i %i", &i2, &i4);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(i3, i4);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_proc) {
  int r1 = 0, r2 = 0;
  char proc1[100] = {0}, proc2[100] = {0};

  r1 = sscanf("%123.456", "%%%9s", proc1);
  r2 = s21_sscanf("%123.456", "%%%9s", proc2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123.456", "%%%9s", proc1);
  r2 = s21_sscanf("123.456", "%%%9s", proc2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_p) {
  int r1 = 0, r2 = 0;
  void *p1 = 0, *p2 = 0;

  r1 = sscanf("0x123", "%4p", &p1);
  r2 = s21_sscanf("0x123", "%4p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0xz123", "%4p", &p1);
  r2 = s21_sscanf("0xz123", "%4p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0zx123", "%4p", &p1);
  r2 = s21_sscanf("0zx123", "%4p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("z0x123", "%4p", &p1);
  r2 = s21_sscanf("z0x123", "%4p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-z0x123", "%4p", &p1);
  r2 = s21_sscanf("-z0x123", "%4p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("-0x123", "%4p", &p1);
  r2 = s21_sscanf("-0x123", "%4p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123", "%4p", &p1);
  r2 = s21_sscanf("123", "%4p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("0x12345", "%p", &p1);
  r2 = s21_sscanf("0x12345", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123.456", "%p", &p1);
  r2 = s21_sscanf("123.456", "%p", &p2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_n) {
  int n1 = 0, n2 = 0, r1 = 0, r2 = 0;
  short int n3 = 0, n4 = 0;
  long int n5 = 0, n6 = 0;

  r1 = sscanf("123.456", "123%hn", &n3);
  r2 = s21_sscanf("123.456", "123%hn", &n4);
  ck_assert_int_eq(n3, n4);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123123.456", "123%ln", &n5);
  r2 = s21_sscanf("123123.456", "123%ln", &n6);
  ck_assert_int_eq(n5, n6);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123.456", "%n", &n1);
  r2 = s21_sscanf("123.456", "%n", &n2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123123.456", "123%n", &n1);
  r2 = s21_sscanf("123123.456", "123%n", &n2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123 123.456", "123 %n", &n1);
  r2 = s21_sscanf("123 123.456", "123 %n", &n2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123 123.456", "123 %n", &n1);
  r2 = s21_sscanf("123 123.456", "123 %n", &n2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123 123.456", "123 %n", &n1);
  r2 = s21_sscanf("123 123.456", "123 %n", &n2);
  ck_assert_int_eq(n1, n2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

START_TEST(sscanf_test_d) {
  int d1 = 0, d2 = 0, d3 = 0, d4 = 0, d5 = 0, d6 = 0, res1 = 0, res2 = 0;
  short int d7 = 0, d8 = 0, d9 = 0, d10 = 0;
  long int d11 = 0, d12 = 0, d13 = 0, d14 = 0;

  //  test %d 1
  res1 = s21_sscanf("0123 456 789", "%d %*d %002d", &d1, &d2);
  res2 = sscanf("0123 456 789", "%d %*d %002d", &d3, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d3);
  ck_assert_int_eq(d2, d4);

  //  test %d 2
  d1 = 0;
  d2 = 0;
  d3 = 0;
  d4 = 0;
  res1 = 0;
  res2 = 0;
  res1 = s21_sscanf("+1234567", "%3d%d", &d1, &d2);
  res2 = sscanf("+1234567", "%3d%d", &d3, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d3);
  ck_assert_int_eq(d2, d4);

  //  test %d 3
  d1 = 0;
  d2 = 0;
  d3 = 0;
  d4 = 0;
  res1 = 0;
  res2 = 0;
  res1 = s21_sscanf("1234567", "123%3d%d", &d1, &d2);
  res2 = sscanf("1234567", "123%3d%d", &d3, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d3);
  ck_assert_int_eq(d2, d4);

  // test %d 4
  d1 = 0;
  d2 = 0;
  d3 = 0;
  d4 = 0;
  d5 = 0;
  d6 = 0;
  res1 = 0;
  res2 = 0;
  res1 = s21_sscanf("-123 4", "%3d%d %3d", &d1, &d2, &d3);
  res2 = sscanf("-123 4", "%3d%d %3d", &d4, &d5, &d6);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d4);
  ck_assert_int_eq(d2, d5);
  ck_assert_int_eq(d3, d6);

  // test %d 5
  d1 = 0;
  d2 = 0;
  d3 = 0;
  d4 = 0;
  res1 = 0;
  res2 = 0;
  res1 = s21_sscanf("5  5 ", "%d %d", &d1, &d2);
  res2 = sscanf("5  5 ", "%d %d", &d3, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d3);
  ck_assert_int_eq(d2, d4);

  // test %d 6
  d1 = 0;
  d2 = 0;
  d3 = 0;
  d4 = 0;
  res1 = 0;
  res2 = 0;
  res1 = s21_sscanf("-2147483648      -000 ", "%d %d", &d1, &d2);
  res2 = sscanf("-2147483648      -000 ", "%d %d", &d3, &d4);
  ck_assert_int_eq(res1, res2);
  ck_assert_int_eq(d1, d3);
  ck_assert_int_eq(d2, d4);

  // test %d 7
  d1 = 0;
  d2 = 0;
  d3 = 0;
  d4 = 0;
  res1 = 0;
  res2 = 0;
  res1 = s21_sscanf("1 hi", "%d %d", &d1, &d2);
  res2 = sscanf("1 hi", "%d %d", &d3, &d4);
  ck_assert_int_eq(d1, d3);
  ck_assert_int_eq(d2, d4);
  ck_assert_int_eq(res1, res2);
  //
  // short int
  res1 = s21_sscanf("12 +123", "%hd %3hd", &d7, &d9);
  res2 = sscanf("12 +123", "%hd %3hd", &d8, &d10);
  ck_assert_int_eq(d7, d8);
  ck_assert_int_eq(d9, d10);
  ck_assert_int_eq(res1, res2);

  // long int
  res1 = s21_sscanf("123456678 +1231234567", "%ld %8ld", &d11, &d13);
  res2 = sscanf("123456678 +1231234567", "%ld %8ld", &d12, &d14);
  ck_assert_int_eq(d11, d12);
  ck_assert_int_eq(d13, d14);
  ck_assert_int_eq(res1, res2);
}
END_TEST

START_TEST(sscanf_test_all) {
  int d1 = 0, d2 = 0, i1 = 0, i2 = 0, n1 = 0, n2 = 0, r1 = 0, r2 = 0;
  float e1 = 0, e2 = 0, E1 = 0, E2 = 0, f1 = 0, f2 = 0, g1 = 0, g2 = 0, G1 = 0,
        G2 = 0;
  unsigned o1 = 0, o2 = 0, x1 = 0, x2 = 0, X1 = 0, X2 = 0;
  void *p1 = 0, *p2 = 0;
  char s1[100], s2[100], c1, c2, proc1[100] = {0}, proc2[100] = {0};
  short hi1 = 0, hi2 = 0, hd1 = 0, hd2 = 0;
  unsigned long lo1 = 0, lo2 = 0, lu1 = 0, lu2 = 0;
  long double Le1 = 0, Le2 = 0, LE1 = 0, LE2 = 0, Lg1 = 0, Lg2 = 0, LG1 = 0,
              LG2 = 0;

  r1 = sscanf("123", "%d", &d1);
  r2 = s21_sscanf("123", "%d", &d2);
  ck_assert_int_eq(d1, d2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123 amogus", "%d%9s", &d1, s1);
  r2 = s21_sscanf("123 amogus", "%d%9s", &d2, s2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("123 amogus q", "%d %9s %c", &d1, s1, &c1);
  r2 = s21_sscanf("123 amogus q", "%d %9s %c", &d2, s2, &c2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("4 123 amogus q", "%i %d %9s %c", &i1, &d1, s1, &c1);
  r2 = s21_sscanf("4 123 amogus q", "%i %d %9s %c", &i2, &d2, s2, &c2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_int_eq(r1, r2);

  r1 =
      sscanf("4 123 amogus q 12e34", "%i %d %9s %c %e", &i1, &d1, s1, &c1, &e1);
  r2 = s21_sscanf("4 123 amogus q 12e34", "%i %d %9s %c %e", &i2, &d2, s2, &c2,
                  &e2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("4 123 amogus q 12e34 43e21", "%i %d %9s %c %e %E", &i1, &d1, s1,
              &c1, &e1, &E1);
  r2 = s21_sscanf("4 123 amogus q 12e34 43e21", "%i %d %9s %c %e %E", &i2, &d2,
                  s2, &c2, &e2, &E2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_int_eq(r1, r2);

  r1 =
      sscanf("4 123 amogus q 12e34 43e21 13.37 2.28",
             "%i %d %9s %c %e %E %f %g", &i1, &d1, s1, &c1, &e1, &E1, &f1, &g1);
  r2 = s21_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28",
                  "%i %d %9s %c %e %E %f %g", &i2, &d2, s2, &c2, &e2, &E2, &f2,
                  &g2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228",
              "%i %d %9s %c %e %E %f %g %G", &i1, &d1, s1, &c1, &e1, &E1, &f1,
              &g1, &G1);
  r2 = s21_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228",
                  "%i %d %9s %c %e %E %f %g %G", &i2, &d2, s2, &c2, &e2, &E2,
                  &f2, &g2, &G2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228",
              "%i %d %9s %c %e %E %f %g %G", &i1, &d1, s1, &c1, &e1, &E1, &f1,
              &g1, &G1);
  r2 = s21_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228",
                  "%i %d %9s %c %e %E %f %g %G", &i2, &d2, s2, &c2, &e2, &E2,
                  &f2, &g2, &G2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(r1, r2);

  r1 = sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101",
              "%i %d %9s %c %e %E %f %g %G %o", &i1, &d1, s1, &c1, &e1, &E1,
              &f1, &g1, &G1, &o1);
  r2 = s21_sscanf("4 123 amogus q 12e34 43e21 13.37 2.28 1337.228 101",
                  "%i %d %9s %c %e %E %f %g %G %o", &i2, &d2, s2, &c2, &e2, &E2,
                  &f2, &g2, &G2, &o2);
  ck_assert_int_eq(i1, i2);
  ck_assert_int_eq(d1, d2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(o1, o2);
  ck_assert_int_eq(r1, r2);

  r1 = sscanf(
      "4 123 amogusq 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 "
      "shrek "
      "& amogus is sus?",
      "%*i %12hi %4hd %20s %c %3Le %7LE %*i %1f %9Lg %5LG %6lo %12lu %*x %11x "
      "%2X %10p %n %21s %"
      "%",
      &hi1, &hd1, s1, &c1, &Le1, &LE1, &f1, &Lg1, &LG1, &lo1, &lu1, &x1, &X1,
      &p1, &n1, proc1);
  r2 = s21_sscanf(
      "4 123 amogusq 12e34 43e21 13.37 2.28 1337.228 101 1854 12ab BA21 "
      "shrek "
      "& amogus is sus?",
      "%*i %12hi %4hd %20s %c %3Le %7LE %*i %1f %9Lg %5LG %6lo %12lu %*x %11x "
      "%2X %10p %n %21s %"
      "%",
      &hi2, &hd2, s2, &c2, &Le2, &LE2, &f2, &Lg2, &LG2, &lo2, &lu2, &x2, &X2,
      &p2, &n2, proc2);
  ck_assert_int_eq(hi1, hi2);
  ck_assert_int_eq(hd1, hd2);
  ck_assert_str_eq(s1, s2);
  ck_assert_int_eq(c1, c2);
  ck_assert_msg(e1 == e2, "floats not equals");
  ck_assert_msg(E1 == E2, "floats not equals");
  ck_assert_msg(f1 == f2, "floats not equals");
  ck_assert_msg(g1 == g2, "floats not equals");
  ck_assert_msg(G1 == G2, "floats not equals");
  ck_assert_int_eq(lo1, lo2);
  ck_assert_int_eq(lu1, lu2);
  ck_assert_int_eq(x1, x2);
  ck_assert_int_eq(X1, X2);
  ck_assert_ptr_eq(p1, p2);
  ck_assert_int_eq(n1, n2);
  ck_assert_str_eq(proc1, proc2);
  ck_assert_int_eq(r1, r2);
}
END_TEST

Suite* sscanf_suite(void) {
  Suite* s;
  s = suite_create("sscanf_suite");

  //  sscanf
  TCase* tc1_1 = tcase_create("Core");
  suite_add_tcase(s, tc1_1);
  tcase_add_test(tc1_1, sscanf_test_l);
  tcase_add_test(tc1_1, sscanf_test_L);
  tcase_add_test(tc1_1, sscanf_test_h);
  tcase_add_test(tc1_1, sscanf_test_n);
  tcase_add_test(tc1_1, sscanf_test_d);
  tcase_add_test(tc1_1, sscanf_test_i);
  tcase_add_test(tc1_1, sscanf_test_e);
  tcase_add_test(tc1_1, sscanf_test_f);
  tcase_add_test(tc1_1, sscanf_test_o);
  tcase_add_test(tc1_1, sscanf_test_x);
  tcase_add_test(tc1_1, sscanf_test_u);
  tcase_add_test(tc1_1, sscanf_test_s);
  tcase_add_test(tc1_1, sscanf_test_p);
  tcase_add_test(tc1_1, sscanf_test_proc);
  tcase_add_test(tc1_1, sscanf_test_all);

  return s;
}
int main() {
  Suite* tests[] = {sprintf_suite(), additional_func_suite(), main_func_suite(),
                    sscanf_suite(), s21_NULL};
  int no_failed = 0;
  for (int i = 0; tests[i]; ++i) {
    SRunner* runner;
    runner = srunner_create(tests[i]);
    srunner_set_fork_status(runner, CK_NOFORK);
    srunner_run_all(runner, CK_NORMAL);
    no_failed += srunner_ntests_failed(runner);
    srunner_free(runner);
  }
  if (no_failed == 0) printf("TEST OK\n");
  return 0;
}
