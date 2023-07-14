/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#include<stdio.h>//for input output processes and for getchar() function
#include<stdbool.h>// to use bool
#include<stdlib.h>//for dynamic memory allocation
#include<string.h>//to use strcpy() and strcmp() functions

#include"LSTD_TYPES.h"
#include"utility_control.h"

#include"book.h"

/********************************************************************/

void create_book_DLL(book *ptr_o)
{
   ptr_o->head = NULL;
   ptr_o->tail = NULL;
}

/********************************************************************/

bool ll_book_is_empty(book *ptrbook)
{
    return (!(ptrbook->head));
}

/********************************************************************/

DBOOK_COND book_name(book_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_book_name = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter name of the book: ");
    gets(local_book_name);

    x = strlen(local_book_name);

    if( (x < 10) || (x > 35) )
    {
        free(local_book_name);
        local_book_name = NULL;
        return WRONG_BOOK_NAME;
    }

    strcpy(ptr->bo.book_name , local_book_name);
    free(local_book_name);
    local_book_name = NULL;
    return ok_book;
}

/********************************************************************/
/*we used usage here to use this function in either ad_new_book() func. or modify_book() func.*/

DBOOK_COND search_book_with_name(book *ptrbook , u8 book_name[36] , USAGE_VAR usage)
{
    u16 num_copies;// max size of variable equal to 65535

    if(ll_book_is_empty(ptrbook) == 1)
        return EMPTY_BOOK_LL;

    book_node *temp = ptrbook->head;

    while(temp != NULL)
    {
        if(strcmp(temp->bo.book_name , book_name) == 0)
        {
            if(usage == ADD_NEW_BOOK_FUNC)
            {
                printf("book is already existed!!\n");

                DBOOK_COND check_book_numcopies = book_numcopies(&num_copies);
                while( check_book_numcopies == WRONG_BOOK_NUMCOPIES)
                {
                    printf("WARNING!! number of copies must be number, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_book_numcopies = book_numcopies(&num_copies);
                }
                temp->bo.num_copies += num_copies;

                if(temp->bo.num_copies > 0)
                    temp->bo.book_av = COPIES_AVAILABLE;
                else if(temp->bo.num_copies == 0)
                    temp->bo.book_av = COPIES_NOT_AVAILABLE;
            }

            return BOOK_EXISTED;
        }
        temp = temp->next;
    }
    return BOOK_NOT_EXISTED;
}

/********************************************************************/

DBOOK_COND book_numcopies(u16 *ptr_num_copies)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_book_numcopies = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return
    u16 max_u16_val = 65535;

    printf("please enter number of copies = ");
    gets(local_book_numcopies);

    x = strlen(local_book_numcopies);

    if( (x > 5) || (x == 0) )// in case user entered enter only or counts of characters higher than 5
    {
        free(local_book_numcopies);
        local_book_numcopies = NULL;
        return WRONG_BOOK_NUMCOPIES;
    }
    else// we need to make sure all the inputs are digits
    {
        for(u16 i = 0  ; i < x ; i++)
        {
            if( !( ( local_book_numcopies[i] >= '0') && (local_book_numcopies[i] <= '9') ) )
            {
                free(local_book_numcopies);
                local_book_numcopies = NULL;
                return WRONG_BOOK_NUMCOPIES;
            }
        }

    }
    if(atoi(local_book_numcopies) > max_u16_val)//in case user entered value higher than 65535
    {
        free(local_book_numcopies);
        local_book_numcopies = NULL;
        return WRONG_BOOK_NUMCOPIES;
    }

    *ptr_num_copies = atoi(local_book_numcopies);
    free(local_book_numcopies);
    local_book_numcopies = NULL;
    return ok_book;
}

/********************************************************************/

DBOOK_COND book_code(book *ptrbook , book_node *ptr , USAGE_VAR usage , AVALI *ptr_book_av , u16 *ptrcopies)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_book_code = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter code of book : ");
    gets(local_book_code);

    x = strlen(local_book_code);

    if(x != 4)
    {
        free(local_book_code);
        local_book_code = NULL;
        return WRONG_BOOK_CODE;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( (local_book_code[i] < '0') || (local_book_code[i] > '9') )
            {
                free(local_book_code);
                local_book_code = NULL;
                return WRONG_BOOK_CODE;
            }
        }
    }


    if(search_book_with_code(ptrbook , local_book_code , ptr_book_av , ptrcopies) == EXISITED_BOOK_CODE)
    {
        if(usage == ADD_NEW_BOOK_FUNC)// call this function in add_new_book() func.
        {
            free(local_book_code);
            local_book_code = NULL;
            return WRONG_BOOK_CODE;
        }

        else if( (usage == CREATE_BORROWING_NODE_FUNC) || (usage == DELETE_BOOK_FUNC) || (usage == MODIFY_BOOK_FUNC) )// call this function in create_borrowing_node() func. or modify_book() func.
        {
            strcpy(ptr->bo.book_code , local_book_code);
            free(local_book_code);
            local_book_code = NULL;
            return EXISITED_BOOK_CODE;
        }
    }

    if(usage == ADD_NEW_BOOK_FUNC)// call this function in add_new_book() func.
    {
        strcpy(ptr->bo.book_code , local_book_code);
        free(local_book_code);
        local_book_code = NULL;
        return ok_book;
    }
    else if( (usage == CREATE_BORROWING_NODE_FUNC) || (usage == DELETE_BOOK_FUNC) || (usage == MODIFY_BOOK_FUNC) )// call this function in create_borrowing_node() func. or modify_book() func.
    {
        free(local_book_code);
        local_book_code = NULL;
        return NOT_EXISTED_BOOK_CODE;
    }
}

/********************************************************************/

DBOOK_COND search_book_with_code(book *ptrbook , u8 book_code[5] , AVALI *ptr_book_av , u16 *ptrnum_copies)
{
    if(ll_book_is_empty(ptrbook) == 1)
        return EMPTY_BOOK_LL;

    book_node *temp = ptrbook->head;

    while(temp != NULL)
    {
        if(strcmp(temp->bo.book_code , book_code) == 0)
        {
            *ptr_book_av = temp->bo.book_av;
            *ptrnum_copies = temp->bo.num_copies;
            return EXISITED_BOOK_CODE;
        }
        temp = temp->next;
    }
    return NOT_EXISTED_BOOK_CODE;
}

/********************************************************************/

DBOOK_COND book_author(book_node *ptr)
{
     u16  x = 150;// it's going to be erased after function return
    u8 *local_book_author = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter author name of the book : ");
    gets(local_book_author);

    x = strlen(local_book_author);

    if( (x < 17) || (x > 35) )
    {
        free(local_book_author);
        local_book_author = NULL;
        return WRONG_AUTHOR_NAME;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( !( ( (local_book_author[i] >= 'a') && (local_book_author[i] <= 'z') ) || ( (local_book_author[i] >= 'A') && (local_book_author[i] <= 'Z') ) || (local_book_author[i] == 32) ) )
            {
                free(local_book_author);
                local_book_author = NULL;
                return WRONG_AUTHOR_NAME;
            }
        }
    }

    strcpy(ptr->bo.author , local_book_author);
    free(local_book_author);
    local_book_author = NULL;
    return ok_book;
}

/********************************************************************/

void add_new_book(book *ptrbook)
{
    AVALI local_book_av;
    u16 local_num_copies;
    u8 des;
    des_state check_decision;
    bool flag = 1;

    while(1)
    {
        des = 'b';//neutralize des value
        flag = 1;

        book_node *ptr_n = (book_node *)malloc(sizeof(book_node));

        if(ptr_n == NULL)
        {
            printf("heap is full, try to free some space in heap first\n");
            return;//general adding list
        }

        printf("\t\t=======================\n");
        printf("\t\t**book adding section**\n");
        printf("\t\t=======================\n");

        //===================================================================
        /*entering new book's name*/

        DBOOK_COND check_book_name = book_name(ptr_n);
        while(check_book_name == WRONG_BOOK_NAME)
        {
            printf("WARNING!! unaccepted book name, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_book_name = book_name(ptr_n);
        }

        if(search_book_with_name(ptrbook , ptr_n->bo.book_name , ADD_NEW_BOOK_FUNC) == BOOK_EXISTED)
        {
            free(ptr_n);
            ptr_n = NULL;
            flag = 0;
        }
        if(flag == 1)
        {
            //===================================================================
            /*entering new book's code*/

            DBOOK_COND check_book_code = book_code(ptrbook , ptr_n , ADD_NEW_BOOK_FUNC , &local_book_av , &local_num_copies);
            while(check_book_code == WRONG_BOOK_CODE)
            {
                printf("WARNING!! unaccepted book code, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_book_code = book_code(ptrbook , ptr_n , ADD_NEW_BOOK_FUNC , &local_book_av , &local_num_copies);
            }

            //===================================================================
            /*entering new book's author name*/

            DBOOK_COND check_book_author = book_author(ptr_n);
            while(check_book_author == WRONG_AUTHOR_NAME)
            {
                printf("WARNING!! unaccepted name of book author, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_book_author = book_author(ptr_n);
            }

            //===================================================================
            /*entering new book's number of copies*/

            DBOOK_COND check_book_numcopies = book_numcopies( &(ptr_n->bo.num_copies) );
            while(check_book_numcopies == WRONG_BOOK_NUMCOPIES)
            {
                printf("WARNING!! number of copies must be number, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_book_numcopies = book_numcopies( &(ptr_n->bo.num_copies) );
            }

            if(ptr_n->bo.num_copies > 0)
                ptr_n->bo.book_av = COPIES_AVAILABLE;
            else
                ptr_n->bo.book_av = COPIES_NOT_AVAILABLE;


            //=====================================================
            /*adding new book node in book list of library*/

            ptr_n->next = NULL;
            ptr_n->prev = NULL;

            if(ll_book_is_empty(ptrbook) == 1)// first node in library book list
            {
            ptrbook->head = ptr_n;
            ptrbook->tail = ptr_n;
            }

            else// just doing appending to book list
            {
                book_node *temp = ptrbook->head;

                while(temp != NULL)
                    temp = temp->next;

                ptr_n->prev = ptrbook->tail;
                ptrbook->tail->next = ptr_n;
                ptrbook->tail = ptr_n;
            }

            printf("\n\t\tbook with code (%s) and name (%s) successfully added in library\n\n", ptr_n->bo.book_code , ptr_n->bo.book_name);
        }

        printf("do you want to add new book again in library book list(y/n)?? ");
        des_state check_var_des =  check_des(&des);
        while(check_var_des == WRONG_DES_FORMAT)
        {
            printf("WARNING!! you must type either y or n, please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to add new book again in library book list(y/n)?? ");
            check_var_des =  check_des(&des);
        }

        getchar();
        if(des == 'y')
        {
            system("cls");
            continue;
        }
        else if(des == 'n')// break function and return back
            break;
    }// end bracket of while(1) of the whole function
}// end bracket of the function itself

/********************************************************************/

void modify_book(book *ptrbook)
{
    u16 choice;
    bool flag = 0 , key_same_book = 0;
    u8 des;
    AVALI local_book_av;
    u16 local_num_copies;
    book_node *temp;

    if(ll_book_is_empty(ptrbook) == 1)
    {
        printf("\t\t============================================\n");
        printf("\t\tlibrary has not listed books in the system!!\n");
        printf("\t\t============================================\n");
        getchar();
        system("cls");
        return;//return back to book editing list
    }

    book_node *ptr_n = (book_node *)malloc(sizeof(book_node));
    if(ptr_n == NULL)
    {
        printf("\t\t==================================================\n");
        printf("\t\theap is full, try to free some space in heap first\n");
        printf("\t\t==================================================\n");
        getchar();
        system("cls");
        return;
    }

    while(1)
    {
        flag = 0;
        des = 'm';

        printf("\t\t\t=================================\n");
        printf("\t\t\t::book's modification section::\n");
        printf("\t\t\t=================================\n");


        if(key_same_book == 0)//in case loop again to modify same book data
        {
            DBOOK_COND check_book_code = book_code(ptrbook , ptr_n ,MODIFY_BOOK_FUNC , &local_book_av , &local_num_copies);
            while(1)
            {
                if(check_book_code == WRONG_BOOK_CODE)
                {
                    printf("WARNING!! unaccepted book code, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_book_code = book_code(ptrbook , ptr_n ,MODIFY_BOOK_FUNC , &local_book_av , &local_num_copies);
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
                        check_book_code = book_code(ptrbook , ptr_n ,MODIFY_BOOK_FUNC , &local_book_av , &local_num_copies);
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

            temp = ptrbook->head;
            while(temp != NULL)
            {
                if(strcmp(temp->bo.book_code , ptr_n->bo.book_code) == 0)
                    break;
                temp = temp->next;
            }

            getchar();
            delete_exact_lines(2);
        }

        printf("current information of book with code of (%s):\n" , ptr_n->bo.book_code);
        printf("==========================================================\n");
        print_book_data(temp);

        printf("\n=====================================================================\n");
        printf("which of the following information do you want to change about the book:\n");
        printf("======================================================================\n\n");
        printf("(1) book name:\n");
        printf("(2) author of book:\n");
        printf("(3) number of copies available:\n");
        printf("(4) Exit: \n");
        printf("\n======================================================================\n");

        choice_state check_var_choice = check_choice(&choice);

        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("WARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_var_choice = check_choice(&choice);
        }

        switch(choice)
        {
            case 1:
                {
                    DBOOK_COND check_book_name = book_name(ptr_n);
                    DBOOK_COND check_book_name_avail = search_book_with_name(ptrbook , ptr_n->bo.book_name , MODIFY_BOOK_FUNC);
                    while( (check_book_name_avail == BOOK_EXISTED) || (check_book_name == WRONG_BOOK_NAME) )
                    {
                        printf("WARNING!! unacceptable new name of book, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_book_name = book_name(ptr_n);
                        check_book_name_avail = search_book_with_name(ptrbook , ptr_n->bo.book_name , MODIFY_BOOK_FUNC);
                    }

                    strcpy(temp->bo.book_name , ptr_n->bo.book_name);
                    printf("\t\t======================================\n");
                    printf("\t\tchanging book name successfully done!!\n");
                    printf("\t\t======================================\n");
                    flag = 1;
                    break;
                }

            case 2:
                {
                    DBOOK_COND check_book_author = book_author(ptr_n);
                    while(check_book_author == WRONG_AUTHOR_NAME)
                    {
                        printf("WARNING!! unacceptable new name of book author, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_book_author = book_author(ptr_n);
                    }

                    strcpy(temp->bo.author , ptr_n->bo.author);
                    printf("\t\t================================================\n");
                    printf("\t\tchanging author name of book successfully done!!\n");
                    printf("\t\t================================================\n");
                    flag = 1;
                    break;
                }

            case 3:
                {
                    DBOOK_COND check_book_numcopies = book_numcopies( &(ptr_n->bo.num_copies) );
                    while(check_book_numcopies == WRONG_BOOK_NUMCOPIES)
                    {
                        printf("WARNING!! number of copies must be number, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_book_numcopies = book_numcopies( &(ptr_n->bo.num_copies) );
                    }

                    temp->bo.num_copies = ptr_n->bo.num_copies;

                    if(temp->bo.num_copies > 0)
                        temp->bo.book_av = COPIES_AVAILABLE;
                    else if(temp->bo.num_copies == 0)
                        temp->bo.book_av = COPIES_NOT_AVAILABLE;

                    printf("\t\t================================================================\n");
                    printf("\t\tchanging number of copies available for book successfully done!!\n");
                    printf("\t\t================================================================\n");
                    flag = 1;
                    break;
                }

            case 4:
                des = 'b';
                break;

            default:
                printf("WARNING!! wrong choice not included in the list...\n");
                break;
        }// end bracket of switch on choice of user to modify book's data

        if(des == 'b')
        {
            getchar();
            free(ptr_n);
            ptr_n = NULL;
            return;
        }
        else if(flag == 1)
        {
            printf("information of book with code of (%s) after modification:\n" , ptr_n->bo.book_code);
            printf("===================================================================\n");
            print_book_data(temp);
        }

        printf("do you want to do another modification to the same book (y/n)? ");
        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do another modification to the same book (y/n)? ");
            check_decision = check_des(&des);
        }

        getchar();

        if(des == 'y')
        {
            system("cls");
            key_same_book = 1;
            continue;
        }

        key_same_book = 0;

        printf("do you want to do another modification to another book (y/n)? ");
        check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do another modification to another book (y/n)? ");
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
    }//end_bracket of while(1) loop of modify_book function
}//end_bracket of function itself

/********************************************************************/

void print_book_data(book_node *ptr)
{
    printf("====================================================================================================================================\n");
    printf("code\t\tname\t\t\t\t\tauthor name\t\tnumber of copies\t\tavailability\n");
    printf("====================================================================================================================================\n");
    if(ptr->bo.book_av == COPIES_AVAILABLE)
    {
        printf("%s\t\t%-35s\t%-25s\t%d\t\t\tcopies available\n" , ptr->bo.book_code , ptr->bo.book_name , ptr->bo.author , ptr->bo.num_copies);
    }
    else if(ptr->bo.book_av == COPIES_NOT_AVAILABLE)
        printf("%s\t\t%-35s\t%-25s\t%d\t\t\tcopies not available\n" , ptr->bo.book_code , ptr->bo.book_name , ptr->bo.author , ptr->bo.num_copies);
    printf("====================================================================================================================================\n");
}

/********************************************************************/

void print_one_book(book *ptrbook)
{
    u8 des;
    book_node *temp;

    if(ll_book_is_empty(ptrbook) == 1)
    {
        printf("library has not listed books in the system!!\n");
        return;//return back to book editing list
    }

    book_node *ptr_n = (book_node *)malloc(sizeof(book_node));
    if(ptr_n == NULL)
    {
        printf("heap is full, try to free some space in heap first\n");
        return;
    }
    while(1)
    {
        printf("\t\t\t\t\t\t\t\t\t====================================\n");
        printf("\t\t\t\t\t\t\t\t\t**showing book's data in book list**\n");
        printf("\t\t\t\t\t\t\t\t\t====================================\n\n");

        DBOOK_COND check_book_name = book_name(ptr_n);
        DBOOK_COND check_book_name_avail = search_book_with_name(ptrbook , ptr_n->bo.book_name , MODIFY_BOOK_FUNC);
        while(1)
        {
            if( (check_book_name == WRONG_BOOK_NAME) && (check_book_name_avail == BOOK_NOT_EXISTED) )
            {
                printf("WARNING!! unaccepted book name, please try again...\n");

                getchar();
                delete_exact_lines(3);

                check_book_name = book_name(ptr_n);
                check_book_name_avail = search_book_with_name(ptrbook , ptr_n->bo.book_name , MODIFY_BOOK_FUNC);
            }
            else if( (check_book_name == ok_book) && (check_book_name_avail == BOOK_NOT_EXISTED) )
            {
                printf("WARNING!! book is not listed in book list, do you want to enter another book name (y/n)? ");

                des_state check_decision = check_des(&des);
                while(check_decision == WRONG_DES_FORMAT)
                {
                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    printf("WARNING!! book is not listed in book list, do you want to enter another book name (y/n)? ");
                    check_decision = check_des(&des);
                }
                getchar();
                if(des == 'y')
                {
                    delete_exact_lines(3);
                    check_book_name = book_name(ptr_n);
                    check_book_name_avail = search_book_with_name(ptrbook , ptr_n->bo.book_name , MODIFY_BOOK_FUNC);
                }
                else if(des == 'n')
                {
                    free(ptr_n);
                    ptr_n = NULL;
                    return;
                }
            }
            else if( (check_book_name == ok_book) && (check_book_name_avail == BOOK_EXISTED) )
                break;
        }
        delete_exact_lines(1);

        temp = ptrbook->head;
        while(temp != NULL)
        {
            if(strcmp(temp->bo.book_name , ptr_n->bo.book_name) == 0)
                break;
            temp = temp->next;
        }

        printf("====================================================================================================================================\n");
        printf("code\t\tname\t\t\t\t\tauthor name\t\tnumber of copies\t\tavailability\n");
        printf("====================================================================================================================================\n");
        if(temp->bo.book_av == COPIES_AVAILABLE)
        {
            printf("%s\t\t%-35s\t%-25s\t%d\t\t\tcopies available\n" , temp->bo.book_code , temp->bo.book_name , temp->bo.author , temp->bo.num_copies);
        }
        else if(temp->bo.book_av == COPIES_NOT_AVAILABLE)
            printf("%s\t\t%-35s\t%-25s\t%d\t\t\tcopies not available\n" , temp->bo.book_code , temp->bo.book_name , temp->bo.author , temp->bo.num_copies);
        printf("====================================================================================================================================\n");

        printf("do you want to show data for another book (y/n)? ");
        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to show data for another book (y/n)? ");
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

void print_book_list(book *ptr)
{
    if(ll_book_is_empty(ptr) == 1)
    {
        printf("library has not listed books in the system!!\n");
        return;
    }

    printf("\t\t\t\t\t\t\t\t\t=============\n");
    printf("\t\t\t\t\t\t\t\t\t::book list::\n");
    printf("\t\t\t\t\t\t\t\t\t=============\n\n");
    printf("====================================================================================================================================\n");
    printf("code\t\tname\t\t\t\t\tauthor name\t\tnumber of copies\t\tavailability\n");
    printf("====================================================================================================================================\n");
    book_node *temp = ptr->head ;
    while(temp != NULL)
    {
        if(temp->bo.book_av == COPIES_AVAILABLE)
            printf("%s\t\t%-35s\t%-25s\t%d\t\t\tcopies available\n" , temp->bo.book_code , temp->bo.book_name , temp->bo.author , temp->bo.num_copies);

        else if(temp->bo.book_av == COPIES_NOT_AVAILABLE)
            printf("%s\t\t%-35s\t%-25s\t%d\t\t\tcopies not available\n" , temp->bo.book_code , temp->bo.book_name , temp->bo.author , temp->bo.num_copies);

        temp = temp->next;
    }

    printf("====================================================================================================================================\n");
}

/********************************************************************/
