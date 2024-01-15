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

void arenaFree(struct Arena arena) {
    munmap(arena.start, arena.size);
}

void* arenaAssignBytes(struct Arena arena, unsigned int bytes) {
    void* allocated = arena.head;
    if (arena.head + bytes > arena.end) {
        errno = ENOMEM;
        return NULL;
    };
    return allocated;
}

void arenaPopBytes(struct Arena arena, unsigned int bytes) {
    arena.head -= bytes;
    // Protect from writing before buffer
    if (arena.start > arena.head) {
        arena.head = arena.start;
    }
}

int arenaIndex(struct Arena arena) {
    return arena.head - arena.start;
}

void arenaRolback(struct Arena arena, unsigned int bytes) {
    arena.head = arena.start + bytes;
    // Protect from writing before buffer
    if (arena.start > arena.head) {
        arena.head = arena.start;
    }
}
