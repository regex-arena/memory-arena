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
int arenaFree(struct Arena arena);
void* arenaAssignBytes(struct Arena* arena, unsigned int bytes);
int arenaPopBytes(struct Arena* arena, unsigned int bytes);

#ifdef __cplusplus
}
#endif
#endif
