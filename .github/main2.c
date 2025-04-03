#include <check.h>
#include <stdlib.h>
#define LINKED_LIST_IMPLEMENTATION
#include "linked_circule_list.h"

void print_int(int value) { printf("%d ", value); }
bool int_cmp(int a, int b) { return a == b; }

START_TEST(test_list_create) {
    List_int* list = list_int_create();
    ck_assert_ptr_nonnull(list);
    ck_assert_ptr_null(list->head);
    ck_assert_ptr_null(list->tail);
    ck_assert_uint_eq(list->length, 0);
    list_int_destroy(list);
}
END_TEST

START_TEST(test_append_and_length) {
    List_int* list = list_int_create();
    ck_assert(list_int_append(list, 10));
    ck_assert_uint_eq(list_int_length(list), 1);
    ck_assert_ptr_eq(list->head, list->tail);
    ck_assert_ptr_eq(list->tail->next, list->head);
    
    ck_assert(list_int_append(list, 20));
    ck_assert_uint_eq(list_int_length(list), 2);
    ck_assert_ptr_eq(list->tail->next, list->head);
    
    list_int_destroy(list);
}
END_TEST

START_TEST(test_insert_and_get) {
    List_int* list = list_int_create();
    int value = 0;
    
    list_int_insert(list, 10, 0);
    ck_assert_ptr_eq(list->tail->next, list->head);
    
    list_int_insert(list, 30, 1);
    ck_assert_ptr_eq(list->tail->next, list->head);
    
    list_int_insert(list, 20, 1);    
    ck_assert(list_int_get(list, 1, &value));
    ck_assert_int_eq(value, 20);
    ck_assert_ptr_eq(list->tail->next, list->head);
    
    list_int_destroy(list);
}
END_TEST

START_TEST(test_remove) {
    List_int* list = list_int_create();
    list_int_append(list, 10);
    list_int_append(list, 20);
    list_int_append(list, 30);
    
    ck_assert(list_int_remove_at(list, 1));
    ck_assert_uint_eq(list_int_length(list), 2);
    ck_assert_ptr_eq(list->tail->next, list->head);
    
    list_int_remove_at(list, 0);
    list_int_remove_at(list, 0);
    ck_assert_ptr_null(list->head);
    ck_assert_ptr_null(list->tail);
    
    list_int_destroy(list);
}
END_TEST

START_TEST(test_circularity_one_element) {
    List_int* list = list_int_create();
    list_int_append(list, 42);
    ck_assert_ptr_eq(list->head, list->tail);
    ck_assert_ptr_eq(list->tail->next, list->head);
    list_int_destroy(list);
}
END_TEST

Suite* linked_list_suite(void){
    Suite* s = suite_create("Circular List");
    TCase* tc = tcase_create("Core");
    tcase_add_test(tc, test_list_create);
    tcase_add_test(tc, test_append_and_length);
    tcase_add_test(tc, test_insert_and_get);
    tcase_add_test(tc, test_remove);
    tcase_add_test(tc, test_circularity_one_element);
    suite_add_tcase(s, tc);
    return s;
}

int main(void) {
    SRunner* sr = srunner_create(linked_list_suite());
    srunner_run_all(sr, CK_NORMAL);
    int failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}