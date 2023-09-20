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
if (num == 0)
{
putchar('0');
return;
}

int binary[32]; // Assuming 32-bit integers
int i = 0;

while (num > 0)
{
binary[i] = num % 2;
num /= 2;
i++;
}

for (int j = i - 1; j >= 0; j--)
{
putchar('0' + binary[j]);
}
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
int printed_chars = 0;

va_start(args, format);

while (*format != '\0')
{
if (*format != '%')
{
_putchar(*format);
printed_chars++;
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
case '%':
_putchar('%');
printed_chars++;
break;
default:
_putchar('%');
_putchar(*format);
printed_chars += 2;
break;
}
}

format++;
}

va_end(args);

return printed_chars;
}
