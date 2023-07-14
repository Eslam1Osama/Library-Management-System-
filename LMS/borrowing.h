/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#ifndef BORROWING_H_INCLUDED
#define BORROWING_H_INCLUDED

/********************************************************************/

/*
  the following enum is for borrow function for all cases of not accepting
  any inputs from user (librian)
*/
typedef enum{
    WRONG_BOOK_NUMCOPIES_BOR_FORMAT,//value of input copies of books borrowed is higher than 1 digit and not a number
    BREAK_LIMIT,// there is a limit (3 copies) of number of copies borrowed of the same book
    ABOVE_AVAIL,// means the number of copies you want for the same book to borrow is under what is available
    WRONG_DATE,// in case do not following rules of typing borrowed dates
    WRONG_BORROW_NUM,//in case if user enter any letter rather than integer for borrow_num
    NOT_EXSISTED_BORROWING_NODE,//using borrow_num if it's not exsisted in borrow DLL
    EXSISTED_BORROWING_NODE,//using borrow_num if it's exsisted in borrow DLL
    LL_EMPTY,//in case DLL is empty with no nodes in it
    ok_borr// in case of the process of getting any data of borrowing node from user in borrowing process is okay
}DBORROW_COND;

/*the followiing enum is for returning process mainly*/
typedef enum{
    LATE,// if the returning date is after expiration date of borrowed books
    IN_TIME,// if the returning date is before expiration date of borrowed books
    IN_PROGRESS,// in case the books borrowed did not returned back and the process of it is still in progress
    RETURNED// if the books borrowed returned, so we could use it as a record of borrowing and returning books for library
}RET_STAT;// that's why it called returning state

typedef enum{
    WITH_BORROWING_ACT,
    WITH_RETRURNING_ACT
}USAGE_COND;

/********************************************************************/

/*
the following struct is going to be used to generate expiration date
which depends entirly on borrowing date
*/
typedef struct{
    u16 day;// for record of day and it is of unsigned short int
    u16 month;// for record of month and it is of unsigned short int
    u16 year;// for record of year and it is of unsigned short int
}date;

/*
the following struct is full of the types of data stored
in borrowing node and note that it is for borrowing process
and returning process
*/
typedef struct{
    u8 member_code[6];// to store which member do borrowing process
    u8 member_name[36];
    u8 book_code[5];// which book he or she borrowed
    u8 book_name[36];
    u16 num_copies;// number of copies of book in borrowing process (MAX -> 3)
    date borrow_date;// date of borrowing transaction
    date expir_date;// due date of returning these books (note after this date member did this process can not do any borrowing process untill reutring these books)
    date return_date;//when user return back books the date of it must be taken to compare it with expiration date
    u16 borrow_num;//this number is going to be used to get borrow node easily without ask for any more information
    RET_STAT ret;//for if member return books after or before expiration date
    RET_STAT state;// the state of this borrowing process, is it still with member (books) (IN_PROGRESS) or returned (RETURNED)
}borrowing_data;

/*
As it is planed we are going to use doubly linked list (DLL) to store
borrowing nodes, so their must be borrowing node
*/
typedef struct borrowing_node{
    borrowing_data bo;// the actual record of data for each and every borrowing process
    struct borrowing_node *next;// as we are using DLL there must be pointer to the next node
    struct borrowing_node *prev;// as we are using DLL there must be pointer to the previous node
}borrowing_node;

/*
As we are using DLL there must be pointer to the head of DLL and also pointer to last
node in DLL (tail)
*/
typedef struct{
    borrowing_node *head;//the pointer to head of DLL
    borrowing_node *tail;//the pointer to tail of DLL
    u16 counter;//this counter is used to differentiate between every and each node
}borrowing;

/********************************************************************/
                            /*functions prototypes*/


void create_borr_DLL(borrowing *ptr_b);

/********************************************************************/

bool ll_bor_is_empty(borrowing *ptrbor);

/********************************************************************/

DBORROW_COND check_num_copies_bor(borrowing_node *ptr , u16 num_avail);

/********************************************************************/

void get_all_late_return(member *ptrm , borrowing *ptrb , borrowing_node *ptrn);

/********************************************************************/

void def_exp_date(borrowing_node *ptr);

/********************************************************************/

void create_borrowing_node(book *ptrbook , member *ptrmember , borrowing *ptrbor);

/********************************************************************/

void get_all_bor_data(borrowing *ptr_bor , member *ptr_mem);

/********************************************************************/

DBORROW_COND search_bor_node(borrowing *ptrbor , u16 borrow_num);

/********************************************************************/

DBORROW_COND check_borrow_num(borrowing *ptrbor , u16 *ptrbor_num);

/********************************************************************/

void returning_action(borrowing *ptrbor , book * ptrbook , member *ptrmember);

/********************************************************************/

DBORROW_COND check_curr_date(date *ptr_curr_date);

/********************************************************************/

void upd_bor_list(borrowing *ptr_bor , member *ptr_mem , date *curr_date);

/********************************************************************/
                    /******************* MEMBER SECTION WITH BORROWING FILE *******************/

void member_list_bor(u8 *ptrmember_code , borrowing *ptrb , book *ptrbook);

/********************************************************************/

void print_one_member(member *ptrmember , borrowing *ptr_bor , book *ptr_book);

/********************************************************************/

void print_member_list(member *ptr , borrowing *ptr_bor , book *ptr_book);

/********************************************************************/

void delete_member(member *ptrmember, u8 member_code[6] , borrowing *ptrb , book *ptrbook , USAGE use);
                    /********************************************************************/
/********************************************************************/
                    /******************* BOOK SECTION WITH BORROWING FILE *******************/

void delete_book(book *ptr_book , borrowing *ptr_bor);

/********************************************************************/

#endif // BORROWING_H_INCLUDED
