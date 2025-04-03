#pragma once
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#define DECLARE_LINKED_LIST(TYPE) \
    typedef struct Node_##TYPE { \
        TYPE data; \
        struct Node_##TYPE* next; \
    } Node_##TYPE; \
    Node_##TYPE* node_##TYPE##_create(TYPE);\
    void node_##TYPE##destroy(Node##TYPE*);\
    \
    typedef struct { \
        Node_##TYPE* head; \
        Node_##TYPE* tail; \
        size_t length; \
    } List_##TYPE; \
    \
    List_##TYPE* list_##TYPE##_create(void); \
    void list_##TYPE##destroy(List##TYPE* list); \
    bool list_##TYPE##insert(List##TYPE* list, TYPE data, size_t pos); \
    bool list_##TYPE##append(List##TYPE* list, TYPE data); \
    bool list_##TYPE##remove_at(List##TYPE* list, size_t pos); \
    bool list_##TYPE##get(const List##TYPE* list, size_t pos, TYPE* out); \
    size_t list_##TYPE##length(const List##TYPE* list); \
    void list_##TYPE##print(const List##TYPE* list, void (*print_fn)(TYPE));

#define IMPLEMENT_LINKED_LIST(TYPE) \
    Node_##TYPE* node_##TYPE##_create(TYPE data){\
        Node_##TYPE* new_node = malloc(sizeof(Node_##TYPE)); \
        new_node->data = data;\
        new_node->next = NULL;\
        return new_node;\
    }\
    void node_##TYPE##destroy(Node##TYPE *node){\
        free(node);\
    }\
    List_##TYPE* list_##TYPE##_create(void) { \
        List_##TYPE* list = malloc(sizeof(List_##TYPE)); \
        if (!list) return NULL; \
        list->head = list->tail = NULL; \
        list->length = 0; \
        return list; \
    } \
    void list_##TYPE##destroy(List##TYPE* list) { \
        if (!list) return; \
        Node_##TYPE* current = list->head; \
        for (size_t i = 0; i < list->length; ++i) { \
            Node_##TYPE* temp = current; \
            current = current->next; \
            free(temp); \
        } \
        free(list); \
    } \
    bool list_##TYPE##insert(List##TYPE* list, TYPE data, size_t pos) { \
        if (!list || pos > list->length) return false; \
        Node_##TYPE* new_node = node_##TYPE##_create(data); \
        if (!new_node) return false; \
        if (list->length == 0) { \
            new_node->next = new_node; \
            list->head = list->tail = new_node; \
        } else if (pos == 0) { \
            new_node->next = list->head; \
            list->head = new_node; \
            list->tail->next = new_node; \
        } else if (pos == list->length) { \
            new_node->next = list->head; \
            list->tail->next = new_node; \
            list->tail = new_node; \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            new_node->next = current->next; \
            current->next = new_node; \
        } \
        list->length++; \
        return true; \
    } \
    bool list_##TYPE##append(List##TYPE* list, TYPE data) { \
        return list_##TYPE##_insert(list, data, list->length); \
    } \
    bool list_##TYPE##remove_at(List##TYPE* list, size_t pos) { \
        if (!list || pos >= list->length) return false; \
        Node_##TYPE* to_delete = NULL; \
        if (pos == 0) { \
            to_delete = list->head; \
            list->head = list->head->next; \
            list->tail->next = list->head; \
            if (list->length == 1) { \
                list->head = list->tail = NULL; \
            } \
        } else { \
            Node_##TYPE* current = list->head; \
            for (size_t i = 0; i < pos - 1; ++i) { \
                current = current->next; \
            } \
            to_delete = current->next; \
            current->next = to_delete->next; \
            if (pos == list->length - 1) { \
                list->tail = current; \
            } \
        } \
        free(to_delete); \
        list->length--; \
        return true; \
    } \
    bool list_##TYPE##get(const List##TYPE* list, size_t pos, TYPE* out) { \
        if (!list || !out || pos >= list->length) return false; \
        Node_##TYPE* current = list->head; \
        for (size_t i = 0; i < pos; ++i) { \
            current = current->next; \
        } \
        *out = current->data; \
        return true; \
    } \
    size_t list_##TYPE##length(const List##TYPE* list) { \
        return list ? list->length : 0; \
    } \
    void list_##TYPE##print(const List##TYPE* list, void (*print_fn)(TYPE)) { \
        if (!list || !print_fn) return; \
        printf("["); \
        Node_##TYPE* current = list->head; \
        for (size_t i = 0; i < list->length; ++i) { \
            print_fn(current->data); \
            if (i != list->length - 1) printf(", "); \
            current = current->next; \
        } \
        printf("]\n"); \
    }


#ifdef LINKED_LIST_IMPLEMENTATION
IMPLEMENT_LINKED_LIST(int)
IMPLEMENT_LINKED_LIST(char)
IMPLEMENT_LINKED_LIST(float)
#endif