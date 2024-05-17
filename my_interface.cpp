#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "my_interface.h"
#include "my_data.h"
#include "my_stack.h"
#include "mess.h"

#pragma warning (disable : 4996)

static char* tab[] =
{
	(char*)"0 - free stack",
	(char*)"1 - push data",
	(char*)"2 - pop data",
	(char*)"3 - search data",
	(char*)"4 - save data to file",
	(char*)"5 - load data from file",
	(char*)"6 - exit"
};

static char* majors[] =
{
	(char*)"0 - computer science",
	(char*)"1 - law",
	(char*)"2 - economics",
	(char*)"3 - medicine",
	(char*)"4 - social sciences"
};

static char* search[] =
{
	(char*)"0 - Lastname",
	(char*)"1 - Year",
	(char*)"2 - Major"
};

void myMenu()
{
	my_stack_init(my_data_free, my_data_print, my_data_save, my_data_load);
	int choice = 0;
	while (1)
	{

		display();
		show_menu();
		choice = input_max(MY_INTERFACE_TOTAL);
		switch (choice)
		{
		case MY_INTERFACE_FREE: clear();
			break;
		case MY_INTERFACE_PUSH: push();
			break;
		case MY_INTERFACE_POP: pop();
			break;
		case MY_INTERFACE_SEARCH: find();
			break;
		case MY_INTERFACE_SAVE: save();
			break;
		case MY_INTERFACE_LOAD: load();
			break;
		case MY_INTERFACE_EXIT: clear();
			return;
		default:
			printf("INCORRECT OPTION! \n\n");
		};
	}
}

void show_menu()
{
	size_t n;
	for (n = 0; n < MY_INTERFACE_TOTAL; ++n)
	{
		printf("%s\n", tab[n]);
	}
}

int input()
{
	int nr, k = 1;

	while (k) {
		if (scanf("%d", &nr) == 1 && nr >= 0)
			k = 0;
		else
		{
			printf("Input number >=0\n");
		}

		while (getchar() != '\n');
	}

	return nr;
}

int input_max(int max)
{
	int nr, k = 1;

	while (k) {
		if (scanf("%d", &nr) == 1 && nr >= 0 && nr < max)
			k = 0;
		else
		{
			printf("Input number >=0 and <=%d\n", max - 1);
		}

		while (getchar() != '\n');
	}

	return nr;
}

void display() 
{
	my_stack_display();
}

void push()
{
	int flag = 1;
	char lastname[256];
	int year, major;
	printf("Lastname:\n");
	scanf_s("%s", lastname, (unsigned)sizeof(lastname));
	printf("Year:\n");
	year = input();
	printf("Major:\n");
	show_majors();
	major = input_max(MAJOR_TOTAL);
	printf("\n");

	void* pdata = my_data_push(lastname, year, (MAJOR)major);
	if (!my_stack_push(pdata))
		my_mess_fun(MY_MESS_MEM_ALLOC_ERROR);

}

void pop()
{
	void* temp = my_stack_pop();
	if (temp != NULL) {
		printf("\n\nData popped:\n");
		my_data_print(temp);
		printf("\n\n");
	}
	my_data_free(temp);
}

void clear()
{
	my_stack_free();
}

void find()
{
	size_t n, choice;
	printf("\nSelect search criterion: \n");
	for (n = 0; n < FIND_TOTAL; ++n)
	{
		printf("%s\n", search[n]);
	}
	choice = input_max(MAJOR_TOTAL);
	switch (choice)
	{
	case FIND_LASTNAME: find_lastname();
		break;
	case FIND_YEAR: find_year();
		break;
	case FIND_MAJOR: find_major();
		break;
	default:
		printf("INCORRECT OPTION\n");
	};
}

void save() 
{
	my_stack_save();
}

void load() 
{
	my_stack_load();
}

void find_lastname()
{
	char str[256];
	printf("Input lastname:\n");
	scanf_s("%s", str, (unsigned)sizeof(str));

	MY_STUDENT* searchdata = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!searchdata)
	{
		my_mess_fun(MY_MESS_MEM_ALLOC_ERROR);
		return;
	}

	memset(searchdata, 0, sizeof(MY_STUDENT));
	size_t size = strlen(str) + 1;
	searchdata->lastname = (char*)malloc(size * sizeof(char));

	if (!searchdata->lastname)
	{
		my_mess_fun(MY_MESS_MEM_ALLOC_ERROR);
		return;
	}
	strcpy(searchdata->lastname, str);

	void* psearch = my_stack_search(searchdata, my_data_lastname, 1);

	if (psearch)
	{
		printf("Data found: \n");
		my_data_print(psearch);
	}
	else
		printf("No data found");

	while (psearch)
	{
		psearch = my_stack_search(searchdata, my_data_lastname, 0);
		if (psearch)
		{
			my_data_print(psearch);
		}
	}
	printf("\n\n");

	my_data_free(searchdata);
}

void find_year()
{
	int search_year;
	printf("Input year:\n");
	search_year = input();

	MY_STUDENT* searchdata = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!searchdata)
	{
		my_mess_fun(MY_MESS_MEM_ALLOC_ERROR);
		return;
	}

	memset(searchdata, 0, sizeof(MY_STUDENT));

	searchdata->year = search_year;

	void* psearch = my_stack_search(searchdata, my_data_year, 1);

	if (psearch)
	{
		printf("Data found: \n");
		my_data_print(psearch);
	}
	else
		printf("No data found");

	while (psearch)
	{
		psearch = my_stack_search(searchdata, my_data_year, 0);
		if (psearch)
		{
			my_data_print(psearch);
		}
	}
	printf("\n\n");

	my_data_free(searchdata);
}

void find_major()
{
	int search_major;
	printf("Choose major:\n");
	show_majors();
	search_major = input_max(MAJOR_TOTAL);

	MY_STUDENT* searchdata = (MY_STUDENT*)malloc(sizeof(MY_STUDENT));

	if (!searchdata)
	{
		my_mess_fun(MY_MESS_MEM_ALLOC_ERROR);
		return;
	}

	memset(searchdata, 0, sizeof(MY_STUDENT));

	searchdata->degree = (MAJOR)search_major;

	void* psearch = my_stack_search(searchdata, my_data_major, 1);

	if (psearch)
	{
		printf("Data found: \n");
		my_data_print(psearch);
	}
	else
		printf("No data found");

	while (psearch)
	{
		psearch = my_stack_search(searchdata, my_data_major, 0);
		if (psearch)
		{
			my_data_print(psearch);
		}
	}
	printf("\n\n");

	my_data_free(searchdata);

}

void show_majors() 
{
	size_t n;
	for (n = 0; n < MAJOR_TOTAL; ++n)
	{
		printf("%s\n", majors[n]);
	}
}
