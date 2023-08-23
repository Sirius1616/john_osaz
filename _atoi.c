#include "shell.h"

/**
 * interact - returns true if shell is interactive mode
 * @info: struct address
 * Return: 1 if in interactive mode, 0 otherwise
 */
int interact(info_t *info) {
    int is_interactive = 0;

    if (isatty(STDIN_FILENO)) {
        if (info->readfd <= 2) {
            is_interactive = 1;
        }
    }

    return is_interactive;
}


/**
 * is_delimiter - checks if character is a delimeter
 * @ch: the character to check
 * @delimiter: the delimeter string
 * Return: 1 if true, 0 if false
 */

int is_delimiter(char ch, char *delimiter) {
    for (int i = 0; delimiter[i] != '\0'; i++) {
        if (delimiter[i] == ch) {
            return 1; 
        }
    }
    return 0;
}


/**
 *_isalpha - checks for alphabetic character
 *@ch: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int ch) {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z')) ? 1 : 0;
}



/**
 *_atoi - converts a string to an integer
 *@str: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *str) {
    int output = 0;
    int sign = 1;
    int flag = 0;
    int i = 0;

    while (str[i] != '\0' && flag != 2) {
        if (str[i] == '-') {
            sign *= -1;
        } else if (str[i] >= '0' && str[i] <= '9') {
            flag = 1;
            output = output * 10 + (str[i] - '0');
        } else if (flag == 1) {
            flag = 2;
        }
        i++;
    }

    return output * sign;
}
