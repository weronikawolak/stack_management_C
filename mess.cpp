#include <stdlib.h>
#include <stdio.h>
#include "mess.h"
#include "my_stack.h"

static char* my_message_str_tab[] =
{
	(char*)"EMEMORY ALLOCATION ERROR",
	(char*)"WSTACK UNDERFLOW",
	(char*)"EFATAL ERROR"
};

void my_mess_fun(enum MY_ERROR_MESS mess)
{
	puts(my_message_str_tab[mess] + 1);

	if (my_message_str_tab[mess][0] == 'E')
	{
		my_stack_free();
		system("pause");
	}

	return;
}

void file_error(FILE* pfile, __int64* fdesc)
{
	if (pfile)
		fclose(pfile);
	if (fdesc)
		free(fdesc);

	my_mess_fun(MY_MESS_FATAL_ERROR);
	system("pause");
	exit(1);
} 