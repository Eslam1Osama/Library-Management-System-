#include<stdio.h>//for input output processes and getchar()
#include<stdbool.h>// to use bool
#include<stdlib.h>//for dynamic memory allocation
#include<string.h>//to use strcpy() & strcmp() & strlen() functions

#include"LSTD_TYPES.h"
#include"utility_control.h"

#include"book.h"
#include"member.h"
#include"borrowing.h"
#include"front.h"

int main()
{
    member    ptrmember;
    book      ptrbook;
    borrowing ptrborr;

    create_book_DLL(&ptrbook);
    create_borr_DLL(&ptrborr);
    create_mem_DLL(&ptrmember);

    entry_window(&ptrbook , &ptrmember , &ptrborr);

    return 0;
}
