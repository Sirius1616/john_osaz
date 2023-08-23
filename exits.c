#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */

char *_strncpy(char *dest, char *src, int n)
{
    int i;

    // Copy characters from src to dest
    for (i = 0; i < n - 1 && src[i] != '\0'; i++)
    {
        dest[i] = src[i];
    }

    // Null-terminate the copied string
    dest[i] = '\0';

    return dest;
}


/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */

char *_strncat(char *dest, char *src, int n)
{
    char *s = dest;

    // Find the end of dest
    int i;
    for (i = 0; dest[i] != '\0'; i++)
    {
        // Empty loop body, just finding the end of dest
    }

    // Concatenate characters from src to dest
    int j;
    for (j = 0; src[j] != '\0' && j < n; j++)
    {
        dest[i + j] = src[j];
    }

    // Null-terminate the concatenated string
    dest[i + j] = '\0';

    return s;
}


/**
 **_strchr - locates a character in a string
 *@s: the string to be parsed
 *@c: the character to look for
 *Return: (s) a pointer to the memory area s
 */

char *_strchr(char *s, char c)
{
    for (; *s != '\0'; s++)
    {
        if (*s == c)
            return s;
    }

    return NULL;
}
