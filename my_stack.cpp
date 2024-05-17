#include <stdlib.h>
#include <stdio.h>
#include "my_stack.h"
#include "mess.h"

static MY_STACK* first = NULL;
char file[] = "file.bin";
NoData pnodata;
PrintObject display;
File savefile;
Load loadfile;

void my_stack_init(NoData ppnodata, PrintObject ddisplay, File ssave, Load lload)
{
	first = NULL;
	pnodata = ppnodata;
	display = ddisplay;
	savefile = ssave;
	loadfile = lload;
}

void my_stack_free() 
{
	MY_STACK* ptr = first, * ptemp = NULL;
	while (ptr) 
	{
		(*pnodata)(ptr->pdata);
		ptemp = ptr;
		ptr = ptr->next;
		free(ptemp);
	}
	first = NULL;
}

MY_STACK* my_stack_push(void* pData) 
{
	MY_STACK* current = (MY_STACK*)malloc(sizeof(MY_STACK));
	if (!current) 
	{
		my_mess_fun(MY_MESS_MEM_ALLOC_ERROR);
		return NULL;
	}

	current->pdata = pData;
	current->next = first;
	first = current;

	return current;
}

void* my_stack_pop()
{
	MY_STACK rv;
	if (!first) 
	{
		my_mess_fun(MY_MESS_STACK_UNDERFLOW);
		return NULL;
	}
	else {
		MY_STACK* next = first->next;
		rv.pdata = first->pdata;
		free(first);
		first = next;
		return rv.pdata;
	}

}

void* my_stack_search(void* psearchdata, Find psearch, int firstentry)
{
	static MY_STACK* ptr;
	MY_STACK* ptrtemp = NULL;
	if (first == NULL)
	{
		my_mess_fun(MY_MESS_STACK_UNDERFLOW);
		return NULL;
	}
	if (firstentry)
		ptr = first;

	while (ptr)
	{
		if (!(*psearch)(ptr->pdata, psearchdata))
		{
			ptr = ptr->next;
		}
		else
		{
			ptrtemp = ptr;
			ptr = ptr->next;
			return ptrtemp->pdata;
		}
	}
	return NULL;
}

void my_stack_display()
{
	MY_STACK* temp = first;
	if (temp != NULL) 
	{
		printf("%-20s", " ");
		printf("%s", "STACK");
		printf("\n\n");
		while (temp != NULL) {
			display(temp->pdata);
			temp = temp->next;
		}
		printf("\n\n");
	}
	else printf("Stack is empty! \n\n");

}

void my_stack_save() 
{
	MY_STACK* temp = first;
	if (temp == NULL) 
	{
		my_mess_fun(MY_MESS_STACK_UNDERFLOW);
		return;
	}

	size_t count = 0;
	while (temp != NULL) 
	{
		count++;
		temp = temp->next;
	}
	temp = first;

	unsigned int elements = (unsigned int)count;
	__int64* file_desc = (__int64*)malloc((elements + 1) * sizeof(__int64));
	if (!file_desc)
	{
		file_error(NULL, file_desc);
	}

	FILE* pf = fopen(file, "wb");
	if (!pf)
	{
		file_error(pf, file_desc);
	}

	if (fwrite(&elements, sizeof(unsigned int), 1, pf) != 1)
	{
		file_error(pf, file_desc);
	}

	_fseeki64(pf, (count + 1) * sizeof(__int64), SEEK_CUR);

	size_t item_s = 0;

	while (temp != NULL) 
	{
		file_desc[item_s] = ftell(pf);
		item_s++;
		if (savefile(temp->pdata, pf) != 1)
		{
			file_error(pf, file_desc);
		}
		temp = temp->next;
	}

	file_desc[item_s] = ftell(pf);

	_fseeki64(pf, sizeof(unsigned int), SEEK_SET);
	if (fwrite(file_desc, sizeof(__int64), count + 1, pf) != count + 1)
		file_error(pf, file_desc);

	if (pf) 
	{
		fclose(pf);
		pf = NULL;
	}

	if (file_desc) 
	{
		free(file_desc);
		file_desc = NULL;
	}
}

void my_stack_load() 
{
	my_stack_free();
	__int64* file_desc = NULL;
	unsigned int items = 0, item_s, record;
	FILE* pf = fopen(file, "rb");
	if (!pf)
	{
		file_error(pf, file_desc);
	}

	if (fread(&items, sizeof(unsigned int), 1, pf) != 1)
	{
		file_error(pf, file_desc);
	}

	file_desc = (__int64*)malloc((items + 1) * sizeof(__int64));
	if (!file_desc)
	{
		file_error(pf, file_desc);
	}

	if (fread(file_desc, sizeof(file_desc[0]), items + 1, pf) != items + 1)
	{
		file_error(pf, file_desc);
	}

	for (item_s = 0; item_s < items; ++item_s)
	{
		record = items - item_s - 1;
		_fseeki64(pf, file_desc[record], SEEK_SET);

		void* ptrdata = loadfile(pf);
		if (!my_stack_push(ptrdata))
		{
			file_error(pf, file_desc);
		}


	}

	if (pf) 
	{
		fclose(pf);
		pf = NULL;
	}

	if (file_desc) 
	{
		free(file_desc);
		file_desc = NULL;
	}
}