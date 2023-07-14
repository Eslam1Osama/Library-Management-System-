/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#include<stdio.h>//for input output processes and getchar()
#include<stdlib.h>//for dynamic memory allocation
#include<stdbool.h>// to use bool

#include"LSTD_TYPES.h"
#include"utility_control.h"

#include"book.h"
#include"member.h"
#include"borrowing.h"

#include"front.h"

/********************************************************************/

void edit(book *ptrbook , member *ptrmember , borrowing *ptrbor)
{
    u8 des;
    u16 choice;
    des_state check_decision;
    choice_state check_var_choice;

    while(1)
    {
        des = 'e';

        printf("\t\t\t=================================\n");
        printf("\t\t\tediting section of library system\n");
        printf("\t\t\t=================================\n");

        printf("\t\t===================================================\n");
        printf("\t\twhich of the following do you want to edit:\n");
        printf("\t\t===================================================\n\n");
        printf("\t\t(1) member\n");
        printf("\t\t(2) book\n");
        printf("\t\t(3) Exit\n");
        printf("\n\t\t===================================================\n");

        check_var_choice = check_choice(&choice);

        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("WARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_var_choice = check_choice(&choice);
        }


        getchar();
        if(choice != 3)
            system("cls");

        switch(choice)
        {
            case 1://member
                while(1)
                {
                    des = 'e';

                    printf("\t\t\t========================================\n");
                    printf("\t\t\tmember editing section of library system\n");
                    printf("\t\t\t========================================\n");

                    member_node *ptr_n = (member_node *)malloc(sizeof(member_node));
                    if(ptr_n == NULL)
                    {
                        printf("\t\t==================================================\n");
                        printf("\t\theap is full, try to free some space in heap first\n");
                        printf("\t\t==================================================\n");
                        return;
                    }

                    printf("\t\t==========================================================================\n");
                    printf("\t\twhich of the following processes do you want to edit about member's list:\n");
                    printf("\t\t==========================================================================\n\n");
                    printf("\t\t(1) modify member\n");
                    printf("\t\t(2) delete member\n");
                    printf("\t\t(3) Exit\n");
                    printf("\n\t\t==========================================================================\n");

                    check_var_choice = check_choice(&choice);

                    while(check_var_choice == WRONG_CHOICE_FORMAT)
                    {
                        printf("WARNING!! choice is always a number, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_var_choice = check_choice(&choice);
                    }

                    getchar();
                    if(choice != 3)
                        system("cls");

                    switch(choice)
                    {
                        case 1://modify any member's info
                            modify_member(ptrmember);
                            break;

                        case 2://delete member from member's list
                            while(1)
                            {

                                des = 'e';

                                printf("\t\t\t=========================\n");
                                printf("\t\t\tmember's deleting section\n");
                                printf("\t\t\t=========================\n\n");

                                DMEMBER_COND check_member_code = member_code(ptrmember , ptr_n , DELETE_MEMBER_FUNC);

                                while(1)
                                {
                                    if(check_member_code == WRONG_MEMBER_CODE)
                                    {
                                        printf("WARNING!! wrong memeber code format, please try again...\n");

                                        getchar();
                                        delete_exact_lines(3);

                                        check_member_code = member_code(ptrmember , ptr_n , DELETE_MEMBER_FUNC);
                                    }
                                    else if(check_member_code == NOT_EXSISTED_MEMBER_CODE)
                                    {
                                        printf("WARNING!! member code is not listed in membership list, do you want to enter another member code (y/n)? ");

                                        check_decision = check_des(&des);
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
                                            check_member_code = member_code(ptrmember , ptr_n , DELETE_MEMBER_FUNC);
                                        }
                                        else if(des == 'n')
                                            break;
                                    }
                                    else if(check_member_code == EXSISTED_MEMBER_CODE)
                                        break;
                                }
                                if(des == 'n')
                                    break;


                                delete_member(ptrmember, ptr_n->bo.member_code , ptrbor , ptrbook , DELETE_MEMBER_FUNC);

                                printf("do you want repeat deleting process again to another member (y/n)?? ");
                                check_decision = check_des(&des);
                                while(check_decision == WRONG_DES_FORMAT)
                                {
                                    printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                                    getchar();
                                    delete_exact_lines(3);

                                    printf("do you want repeat deleting process again to another member (y/n)?? ");
                                    check_decision = check_des(&des);
                                }

                                getchar();
                                if(des == 'y')
                                {
                                    system("cls");
                                    continue;
                                }
                                else if(des == 'n')
                                    break;
                            }
                            break;

                        case 3://exit modifiy member list and return to edit list
                           des = 'm';
                           break;

                        default:
                            printf("wrong choice (not included in member list), please try again...\n");
                    }
                    if(des == 'm')
                    {
                        free(ptr_n);
                        ptr_n = NULL;
                        break;
                    }

                    else
                    {
                        printf("do you want to edit member list again (y/n)??");
                        check_decision = check_des(&des);
                        while(check_decision == WRONG_DES_FORMAT)
                        {
                            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                            getchar();
                            delete_exact_lines(3);

                            printf("do you want to edit member list again (y/n)??");
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
                            break;
                        }
                    }
                }
                break;

            case 2://book
                while(1)
                {
                    des = 'e';

                    printf("\t\t\t======================================\n");
                    printf("\t\t\tbook editing section of library system\n");
                    printf("\t\t\t======================================\n");

                    printf("\t\t========================================================================\n");
                    printf("\t\twhich of the following proccesses do you want to edit about book's list:\n");
                    printf("\t\t========================================================================\n\n");
                    printf("\t\t(1) modify book\n");
                    printf("\t\t(2) delete book\n");
                    printf("\t\t(3) Exit\n");
                    printf("\n\t\t==========================================================================\n");

                    check_var_choice = check_choice(&choice);

                    while(check_var_choice == WRONG_CHOICE_FORMAT)
                    {
                        printf("WARNING!! choice is always a number, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_var_choice = check_choice(&choice);
                    }


                    getchar();
                    if(choice != 3)
                        system("cls");

                    switch(choice)
                    {
                        case 1://modify any book's info
                            modify_book(ptrbook);
                            break;

                        case 2://delete book from book's list
                            delete_book(ptrbook , ptrbor);
                            break;

                        case 3://exit modifiy book list and return to edit list
                           des = 'b';
                           break;

                        default:
                            printf("wrong choice (not included in book list), please try again...\n");
                    }
                    if(des == 'b')
                        break;
                    else
                    {
                        printf("do you want to edit book list again (y/n)?? ");
                        check_decision = check_des(&des);
                        while(check_decision == WRONG_DES_FORMAT)
                        {
                            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                            getchar();
                            delete_exact_lines(3);

                            printf("do you want to edit book list again (y/n)?? ");
                            check_decision = check_des(&des);
                        }

                        getchar();
                        if(des == 'y')
                        {
                            system("cls");
                            continue;
                        }
                        else if(des == 'n')
                            break;
                    }
                }
                break;

            case 3://exit general edit and return to if you want to continue as librarian
                des = 't';
                break;

            default:
                printf("wrong choice (not included in general editing list), please try again...\n");
        }//switching on general list
        if(des == 't')//librarian choose to exit general editing list
            break;

        else//ask librarian if he or she want to continue in general editing list
        {
            printf("do you want to continue in general editing list (for membership list and book list) (y/n)??");
            check_decision = check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                getchar();
                delete_exact_lines(3);

                printf("do you want to continue in general editing list (for membership list and book list) (y/n)??");
                check_decision = check_des(&des);
            }

            getchar();
            if(des == 'y')
            {
                system("cls");
                continue;
            }
            else if(des == 'n')
                break;
        }//else end_bracket
    }//while(1) of  editing function
}// end_brack of edit function

/********************************************************************/

FRONT_COND getting_username(u8 mem_username[15])
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_username = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter UserName : ");
    gets(local_username);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_username);

    if(x == 0)
    {
        free(local_username);
        local_username = NULL;
        return WRONG_USERNAME;
    }

    if(strcmp(local_username , librar_username) != 0)
    {
        free(local_username);
        local_username = NULL;
        return WRONG_USERNAME;
    }


    strcpy(mem_username , local_username);
    free(local_username);
    local_username = NULL;
    return ok;
}

/********************************************************************/

FRONT_COND getting_passw(u8 mem_passw[10])
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_passw = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter Password : ");
    gets(local_passw);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_passw);

    if(x == 0)
    {
        free(local_passw);
        local_passw = NULL;
        return WRONG_PASSW;
    }

    else if(strcmp(local_passw , librar_password) != 0)
    {
        free(local_passw);
        local_passw = NULL;
        return WRONG_PASSW;
    }



    strcpy(mem_passw , local_passw);
    free(local_passw);
    local_passw = NULL;
    return ok;
}

/********************************************************************/
        /*************************   member part   *************************/

void GoTo_member_section(book *ptrbook , member *ptrmember , borrowing *ptrbor)
{
    u8 des = 'm';
    u16 choice;
    des_state check_decision;
    choice_state check_var_choice;

    while(1)
    {
        des = 'm';

        printf("\t\t================\n");
        printf("\t\tmember section**\n");
        printf("\t\t================\n\n");

        printf("=====================================================================================================\n\n");

        printf("(1) Show one member info.\n");
        printf("(2) Show one book info. \n");
        printf("(3) Show book list \n");
        printf("(4) Exist:\n");

        printf("\n\n=====================================================================================================\n");

        check_var_choice = check_choice(&choice);
        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("WARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_var_choice = check_choice(&choice);
        }

        getchar();
        if(choice != 4)
            system("cls");

        switch(choice)
        {
            case 1 :
                print_one_member(ptrmember , ptrbor , ptrbook);
                break;

            case 2:
                print_one_book(ptrbook);
                break;

            case 3:
                print_book_list(ptrbook);
                break;

            case 4:
                des = 't';// 't' stands for terminate
                break;

            default:
                printf("WARNING!! wrong choice....\n");
                break;
        }

        if(des == 't')
            return;
        else
        {
            printf("do you want to continue in member section (y/n)? ");
            check_decision = check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                getchar();
                delete_exact_lines(3);

                printf("do you want to continue in member section (y/n)? ");
                check_decision = check_des(&des);
            }

            getchar();
            if(des == 'y')
            {
                system("cls");
                continue;
            }
            else if(des == 'n')
                return;
        }
    }
}

/********************************************************************/
        /*************************   librarian part   *************************/

void GoTo_librarian_section(book *ptrbook , member *ptrmember , borrowing *ptrbor)
{
    u8 local_username[10];
    u8 local_password[9];
    des_state check_decision;
    choice_state check_var_choice;

    u8 des = 'm';
    u16 choice;

    printf("\t\t===================\n");
    printf("\t\tLibrarian section**\n");
    printf("\t\t===================\n\n");

    FRONT_COND check_lib_username = getting_username(local_username);
    while(check_lib_username == WRONG_USERNAME)
    {
        printf("WARNING!! wrong librarian user-name, please try again...\n");

        getchar();
        delete_exact_lines(3);

        check_lib_username = getting_username(local_username);
    }

    FRONT_COND check_lib_passw = getting_passw(local_password);
    while(check_lib_passw == WRONG_PASSW)
    {
        printf("WARNING!! wrong librarain password, please try again...\n");

        getchar();
        delete_exact_lines(3);

        check_lib_passw = getting_passw(local_password);
    }

    getchar();
    delete_exact_lines(3);

    while(1)
    {

        printf("=====================================================================================================\n\n");

        printf("(1) add member to membership list\n");
        printf("(2) add book to book list\n");
        printf("(3) General Editing List\n");
        printf("(4) Show one member info.\n");
        printf("(5) Show membership list \n");
        printf("(6) Show one book info. \n");
        printf("(7) Show book list \n");
        printf("(8) Show records of borrowing list \n");
        printf("(9) Borrowing Process\n");
        printf("(10) Returning Process\n");
        printf("(11) Exist:\n");

        printf("\n\n=====================================================================================================\n");

        check_var_choice = check_choice(&choice);
        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("WARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_var_choice = check_choice(&choice);
        }

        getchar();
        if(choice < 11)
            system("cls");

        switch(choice)
        {
            case 1 :
                add_new_member(ptrmember);
                break;

            case 2 :
                add_new_book(ptrbook);
                break;

            case 3 :
                edit(ptrbook , ptrmember , ptrbor);
                break;

            case 4:
                print_one_member(ptrmember , ptrbor , ptrbook);
                break;

            case 5:
                print_member_list(ptrmember , ptrbor , ptrbook);
                break;

            case 6:
                print_one_book(ptrbook);
                break;

            case 7:
                print_book_list(ptrbook);
                break;

            case 8:
                get_all_bor_data(ptrbor , ptrmember);
                break;

            case 9:
                create_borrowing_node(ptrbook , ptrmember , ptrbor);
                break;

            case 10:
                returning_action(ptrbor , ptrbook , ptrmember);
                break;

            case 11:
                des = 't';// 't' stands for terminate
                break;

            default:
                printf("WARNING!! wrong choice....\n");
                break;
        }

        if(des == 't')
            return;
        else
        {
            printf("do you want to continue in librarian section (y/n)? ");
            check_decision = check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                getchar();
                delete_exact_lines(3);

                printf("do you want to continue in librarian section (y/n)? ");
                check_decision = check_des(&des);
            }

            getchar();
            if(des == 'y')
            {
                system("cls");
                printf("\t\t===================\n");
                printf("\t\tLibrarian section**\n");
                printf("\t\t===================\n\n");
                continue;
            }
            else if(des == 'n')
                return;
        }
    }
}

/********************************************************************/

void LibraryGroundRules(void)
{
    printf("\t\t\t\t\t======================\n");
    printf("\t\t\t\t\tLibrary Ground Rules::\n");
    printf("\t\t\t\t\t======================\n\n");

    printf("==========================================================================================================\n\n");
    printf("(1) NOT MORE THAN 1 ACCOUNT FOR EACH MEMBER. \n");
    printf("(2) EACH BORROWING PROCESS HAS LIMIT OF 3 COPIES OF THE SAME BOOK. \n");
    printf("(3) THERE IS A LIMIT OF 5 TIMES OF BORROWING PROCESSES FOR EACH MEMBER WITHOUT RETURNING. \n");
    printf("(4) DO NOT EXCEED 4 TIMES OF LATE RETURNINGS OR YOUR MEMMBERSHIP IS GOING TO BE DELETED. \n");
    printf("(5) 1 LATE (EXCEEDING EXPIRATION DATE) WITH NO RETURN WILL FORBIDE YOU FROM MAKING ANY BORROWING PROCESS. \n");
    printf("(6) BRAKING ANY OF RULES NUM. (3 & 4 & 5) IS GOING TO MAKE YOU PANDED FOR MAKING ANY BORROWING PROCESS. \n");
    printf("\n==========================================================================================================\n");

}

/********************************************************************/

void entry_window(book *ptrbook , member *ptrmember , borrowing *ptrbor)
{
    u8 des = 'm';
    u16 choice;
    bool flag = 0;
    choice_state check_var_choice;
    des_state check_decision;

    while(1)
    {
        flag = 0;

        printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t\t\t\t\t\t\t=======================================\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t**welcome to El-safwa Public Library **\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t=======================================\n\n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t(1) you are Member \n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t(2) you are Librarian \n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t(3) Library Ground Rules \n");
        printf("\t\t\t\t\t\t\t\t\t\t\t\t(4) Exit \n");
        printf("\n\t\t\t\t\t\t\t\t\t\t\t\t=======================================\n\n");

        printf("\t\t\t\t\t\t\t\t\t\t\t\t");
        check_var_choice = check_choice(&choice);
        while(check_var_choice == WRONG_CHOICE_FORMAT)
        {
            printf("\t\t\t\t\t\t\t\t\t\t\t\tWARNING!! choice is always a number, please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            check_var_choice = check_choice(&choice);
        }

        getchar();
        if(choice <= 3)
            system("cls");

        switch(choice)
        {
            case 1 :
                GoTo_member_section(ptrbook , ptrmember , ptrbor);
                break;

            case 2:
                GoTo_librarian_section(ptrbook , ptrmember , ptrbor);
                break;

            case 3:
                LibraryGroundRules();
                break;

            case 4:
                des = 't';// 't' stands for terminate
                break;

            default:
                printf("\t\t\t\t\t\t\t\t\t\t\t\tWARNING!! wrong choice....\n");
                flag = 1;
                break;
        }

        if(des == 't')
            return;
        else
        {
            if(flag == 1) printf("\t\t\t\t\t\t\t\t\t\t\t\t");
            printf("do you want to return to library entry list (y/n)? ");
            check_decision = check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                if(flag == 1) printf("\t\t\t\t\t\t\t\t\t\t\t\t");
                printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

                getchar();
                delete_exact_lines(3);

                if(flag == 1) printf("\t\t\t\t\t\t\t\t\t\t\t\t");
                printf("do you want to return to library entry list (y/n)? ");
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
                free(ptrbook);
                ptrbook = NULL;

                free(ptrbor);
                ptrbor = NULL;

                free(ptrmember);
                ptrmember = NULL;
                return;
            }
        }
    }
}

/********************************************************************/
