#pragma once

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    size_t size;
    size_t pos;
    void* mem;
} Arena;

#ifndef ARENA_IMPLEMENTATION

bool arena_make(Arena* arena, size_t size);
void arena_free(Arena* arena);
void* arena_alloc(Arena* arena, size_t size);
void arena_reset(Arena* arena);

#else

bool arena_make(Arena* arena, size_t size) {
    arena->mem = malloc(size);
    if(arena->mem == NULL) {
        return false;
    }

    arena->size = size;
    arena->pos = 0;
    return true;
}

void arena_free(Arena* arena) {
    free(arena->mem);
}

void* arena_alloc(Arena* arena, size_t size) {
    if(arena->pos + size > arena->size) {
        return NULL;
    }

    void* p = arena->mem + arena->pos;
    arena->pos += size;
    return p;
}

void arena_reset(Arena* arena) {
    arena->pos = 0;
}

#endif /* ARENA_IMPLEMENTATION */