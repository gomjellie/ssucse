#include "hash_table.h"

#include <stdlib.h>
#include <stdbool.h>

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

void hash_table_linear_set(hash_table_t *this, element_t elem) {
    for (size_t i = 0; i < this->capacity; i++) {
        size_t target_idx = (elem + i) % this->capacity;
        if (__hash_table_is_slot_empty(this, target_idx) == false) continue;
        
        this->body[target_idx] = (slot_t) {
            .elem = elem,
            .is_set = true,
        };
        return;
    }
}

void hash_table_quadratic_set(hash_table_t *this, element_t elem) {
    // 구현하기.
}

bool hash_table_get(hash_table_t *this, size_t idx, element_t *result) {
    if (__hash_table_is_slot_empty(this, idx)) {
        return false;
    }

    *result = this->body[idx].elem;
    return true;
}

static bool __hash_table_is_slot_empty(hash_table_t *this, size_t idx) {
    if (this->body[idx].is_set == false) return true;

    return false;
}
