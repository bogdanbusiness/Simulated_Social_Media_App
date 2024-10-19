#ifndef HELPERS_H
#define HELPERS_H

#include <stdint.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "users.h"

// Definitions

typedef int16_t (*compare_fn)(const void *, const void *);

// Functions

void __users_extract(char *input, uint16_t *cur_user, uint16_t *friend_user);

void __user_extract(char *input, uint16_t *cur_user);

int16_t compare_uint16(const void *a, const void *b);

void bubble_sort(void *base, size_t num, size_t size, compare_fn compare);

#endif /* HELPERS_H */