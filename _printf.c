#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

/**
* _putchar - Write a character to stdout.
* @c: The character to write.
*
* Return: On success, returns the character written as an unsigned char
* cast to an int. On error, returns -1.
*/
int _putchar(char c)
{
return (write(1, &c, 1));
}

/**
* print_binary - Print an unsigned integer in binary format.
* @num: The unsigned integer to be printed in binary.
*/
void print_binary(unsigned int num)
{
if (num > 1)
print_binary(num / 2);
_putchar('0' + num % 2);
}

/**
* rot13 - Apply ROT13 encoding to a character.
* @c: The character to be encoded.
*
* Return: The ROT13-encoded character.
*/
char rot13(char c)
{
if ((c >= 'a' && c <= 'z'))
{
return ((((c - 'a') + 13) % 26) + 'a');
}
else if ((c >= 'A' && c <= 'Z'))
{
return ((((c - 'A') + 13) % 26) + 'A');
}
else
{
return (c);
}
}

/**
 * _printf - Custom printf function.
 * @format: A format string containing conversion specifiers.
 * @...: Variable number of arguments to be formatted.
 *
 * Return: The number of characters printed (excluding the null byte used to
 *         end output to strings).
 */
int _printf(const char *format, ...)
{
va_list args;
char buffer[1024];
int buffer_index = 0;
int printed_chars = 0;

int flag_plus = 0;
int flag_space = 0;
int flag_hash = 0;
int flag_zero = 0;
int flag_minus = 0;
int field_width = 0;
int precision = -1;
int num = va_arg(args, int);
int num_digits = 0;
unsigned int temp = num;

va_start(args, format);

while (*format != '\0')
{
if (*format != '%')
{
if (buffer_index < (int)(sizeof(buffer) - 1))
{
if (*format < 32 || *format >= 127)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "\\x%02X", (unsigned char)*format);
buffer_index += 4;
}
else
{
buffer[buffer_index++] = *format;
}

printed_chars++;
}
else
{
write(1, buffer, buffer_index);
buffer_index = 0;
}
}
else
{
format++;

while (*format == '+' || *format == ' ' || *format == '#' || *format == '0' || *format == '-')
{
if (*format == '+')
flag_plus = 1;
else if (*format == ' ')
flag_space = 1;
else if (*format == '#')
flag_hash = 1;
else if (*format == '0')
flag_zero = 1;
else if (*format == '-')
flag_minus = 1;

format++;
}

while (*format >= '0' && *format <= '9')
{
field_width = field_width * 10 + (*format - '0');
format++;
}

if (*format == '.')
{
format++;
precision = 0;
while (*format >= '0' && *format <= '9')
{
precision = precision * 10 + (*format - '0');
format++;
}
}

switch (*format)
{
case 'c':
{
char c = va_arg(args, int);
if (!flag_minus)
{
int padding = field_width - 1;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = flag_zero ? '0' : ' ';
}
}
buffer[buffer_index++] = c;
if (flag_minus)
{
int padding = field_width - 1;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
printed_chars++;
}
break;

case 's':
{
char *str = va_arg(args, char *);
int str_len = strlen(str);
if (precision >= 0 && precision < str_len)
{
str_len = precision;
}
if (!flag_minus)
{
int padding = field_width - str_len;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = flag_zero ? '0' : ' ';
}
}
for (int i = 0; i < str_len; i++)
{
buffer[buffer_index++] = str[i];
}
if (flag_minus)
{
int padding = field_width - str_len;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
printed_chars += str_len;
}
break;

case '%':
{
if (!flag_minus)
{
int padding = field_width - 1;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = flag_zero ? '0' : ' ';
}
}
buffer[buffer_index++] = '%';
if (flag_minus)
{
int padding = field_width - 1;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
printed_chars++;
}
break;

case 'd':
case 'i':
{
if (num < 0)
{
num = -num;
buffer[buffer_index++] = '-';
}
else if (flag_plus)
{
buffer[buffer_index++] = '+';
}
else if (flag_space)
{
buffer[buffer_index++] = ' ';
}
if (precision == 0 && num == 0)
{
break;
}
int temp = num;
while (temp > 0)
{
temp /= 10;
num_digits++;
}
if (num_digits < precision)
{
for (int i = 0; i < precision - num_digits; i++)
{
buffer[buffer_index++] = '0';
}
}
char num_str[12];
snprintf(num_str, sizeof(num_str), "%d", num);
for (int i = 0; i < num_digits; i++)
{
buffer[buffer_index++] = num_str[i];
}
printed_chars += num_digits;
if (!flag_minus)
{
int padding = field_width - num_digits;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
}
break;

case 'u':
{
unsigned int num = va_arg(args, unsigned int);
if (precision == 0 && num == 0)
{
break;
}
while (temp > 0)
{
temp /= 10;
num_digits++;
}
if (num_digits < precision)
{
for (int i = 0; i < precision - num_digits; i++)
{
buffer[buffer_index++] = '0';
}
}
char num_str[12];
snprintf(num_str, sizeof(num_str), "%u", num);
for (int i = 0; i < num_digits; i++)
{
buffer[buffer_index++] = num_str[i];
}
printed_chars += num_digits;
if (!flag_minus)
{
int padding = field_width - num_digits;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
}
break;

case 'o':
{
unsigned int num = va_arg(args, unsigned int);
if (precision == 0 && num == 0)
{
break;
}
while (temp > 0)
{
temp /= 8;
num_digits++;
}
if (flag_hash && num != 0)
{
buffer[buffer_index++] = '0';
}
if (num_digits < precision)
{
for (int i = 0; i < precision - num_digits; i++)
{
buffer[buffer_index++] = '0';
}
}
char num_str[12];
snprintf(num_str, sizeof(num_str), "%o", num);
for (int i = 0; i < num_digits; i++)
{
buffer[buffer_index++] = num_str[i];
}
printed_chars += num_digits;
if (!flag_minus)
{
int padding = field_width - num_digits;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
}
break;

case 'x':
{
unsigned int num = va_arg(args, unsigned int);
if (precision == 0 && num == 0)
{
break;
}
while (temp > 0)
{
temp /= 16;
num_digits++;
}
if (flag_hash && num != 0)
{
buffer[buffer_index++] = '0';
buffer[buffer_index++] = 'x';
}
if (num_digits < precision)
{
for (int i = 0; i < precision - num_digits; i++)
{
buffer[buffer_index++] = '0';
}
}
char num_str[12];
snprintf(num_str, sizeof(num_str), "%x", num);
for (int i = 0; i < num_digits; i++)
{
buffer[buffer_index++] = num_str[i];
}
printed_chars += num_digits;
if (!flag_minus)
{
int padding = field_width - num_digits;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
}
break;

case 'X':
{
unsigned int num = va_arg(args, unsigned int);
if (precision == 0 && num == 0)
{
break;
}
while (temp > 0)
{
temp /= 16;
num_digits++;
}
if (flag_hash && num != 0)
{
buffer[buffer_index++] = '0';
buffer[buffer_index++] = 'X';
}
if (num_digits < precision)
{
for (int i = 0; i < precision - num_digits; i++)
{
buffer[buffer_index++] = '0';
}
}
char num_str[12];
snprintf(num_str, sizeof(num_str), "%X", num);
for (int i = 0; i < num_digits; i++)
{
buffer[buffer_index++] = num_str[i];
}
printed_chars += num_digits;
if (!flag_minus)
{
int padding = field_width - num_digits;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
}
break;

case 'b':
{
unsigned int num = va_arg(args, unsigned int);
print_binary(num);
printed_chars += num_digits;
}
break;

case 'S':
{
char *str = va_arg(args, char *);
int str_len = strlen(str);
if (precision >= 0 && precision < str_len)
{
str_len = precision;
}
for (int i = 0; i < str_len; i++)
{
if (str[i] < 32 || str[i] >= 127)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "\\x%02X", (unsigned char)str[i]);
buffer_index += 4;
}
else
{
buffer[buffer_index++] = str[i];
}
}
printed_chars += str_len;
}
break;

case 'p':
{
void *ptr = va_arg(args, void *);
if (ptr != NULL)
{
unsigned long int address = (unsigned long int)ptr;
buffer[buffer_index++] = '0';
buffer[buffer_index++] = 'x';
for (int i = 15; i >= 0; i--)
{
int hex_digit = (address >> (i * 4)) & 0xF;
buffer[buffer_index++] = hex_digit < 10 ? '0' + hex_digit : 'a' + (hex_digit - 10);
}
printed_chars += 18;
}
else
{
char *null_str = "(nil)";
int str_len = strlen(null_str);
for (int i = 0; i < str_len; i++)
{
buffer[buffer_index++] = null_str[i];
}
printed_chars += str_len;
}
break;

case 'r':
{
char *str = va_arg(args, char *);
int str_len = strlen(str);
if (precision >= 0 && precision < str_len)
{
str_len = precision;
}
if (!flag_minus)
{
int padding = field_width - str_len;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = flag_zero ? '0' : ' ';
}
}
for (int i = str_len - 1; i >= 0; i--)
{
buffer[buffer_index++] = str[i];
}
if (flag_minus)
{
int padding = field_width - str_len;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
printed_chars += str_len;
}
break;

case 'R':
{
char *str = va_arg(args, char *);
int str_len = strlen(str);
if (precision >= 0 && precision < str_len)
{
str_len = precision;
}
if (!flag_minus)
{
int padding = field_width - str_len;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = flag_zero ? '0' : ' ';
}
}
for (int i = 0; i < str_len; i++)
{
buffer[buffer_index++] = rot13(str[i]);
}
if (flag_minus)
{
int padding = field_width - str_len;
for (int i = 0; i < padding; i++)
{
buffer[buffer_index++] = ' ';
}
}
printed_chars += str_len;
}
break;

default:
buffer[buffer_index++] = '%';
if (*format != '\0')
{
buffer[buffer_index++] = *format;
printed_chars++;
}
break;
}
}

if (buffer_index >= sizeof(buffer) - 1)
{
write(1, buffer, buffer_index);
buffer_index = 0;
}

format++;
}

if (buffer_index > 0)
{
write(1, buffer, buffer_index);
}

va_end(args);

return (printed_chars);
}
