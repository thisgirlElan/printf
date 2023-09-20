#include "main.h"
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIZE 1024

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
char buffer[BUFFER_SIZE]; 
int buffer_index = 0;
int printed_chars = 0;

va_start(args, format);

while (*format != '\0')
{
if (*format != '%')
{
if (buffer_index < BUFFER_SIZE - 1)
{
buffer[buffer_index] = *format;
buffer_index++;
}
else
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
}
printed_chars++;
}
else
{
format++;

switch (*format)
{
case 'c':
if (buffer_index < BUFFER_SIZE - 1)
{
buffer[buffer_index] = va_arg(args, int);
buffer_index++;
}
else
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
buffer[buffer_index] = va_arg(args, int);
buffer_index++;
}
printed_chars++;
break;
case 's':
while (*buffer_index < BUFFER_SIZE - 1)
{
buffer[buffer_index] = *va_arg(args, char *);
buffer_index++;
}
if (buffer_index >= BUFFER_SIZE - 1)
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
}
break;
case 'd':
case 'i':
buffer_index += snprintf(buffer + buffer_index, BUFFER_SIZE - buffer_index, "%d", va_arg(args, int));
if (buffer_index >= BUFFER_SIZE - 1)
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
}
break;
case 'b':
print_binary(va_arg(args, unsigned int));
printed_chars++;
break;
case 'u':
buffer_index += snprintf(buffer + buffer_index, BUFFER_SIZE - buffer_index, "%u", va_arg(args, unsigned int));
if (buffer_index >= BUFFER_SIZE - 1)
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
}
break;
case 'o':
buffer_index += snprintf(buffer + buffer_index, BUFFER_SIZE - buffer_index, "%o", va_arg(args, unsigned int));
if (buffer_index >= BUFFER_SIZE - 1)
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
}
break;
case 'x':
buffer_index += snprintf(buffer + buffer_index, BUFFER_SIZE - buffer_index, "%x", va_arg(args, unsigned int));
if (buffer_index >= BUFFER_SIZE - 1)
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
}
break;
case 'X':
buffer_index += snprintf(buffer + buffer_index, BUFFER_SIZE - buffer_index, "%X", va_arg(args, unsigned int));
if (buffer_index >= BUFFER_SIZE - 1)
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
}
break;
case '%':
if (buffer_index < BUFFER_SIZE - 1)
{
buffer[buffer_index] = '%';
buffer_index++;
}
else
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
buffer[buffer_index] = '%';
buffer_index++;
}
printed_chars++;
break;
default:
if (buffer_index < BUFFER_SIZE - 1)
{
buffer[buffer_index] = '%';
buffer_index++;
buffer[buffer_index] = *format;
buffer_index++;
}
else
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
buffer[buffer_index] = '%';
buffer_index++;
buffer[buffer_index] = *format;
buffer_index++;
}
printed_chars += 2;
break;
}
}

if (buffer_index >= BUFFER_SIZE - 1)
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
buffer_index = 0;
}

format++;
}

if (buffer_index > 0)
{
write(1, buffer, buffer_index);
printed_chars += buffer_index;
}

va_end(args);

return printed_chars;
}
