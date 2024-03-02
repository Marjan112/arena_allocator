#pragma once

#include <stdlib.h>

typedef struct {
    size_t size;
    size_t pos;
    void* mem;
} Arena;

#ifndef ARENA_IMPLEMENTATION

Arena* arena_make(size_t size);
void arena_free(Arena* arena);
void* arena_alloc(Arena* arena, size_t size);
void arena_reset(Arena* arena);

#else

Arena* arena_make(size_t size) {
    Arena* allocator = (Arena*)malloc(sizeof(Arena));
    if(allocator == NULL) {
        return NULL;
    }

    allocator->mem = malloc(size);
    if(allocator->mem == NULL) {
        return NULL;
    }

    allocator->size = size;
    allocator->pos = 0;
    return allocator;
}

void arena_free(Arena* arena) {
    free(arena->mem);
    free(arena);
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