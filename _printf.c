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
size_t buffer_index = 0;
int printed_chars = 0;

va_start(args, format);

while (*format != '\0')
{
    
int flag_plus = 0;
int flag_space = 0;
int flag_hash = 0;
int flag_zero = 0;
int flag_minus = 0;

int length_modifier_l = 0;
int length_modifier_h = 0;

int precision = -1;

int field_width = 0;

if (*format != '%')
{
if (buffer_index < sizeof(buffer) - 1)
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

format++;

while (*format == '+' || *format == ' ' || *format == '#')
{
if (*format == '+')
{
flag_plus = 1;
}
else if (*format == ' ')
{
flag_space = 1;
}
else if (*format == '#')
{
flag_hash = 1;
}
else if (*format == '0')
{
flag_zero = 1;
}
else if (*format == '-')
{
flag_minus = 1;
}

format++;
}

while (*format == 'l' || *format == 'h')
{
if (*format == 'l')
length_modifier_l++;
else if (*format == 'h')
length_modifier_h++;
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
_putchar(va_arg(args, int));
printed_chars++;
break;
case 's':
printed_chars += printf("%s", va_arg(args, char *));
break;
case 'd':
case 'i':
{
if (precision != -1)
{
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%s%d.%dd", (flag_minus ? "-" : ""), flag_zero, precision);
int value = va_arg(args, int);
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
if (length_modifier_l == 1)
{
long value = va_arg(args, long);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%sld", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
else if (length_modifier_h == 1)
{
short value = (short)va_arg(args, int);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%shd", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
else
{
int value = va_arg(args, int);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%sd", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
}
break;

case 'b':
print_binary(va_arg(args, unsigned int));
printed_chars++;
break;
case 'u':
{
if (precision != -1)
{
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%s%d.%du", (flag_minus ? "-" : ""), flag_zero, precision);
unsigned int value = va_arg(args, unsigned int);
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
if (length_modifier_l == 1)
{
unsigned long value = va_arg(args, unsigned long);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%slu", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
else if (length_modifier_h == 1)
{
unsigned short value = (unsigned short)va_arg(args, unsigned int);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%shu", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
else
{
unsigned int value = va_arg(args, unsigned int);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%su", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
}
break;
case 'o':
{
if (precision != -1)
{
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%s%d.%do", (flag_minus ? "-" : ""), flag_zero, precision);
unsigned int value = va_arg(args, unsigned int);
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
if (length_modifier_l == 1)
{
unsigned long value = va_arg(args, unsigned long);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%slo", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
else if (length_modifier_h == 1)
{
unsigned short value = (unsigned short)va_arg(args, unsigned int);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%sho", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
else
{
unsigned int value = va_arg(args, unsigned int);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%so", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
}
break;
case 'x':
{
if (length_modifier_l == 1)
{
unsigned long value = va_arg(args, unsigned long);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%#*lx", field_width, value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%*lx", field_width, value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else if (length_modifier_h == 1)
{
unsigned short value = (unsigned short)va_arg(args, unsigned int);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%#*hx", field_width, value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%*hx", field_width, value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
unsigned int value = va_arg(args, unsigned int);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%#*x", field_width, value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%*x", field_width, value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
}
break;
case 'p':
{
void *ptr = va_arg(args, void *);
printed_chars += printf("0x%lx", (unsigned long)ptr);
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
buffer[buffer_index++] = flag_zero ? '0' : ' ';
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
buffer[buffer_index++] = flag_zero ? '0' : ' ';
}
}

printed_chars += str_len;
}
break;
case 'X':
{
if (precision != -1)
{
char format_str[32]; 
snprintf(format_str, sizeof(format_str), "%%%s%d.%dX", (flag_minus ? "-" : ""), flag_zero, precision);
unsigned int value = va_arg(args, unsigned int);
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
if (length_modifier_l == 1)
{
unsigned long value = va_arg(args, unsigned long);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%slX", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
else if (length_modifier_h == 1)
{
unsigned short value = (unsigned short)va_arg(args, unsigned int);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%shX", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
else
{
unsigned int value = va_arg(args, unsigned int);
char format_str[32];
snprintf(format_str, sizeof(format_str), "%%%sX", (flag_minus ? "-" : ""));
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, format_str, value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
}
break;

case 'S':
{
char *str = va_arg(args, char *);
while (*str != '\0')
{
if (*str < 32 || *str >= 127)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "\\x%02X", (unsigned char)*str);
buffer_index += 4;
}
else
{
buffer[buffer_index++] = *str;
}
str++;
printed_chars++;
        
if (buffer_index == sizeof(buffer) - 1)
{
write(1, buffer, buffer_index);
buffer_index = 0;
}
}
}
break;
case '%':
if (buffer_index < sizeof(buffer) - 1)
{
buffer[buffer_index++] = '%';
printed_chars++;
}
else
{
write(1, buffer, buffer_index);
buffer_index = 0;
}
break;
default:
if (buffer_index < sizeof(buffer) - 2)
{
buffer[buffer_index++] = '%';
buffer[buffer_index++] = *format;
printed_chars += 2;
}
else
{
write(1, buffer, buffer_index);
buffer_index = 0;
}
break;
}


if (buffer_index == sizeof(buffer) - 1)
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

return printed_chars;
}
