#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @ptrr: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */

int bfree(void **ptrr)
{
    if (!ptrr || !*ptrr)
    {
        return 0;  // No memory to free
    }
    
    free(*ptrr);  // Free the memory pointed to by *ptrr
    *ptrr = NULL; // Set the original pointer to NULL
    return 1;     // Memory freed successfully
}
