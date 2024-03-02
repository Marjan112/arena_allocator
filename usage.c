#include <stdio.h>

#define ARENA_IMPLEMENTATION
#include "arena.h"

int main() {
    // allocate 1MB for arena
    Arena* arena = arena_make(1024 * 1024);

    int* n = arena_alloc(arena, sizeof(int));
    *n = 69;

    printf("%p: %d\n", n, *n);

    long long* lln = arena_alloc(arena, sizeof(long long));
    *lln = 9223372036854775807LL;

    printf("%p: %lld\n", lln, *lln);

    // free everything in arena and arena itself
    arena_free(arena);
    return 0;
}