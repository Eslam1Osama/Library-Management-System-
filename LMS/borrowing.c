/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#include<stdio.h>//for input output processes and for getchar() function
#include<stdbool.h>// to use bool
#include<stdlib.h>//for dynamic memory allocation
#include<string.h>//to use strcpy() and strcmp() functons

#include"LSTD_TYPES.h"
#include"utility_control.h"

#include"book.h"
#include"member.h"

#include"borrowing.h"

/********************************************************************/

void create_borr_DLL(borrowing *ptr_b)
{
   ptr_b->head = NULL;
   ptr_b->tail = NULL;
   ptr_b->counter = 0;
}

/********************************************************************/

bool ll_bor_is_empty(borrowing *ptrbor)
{
    return( !(ptrbor->head));
}

/********************************************************************/

DBORROW_COND check_num_copies_bor(borrowing_node *ptr , u16 num_avail)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_num_copies_bor = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter number of copies which you want to borrow : ");
    gets(local_num_copies_bor);

    x = strlen(local_num_copies_bor);

    /*just one digit integer, not negative, between 1 and 3, and related to what is available of copies of that book*/
    if( (x != 1) || ( ( local_num_copies_bor[0] < '0') || (local_num_copies_bor[0] > '9') ) )// we need to make sure all the inputs are digits and just one digit
    {
        free(local_num_copies_bor);
        local_num_copies_bor = NULL;
        return WRONG_BOOK_NUMCOPIES_BOR_FORMAT;
    }
    else if( ( local_num_copies_bor[0] <= '0') || (local_num_copies_bor[0] > '3') )// we need to make sure the input digit is between 1 and 3
    {
            free(local_num_copies_bor);
            local_num_copies_bor = NULL;
            return BREAK_LIMIT;
    }
    else if( atoi(local_num_copies_bor) > num_avail)// we need to make sure the input digit is less than or equal of what is available of book copies
    {
            free(local_num_copies_bor);
            local_num_copies_bor = NULL;
            return ABOVE_AVAIL;
    }

    ptr->bo.num_copies = atoi(local_num_copies_bor);
    free(local_num_copies_bor);
    local_num_copies_bor = NULL;
    return ok_borr;
}

/********************************************************************/
/*
this function has 2 goals:
1- update on borrowing nodes for "exact" member with current date
2- print all late borrowing process for the "exact" member

- if you want to use the following function to get if there is any late returns
in the choice list you can first ask for borrowing code and then search for
borrowing node to see for user if he has any late returns or not.
*/
void get_all_late_return(member *ptrm , borrowing *ptrb , borrowing_node *ptrn)
{
    u8 flag_late_exact = 0;

    member_node *tempm = ptrm->head;

    while(tempm != NULL)
    {
        if(strcmp(ptrn->bo.member_code , tempm->bo.member_code) == 0)
            break;

        tempm = tempm->next;
    }

    borrowing_node *tempb = ptrb->head;
    while(tempb != NULL)
    {
        if( (strcmp(tempm->bo.member_code , tempb->bo.member_code) == 0) && (tempb->bo.state == IN_PROGRESS) && (tempm->bo.member_perm == PANDED) )
        {
            if(flag_late_exact == 0)
            {
                flag_late_exact = 1;
                printf("\t\t\t=====================================================================================================\n");
                printf("\t\t\t::member with code (%s) can not borrow a book until returning the following late returning books::\n" , tempm->bo.member_code);
                printf("\t\t\t=====================================================================================================\n\n");
                printf("===========================================================================================================\n");
                printf("book code      number of copies      borrowing date\t\texpiration date\n");
                printf("===========================================================================================================\n");
            }
            printf("%-8s\t%d\t\t     %d-%d-%d\t\t\t %d-%d-%d\n" , tempb->bo.book_code , tempb->bo.num_copies , tempb->bo.borrow_date.day , tempb->bo.borrow_date.month , tempb->bo.borrow_date.year , tempb->bo.expir_date.day , tempb->bo.expir_date.month , tempb->bo.expir_date.year);
        }
        tempb = tempb->next;
    }

    if(flag_late_exact == 0)
        printf("\n::member with code (%s) has no late returnings::\n" , tempm->bo.member_code);

    printf("===========================================================================================================\n\n");
}

/********************************************************************/
/*
the following func. is to auto generate expiration date of borrowing node
based on borrowing date. (in borrowing function)
*/
void def_exp_date(borrowing_node *ptr)
{
    u16 year  = ptr->bo.borrow_date.year ;
    u16 month = ptr->bo.borrow_date.month;
    u16 day   = ptr->bo.borrow_date.day  ;

    if( (month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) ||(month == 10) || (month == 12) )
    {
        if(day == 17)
            ptr->bo.expir_date.day = 31;
        else
            ptr->bo.expir_date.day = (day + 14) % 31;

        if( (month == 12) && (day > 17) )
        {
            ptr->bo.expir_date.month  = 1;
            ptr->bo.expir_date.year   = year + 1;
        }
        else
        {
            if( (day > 17) && (month != 12) )
                ptr->bo.expir_date.month  = month + 1;
            else
                ptr->bo.expir_date.month  = month;
            ptr->bo.expir_date.year   = year;
        }
    }

    else if( (month == 4) || (month == 9) || (month == 11) || (month == 6) )
    {
        if(day == 16)
            ptr->bo.expir_date.day = 30;
        else
            ptr->bo.expir_date.day = (day + 14) % 30;

        if(day > 16)
            ptr->bo.expir_date.month  = month + 1;
        else
            ptr->bo.expir_date.month  = month;
        ptr->bo.expir_date.year = year;
    }

    else if(month == 2)
    {
        if( (year % 4 == 0) && (year % 10 != 0) )//leap year
        {
            if(day == 15)
               ptr->bo.expir_date.day = 29;
            else
                ptr->bo.expir_date.day = (day + 14) % 29;

            if(day > 15)
                ptr->bo.expir_date.month  = month + 1;
            else
                ptr->bo.expir_date.month  = month;
            ptr->bo.expir_date.year = year;

        }

        else
        {
            if(day == 14)
               ptr->bo.expir_date.day = 28;
            else
                ptr->bo.expir_date.day = (day + 14) % 28;

            if(day > 14)
                ptr->bo.expir_date.month  = month + 1;
            else
                ptr->bo.expir_date.month  = month;
            ptr->bo.expir_date.year = year;
        }
    }
}

/********************************************************************/
void create_borrowing_node(book *ptrbook , member *ptrmember , borrowing *ptrbor)
{
    //==================================================================
    u8 des;                 //for yes or no to repeat any process in borrowing function
    AVALI bavail;           //for getting state of availability from book linked list using it's code
    u16 copies;             //for getting number of copies available from book linked list to show it to user
   //==================================================================

    if(ll_book_is_empty(ptrbook) == 1)
    {
        printf("WARNING!! no books added in library system (book list is empty)...\n");

        if(ll_member_is_empty(ptrmember) == 1)
            printf("WARNING!! no members added in library system (member list is empty)...\n");
        return;
    }
    else if(ll_member_is_empty(ptrmember) == 1)
    {
        printf("WARNING!! no members added in library system (member list is empty)...\n");
        return;
    }

    while(1)
    {
        des = 'b';

        borrowing_node *ptr_n = (borrowing_node *)malloc(sizeof(borrowing_node));
        book_node *ptr_botemp = (book_node *)malloc(sizeof(book_node));
        member_node *ptr_metemp = (member_node *)malloc(sizeof(member_node));

        if( (ptr_n == NULL) && (ptr_botemp == NULL) && (ptr_metemp == NULL) )
        {
            printf("heap is full, please free some memory in heap!!\n");
            return;
        }

        printf("\t\t\t=====================\n");
        printf("\t\t\t::borrowing section::\n");
        printf("\t\t\t=====================\n");

        //==========================================================================
        /*getting member code who wants to borrow a book from library*/

        DMEMBER_COND check_member_code = member_code(ptrmember , ptr_metemp , CREATE_BORROWING_NODE_FUNC);
        while(1)
        {
            if(check_member_code == WRONG_MEMBER_CODE)
            {
                printf("WARNING!! unaccepted member code, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_member_code = member_code(ptrmember , ptr_metemp , CREATE_BORROWING_NODE_FUNC);
            }

            else if(check_member_code == NOT_EXSISTED_MEMBER_CODE)
            {
                printf("WARNING!! member's code is not existed in library membership system, do you want to try again (y/n)?? ");

                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("WARNING!! member's code is not existed in library membership system, do you want to try again (y/n)?? ");
                    check_decision = check_des(&des);
                }

                getchar();

                if(des == 'n')
                    break;

                else if(des == 'y')
                {
                    delete_exact_lines(3);
                    check_member_code = member_code(ptrmember , ptr_metemp , CREATE_BORROWING_NODE_FUNC);
                }
            }

            else if(check_member_code == EXSISTED_MEMBER_CODE)
            {
                strcpy(ptr_n->bo.member_code , ptr_metemp->bo.member_code);
                free(ptr_metemp);
                ptr_metemp = NULL;
                break;
            }
        }

        if(des == 'n')
        {
            free(ptr_botemp);
            ptr_botemp = NULL;
            free(ptr_n);
            ptr_n = NULL;
            break;
        }
        des = 'b';

        /*********************************************************************************************************************************/
        /*
        through the following function, we can first update borrowing list and also if member is not panded we can assign current time
        got in this function as borrowing date and also automatically generate expiration date in case member is not panded.
        */
        upd_bor_list(ptrbor , ptrmember , &(ptr_n->bo.borrow_date));

        member_node *temp_m = ptrmember->head;
        while(temp_m != NULL)
        {
            if( strcmp(temp_m->bo.member_code , ptr_n->bo.member_code) == 0 )
                break;
            temp_m = temp_m->next;
        }
        /*********************************************************************************************************************************/

        if(check_member_code == EXSISTED_MEMBER_CODE)
        {
            if( (temp_m->bo.member_perm == NOT_PANDED) && (temp_m->bo.exceed_exp <= 4) )
            {
                def_exp_date(ptr_n);//automatically generate expiration date according to borrowing date of current borrowing process
                strcpy(ptr_n->bo.member_name , temp_m->bo.member_name);
                printf("\t\t==================================\n");
                printf("\t\tmember is allowed to borrow a book\n");
                printf("\t\t==================================\n");
                getchar();
                delete_exact_lines(4);
            }
            else if( (temp_m->bo.member_perm == PANDED) || (temp_m->bo.exceed_exp > 4) )
            {
                printf("\t\t==================================================\n");
                printf("\t\tWARNING!! member is not allowed to borrow books...\n");
                printf("\t\t==================================================\n");

                get_all_late_return(ptrmember , ptrbor , ptr_n);

                printf("do you want to enter another member code again (y/n)?? ");

                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("do you want to enter another member code again (y/n)?? ");
                    check_decision = check_des(&des);
                }
                free(ptr_n);
                ptr_n = NULL;

                getchar();

                if(des == 'n')
                    break;
                else if(des == 'y')
                    continue;
            }
        }

        //==========================================================================
        /*getting book code which member wants to borrow from library*/

        while(1)
        {
            DBOOK_COND check_book_code = book_code(ptrbook , ptr_botemp , CREATE_BORROWING_NODE_FUNC , &bavail , &copies);
            while(1)
            {
                if(check_book_code == WRONG_BOOK_CODE)
                {
                    printf("WARNING!! unaccepted book code, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_book_code = book_code(ptrbook , ptr_botemp , CREATE_BORROWING_NODE_FUNC , &bavail , &copies);
                }

                else if(check_book_code == NOT_EXISTED_BOOK_CODE)
                {
                    printf("WARNING!! book code is not existed in library system, do you want to enter book code again (y/n)?? ");

                    des_state check_decision = check_des(&des);
                    while(check_decision == WRONG_DES_FORMAT)
                    {
                        printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        printf("WARNING!! book code is not existed in library system, do you want to enter book code again (y/n)?? ");
                        check_decision = check_des(&des);
                    }

                    getchar();
                    if(des == 'n')
                        break;

                    else if(des == 'y')
                    {
                        delete_exact_lines(3);
                        check_book_code = book_code(ptrbook , ptr_botemp , CREATE_BORROWING_NODE_FUNC , &bavail , &copies);
                    }
                }

                else if(check_book_code == EXISITED_BOOK_CODE)
                {
                    strcpy(ptr_n->bo.book_code , ptr_botemp->bo.book_code);
                    break;
                }
            }

            if(des == 'n')
                break;

            if(check_book_code == EXISITED_BOOK_CODE)
            {
                if(bavail == COPIES_AVAILABLE)
                {
                    book_node *tempbook = ptrbook->head;
                    while(tempbook != NULL)
                    {
                        if( strcmp(ptr_n->bo.book_code , tempbook->bo.book_code) == 0 )
                        {
                            strcpy(ptr_n->bo.book_name , tempbook->bo.book_name);
                            break;
                        }
                        tempbook = tempbook->next;
                    }
                    free(ptr_botemp);
                    ptr_botemp = NULL;

                    printf("\t\t=================================================\n");
                    printf("\t\tbook with code (%s) is available with %d copies\n" , ptr_n->bo.book_code , copies);
                    printf("\t\t=================================================\n");
                    getchar();
                    delete_exact_lines(4);
                    break;
                }
                else if(bavail == COPIES_NOT_AVAILABLE)
                {
                    printf("\t\t=============================================\n");
                    printf("\t\tbook with code (%s) is not available\n" , ptr_n->bo.book_code);
                    printf("\t\t=============================================\n");

                    printf("do you want to enter another book code again (y/n)?? ");

                    des_state check_decision = check_des(&des);
                    while(check_decision == WRONG_DES_FORMAT)
                    {
                        printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        printf("do you want to enter another book code again (y/n)?? ");
                        check_decision = check_des(&des);
                    }

                    getchar();
                    if(des == 'n')
                        break;

                    else if(des == 'y')
                    {
                        delete_exact_lines(6);
                        //continue;
                    }
                }
            }
        }

        if(des == 'n')
        {
            free(ptr_n);
            ptr_n = NULL;
            break;
        }
        des = 'b';



        //==========================================================================================================
        /*getting number of copies in the borrowing process from member*/

        DBORROW_COND check_borrowing_amount = check_num_copies_bor(ptr_n , copies);
        while(1)
        {
            if(check_borrowing_amount == WRONG_BOOK_NUMCOPIES_BOR_FORMAT)
            {
                printf("WARNING!! wrong format for number of copies, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_borrowing_amount = check_num_copies_bor(ptr_n , copies);
            }

            else if(check_borrowing_amount == BREAK_LIMIT)//max 3 books for the same book code at a time
            {
                printf("WARNING!! the limit of borrowing book at a time is 3, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_borrowing_amount = check_num_copies_bor(ptr_n , copies);
            }

            else if(check_borrowing_amount == ABOVE_AVAIL)// when member want to borrow number of copies above what is available in library
            {
                printf("WARNING!! there is only (%d) copies of book with code (%s) available , please try again...\n" , copies , ptr_n->bo.book_code);

                getchar();
                delete_exact_lines(3);

                check_borrowing_amount = check_num_copies_bor(ptr_n , copies);
            }

            else if(check_borrowing_amount == ok_borr)
            {
                book_node *tempb = ptrbook->head;
                while(tempb != NULL)
                {
                    if(strcmp(tempb->bo.book_code , ptr_n->bo.book_code) == 0)
                    {
                        tempb->bo.num_copies -= ptr_n->bo.num_copies;

                        if(tempb->bo.num_copies == 0)
                            tempb->bo.book_av = COPIES_NOT_AVAILABLE;

                        else if(tempb->bo.num_copies > 0)
                            tempb->bo.book_av = COPIES_AVAILABLE;

                        break;
                    }
                    tempb = tempb->next;
                }
                break;
            }
        }

        //==========================================================================================================
        ptr_n->bo.state = IN_PROGRESS;
        ptr_n->bo.ret = IN_TIME;

        if( ++(temp_m->bo.num_bor) == 5 )
            temp_m->bo.member_perm = PANDED;
        //==========================================================================================================
        ptr_n->next = NULL;
        ptr_n->prev = NULL;

        if(ll_bor_is_empty(ptrbor) == 1)//the first borrowing node in DLL
        {
            ptrbor->head = ptr_n;
            ptrbor->tail = ptr_n;
            ptr_n->bo.borrow_num = ptrbor->counter = 1;//1 due to it is first borrowing node in DLL
        }

        else//just doing appending to DLL
        {
            borrowing_node *temp = ptrbor->head;

            while(temp != NULL)
                temp = temp->next;

            ptr_n->prev = ptrbor->tail;
            ptrbor->tail->next = ptr_n;
            ptrbor->tail = ptr_n;
            ptr_n->bo.borrow_num = ++ptrbor->counter;
        }

        printf("\t\t================================================================================================================================================\n");
        printf("\t\tborrowing process successfully done for member with code (%s) of borrowing (%d) copies of book with code (%s) and store it in borrowing list\n" , ptr_n->bo.member_code , ptr_n->bo.num_copies , ptr_n->bo.book_code);
        printf("\t\t================================================================================================================================================\n");
        printf("do you want to do process of borrowing again (y/n)?? ");

        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do process of borrowing again (y/n)?? ");
            check_decision = check_des(&des);
        }

        getchar();
        if(des == 'y')
        {
            system("cls");
            continue;
        }
        else if(des == 'n')// return back general adding list
            break;
    }
}

/********************************************************************/

void get_all_bor_data(borrowing *ptr_bor , member *ptr_mem)
{
    date curr_date;
    if(ll_bor_is_empty(ptr_bor) == 1)
    {
        printf("=======================\n");
        printf("borrowing list is empty\n");
        printf("=======================\n");
        return;
    }

    upd_bor_list(ptr_bor , ptr_mem , &curr_date);//to update borrowing list with current date
    getchar();
    delete_exact_lines(2);

    borrowing_node *tempb = ptr_bor->head ;

    printf("\t\t\t\t\t\t\t\t\t\t\t==================\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t::borrowing list::\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t==================\n\n");
    printf("=========================================================================================================================================================================================================================================\n");
    printf("num\t\tmember ID      member name\t\t\tbook name\t\t\t\tnumber of copies borrowed     borrowing date\texpiration date\t\treturning date\t\tcondition\tstate\n");
    printf("=========================================================================================================================================================================================================================================\n\n");
    while(tempb != NULL)
    {
        if( (tempb->bo.state == IN_PROGRESS) && (tempb->bo.ret == LATE) )
            printf("%d\t\t%s\t\t%-25s\t%-35s\t%d\t\t\t      %d-%d-%d\t\t%d-%d-%d\t\t--------------\t\tlate\t\tStill with member\n" , tempb->bo.borrow_num , tempb->bo.member_code , tempb->bo.member_name , tempb->bo.book_name , tempb->bo.num_copies , tempb->bo.borrow_date.day , tempb->bo.borrow_date.month , tempb->bo.borrow_date.year , tempb->bo.expir_date.day , tempb->bo.expir_date.month , tempb->bo.expir_date.year);
        else if( (tempb->bo.state == IN_PROGRESS) && (tempb->bo.ret == IN_TIME) )
            printf("%d\t\t%s\t\t%-25s\t%-35s\t%d\t\t\t      %d-%d-%d\t\t%d-%d-%d\t\t--------------\t\tin time\t\tStill with member\n" , tempb->bo.borrow_num , tempb->bo.member_code , tempb->bo.member_name , tempb->bo.book_name , tempb->bo.num_copies , tempb->bo.borrow_date.day , tempb->bo.borrow_date.month , tempb->bo.borrow_date.year , tempb->bo.expir_date.day , tempb->bo.expir_date.month , tempb->bo.expir_date.year);
        else if( (tempb->bo.state == RETURNED) && (tempb->bo.ret == IN_TIME) )
            printf("%d\t\t%s\t\t%-25s\t%-35s\t%d\t\t\t      %d-%d-%d\t\t%d-%d-%d\t\t%d-%d-%d\t\tin time\t\treturned\n" , tempb->bo.borrow_num , tempb->bo.member_code , tempb->bo.member_name , tempb->bo.book_name , tempb->bo.num_copies , tempb->bo.borrow_date.day , tempb->bo.borrow_date.month , tempb->bo.borrow_date.year , tempb->bo.expir_date.day , tempb->bo.expir_date.month , tempb->bo.expir_date.year , tempb->bo.return_date.day , tempb->bo.return_date.month , tempb->bo.return_date.year);
        else if( (tempb->bo.state == RETURNED) && (tempb->bo.ret == LATE) )
            printf("%d\t\t%s\t\t%-25s\t%-35s\t%d\t\t\t      %d-%d-%d\t\t%d-%d-%d\t\t%d-%d-%d\t\tlate\t\      returned\n" , tempb->bo.borrow_num , tempb->bo.member_code , tempb->bo.member_name , tempb->bo.book_name , tempb->bo.num_copies , tempb->bo.borrow_date.day , tempb->bo.borrow_date.month , tempb->bo.borrow_date.year , tempb->bo.expir_date.day , tempb->bo.expir_date.month , tempb->bo.expir_date.year , tempb->bo.return_date.day , tempb->bo.return_date.month , tempb->bo.return_date.year);
        tempb = tempb->next;
    }
    printf("\n=========================================================================================================================================================================================================================================\n");
}

/********************************************************************/

DBORROW_COND search_bor_node(borrowing *ptrbor , u16 borrow_num)
{
    if(ll_bor_is_empty(ptrbor) == 1)
        return LL_EMPTY;

    borrowing_node *temp = ptrbor->head;
    while(temp != NULL)
    {
        if( (borrow_num == temp->bo.borrow_num) && (temp->bo.state == IN_PROGRESS) )
            return EXSISTED_BORROWING_NODE;

        temp = temp->next;
    }

    return NOT_EXSISTED_BORROWING_NODE;
}

/********************************************************************/

DBORROW_COND check_borrow_num(borrowing *ptrbor , u16 *ptrbor_num)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_bor_num = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter borrowing number: ");
    gets(local_bor_num);

    x = strlen(local_bor_num);

    if(x == 0)
    {
        free(local_bor_num);
        local_bor_num = NULL;
        return WRONG_BORROW_NUM;
    }
    for(u16 i = 0 ; i < x ; i++)
    {
        if( (local_bor_num[i] < '0') || (local_bor_num[i] > '9') )
        {
            free(local_bor_num);
            local_bor_num = NULL;
            return WRONG_BORROW_NUM;
        }
    }

    if( search_bor_node(ptrbor, atoi(local_bor_num)) == NOT_EXSISTED_BORROWING_NODE )
        return NOT_EXSISTED_BORROWING_NODE;

    *ptrbor_num =  atoi(local_bor_num);
    free(local_bor_num);
    local_bor_num = NULL;
    return EXSISTED_BORROWING_NODE;
}

/********************************************************************/

void returning_action(borrowing *ptrbor , book * ptrbook , member *ptrmember)
{
    u16 borrow_num;
    u8 des;
    des_state check_decision;
    bool flag_del = 0;

    if(ll_bor_is_empty(ptrbor) == 1)
    {
        printf("WARNING!! there is no borrowing records in database (empty)!!\n");
        return;
    }

    while(1)
    {
        des = 'r';
        printf("\t\t=====================\n");
        printf("\t\t**returning process**\n");
        printf("\t\t=====================\n");

        //===================================================================================
        /*getting borrowing node using it's number*/

        DBORROW_COND check_borrowing_num = check_borrow_num(ptrbor , &borrow_num);
        while(1)
        {
            if(check_borrowing_num == WRONG_BORROW_NUM)
            {
                printf("WARNING!! borrow number must be of positive integer value, please try again...");

                getchar();
                delete_exact_lines(3);

                check_borrowing_num =  check_borrow_num(ptrbor , &borrow_num);
            }

            else if(check_borrowing_num == NOT_EXSISTED_BORROWING_NODE)
            {
                printf("WARNING!! borrow number entered is not in library system or it is returned (part of history records of borrowing list), do you want to try again using another borrow number (y/n)?? ");

                check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("WARNING!! borrow number entered is not in library system, do you want to try again using another borrow number (y/n)?? ");
                    check_decision = check_des(&des);
                }

                getchar();

                if(des == 'n')
                    break;
                else if(des == 'y')
                {
                    delete_exact_lines(3);
                    check_borrowing_num = check_borrow_num(ptrbor , &borrow_num);
                }
            }

            else if(check_borrowing_num == EXSISTED_BORROWING_NODE)
                break;
        }

        if(des == 'n')
            break;

        //===================================================================================
        /*for borrowing node*/

        borrowing_node *temp = ptrbor->head;
        while(temp != NULL)
        {
            if(borrow_num == temp->bo.borrow_num)
               break;

            temp = temp->next;
        }

        printf("\n\t\t==================================================================================================================\n");
        printf("\t\tNOTE THAT -> returning of books must be of (%d) copies of book with code (%s) to complete returning process\n" , temp->bo.num_copies , temp->bo.book_code);
        printf("\t\t====================================================================================================================\n");

        printf("does returning process consists of what is mentioned above (y/n)?? ");
        check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong answer format (answer is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("does returning process consists of what is mentioned above (y/n)?? ");
            check_decision = check_des(&des);
        }

        getchar();

        if(des == 'n')
            break;
        if(des == 'y')
            delete_exact_lines(6);

        des = 'r';

        //===================================================================================
        /*for member node date*/

        member_node *tempm = ptrmember->head;

        while(tempm != NULL)
        {
            if(strcmp(tempm->bo.member_code , temp->bo.member_code) == 0)
                break;

            tempm = tempm->next;
        }

        //===================================================================================
        /*for book node data*/

        book_node *tempb = ptrbook->head;

        while(tempb != NULL)
        {
            if(strcmp(tempb->bo.book_code , temp->bo.book_code) == 0)
                break;

            tempb = tempb->next;
        }

        /*====================================================================================================================*/

        /*********************************************************************************************************************************/

        /*through the following function, we can first update borrowing list and also we can assign current time got in this function as returning date.*/
        upd_bor_list(ptrbor , ptrmember , &(temp->bo.return_date));

        /*********************************************************************************************************************************/

        tempb->bo.num_copies += temp->bo.num_copies;
        if(tempb->bo.num_copies > 0)
            tempb->bo.book_av = COPIES_AVAILABLE;
        temp->bo.state = RETURNED;
        tempm->bo.num_bor--;//be aware that max number of making borrowing processes and still no returning is "5"

        if( temp->bo.ret == LATE )
        {
            printf("\t\t====================================================================\n");
            printf("\t\tmember with code (%s) exceed expiration date of returning books!!\n" , tempm->bo.member_code);//for the current returning process
            printf("\t\t====================================================================\n");

            tempm->bo.num_late--;

            if(tempm->bo.exceed_exp <= 4)
                tempm->bo.exceed_exp++;/*for any member there is counter which called exceed_exp used to count number of late returnings and when it is higher than 4 member's data
                                         and permission to borrow is deleted*/

            if( (tempm->bo.num_late == 0) && (tempm->bo.exceed_exp <= 4) )
                tempm->bo.member_perm = NOT_PANDED;

            else if(tempm->bo.num_late > 0)
                tempm->bo.member_perm = PANDED;
        }

        /*======================================================================================================================*/

        /*======================================================================================================================================================================*/
        /*THIS IS THE PLACE WHERE WE CAN MODIFIY VARIABLE OF exceed_exp WHICH IS ONLY MODIFIED HERE IN RETURNING FUNCTION*/
        /*****************************************************************************************************************/

        /*if member still panded and exceed 4 times of returning books of one borrowing process, so first he or she must return all books and after that his or her membership is going to get deleted*/
        if ( (tempm->bo.exceed_exp > 4) && (tempm->bo.num_bor > 0) )
            printf("WARNING!! member with code (%s) has exceeded 4 times of latency of returning books, but still has to finish all returning processes!!\n" , tempm->bo.member_code);

        else if( (tempm->bo.exceed_exp > 4) && (tempm->bo.num_bor == 0) )
        {
            printf("WARNING member with code (%s) has exceeded 4 times of latency of returning books and finish all returning processes, so it is officially been deleted from library membership system (no longer member in library)!!\n" , tempm->bo.member_code);
            printf("====================================================================================================================================================================================================================\n\n");
            delete_member(ptrmember , temp->bo.member_code , ptrbor , ptrbook , USE_IN_BORROWING_FUNC);
            printf("\n====================================================================================================================================================================================================================\n");
            getchar();
            delete_exact_lines(9);//to delete 3 lines of deleting successfully done and getchar() line
            flag_del = 1;
        }
        if( (tempm->bo.exceed_exp > 0) && (flag_del == 0) )
            printf("WARNING!! be aware member with code (%s) now has (%d) times of latencies in returning books!!\n" , tempm->bo.member_code , tempm->bo.exceed_exp);

        /*======================================================================================================================================================================*/


        printf("\t\t=================================================\n");
        printf("\t\tthe process of returning successfully accomplised\n");
        printf("\t\t=================================================\n");

        if(flag_del == 0)
        {
            /*through the following function we can notify librarian about late returns of member doing this return action to notify him (member)*/
            get_all_late_return(ptrmember , ptrbor , tempm);
        }
        flag_del = 0;

        printf("do you want to do returning process again (y/n)?? ");
        check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do returning process again (y/n)?? ");
            check_decision = check_des(&des);
        }

        getchar();

        if(des == 'n')
            break;
        if(des == 'y')
        {
            system("cls");
            continue;
        }
    }//end_bracket of while(1) for the whole process of returning book
}//end_bracket of function of returning book

/********************************************************************/

DBORROW_COND check_curr_date(date *ptr_curr_date)
{
    u8 days[3] , months[3] , years[5];

    u16  x = 150;// it's going to be erased after function return
    u8 *local_curr_date = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter current date: ");
    gets(local_curr_date);

    x = strlen(local_curr_date);

    if(x != 10)
    {
        free(local_curr_date);
        local_curr_date = NULL;
        return WRONG_DATE;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( ( (i == 2) && (local_curr_date[i] == '-') ) || ( (i == 5) && (local_curr_date[i] == '-') ) )
                continue;
            else if( (local_curr_date[i] < '0') || (local_curr_date[i] > '9') )
            {
                free(local_curr_date);
                local_curr_date = NULL;
                return WRONG_DATE;
            }
        }
    }

    strncpy(days , local_curr_date , 2);
    u16 day = atoi(days);

    strncpy(months , local_curr_date + 3 , 2);
    u16 month = atoi(months);

    strncpy(years , local_curr_date + 6 , 4);
    u16 year = atoi(years);

    free(local_curr_date);
    local_curr_date = NULL;

    if( (month > 12) || (month == 0) || (day == 0) || (year == 0) )
        return WRONG_DATE;
    else if( (month == 1) || (month == 3) || (month == 5) || (month == 7) || (month == 8) ||(month == 10) || (month == 12) )
    {
        if(day > 31)
            return WRONG_DATE;
    }

    else if( (month == 4) || (month == 9) || (month == 11) || (month == 6) )
    {
        if(day > 30)
            return WRONG_DATE;
    }

    else if(month == 2)
    {
        if( (year % 4 == 0) && (year % 10 != 0) )//leap year
        {
            if(day > 29)
                return WRONG_DATE;
        }
        else
            if(day > 28)
                return WRONG_DATE;
    }

    /*===========================*/
    /*in case borrowing date follows it's rules correctly*/
    ptr_curr_date->year     = year ;
    ptr_curr_date->month    = month;
    ptr_curr_date->day      = day  ;
    /*==========================*/

    return ok_borr;
}

/********************************************************************/

void upd_bor_list(borrowing *ptr_bor , member *ptr_mem , date *curr_date)
{
    DBORROW_COND handle_curr_date = check_curr_date(curr_date);
    while(handle_curr_date == WRONG_DATE)
    {
        printf("WARNING!! something wrong with typed date and it must be like the following format (02-12-2022), please try again...\n");

        getchar();
        delete_exact_lines(3);

        handle_curr_date = check_curr_date(curr_date);
    }

    /*======================================*/
    member_node    *tempm    = ptr_mem->head;
    borrowing_node *tempb    = ptr_bor->head;
    /*=====================================*/

    while(tempm != NULL)// for member list
    {
        if( (tempm->bo.num_bor == 5) || (tempm->bo.exceed_exp > 4) || (tempm->bo.num_late > 0) )
            tempm->bo.member_perm = PANDED;
        else if( (tempm->bo.num_bor < 5) && (tempm->bo.exceed_exp <= 4) && (tempm->bo.num_late == 0) )
            tempm->bo.member_perm = NOT_PANDED;

        while(tempb != NULL)// for borrowing list
        {
            if( (strcmp(tempm->bo.member_code , tempb->bo.member_code) == 0) && (tempb->bo.state == IN_PROGRESS) && (tempb->bo.ret == IN_TIME) )
            {
                if( (curr_date->year > tempb->bo.expir_date.year) || ( (curr_date->year == tempb->bo.expir_date.year) && (curr_date->month > tempb->bo.expir_date.month) ) || ( (curr_date->year == tempb->bo.expir_date.year) && (curr_date->month == tempb->bo.expir_date.month) && (curr_date->day > tempb->bo.expir_date.day) ) )
                {
                    tempb->bo.ret = LATE;
                    tempm->bo.num_late++;/*remember the variable of exceed_exp is going to be modified when member end borrowing node by doing returning proces*/
                    tempm->bo.member_perm = PANDED;
                }
            }
            tempb = tempb->next;
        }
        tempm = tempm->next;
        tempb = ptr_bor->head;
    }
}

/********************************************************************/
                    /******************* MEMBER SECTION WITH BORROWING FILE *******************/

/*see if this function is located here or in borrowing file*/

void member_list_bor(u8 *ptrmember_code , borrowing *ptrb , book *ptrbook)
{
    u8 flag = 0;
    borrowing_node *tempb = ptrb->head;
    book_node *tempo = ptrbook->head;

    printf("\t\t\t\t\t\t\t\t\t\t\t::member's borrowing transactions with no returning until now::\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t================================================================\n\n");
    printf("=================================================================================================================================================================================================================\n");
    printf("book name\t\t\t\tnumber of copies borrowed\tborrowing date\t   expiration date\n");
    printf("=================================================================================================================================================================================================================\n");
    while(tempb != NULL)
    {
        if( (strcmp(ptrmember_code , tempb->bo.member_code) == 0) && (tempb->bo.state == IN_PROGRESS) )//look for member's code in borrowing list and only if the borrowing node is in progress
        {
            flag = 1;
            while(tempo != NULL)// after finding borrowing node use book code stored inside it to look for book code in book list to get book name
            {
                if(strcmp(tempo->bo.book_code , tempb->bo.book_code) == 0)
                    printf("%-35s\t%d\t\t\t\t%d-%d-%d\t   %d-%d-%d\n" , tempo->bo.book_name , tempb->bo.num_copies , tempb->bo.borrow_date.day , tempb->bo.borrow_date.month , tempb->bo.borrow_date.year , tempb->bo.expir_date.day , tempb->bo.expir_date.month , tempb->bo.expir_date.year);
                tempo = tempo->next;
            }
        }
        tempb = tempb->next;
        tempo = ptrbook->head;
    }
    printf("=================================================================================================================================================================================================================\n");
    if(flag == 0)
    {
        delete_exact_lines(7);
        printf("\n\t\t\t\t\t\t!!member has no borrowing transaction in progress at the moment!!\n\n");
    }

}

/********************************************************************/

void print_one_member(member *ptrmember , borrowing *ptr_bor , book *ptr_book)
{
    u8 des = 'm';
    member_node *temp;
    date curr_date;

    member_node *ptr = (member_node *)malloc(sizeof(member_node));
    if(ptr == NULL)
    {
        printf("heap is full (please try to free some memory in heap first)...\n");;
        return;
    }

    if(ll_member_is_empty(ptrmember) == 1)
    {
        printf("member list is empty at the moment\n");
        return;
    }

    while(1)
    {
        printf("\t\t============================================\n");
        printf("\t\t**showing member's data in membership list**\n");
        printf("\t\t============================================\n\n");

        DMEMBER_COND check_member_code = member_code(ptrmember , ptr , MODIFY_MEMBER_FUNC);

        while(1)
        {
            if(check_member_code == WRONG_MEMBER_CODE)
            {
                printf("WARNING!! wrong member code format, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_member_code = member_code(ptrmember , ptr , MODIFY_MEMBER_FUNC);
            }
            else if(check_member_code == NOT_EXSISTED_MEMBER_CODE)
            {
                printf("WARNING!! member code is not listed in membership list, do you want to enter another member code (y/n)? ");

                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("WARNING!! member code is not listed in membership list, do you want to enter another member code (y/n)? ");
                    check_decision = check_des(&des);
                }
                getchar();
                if(des == 'y')
                {
                    delete_exact_lines(3);
                    check_member_code = member_code(ptrmember , ptr , MODIFY_MEMBER_FUNC);
                }
                else if(des == 'n')
                {
                    free(ptr);
                    ptr = NULL;
                    system("cls");
                    return;
                }
            }
            else if(check_member_code == EXSISTED_MEMBER_CODE)
                break;
        }

        delete_exact_lines(1);

        upd_bor_list(ptr_bor , ptrmember , &curr_date);// to update borrowing list before showing member's data
        getchar();
        delete_exact_lines(2);

        temp = ptrmember->head;
        while(temp  != NULL)
        {
            if(strcmp(temp->bo.member_code , ptr->bo.member_code) == 0)
                break;

            temp = temp->next;
        }
        printf("\t\t=======================================\n");
        printf("\t\t**data of member with code of (%s)**\n" , temp->bo.member_code);
        printf("\t\t=======================================\n\n");
        printf("=====================================================================================================================================================================================================================================\n\n");
        printf("name\t\t\t\t   gender\tage\t\tphone number\t\tgovernment\t\tdistrict\t\t\t\tstreet\t\t\t\t\thome number\n");
        printf("%-35s" , temp->bo.member_name);

        if(temp->bo.gender == 'm')
            printf("male\t\t");
        else if(temp->bo.gender == 'f')
            printf("female       ");

        printf("%d\t\t%-11s\t\t" , temp->bo.age , temp->bo.pho_num);
        show_gover_member(temp);
        printf("\t\t%-35s\t%-35s\t%d\n" , temp->bo.member_addre.distr , temp->bo.member_addre.distr , temp->bo.member_addre.home_no);

        printf("member's number of borrowing processes (no returning) : ");
        printf("%d \n" , temp->bo.num_bor);

        printf("member's number of late (no returning) : ");
        printf("%d \n" , temp->bo.num_late);

        printf("member's number of exceed expiration dates : ");
        printf("%d \n" , temp->bo.exceed_exp);

        printf("member's permission : ");
        if(temp->bo.member_perm == PANDED)
            printf("Panded \n");
        else if(temp->bo.member_perm == NOT_PANDED)
            printf("Not Panded \n");

        printf("\n=====================================================================================================================================================================================================================================\n\n");

        member_list_bor(temp->bo.member_code , ptr_bor , ptr_book);

        printf("do you want to show data for another member code (y/n)? ");
        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to show data for another member code (y/n)? ");
            check_decision = check_des(&des);
        }
        getchar();

        if(des == 'y')
        {
            system("cls");
            continue;
        }
        else if(des == 'n')
        {
            free(ptr);
            ptr = NULL;
            return;
        }
    }
}

/********************************************************************/

void print_member_list(member *ptr, borrowing *ptr_bor, book *ptr_book)
{
    date curr_date;
    if(ll_member_is_empty(ptr) == 1)
    {
        printf("member list is empty at the moment\n");
        return;
    }

    upd_bor_list(ptr_bor , ptr , &curr_date);// to update member list with current before printing all their data
    getchar();
    delete_exact_lines(2);

    member_node *tempm = ptr->head;
    printf("\t\t\t\t\t\t\t\t\t\t\t===================\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t::membership list::\n");
    printf("\t\t\t\t\t\t\t\t\t\t\t===================\n\n");
    printf("=====================================================================================================================================================================================================================================\n");
    while(tempm  != NULL)
    {
        printf("ID\tname\t\t\t\t   gender\tage\t\tphone number\t\tgovernment\t\tdistrict\t\t\t\tstreet\t\t\t\t\thome number\n");

        printf("%s\t%-35s" , tempm->bo.member_code , tempm->bo.member_name);

        if(tempm->bo.gender == 'm')
            printf("male\t\t");
        else if(tempm->bo.gender == 'f')
            printf("female       ");

        printf("%d\t\t%-11s\t\t" , tempm->bo.age , tempm->bo.pho_num);
        show_gover_member(tempm);
        printf("\t\t%-35s\t%-35s\t%d\n" , tempm->bo.member_addre.distr , tempm->bo.member_addre.distr , tempm->bo.member_addre.home_no);

        printf("member's number of borrowing processes (no returning) : ");
        printf("%d \n" , tempm->bo.num_bor);

        printf("member's number of late (no returning) : ");
        printf("%d \n" , tempm->bo.num_late);

        printf("member's number of exceed expiration dates : ");
        printf("%d \n" , tempm->bo.exceed_exp);

        printf("member's permission : ");
        if(tempm->bo.member_perm == PANDED)
            printf("Panded \n");
        else if(tempm->bo.member_perm == NOT_PANDED)
            printf("Not Panded \n");


        printf("\n=====================================================================================================================================================================================================================================\n\n");
        tempm = tempm->next;
    }
}

/********************************************************************/
/*in librarian function - section of deleting memeber
(1) header which tells us it's deleting section
(2) ask for member code like way in modification func.
*/
void delete_member(member *ptrmember, u8 member_code[6] , borrowing *ptrb , book *ptrbook , USAGE use)
{
    date curr_date;
    bool flag = 0;
    if(ll_member_is_empty(ptrmember) == 1)
    {
        printf("library has not listed members in the system!!\n");
        return;
    }

    if(use == DELETE_MEMBER_FUNC)
    {
        upd_bor_list(ptrb , ptrmember , &curr_date);
        getchar();
        delete_exact_lines(2);
    }


    member_node *temp = ptrmember->head;

    while(temp != NULL)
    {
        /*in order to delete member's account from library membership list, he or she must return all books which he or she borrowed first, so num_bor must equal zero*/
        if( (strcmp(temp->bo.member_code, member_code) == 0) && (temp->bo.num_bor == 0) )
        {
            if( (temp->prev == NULL) && (temp->next == NULL) )//node is the first and only in linked list
            {
                ptrmember->head = ptrmember->tail = NULL;
                printf("BE AWARE!! membership list is empty now\n");
            }
            else if(temp->prev == NULL)//node is the first in linked list
            {
                ptrmember->head = temp->next;
                temp->next->prev = NULL;
            }
            else if(temp->next == NULL)//node is the last in linked list
            {
                ptrmember->tail = temp->prev;
                temp->prev->next = NULL;
            }
            else//anywhere in the middle
            {
                temp->next->prev = temp->prev;
                temp->prev->next = temp->next;
            }
            free(temp);
            temp = NULL;

            flag = 1;
            break;
        }
        else if( (strcmp(temp->bo.member_code, member_code) == 0) && (temp->bo.num_bor != 0) )
        {
            printf("member with code (%s) cannot delete it's account until terminate all the borrowing processes left as follows:: \n" , member_code);
            member_list_bor(member_code , ptrb , ptrbook);
            flag = 2;
            break;
        }
        temp = temp->next;
    }

    if(flag == 1)
    {
        printf("\t\t=============================\n");
        printf("\t\t!!node successfully deleted!!\n");
        printf("\t\t=============================\n");
    }
}

                    /********************************************************************/
/********************************************************************/
                    /******************* BOOK SECTION WITH BORROWING FILE *******************/


void delete_book(book *ptr_book , borrowing *ptr_bor)
{
    bool flag = 0;// this flag is used to decide either to going to delete this book from book list or not or even this book is in book list or not to delete it in the first place
    u16 local_num_copies;
    AVALI local_book_av;
    u8 des;

    book_node *ptr_n = (book_node *)malloc(sizeof(book_node));
    if(ptr_n == NULL)
    {
        printf("heap is full, please try to free some memory first in heap...\n");
        return;
    }

    if(ll_book_is_empty(ptr_book) == 1)
    {
        printf("library has not listed books in the system!!\n");
        return;
    }

    borrowing_node *tempbor;
    book_node *temp;

    while(1)
    {
        flag = 0;
        des = 'd';

        printf("\t\t\t===========================\n");
        printf("\t\t\t::book's deleting section::\n");
        printf("\t\t\t===========================\n");


        DBOOK_COND check_book_code = book_code(ptr_book , ptr_n ,DELETE_BOOK_FUNC , &local_book_av , &local_num_copies);
        while(1)
        {
            if(check_book_code == WRONG_BOOK_CODE)
            {
                printf("WARNING!! unaccepted book code, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_book_code = book_code(ptr_book , ptr_n ,DELETE_BOOK_FUNC , &local_book_av , &local_num_copies);
            }
            else if(check_book_code == NOT_EXISTED_BOOK_CODE)
            {
                printf("WARNING!! book code is not listed in book list, do you want to enter another book code (y/n)? ");

                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("WARNING!! book code is not listed in book list, do you want to enter another book code (y/n)? ");
                    check_decision = check_des(&des);
                }
                getchar();
                if(des == 'y')
                {
                    delete_exact_lines(3);
                    check_book_code = book_code(ptr_book , ptr_n ,DELETE_BOOK_FUNC , &local_book_av , &local_num_copies);
                }
                else if(des == 'n')
                {
                free(ptr_n);
                ptr_n = NULL;
                return;
                }
            }
            else if(check_book_code == EXISITED_BOOK_CODE)
                break;
        }


        if(ll_bor_is_empty(ptr_bor) == 1)
            flag = 0;// no one have borrowed any copies of this book so it's safe to delete it from book list
        else
        {
            tempbor = ptr_bor->head;
            while(tempbor != NULL)
            {
                if( (strcmp(tempbor->bo.book_code , ptr_n->bo.book_code) == 0) && (tempbor->bo.state == IN_PROGRESS) )
                {
                    flag = 1;// which means there is number of copies of this book which is borrowed and need to get returned first before delete it from book list
                    break;
                }

                tempbor = tempbor->next;
            }
        }

        if(flag == 0)//it's safe to delete this book from book list of library system
        {
            temp = ptr_book->head;
            while(temp != NULL)
            {
                if(strcmp(temp->bo.book_code , ptr_n->bo.book_code) == 0)
                {
                    if( (temp->prev == NULL) && (temp->next == NULL) )//node is the first and only in linked list
                    {
                        ptr_book->head = ptr_book->tail = NULL;
                        printf("BE AWARE!! book list is empty now\n");
                    }

                    else if(temp->prev == NULL)//node is the first in linked list
                    {
                        ptr_book->head = temp->next;
                        temp->next->prev = NULL;
                    }
                    else if(temp->next == NULL)//node is the last in linked list
                    {
                        ptr_book->tail = temp->prev;
                        temp->prev->next = NULL;
                    }
                    else//anywhere in the middle
                    {
                        temp->next->prev = temp->prev;
                        temp->prev->next = temp->next;
                    }
                    free(temp);
                    temp = NULL;
                    printf("\t\t=========================\n");
                    printf("\t\tbook successfully deleted\n");
                    printf("\t\t=========================\n");
                    break;
                }
                temp = temp->next;
            }

        }

        if(flag == 1)
        {
            printf("\t\t============================================================================\n");
            printf("\t\tbook with code of (%s) cannot be deleted due to some members borrowed it\n" , ptr_n->bo.book_code);
            printf("\t\t============================================================================\n");
        }

        printf("do you want to do deleting process for another book again (y/n)??");

        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do deleting process for another book again (y/n)??)");
            check_decision = check_des(&des);
        }

        getchar();

        if(des == 'y')
        {
            system("cls");
            continue;
        }
        else if(des == 'n')
        {
            free(ptr_n);
            ptr_n = NULL;
            return;
        }

    }
}

/********************************************************************/
