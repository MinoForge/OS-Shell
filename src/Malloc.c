#include <stdlib.h>
#include <stdio.h>
/**
 * Contains code for a safe implementation of malloc().
 *
 * @author Peter Gardner
 * @author Wesley Rogers
 * @version February 27, 2019
 */

/**
 * Safely allocates memory. Will exit if the allocate fails.
 *
 * @param The number of bytes to allocate
 * @return A pointer to the allocated memory
 */
void *Malloc(size_t size){
    void *data = malloc(size);

    if(!data){
        perror("Failed to allocate memory");
        exit(1);
    }

    return data;
}

/**
 * Reallocates the memory available at the given pointer to have a new size.
 *
 * @param The pointer to the memory to reallocate.
 * @param The new size of the allocated block
 * @returns The new pointer to memory.
 */
void *Realloc(void *ptr, size_t size){
    void *data = realloc(ptr, size);

    if(!data){
        perror("Failed to allocate memory");
        exit(1);
    }

    return data;
}

void *Calloc(size_t num_blocks, size_t block_size) {
    void *data = calloc(num_blocks, block_size);

    if(!data){
        perror("Failed to allocate memory");
        exit(1);
    }

    return data;
}
