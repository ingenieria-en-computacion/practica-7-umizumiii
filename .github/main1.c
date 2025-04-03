#define LINKED_LIST_IMPLEMENTATION
#include "linked_list.h"
#include <stdio.h>

void print_int(int value) {
    printf("%d", value);
}

bool int_cmp(int a, int b) {
    return a == b;
}

void print_char(char value) {
    printf("%c", value);
}

bool char_cmp(char a, char b) {
    return a == b;
}

int main() {
    // Lista de enteros
    List_int* nums = list_int_create();
    list_int_append(nums, 10);
    list_int_append(nums, 20);
    
    // Verificar circularidad en enteros
    printf("Lista enteros (circularidad): ");
    if (nums->head && nums->tail) {
        ck_assert_ptr_eq(nums->tail->next, nums->head);  // tail->next debe apuntar a head
        printf("Tail->next == Head: OK\n");
    }
    list_int_print(nums, print_int);
    list_int_destroy(nums);

    // Lista de caracteres
    List_char *chars = list_char_create();
    list_char_append(chars, 'a');
    list_char_append(chars, 'b');
    list_char_append(chars, 'c');
    
    // Verificar circularidad en caracteres
    printf("\nLista chars (circularidad): ");
    if (chars->head && chars->tail) {
        ck_assert_ptr_eq(chars->tail->next, chars->head);  // tail->next debe apuntar a head
        printf("Tail->next == Head: OK\n");
    }
    list_char_print(chars, print_char);
    list_char_destroy(chars);

    return 0;
}