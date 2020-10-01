#include <stdio.h>
#include "hash_table.h"
#include "chain_htable.h"

#define Q3
// #define Q4
// #define Q5

int main() {
    int arr[8] = {
        10, 20, 30, 40, 33, 46, 50, 60,
    };
    int arr_len = sizeof(arr) / sizeof(int);

#ifdef Q3
    hash_table_t *hash_table = hash_table_new(13);

    for (int i = 0; i < arr_len; i++) {
        hash_table_linear_set(hash_table, arr[i]);
        if (i < arr_len - 4) continue;
        printf("|%3d삽입 |\n", arr[i]);
        hash_table_show(hash_table);
    }

    hash_table_del(hash_table);
#endif /* Q3 */

#ifdef Q4
    hash_table_t *hash_table = hash_table_new(13);

    for (int i = 0; i < arr_len; i++) {
        hash_table_quadratic_set(hash_table, arr[i]);
        if (i < arr_len - 4) continue;
        printf("|%3d삽입 |\n", arr[i]);
        hash_table_show(hash_table);
    }

    hash_table_del(hash_table);

#endif /* Q4 */

#ifdef Q5
    chain_htable_t *htable = chain_htable_new(13);

    for (int i = 0; i < arr_len; i++) {
        chain_htable_set(htable, arr[i]);
        if (i < arr_len - 4) continue;
        printf("%3d삽입\n", arr[i]);
        chain_htable_show(htable);
    }
    chain_htable_del(htable);
#endif /* Q5 */
    return 0;
}
