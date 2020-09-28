#include <stdio.h>
#include "hash_table.h"

int main() {
    int arr[8] = {
        10, 20, 30, 40, 33, 46, 50, 60,
    };
    int arr_len = sizeof(arr) / sizeof(int);
    hash_table_t *hash_table = hash_table_new(13);

    for (int i = 0; i < arr_len; i++) {
        hash_table_quadratic_set(hash_table, arr[i]);
    }

    for (int i = 0; i < 13; i++) {
        int result;
        if (hash_table_get(hash_table, i, &result)) {
            printf("%d번째: %d\n", i, result);
        }
    }

    hash_table_del(hash_table);

    return 0;
}
