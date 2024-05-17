#pragma once

#ifndef MY_STACK_H
#define MY_STACK_H
#pragma warning (disable : 4996)

struct MY_STACK {
	void* pdata;
	struct MY_STACK* next;
};

typedef void(*NoData)(void* pdata);
typedef void(*PrintObject)(void* pdata);
typedef int(*File)(void* pdata, FILE* file);
typedef void* (*Load)(FILE* file);
typedef int(Find)(void* currentdata, void* searchdata);

void my_stack_init(NoData ptr, PrintObject display, File save, Load load);
void my_stack_free();
MY_STACK* my_stack_push(void* ptrData);
void* my_stack_pop();
void* my_stack_search(void* psearchdata, Find psearch, int firstentry);
void my_stack_display();

void my_stack_save();
void my_stack_load();

#endif