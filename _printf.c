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
if (*format != '%')
{
if (buffer_index < sizeof(buffer) - 1)
{
buffer[buffer_index++] = *format;
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
printed_chars += printf("%d", va_arg(args, int));
break;
case 'b':
print_binary(va_arg(args, unsigned int));
printed_chars++;
break;
case 'u':
printed_chars += printf("%u", va_arg(args, unsigned int));
break;
case 'o':
printed_chars += printf("%o", va_arg(args, unsigned int));
break;
case 'x':
printed_chars += printf("%x", va_arg(args, unsigned int));
break;
case 'X':
printed_chars += printf("%X", va_arg(args, unsigned int));
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
