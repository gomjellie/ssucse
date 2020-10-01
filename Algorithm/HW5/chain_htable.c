#include "chain_htable.h"

#include <stdlib.h>
#include <stdio.h>

/* 생성자 */
chain_htable_t *chain_htable_new(size_t capacity) {
    chain_htable_t *this = malloc(sizeof(chain_htable_t));
    this->capacity = capacity;
    this->body = calloc(capacity, sizeof(node_t *));

    return this;
}

/* 소멸자 */
void chain_htable_del(chain_htable_t *this) {
    for (size_t i = 0; i < this->capacity; i++) {
        node_t *node = this->body[i];
        while (node != NULL) {
            node_t *next = node->next;
            node_del(node);
            node = next;
        }
    }
    free(this);
}

node_t *node_new(element_t elem) {
    node_t *this = malloc(sizeof(node_t));
    this->elem = elem;
    this->next = NULL;

    return this;
}

void node_del(node_t *this) {
    free(this); // this->next 를 정리해주는 로직이 밖에서 반드시 필요함.
}

void node_append(node_t *this, node_t *next) {
    this->next = next;
}

/* elem을 해쉬해서 버킷에 집어넣는다. 버킷은 링크드 리스트로 관리된다. */
bool chain_htable_set(chain_htable_t *this, element_t elem) {
    size_t key = (size_t)elem % this->capacity;
    node_t *new_node = node_new(elem);

    new_node->next = this->body[key];
    this->body[key] = new_node;
    return true;
}

/**
 * 검색 성공하면 result에 담아서 전달하고 return true.
 * 검색 실패시 false를 return한다.
*/
bool chain_htable_get(chain_htable_t *this, element_t elem, element_t *result) {
    size_t key = (size_t)elem % this->capacity;
    node_t *node = this->body[key];

    while (node != NULL) {
        if (node->elem == elem) {
            *result = node->elem;
            return true;
        }
        node = node->next;
    }
    
    return false;
}

void chain_htable_show(chain_htable_t *this) {
    for (size_t i = 0; i < this->capacity; i++) {
        printf("%2zu : ", i);
        node_t *node = this->body[i];
        while (node != NULL) {
            element_t val = node->elem;
            printf("%d ->  ", val);
            node = node->next;
        }
        puts("NULL");
    }
    puts("");
}
