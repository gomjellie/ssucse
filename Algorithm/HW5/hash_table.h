#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <ctype.h>
#include <stdbool.h>

typedef int element_t;

typedef struct _slot {
    bool is_set;
    element_t elem;
} slot_t;

typedef struct _hash {
    size_t capacity;
    slot_t *body;
} hash_table_t;

/* 생성자 */
hash_table_t *hash_table_new(size_t capacity);

/* 소멸자 */
void hash_table_del(hash_table_t *this);

/**
 * this->body[elem] 에 elem을 설정함.
 * 만약 idx자리에 넣을 수 없다면 선형으로 조사해서 넣는다.
 */
void hash_table_linear_set(hash_table_t *this, element_t elem);

/**
 * this->body[elem] 에 elem을 설정함.
 * 만약 idx자리에 넣을 수 없다면 2차원 조사를해서 넣는다.
 */
void hash_table_quadratic_set(hash_table_t *this, element_t elem);

/**
 * this->body[idx] 가 값이 있는 상태면 result에 담아서 전달하고 return true.
 * 값이 없는 상태면 false를 return한다.
*/
bool hash_table_get(hash_table_t *this, size_t idx, element_t *result);

#endif /* __HASH_TABLE_H__ */
