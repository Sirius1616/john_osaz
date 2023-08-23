#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @str: the string whose length to check
 *
 * Return: integer length of string
 */

int _strlen(char *str)
{
    int x = 0;

    if (!str)
        return 0;  // Return 0 if str is NULL

    for (; *str != '\0'; str++)
        x++;       // Increment x for each character in the string

    return x;      // Return the length of the string
}

/**
 * _strcmp - performs lexicogarphic comparison of two strings.
 * @str1: the first string
 * @str2: the second string
 *
 * Return: negative if str1 < str2, +ve if str1 > str2, zero if str1 == str2
 */

int _strcmp(char *str1, char *str2)
{
    for (; *str1 && *str2; str1++, str2++)
    {
        if (*str1 != *str2)
            return (*str1 - *str2);
    }
    
    if (*str1 == *str2)
        return 0;
    else
        return (*str1 < *str2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * @haystacks: string to search
 * @needles: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */

char *starts_with(const char *haystacks, const char *needles)
{
    for (; *needles; needles++, haystacks++)
    {
        if (*needles != *haystacks)
            return NULL;
    }
    
    return (char *)haystacks;
}


/**
 * _strcat - concatenates two strings
 * @_dest: the destination buffer
 * @_src: the source buffer
 *
 * Return: pointer to destination buffer
 */

char *_strcat(char *_dest, char *_src)
{
    char *rt = _dest;  // Store the original value of _dest
    
    for (; *_dest; _dest++)
    {
        // Move _dest to the end of the first string
    }
    
    for (; *_src; _src++, _dest++)
    {
        *_dest = *_src;  // Copy characters from _src to _dest
    }
    
    *_dest = *_src;  // Copy the null terminator from _src to _dest
    
    return rt;  // Return the original value of _dest
}
