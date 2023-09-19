#include "main.h"
#include <stdio.h>

/**
* main - Entry point for testing the _printf function.
*
* Return: Always 0 (Success)
*/

int main(void)
{
int len;

len = _printf("Testing some basic conversions:\n");
_printf("1. Character: %c\n", 'A');
_printf("2. String: %s\n", "Hello, World!");
_printf("3. Percentage: %%\n");
_printf("\n");

len = _printf("Testing some custom conversions:\n");
_printf("4. Binary: %b\n", 42);
_printf("5. Non-printable characters: %S\n", "Hello\x02World");
_printf("6. Reversed string: %r\n", "abcdefg");
_printf("7. ROT13 encoding: %R\n", "Hello, World!");
_printf("\n");

return (0);
}
