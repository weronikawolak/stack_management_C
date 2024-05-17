#pragma once
#pragma warning (disable : 4996)

#ifndef MY_DATA_H
#define MY_DATA H

enum MAJOR
{
	COMPUTER_SCIENCE,
	LAW,
	ECONOMICS,
	MEDICINE,
	SOCIAL_SCIENCES,
	MAJOR_TOTAL
};


struct MY_STUDENT
{
	int year;
	enum MAJOR degree;
	size_t length;
	char* lastname;
};

void* my_data_init(char* llastname, int year, enum MAJOR major);
void my_data_free(void* ptr);
void* my_data_push(char* lastname, int year, enum MAJOR major);
void my_data_print(void* ptr);

int my_data_lastname(void* pcurrentdata, void* psearchdata);
int my_data_year(void* pcurrentdata, void* psearchdata);
int my_data_major(void* pcurrentdata, void* psearchdata);

int my_data_save(void* ptr, FILE* filename);
void* my_data_load(FILE* filename);
#endif


