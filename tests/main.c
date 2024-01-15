#include "../lib/arena.h"
#include <assert.h>
#include <errno.h>
#include <stddef.h>

int main() {
    struct Arena arena = arenaAllocate(16*sizeof(int));
    // Fails on unsucessfull allocation
    assert(arena.size != 0);
    int* seven = arenaAssignBytes(&arena, sizeof(int));
    assert(arena.head == arena.start + sizeof(int));
    // Check for read/writeability of memory
    *seven = 7;
    assert(*seven == 7);
    // Returns zero on successfull re-asignment
    assert(arenaPopBytes(&arena, sizeof(int)) == 0);
    assert(arenaAssignBytes(&arena, sizeof(int)) != NULL);
    // Overflows stack - should return NULL 
    seven = arenaAssignBytes(&arena, 16*sizeof(int));
    assert(seven == NULL);
    // error for no memory
    assert(errno == ENOMEM); 
    arenaFree(arena);
}
