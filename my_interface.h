#pragma once
#ifndef MY_INTERFACE_H
#define MY_INTERFACE_H

enum MY_INTERFACE
{
	MY_INTERFACE_FREE,
	MY_INTERFACE_PUSH,
	MY_INTERFACE_POP,
	MY_INTERFACE_SEARCH,
	MY_INTERFACE_SAVE,
	MY_INTERFACE_LOAD,
	MY_INTERFACE_EXIT,
	MY_INTERFACE_TOTAL
};

enum SEARCH_DATA
{
	FIND_LASTNAME,
	FIND_YEAR,
	FIND_MAJOR,
	FIND_TOTAL
};

void myMenu();
void show_menu();

int input();
int input_max(int max);

void display();
void push();
void pop();
void clear();
void find();
void save();
void load();

void find_lastname();
void find_year();
void find_major();
void show_majors();

#endif

