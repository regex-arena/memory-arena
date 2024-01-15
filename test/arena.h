#ifndef __ARENA_H__
#define __ARENA_H__
#ifdef __cplusplus
extern "C" {
#endif
struct Arena {
    void* start;
    void* head;
    void* end;
    int size;
};

// Pages allocated by arena cannot be executed
//  - This may be updated int the future (potentialy a flag?)
struct Arena arenaAllocate(unsigned int size);
void arenaFree(struct Arena arena);
void* arenaAssignBytes(struct Arena arena, unsigned int bytes);
void arenaPopBytes(struct Arena arena, unsigned int bytes);
int arenaIndex(struct Arena arena);
void arenaRolback(struct Arena arena, unsigned int bytes);

#ifdef __cplusplus
}
#endif
#endif
