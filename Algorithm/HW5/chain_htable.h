#ifndef __CHAIN_HTABLE_H__
#define __CHAIN_HTABLE_H__

#include <ctype.h>
#include <stdbool.h>
#include <stddef.h>

typedef int element_t;

typedef struct _chain_htable_node {
    element_t elem;
    struct _chain_htable_node *next;
} node_t;

typedef struct _chain_htable {
    size_t capacity; // 적재 가능한 크기
    node_t **body;
} chain_htable_t;

node_t *node_new(element_t elem);

void node_del(node_t *this);

void node_append(node_t *this, node_t *next);

/* 생성자 */
chain_htable_t *chain_htable_new(size_t capacity);

/* 소멸자 */
void chain_htable_del(chain_htable_t *this);

/* elem을 해쉬해서 버킷에 집어넣는다. 버킷은 링크드 리스트로 관리된다. */
bool chain_htable_set(chain_htable_t *this, element_t elem);

/**
 * this->body[idx] 가 값이 있는 상태면 result에 담아서 전달하고 return true.
 * 값이 없는 상태면 false를 return한다.
*/
bool chain_htable_get(chain_htable_t *this, element_t elem, element_t *result);

/* htable 내부 프린트 */
void chain_htable_show(chain_htable_t *this);

#endif /* __CHAIN_HTABLE_H__ */
