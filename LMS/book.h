/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#ifndef BOOK_H_INCLUDED
#define BOOK_H_INCLUDED

/********************************************************************/

typedef enum{COPIES_AVAILABLE , COPIES_NOT_AVAILABLE}AVALI;

typedef enum{
    EMPTY_BOOK_LL,
    WRONG_BOOK_NAME,
    WRONG_BOOK_CODE,
    WRONG_AUTHOR_NAME,
    WRONG_BOOK_NUMCOPIES,
    BOOK_EXISTED,
    BOOK_NOT_EXISTED,
    EXISITED_BOOK_CODE,//<-
    NOT_EXISTED_BOOK_CODE,//<-
    ok_book
}DBOOK_COND;

typedef enum{
    ADD_NEW_BOOK_FUNC,
    CREATE_BORROWING_NODE_FUNC,
    MODIFY_BOOK_FUNC,
    DELETE_BOOK_FUNC
}USAGE_VAR;

/********************************************************************/

typedef struct{
    u8 book_code[5];//not more than 4 digits
    u8 book_name[36];
    u8 author[36];
    u16 num_copies;
    AVALI book_av;
}data_book;

typedef struct book_node{
    data_book bo;
    struct book_node *next;
    struct book_node *prev;
}book_node;

typedef struct{
    book_node *head;
    book_node *tail;
}book;

/********************************************************************/
                        /*functions prototypes*/

void create_book_DLL(book *ptr_o);

/********************************************************************/

bool ll_book_is_empty(book *ptrbook);

/********************************************************************/

DBOOK_COND book_name(book_node *ptr);

/********************************************************************/

DBOOK_COND search_book_with_name(book *ptrbook , u8 book_name[36] , USAGE_VAR usage);

/********************************************************************/

DBOOK_COND book_numcopies(u16 *ptr_num_copies);

/********************************************************************/

DBOOK_COND book_code(book *ptrbook , book_node *ptr , USAGE_VAR usage , AVALI *ptr_book_av , u16 *ptrcopies);//*edit

/********************************************************************/

DBOOK_COND search_book_with_code(book *ptrbook , u8 book_code[5] , AVALI *ptr_book_av , u16 *ptrnum_copies);//*edit

/********************************************************************/

DBOOK_COND book_author(book_node *ptr);

/********************************************************************/

void add_new_book(book *ptrbook);

/********************************************************************/

void modify_book(book *ptrbook);

/********************************************************************/

void print_book_data(book_node *ptr);

/********************************************************************/

void print_one_book(book *ptrbook);

/********************************************************************/

void print_book_list(book *ptr);

/********************************************************************/

#endif // BOOK_H_INCLUDED
