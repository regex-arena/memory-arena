#ifndef __ARENA_H__
#define __ARENA_H__
#ifdef __cplusplus
extern "C" {
#endif

struct Arena {
    static void* address;
    static int index;
};

struct Arena arenaAllocate();
void arenaFree(struct Arena arena);
void* arenaAssignBytes(struct Arena arena);
void arenaPopBytes(struct Arena arena);
int arenaIndex(struct Arena arena);
void arenaRolback(struct Arena arena);

#ifdef __cplusplus
}
#endif
#endif
