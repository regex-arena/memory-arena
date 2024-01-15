# C arena memory allocator
Creation of an arena allocator with C

## What is an arena
An arena allocater is a stack based memory allocation system wich allows for custom memory lifetimes.
This means that the allocated memory can extend past its initial scope, but it allows for all memory to be
freed simeltaniously, without the need for a free call for each allocation. [More Information](https://www.cs.princeton.edu/techreports/1988/191.pdf)

## Usage
 - `struct Arena arenaAllocate(unsigned int size)`
Create arena with max size `size`. Physical memory is not allocated at this stage, instead virtual memory is reserved.

 - `int arenaFree(struct Arena arena)`
Unreserves mapping from virtual memory

 - `void* arenaAssignBytes(struct Arena* arena, unsigned int bytes)`
Moves the allocator head by `bytes` bytes and returns the old head. Marks the first `bytes` bytes after the returned address
as `PROT_READ` and `PROT_WRITE`, allowing for reading and writing.

 - `int arenaPopBytes(struct Arena* arena, unsigned int bytes)`
Decrements allocater head by `bytes` bytes.
