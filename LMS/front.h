/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#ifndef FRONT_H_INCLUDED
#define FRONT_H_INCLUDED

/********************************************************************/

typedef enum{
    WRONG_USERNAME,
	WRONG_PASSW,
	ok
}FRONT_COND;

#define librar_username             "librarian"
#define librar_password             "98071539"

/********************************************************************/
                            /*functions prototypes*/

void edit(book *ptrbook , member *ptrmember , borrowing *ptrbor);

/********************************************************************/

FRONT_COND getting_username(u8 mem_username[15]);

/********************************************************************/

FRONT_COND getting_passw(u8 mem_passw[10]);

/********************************************************************/

void GoTo_member_section(book *ptrbook , member *ptrmember , borrowing *ptrbor);

/********************************************************************/

void GoTo_librarian_section(book *ptrbook , member *ptrmember , borrowing *ptrbor);

/********************************************************************/

void LibraryGroundRules(void);

/********************************************************************/

void entry_window(book *ptrbook , member *ptrmember , borrowing *ptrbor);

/********************************************************************/

#endif // FRONT_H_INCLUDED
