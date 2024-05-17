#include <stdlib.h>
#include <stdio.h>
#include "my_data.h"
#include "string.h"
#include "mess.h"

void* my_data_init(char* llastname, int year, enum MAJOR major) 
{
	MY_STUDENT* pdata = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (!pdata) 
	{
		my_mess_fun(MY_MESS_MEM_ALLOC_ERROR);
		return NULL;
	}
	if (pdata)
	{
		size_t size = strlen(llastname) + 1;
		pdata->length = size;
		pdata->lastname = (char*)malloc(size * sizeof(char));
		if (!pdata->lastname) 
		{
			my_mess_fun(MY_MESS_MEM_ALLOC_ERROR);
			return NULL;
		}
		strcpy(pdata->lastname, llastname);
		pdata->year = year;
		pdata->degree = major;
	}
	return (void*)(pdata);
}

void my_data_free(void* ptr)
{
	MY_STUDENT* pdata = (MY_STUDENT*)ptr;
	if (pdata)
	{
		free(pdata->lastname);
		pdata->lastname = NULL;

		free(pdata);
		pdata = NULL;
	}
}

void* my_data_push(char* lastname, int year, enum MAJOR major) 
{
	return my_data_init(lastname, year, major);
}

void my_data_print(void* ptr) 
{
	MY_STUDENT* p = (MY_STUDENT*)ptr;
	if (p)
	{
		printf("|%-17s|", p->lastname);
		printf("%-17d|", p->year);
		switch (p->degree) 
		{
			case COMPUTER_SCIENCE:
				printf("%-17s|\n", "Computer Science");
				break;
			case LAW:
				printf("%-17s|\n", "Law");
				break;
			case ECONOMICS:
				printf("%-17s|\n", "Economics");
				break;
			case MEDICINE:
				printf("%-17s|\n", "Medicine");
				break;
			case SOCIAL_SCIENCES:
				printf("%-17s|\n", "Social Sciences");
				break;
		}
	}
}

int my_data_lastname(void* pcurrentdata, void* psearchdata)
{
	MY_STUDENT* pcurrent = (MY_STUDENT*)pcurrentdata;
	MY_STUDENT* psearch = (MY_STUDENT*)psearchdata;

	if (strcmp(pcurrent->lastname, psearch->lastname) == 0)
		return 1;

	return 0;
}

int my_data_year(void* pcurrentdata, void* psearchdata)
{
	MY_STUDENT* pcurrent = (MY_STUDENT*)pcurrentdata;
	MY_STUDENT* psearch = (MY_STUDENT*)psearchdata;

	if (pcurrent->year == psearch->year)
		return 1;

	return 0;
}

int my_data_major(void* pcurrentdata, void* psearchdata)
{
	MY_STUDENT* pcurrent = (MY_STUDENT*)pcurrentdata;
	MY_STUDENT* psearch = (MY_STUDENT*)psearchdata;

	if (pcurrent->degree == psearch->degree)
		return 1;

	return 0;
}

int my_data_save(void* ptr, FILE* filename) 
{
	MY_STUDENT* pdata = (MY_STUDENT*)ptr;

	if (fwrite(pdata, sizeof(MY_STUDENT), 1, filename) != 1)
		return 0;
	if (fwrite(pdata->lastname, pdata->length * sizeof(pdata->lastname[0]), 1, filename) != 1)
		return 0;

	return 1;
}

void* my_data_load(FILE* filename)
{
	MY_STUDENT* temp = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));
	if (!temp)
	{
		my_mess_fun(MY_MESS_MEM_ALLOC_ERROR);
	}

	memset(temp, 0, sizeof(MY_STUDENT));

	if (fread(temp, sizeof(MY_STUDENT), 1, filename) != 1)
		return 0;

	temp->lastname = (char*)malloc(temp->length * sizeof(char));

	if (fread(temp->lastname, temp->length * sizeof(char), 1, filename) != 1)
		return 0;

	return temp;

}