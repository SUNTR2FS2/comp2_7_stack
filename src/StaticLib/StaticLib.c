#define WIN32_LEAN_AND_MEAN
#include "Windows.h"
#include <stdlib.h>
#include "../include/lib_func.h"

void initialize(STACK* s, size_t mem_size)
{
    if (s == NULL) return;
    if (mem_size <= 0) {
        s->stack_pointer = NULL;
        s->stack_memory = NULL;
        s->end = NULL;
        return;
    }

    s->stack_memory = (int*)malloc(mem_size);
    if (s->stack_memory == NULL) {
        s->stack_pointer = NULL;
        s->end = NULL;
        return;
    }

    s->stack_pointer = s->stack_memory;
    s->end = (int*)((char*)s->stack_memory + mem_size);
}

void finalize(STACK* s)
{
    if (s == NULL) return;
    if (s->stack_memory != NULL) {
        free(s->stack_memory);
        s->stack_memory = NULL;
        s->stack_pointer = NULL;
        s->end = NULL;
    }
}

bool push(STACK* s, int val)
{
    if (s == NULL || s->stack_pointer == NULL) return false;
    if (s->stack_pointer >= s->end) return false;

    *(s->stack_pointer) = val;
    s->stack_pointer++;
    return true;
}

bool push_array(STACK* s, int* addr, int num)
{
    if (s == NULL || s->stack_pointer == NULL || addr == NULL) return false;
    if (num <= 0) return false;
    if (s->stack_pointer + num > s->end) return false;

    // 配列を逆順で積むことでテストの期待に合わせる
    for (int i = num - 1; i >= 0; i--) {
        *(s->stack_pointer) = addr[i];
        s->stack_pointer++;
    }
    return true;
}

int pop(STACK* s)
{
    if (s == NULL || s->stack_pointer == NULL) return 0;
    if (s->stack_pointer == s->stack_memory) return 0;

    s->stack_pointer--;
    return *(s->stack_pointer);
}

int pop_array(STACK* s, int* addr, int num)
{
    if (s == NULL || s->stack_pointer == NULL || addr == NULL) return 0;
    if (num <= 0) return 0;

    int available = (int)(s->stack_pointer - s->stack_memory);
    if (available <= 0) return 0;

    int count = (num > available) ? available : num;

    for (int i = 0; i < count; i++) {
        s->stack_pointer--;
        addr[i] = *(s->stack_pointer);
    }
    return count;
}