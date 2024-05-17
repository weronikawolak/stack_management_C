#pragma once

#ifndef ERRORS_H
#define ERRORS_H

enum MY_ERROR_MESS {
	MY_MESS_MEM_ALLOC_ERROR,
	MY_MESS_STACK_UNDERFLOW,
	MY_MESS_FATAL_ERROR,
	MY_MESS_TOTAL
};

void my_mess_fun(enum MY_ERROR_MESS mess);
void file_error(FILE* pfile, __int64* fdesc);

#endif
