#include <errno.h>
#include <stddef.h>
#include <sys/mman.h>

struct Arena {
    void* start;
    void* head;
    void* end;
    int size;
};

struct Arena arenaAllocate(unsigned int size) {
    struct Arena arena;
    arena.head = arena.start = mmap(
        NULL,
        size,
        PROT_NONE,
        MAP_PRIVATE | MAP_ANON,
        -1,
        0
    );
    if (arena.start == MAP_FAILED) {
        struct Arena a = { 0 };
        return a;
    }
    arena.end = arena.start + size;
    arena.size = size;
    return arena;
}

int arenaFree(struct Arena arena) {
    return munmap(arena.start, arena.size);
}

void* arenaAssignBytes(struct Arena* arena, unsigned int bytes) {
    void* allocated = arena->head;
    if (arena->head + bytes > arena->end) {
        errno = ENOMEM;
        return NULL;
    };
    if (mprotect(arena->head, bytes, PROT_READ | PROT_WRITE) == -1) {
        return NULL;
    };
    arena->head += bytes;
    return allocated;
}

int arenaPopBytes(struct Arena* arena, unsigned int bytes) {
    // Prevents writing before buffer start
    if (arena->start > arena->head - bytes) {
        bytes = arena->head - arena->start;
        arena->head = arena->start;
        return mprotect(arena->start, bytes, PROT_NONE);
    } else {
        arena->head -= bytes;
        return mprotect(arena->head, bytes, PROT_NONE);
    }
}
