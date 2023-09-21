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

int length_modifier_l = 0;
int length_modifier_h = 0;

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
if (length_modifier_l == 1)
{
long value = va_arg(args, long);
if (flag_plus && value >= 0)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "+%ld", value);
}
else if (flag_space && value >= 0)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, " %ld", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%ld", value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else if (length_modifier_h == 1)
{
short value = (short)va_arg(args, int);
if (flag_plus && value >= 0)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "+%hd", value);
}
else if (flag_space && value >= 0)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, " %hd", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%hd", value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
int value = va_arg(args, int);
if (flag_plus && value >= 0)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "+%d", value);
}
else if (flag_space && value >= 0)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, " %d", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%d", value);
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
if (length_modifier_l == 1)
{
unsigned long value = va_arg(args, unsigned long);
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%lu", value);
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else if (length_modifier_h == 1)
{
unsigned short value = (unsigned short)va_arg(args, unsigned int);
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%hu", value);
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
unsigned int value = va_arg(args, unsigned int);
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%u", value);
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
}
break;
case 'o':
{
if (length_modifier_l == 1)
{
unsigned long value = va_arg(args, unsigned long);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "0%lo", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%lo", value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else if (length_modifier_h == 1)
{
unsigned short value = (unsigned short)va_arg(args, unsigned int);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "0%ho", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%ho", value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
unsigned int value = va_arg(args, unsigned int);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "0%o", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%o", value);
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
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "0x%lx", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%lx", value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else if (length_modifier_h == 1)
{
unsigned short value = (unsigned short)va_arg(args, unsigned int);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "0x%hx", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%hx", value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
unsigned int value = va_arg(args, unsigned int);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "0x%x", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%x", value);
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
case 'X':
{
if (length_modifier_l == 1)
{
unsigned long value = va_arg(args, unsigned long);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "0X%lX", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%lX", value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else if (length_modifier_h == 1)
{
unsigned short value = (unsigned short)va_arg(args, unsigned int);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "0X%hX", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%hX", value);
}
buffer_index += strlen(buffer + buffer_index);
printed_chars += strlen(buffer + buffer_index);
}
else
{
unsigned int value = va_arg(args, unsigned int);
if (flag_hash)
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "0X%X", value);
}
else
{
snprintf(buffer + buffer_index, sizeof(buffer) - buffer_index, "%X", value);
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
