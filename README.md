# C arena memory allocator
Creation of an arena allocator with C

## What is an arena
https://www.cs.princeton.edu/techreports/1988/191.pdf

## Usage
! INCLUDE SPECIFICATION
struct Arena arenaAllocate(int size);
void arenaFree(struct Arena arena);
void* arenaAssignBytes(struct Arena arena);
void arenaPopBytes(struct Arena arena);
int arenaIndex(struct Arena arena);
void arenaRolback(struct Arena arena);

## Completion
 [x] Implement memory arena interface
 [ ] Implement tests for allocation and free
 [ ] Implement tests for asignments
 [ ] Implement tests for data rollback
 [ ] Implement tests for buffer overflow
