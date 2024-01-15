#include "arena.h"
#include <assert.h>
#include <stdio.h>

int main() {
    struct Arena arena = arenaAllocate(16*sizeof(int));
    assert(arena.size != 0);
    arenaFree(arena);
}
