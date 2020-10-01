#include "hash_table.h"

#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <math.h>

/* body[idx]에 설정된값이 없어서 비었다면 true, 아니면 false */
static bool __hash_table_is_slot_empty(hash_table_t *this, size_t idx);

hash_table_t *hash_table_new(size_t capacity) {
    hash_table_t *this = malloc(sizeof(hash_table_t));
    this->body = calloc(capacity, sizeof(element_t));
    this->capacity = capacity;

    return this;
}

void hash_table_del(hash_table_t *this) {
    free(this->body);
    free(this);
}

bool hash_table_linear_set(hash_table_t *this, element_t elem) {
    size_t key = (size_t)elem % this->capacity;
    for (size_t i = 0; i < this->capacity; i++) {
        size_t slot_idx = (key + i) % this->capacity;
        if (__hash_table_is_slot_empty(this, slot_idx) == false) continue;
        
        this->body[slot_idx] = (bucket_t) {
            .elem = elem,
            .is_set = true,
        };
        return true;
    }
    return false;
}

bool hash_table_quadratic_set(hash_table_t *this, element_t elem) {
    // 구현하기.
    size_t key = (size_t)elem;
    for (size_t i = 0; i < this->capacity; i++) {
        size_t jump = (size_t)pow(i, 2); // i ^ 2 만큼 점프 하면서 탐색
        size_t slot_idx = (key + jump) % this->capacity;
        if (__hash_table_is_slot_empty(this, slot_idx) == false) continue;
        
        this->body[slot_idx] = (bucket_t) {
            .elem = elem,
            .is_set = true,
        };
        return true;
    }
    return false;
}

bool hash_table_get(hash_table_t *this, size_t idx, element_t *result) {
    if (__hash_table_is_slot_empty(this, idx)) {
        return false;
    }

    *result = this->body[idx].elem;
    return true;
}

void hash_table_show(hash_table_t *this) {
    for (int i = 0; i < 13; i++) {
        int result;
        if (hash_table_get(this, i, &result)) {
            printf("|%2d | %3d|\n", i, result);
            continue;
        }
        printf("|%2d | N/A|\n", i);
    }
    puts("+---+----+");
}

static bool __hash_table_is_slot_empty(hash_table_t *this, size_t idx) {
    if (this->body[idx].is_set == false) return true;

    return false;
}
