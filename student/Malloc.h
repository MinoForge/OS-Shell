/**
 * Header file for Malloc.
 *
 * @author Peter Gardner
 * @author Wesley Rogers
 * @version February 27, 2019
 */

#ifndef OPERATINGSYSTEMS_MALLOC_H
#define OPERATINGSYSTEMS_MALLOC_H
#include <stdlib.h>

/**
 * Safely allocates memory. Will exit if the allocate fails.
 *
 * @param The number of bytes to allocate
 * @return A pointer to the allocated memory
 */
void *Malloc(size_t);

/**
 * Reallocates the memory available at the given pointer to have a new size.
 *
 * @param The pointer to the memory to reallocate.
 * @param The new size of the allocated block
 * @returns The new pointer to memory.
 */
void *Realloc(void*, size_t);

//TODO comment
void *Calloc(size_t, size_t);

#endif /* OPERATINGSYSTEMS_MALLOC_H */
