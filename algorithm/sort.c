#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <limits.h>

#define SWAP(x, y) do { typeof(x) SWAP = x; x = y; y = SWAP; } while (0)
#define MAX(a,b) ((a) > (b) ? a : b)
#define MIN(a,b) ((a) < (b) ? a : b)
#define RAND_HALF (RAND_MAX / 2)

#define MAX_ARR_LEN 10
#define PRINT_STEP

typedef int (*cmp_f)(const void *a, const void *b);

int cmp_int(const void *a, const void *b) {
    int e1 = *(int *)a;
    int e2 = *(int *)b;
    if (e1 < e2) return -1;
    if (e1 == e2) return 0;
    return 1;
}

int cmp_double(const void *a, const void *b) {
    double e1 = *(double *)a;
    double e2 = *(double *)b;
    if (e1 < e2) return -1;
    if (e1 == e2) return 0;
    return 1;
}

void swap(void *a, void *b, size_t sz) {
    void *tmp = malloc(sz);
    memcpy(tmp, a, sz);
    memcpy(a, b, sz);
    memcpy(b, tmp, sz);

    free(tmp);
}

/**
 * arr: 소팅할 배열의 시작 주소값
 * arr_len: 소팅할 배열의 길이 ex) sizeof(arr) / sizeof(int)
 * sz: 배열 원소하나의 크기 ex) sizeof(int)
 * cmp: 배열 원소의 비교함수
 */
void selection_sort(void *arr, size_t arr_len, size_t sz, cmp_f cmp);
void insertion_sort(void *arr, size_t arr_len, size_t sz, cmp_f cmp);
void bubble_sort(void *arr, size_t arr_len, size_t sz, cmp_f cmp);
void heap_sort(void *arr, size_t arr_len, size_t sz, cmp_f cmp);
void quick_sort(void *arr, int l, int r, size_t sz, cmp_f cmp);

/**
 * 최초 호출시 넘겨줘야 하는 값은 다음과 같다
 * arr: 배열의 시작 주소값
 * p: 0
 * r: length - 1
 * sz: 원소 하나의 크기
 * cmp: 비교함수
 */
void merge_sort(void *arr, size_t p, size_t r, size_t sz, cmp_f cmp);

/**
 * arr: 프린트할 배열의 시작 주소값
 * arr_len: 배열의 길이 ex) sizeof(arr) / sizeof(int)
 */
void arr_print_int(void *arr, size_t arr_len);
void arr_print_double(void *arr, size_t arr_len);

void __merge(void *arr, size_t p, size_t q, size_t r, size_t sz, cmp_f cmp);

int main() {
    srand((unsigned int)time(NULL));
//    int arr_q1[MAX_ARR_LEN] = {
//        12, 70, 30, 20, 55, 25, 40, 50,
//    };
    double arr[MAX_ARR_LEN];
    double arr_q2[MAX_ARR_LEN];
    for (int i = 0; i < MAX_ARR_LEN; i++) {
        arr_q2[i] = (double)(rand() - RAND_HALF) / RAND_HALF;
    }
    arr_print_double(arr_q2, sizeof(arr_q2) / sizeof(double));
    
    memcpy(arr, arr_q2, sizeof(double) * MAX_ARR_LEN);
    puts("선택정렬");
    selection_sort(arr, MAX_ARR_LEN, sizeof(double), cmp_double);
    arr_print_double(arr, MAX_ARR_LEN);
    
    memcpy(arr, arr_q2, sizeof(double) * MAX_ARR_LEN);
    puts("삽입정렬");
    insertion_sort(arr, MAX_ARR_LEN, sizeof(double), cmp_double);
    arr_print_double(arr, MAX_ARR_LEN);
    
    memcpy(arr, arr_q2, sizeof(double) * MAX_ARR_LEN);
    puts("버블정렬");
    bubble_sort(arr, MAX_ARR_LEN, sizeof(double), cmp_double);
    arr_print_double(arr, MAX_ARR_LEN);
    
    memcpy(arr, arr_q2, sizeof(double) * MAX_ARR_LEN);
    puts("합병정렬");
    merge_sort(arr, 0, MAX_ARR_LEN - 1, sizeof(double), cmp_double);
    arr_print_double(arr, MAX_ARR_LEN);

    memcpy(arr, arr_q2, sizeof(double) * MAX_ARR_LEN);
    puts("힙소트");
    heap_sort(arr, MAX_ARR_LEN, sizeof(double), cmp_double);
    arr_print_double(arr, MAX_ARR_LEN);

    memcpy(arr, arr_q2, sizeof(double) * MAX_ARR_LEN);
    puts("퀵소트");
    quick_sort(arr, 0, MAX_ARR_LEN - 1, sizeof(double), cmp_double);
    arr_print_double(arr, MAX_ARR_LEN);
}

void arr_print_int(void *arr, size_t arr_len) {
    int *int_arr = arr;
    for (size_t i = 0; i < arr_len; i++) {
        printf("%d ", int_arr[i]);
    }
    puts("");
}

void arr_print_double(void *arr, size_t arr_len) {
    double *double_arr = arr;
    for (size_t i = 0; i < arr_len; i++) {
        printf("%.3lf ", double_arr[i]);
    }
    puts("");
}

void selection_sort(void *arr, size_t arr_len, size_t sz, cmp_f cmp) {
    static int counter = 0;
    void *biggest;
    for (int slit = arr_len - 1; 0 <= slit; slit--) { // 칸막이를 마지막에서부터 하나씩 줄여옴.
        biggest = arr; // 첫번째꺼를 biggest로
        for (int j = 0; j <= slit; j++) {
            void *tmp = (char *)arr + j * sz;
            if (cmp(biggest, tmp) == 1) continue; // biggest > tmp
            biggest = tmp;
        }
        void *tar = (char *)arr + slit * sz;
        if (tar != biggest)
            swap(tar, biggest, sz);
#ifdef PRINT_STEP
        if (counter < 5) {
            printf("%d번째 step: ", counter ++);
            arr_print_double(arr, arr_len);
        }
#endif /* PRINT_STEP */
    }
}

void insertion_sort(void *arr, size_t arr_len, size_t sz, cmp_f cmp) {
    static int counter = 0;
    for (int sel = 1; sel < arr_len; sel++) { // selected
        void *sel_ptr = (char *)arr + sel * sz;
        for (int i = 0; i < sel; i++) {
            void *tmp = (char *)arr + i * sz;

            if (cmp(sel_ptr, tmp) == 1) continue; // sel > tmp 끼워넣을 자리가 아니면 패스

            for (int j = sel; j > i; j--) { // shift & insert
                void *ptr1 = (char *)arr + j * sz;
                void *ptr2 = (char *)arr + (j - 1) * sz;
                swap(ptr1, ptr2, sz);
            }
        }
#ifdef PRINT_STEP
        if (counter < 5) {
            printf("%d번째 step: ", counter ++);
            arr_print_double(arr, arr_len);
        }
#endif /* PRINT_STEP */
    }
}

void bubble_sort(void *arr, size_t arr_len, size_t sz, cmp_f cmp) {
    static int counter = 0;
    for (int slit = arr_len - 1; 0 <= slit; slit--) { // 칸막이를 마지막에서부터 하나씩 줄여옴.
        for (int j = 0; j < slit; j++) {
            void *addr1 = (char *)arr + j * sz;
            void *addr2 = (char *)arr + (j + 1) * sz;
            if (cmp(addr1, addr2) <= 0) continue;
            swap(addr1, addr2, sz);
        }
#ifdef PRINT_STEP
        if (counter < 5) {
            printf("%d번째 step: ", counter ++);
            arr_print_double(arr, arr_len);
        }
#endif /* PRINT_STEP */
    }
}

/* 처음 호출시 q = 0, r = len - 1 */
void merge_sort(void *arr, size_t p, size_t r, size_t sz, cmp_f cmp) {
    static int counter = 0;
    if (p >= r) return;
    size_t q = (p + r) / 2;
    merge_sort(arr, p, q, sz, cmp);
    merge_sort(arr, q + 1, r, sz, cmp);
    __merge(arr, p, q, r, sz, cmp);
#ifdef PRINT_STEP
    if (counter < 5) {
        printf("%d번째 step: ", counter ++);
        arr_print_double((char *)arr + p * sz, r - p + 1);
    }
#endif /* PRINT_STEP */
}

void __merge(void *arr, size_t p, size_t q, size_t r, size_t sz, cmp_f cmp) {
    size_t len = r - p + 1;
    size_t start = p, mid = q;
    void *res = malloc(len * sz);
    
    for (int i = 0; i < len; i++) {
        void *p1 = (char *)arr + p * sz;
        void *p2 = (char *)arr + (q + 1) * sz;

        if (r <= q || (p <= mid && cmp(p1, p2) < 0)) { // *p1 < *p2
            memcpy((char *)res + i * sz, p1, sz);
            p++;
        } else {
            memcpy((char *)res + i * sz, p2, sz);
            q++;
        }
    }

    memcpy((char *)arr + start * sz, res, len * sz);
    free(res);
}

typedef struct _heap {
    void *body;
    size_t capacity;
    size_t length;
    size_t sz; // sizeof(type)
    cmp_f cmp;
} heap_t;

heap_t *heap_new(size_t capacity, size_t sz, cmp_f cmp) {
    heap_t *this = malloc(sizeof(heap_t));
    this->body = malloc(sz * capacity);
    this->capacity = capacity;
    this->sz = sz;
    this->cmp = cmp;
    this->length = 0;

    return this;
}

bool heap_empty(heap_t *this) {
    return this->length == 0;
}

void heap_destroy(heap_t *this) {
    free(this->body);
    free(this);
}

void *heap_top(heap_t *this) {
    if (heap_empty(this)) NULL;
    
    return (char *)this->body + this->sz;
}

void heap_push(heap_t *this, void* elem) {
    size_t sz = this->sz;
    size_t cur = ++this->length;
    
    while (cur != 1 && this->cmp(elem, (char *)this->body + (cur / 2) * sz) != 1) {
        memcpy((char *)this->body + cur * sz, (char *)this->body + (cur / 2) * sz, sz);
        cur /= 2;
    }
    memcpy((char *)this->body + cur * sz, elem, sz);
}

void heap_pop(heap_t *this) {
    size_t sz = this->sz;
    if (heap_empty(this)) return;

    void *last_elem = malloc(sz);
    memcpy(last_elem, (char *)this->body + (this->length--) * sz, sz);

    size_t cur = 1;
    size_t child = 2;

    while (child <= this->length) {
        if (child < this->length && this->cmp((char *)this->body + (child + 1) * sz, (char *)this->body + child * sz) != 1)
            child++;
        if (this->cmp(last_elem, (char *)this->body + child * sz) != 1) break;

        memcpy((char *)this->body + cur * sz, (char *)this->body + child * sz, sz);
        cur = child; child *= 2;
    }
    memcpy((char *)this->body + cur * sz, last_elem, sz);

    free(last_elem);
}

void heap_sort(void *arr, size_t arr_len, size_t sz, cmp_f cmp) {
    heap_t *heap = heap_new(arr_len + 2, sz, cmp);

    for (size_t i = 0; i < arr_len; i++) {
        heap_push(heap, (char *)arr + i * sz);
    }

    for (size_t i = 0; i < arr_len; i++) {
        void *res = heap_top(heap);
        memcpy((char *)arr + i * sz, res, sz);
        heap_pop(heap);

#ifdef PRINT_STEP
        if (i < 5) {
            printf("%zu번째 step: ", i);
            arr_print_double(arr, arr_len);
        }
#endif /* PRINT_STEP */
    }
    
    heap_destroy(heap);
}

void quick_sort(void *arr, int l, int r, size_t sz, cmp_f cmp) {
    static int counter = 0;
    if (l >= r) return;
    size_t pivot;

#ifdef PRINT_STEP
    if (counter < 5) {
        printf("%d번째 step: ", counter ++);
        arr_print_double((char *)arr + l * sz, r - l);
    }
#endif /* PRINT_STEP */

    void *std = (char *)arr + r * sz;
    for (int i = 0, j = 0; j <= r; j++) {
        void *elem = (char *)arr + j * sz;
        if (cmp(elem, std) > 0) { // *elem > *std
            continue;
        }
        swap((char *)arr + i * sz, (char *)arr + j * sz, sz);
        pivot = i++;
    }

    quick_sort(arr, l, pivot - 1, sz, cmp);
    quick_sort(arr, pivot + 1, r, sz, cmp);
}
