/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#include<stdio.h>//for input output processes and getchar()
#include<stdbool.h>// to use bool
#include<stdlib.h>//for dynamic memory allocation
#include<string.h>//to use strcpy() & strcmp() & strlen() functions

#include"LSTD_TYPES.h"
#include"utility_control.h"

#include"member.h"

/********************************************************************/

void create_mem_DLL(member *ptr_m)
{
   ptr_m->head = NULL;
   ptr_m->tail = NULL;
}

/********************************************************************/

bool ll_member_is_empty(member *ptrmember)
{
    return (!(ptrmember->head));
}

/********************************************************************/

DMEMBER_COND member_name(member_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_member_name = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter member name : ");
    gets(local_member_name);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_member_name);
    if( (x < 17) || (x > 35))
    {
        free(local_member_name);
        local_member_name = NULL;
        return WRONG_MEMBER_NAME;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( !( ( (local_member_name[i] >= 'a') && (local_member_name[i] <= 'z') ) || ( (local_member_name[i] >= 'A') && (local_member_name[i] <= 'Z') ) || (local_member_name[i] == 32) ) )
            {
                free(local_member_name);
                local_member_name = NULL;
                return WRONG_MEMBER_NAME;
            }
        }
    }

    strcpy(ptr->bo.member_name , local_member_name);
    free(local_member_name);
    local_member_name = NULL;
    return ok_mem;
}

/********************************************************************/
/*
 usage is for differentiate use of function in add_new_member() func. or create_borrowing_node() func. in borrowing file
PRM *ptr_state_perm is used in  create_borrowing_node() func. to get if member allowed or not allowed of making borrowing process
*/
DMEMBER_COND member_code(member *ptrmember , member_node *ptr , USAGE usage)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_member_code = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter member code : ");
    gets(local_member_code);

    x = strlen(local_member_code);

    if(x != 5)
    {
        free(local_member_code);
        local_member_code = NULL;
        return WRONG_MEMBER_CODE;
    }

    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( (local_member_code[i] < '0') || (local_member_code[i] > '9') )
                {
                    free(local_member_code);
                    local_member_code = NULL;
                    return WRONG_MEMBER_CODE;
                }
        }
    }

    if(search_member_with_code(ptrmember , local_member_code) == EXSISTED_MEMBER_CODE)
    {
        if(usage == ADD_NEW_MEMBER_FUNC)// call this function in add_new_member() func.
        {
            free(local_member_code);
            local_member_code = NULL;
            return WRONG_MEMBER_CODE;
        }
        else if( (usage == CREATE_BORROWING_NODE) || (usage == MODIFY_MEMBER_FUNC) || (usage == DELETE_MEMBER_FUNC) )// call this function in add_new_member() func. or modify_member() func. or delete_member()
        {
            strcpy(ptr->bo.member_code , local_member_code);
            free(local_member_code);
            local_member_code = NULL;
            return EXSISTED_MEMBER_CODE;
        }
    }

    if(usage == ADD_NEW_MEMBER_FUNC)// call this function in add_new_member() func.
    {
        strcpy(ptr->bo.member_code , local_member_code);
        free(local_member_code);
        local_member_code = NULL;
        return ok_mem;
    }
    else if( (usage == CREATE_BORROWING_NODE) || (usage == MODIFY_MEMBER_FUNC) || (usage == DELETE_MEMBER_FUNC) )// call this function in add_new_member() func. or modify_member() func. or delete_member()
    {
        free(local_member_code);
        local_member_code = NULL;
        return NOT_EXSISTED_MEMBER_CODE;
    }
}

/********************************************************************/

DMEMBER_COND search_member_with_code(member *ptrmember, u8 member_code[6])
{
    if(ll_member_is_empty(ptrmember) == 1)
        return EMPTY_MEMBER_LL;

    member_node *temp = ptrmember->head;

    while(temp != NULL)
    {
        if(strcmp(temp->bo.member_code, member_code) == 0)
            return EXSISTED_MEMBER_CODE;
        temp = temp->next;
    }

    return NOT_EXSISTED_MEMBER_CODE;
}

/********************************************************************/

DMEMBER_COND mem_gender(member_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_mem_gender = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter gender ('m' male or 'f' female): ");
    gets(local_mem_gender);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_mem_gender);

    if(x != 1)
    {
        free(local_mem_gender);
        local_mem_gender = NULL;
        return WRONG_GENDER;
    }
    else if( !( (local_mem_gender[0] == 'm') || (local_mem_gender[0] == 'f') ) )
    {
        free(local_mem_gender);
        local_mem_gender = NULL;
        return WRONG_GENDER;
    }

    ptr->bo.gender = local_mem_gender[0];
    free(local_mem_gender);
    local_mem_gender = NULL;
    return ok_mem;
}

/********************************************************************/

DMEMBER_COND mem_age(member_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_mem_age = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter your age : ");
    gets(local_mem_age);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_mem_age);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_mem_age);
        local_mem_age = NULL;
        return WRONG_AGE;
    }
    //65535 is max size of u16
    else if( !( (atoi(local_mem_age) >= 1) && (atoi(local_mem_age) <= 65535) ) )
    {
        free(local_mem_age);
        local_mem_age = NULL;
        return WRONG_AGE;
    }

    ptr->bo.age = atoi(local_mem_age);
    free(local_mem_age);
    local_mem_age = NULL;
    return ok_mem;
}

/********************************************************************/

//Getting address from member :
//=============================
//1- governments
DMEMBER_COND mem_addre_gover(member_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_mem_addre_gover = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please choose from the above government list using it's number (your government) : ");
    gets(local_mem_addre_gover);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_mem_addre_gover);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_mem_addre_gover);
        local_mem_addre_gover = NULL;
        return WRONG_GOVER_NUM;
    }

    // in the choice list there are only 27 choices (governments in egypt)
    else if( !( (atoi(local_mem_addre_gover) >= 1) && (atoi(local_mem_addre_gover) <= 27) ) )
    {
        free(local_mem_addre_gover);
        local_mem_addre_gover = NULL;
        return WRONG_GOVER_NUM;
    }

    ptr->bo.member_addre.gover = atoi(local_mem_addre_gover);
    free(local_mem_addre_gover);
    local_mem_addre_gover = NULL;
    return ok_mem;
}

/********************************************************************/

//2- district
DMEMBER_COND mem_addre_distr(member_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_mem_addre_distr = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter which district in the government choosen : ");
    gets(local_mem_addre_distr);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_mem_addre_distr);

    if( (x < 8) || (x > 35) )
    {
        free(local_mem_addre_distr);
        local_mem_addre_distr = NULL;
        return WRONG_DISTR_FORMAT;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( !( ( (local_mem_addre_distr[i] >= 'a') && (local_mem_addre_distr[i] <= 'z') ) || ( (local_mem_addre_distr[i] >= 'A') && (local_mem_addre_distr[i] <= 'Z') ) || (local_mem_addre_distr[i] == 32) ) )
            {
                free(local_mem_addre_distr);
                local_mem_addre_distr = NULL;
                return WRONG_DISTR_FORMAT;
            }
        }
    }

    strcpy(ptr->bo.member_addre.distr , local_mem_addre_distr);
    free(local_mem_addre_distr);
    local_mem_addre_distr = NULL;
    return ok_mem;
}

/********************************************************************/

//2- street
DMEMBER_COND mem_addre_stre(member_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_mem_addre_stre = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter which street in the district entered : ");
    gets(local_mem_addre_stre);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_mem_addre_stre);

    if( (x < 8) || (x > 35) )
    {
        free(local_mem_addre_stre);
        local_mem_addre_stre = NULL;
        return WRONG_STRE_FORMAT;
    }
    else if( !( (local_mem_addre_stre[x-1] == 't') && (local_mem_addre_stre[x-2] == 's') && (local_mem_addre_stre[x-3] == '.') ) )
    {
        free(local_mem_addre_stre);
        local_mem_addre_stre = NULL;
        return WRONG_STRE_FORMAT;
    }
    else
    {
        for(u16 i = 0 ; i < (x-3) ; i++)
        {
            if( !( ( (local_mem_addre_stre[i] >= 'a') && (local_mem_addre_stre[i] <= 'z') ) || ( (local_mem_addre_stre[i] >= 'A') && (local_mem_addre_stre[i] <= 'Z') ) || (local_mem_addre_stre[i] == 32) ) )
            {
                free(local_mem_addre_stre);
                local_mem_addre_stre = NULL;
                return WRONG_STRE_FORMAT;
            }
        }
    }

    strcpy(ptr->bo.member_addre.street , local_mem_addre_stre);
    free(local_mem_addre_stre);
    local_mem_addre_stre = NULL;
    return ok_mem;
}

/********************************************************************/

DMEMBER_COND mem_addre_home_num(member_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_mem_addre_home_num = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter your home number : ");
    gets(local_mem_addre_home_num);//we are using gets() because scanf() do not accept spaces and we need them in getting name of member

    x = strlen(local_mem_addre_home_num);

    //important to prevent user from press enter at the start of getting input
    if(x == 0)
    {
        free(local_mem_addre_home_num);
        local_mem_addre_home_num = NULL;
        return WRONG_HOME_NUM_FORMAT;
    }
    //65535 is max size of u16
    else if( !( (atoi(local_mem_addre_home_num) >= 1) && (atoi(local_mem_addre_home_num) <= 65535) ) )
    {
        free(local_mem_addre_home_num);
        local_mem_addre_home_num = NULL;
        return WRONG_HOME_NUM_FORMAT;
    }

    ptr->bo.member_addre.home_no = atoi(local_mem_addre_home_num);
    free(local_mem_addre_home_num);
    local_mem_addre_home_num = NULL;
    return ok_mem;
}

/********************************************************************/

DMEMBER_COND member_phonnum(member_node *ptr)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_member_phonnum = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return

    printf("please enter member phone number : ");
    gets(local_member_phonnum);

    x = strlen(local_member_phonnum);

    if(x != 11)
    {
        free(local_member_phonnum);
        local_member_phonnum = NULL;
        return WRONG_MEMBER_PHONNUM;
    }
    else
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( (local_member_phonnum[i] < '0') || (local_member_phonnum[i] > '9') )
            {
                free(local_member_phonnum);
                local_member_phonnum = NULL;
                return WRONG_MEMBER_PHONNUM;
            }
        }
    }

    strcpy(ptr->bo.pho_num , local_member_phonnum);
    free(local_member_phonnum);
    local_member_phonnum = NULL;
    return ok_mem;
}

/********************************************************************/

void print_list_gover(void)
{
    printf("(1) Alexandria\n");
    printf("(2) Aswan\n");
    printf("(3) Asyut\n");
    printf("(4) Beheira\n");
    printf("(5) BeniSuef\n");
    printf("(6) Cairo\n");
    printf("(7) Dakahlia\n");
    printf("(8) Damietta\n");
    printf("(9) Faiyum\n");
    printf("(10) Gharbia\n");
    printf("(11) Giza\n");
    printf("(12) Ismailia\n");
    printf("(13) Kafr El-Sheikh\n");
    printf("(14) Luxor\n");
    printf("(15) Matruh\n");
    printf("(16) Minya\n");
    printf("(17) Monufia\n");
    printf("(18) New Valley\n");
    printf("(19) North Sinai\n");
    printf("(20) Port Said\n");
    printf("(21) Qalyubia\n");
    printf("(22) Qena\n");
    printf("(23) Red Sea\n");
    printf("(24) Sharqia\n");
    printf("(25) Sohag\n");
    printf("(26) South Sinai\n");
    printf("(27) Suez\n");
}

/********************************************************************/

void show_gover_member(member_node *ptr)
{
   switch(ptr->bo.member_addre.gover)
   {
       case Alexandria:     printf("Alexandria    ");             break;
       case Aswan:          printf("Aswan         ");             break;
       case Asyut:          printf("Asyut         ");             break;
       case Beheira:        printf("Beheira       ");             break;
       case BeniSuef:       printf("Beni-Suef     ");             break;
       case Cairo:          printf("Cairo         ");             break;
       case Dakahlia:       printf("Dakahlia      ");             break;
       case Damietta:       printf("Damietta      ");             break;
       case Faiyum:         printf("Faiyum        ");             break;
       case Gharbia:        printf("Gharbia       ");             break;
       case Giza:           printf("Giza          ");             break;
       case Ismailia:       printf("Ismailia      ");             break;
       case KafrEl_Sheikh:  printf("Kafr El-Sheikh");             break;
       case Luxor:          printf("Luxor         ");             break;
       case Matruh:         printf("Matruh        ");             break;
       case Minya:          printf("Minya         ");             break;
       case Monufia:        printf("Monufia       ");             break;
       case NewValley:      printf("New Valley    ");             break;
       case NorthSinai:     printf("North Sinai   ");             break;
       case PortSaid:       printf("Port Said     ");             break;
       case Qalyubia:       printf("Qalyubia      ");             break;
       case Qena:           printf("Qena          ");             break;
       case RedSea:         printf("Red Sea       ");             break;
       case Sharqia:        printf("Sharqia       ");             break;
       case Sohag:          printf("Sohag         ");             break;
       case SouthSinai:     printf("South Sinai   ");             break;
       case Suez:           printf("Suez          ");             break;
   }
}

/********************************************************************/

void add_new_member(member *ptrmember)
{
    u8 des;
    bool flag_repeated_account = 0;
    des_state check_decision;

    while(1)
    {
        des = 'b';
        flag_repeated_account = 0;

        member_node *ptr_n = (member_node *)malloc(sizeof(member_node));

        if(ptr_n == NULL)
        {
            printf("heap is full, try to free some space in heap first\n");
            return;//general adding list
        }

        printf("\t\t=========================\n");
        printf("\t\t**member adding section**\n");
        printf("\t\t=========================\n");

        //===================================================================
        /*entering new member's name*/

        DMEMBER_COND check_member_name = member_name(ptr_n);
        while(check_member_name == WRONG_MEMBER_NAME)
        {
            printf("WARNING!! unaccepted member name, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_member_name = member_name(ptr_n);
        }

        //===================================================================
        /*entering new member's code*/

        DMEMBER_COND check_member_code = member_code(ptrmember, ptr_n , ADD_NEW_MEMBER_FUNC);
        while(check_member_code == WRONG_MEMBER_CODE)
        {
            printf("WARNING!! unaccepted member code, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_member_code = member_code(ptrmember, ptr_n , ADD_NEW_MEMBER_FUNC);
        }

        //===================================================================
        /*getting member gender*/

        DMEMBER_COND check_mem_gender = mem_gender(ptr_n);
        while(check_mem_gender == WRONG_GENDER)
        {
            printf("WARNING!! gender is either m or f, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_mem_gender = mem_gender(ptr_n);
        }

        //===================================================================
        /*getting member age*/

        DMEMBER_COND check_mem_age = mem_age(ptr_n);
        while(check_mem_age == WRONG_AGE)
        {
           printf("WARNING!! wrong age format, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_mem_age = mem_age(ptr_n);
        }

        //===================================================================
        /*getting member phone number*/
        DMEMBER_COND check_mem_phon_num = member_phonnum(ptr_n);
        while(check_mem_phon_num == WRONG_MEMBER_PHONNUM)
        {
            printf("WARNING!! wrong phone number format, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_mem_phon_num = member_phonnum(ptr_n);
        }

        //===================================================================
        /*Getting Address of member*/

        //1- governments
        print_list_gover();

        DMEMBER_COND check_mem_addre_gover = mem_addre_gover(ptr_n);
        while(check_mem_addre_gover == WRONG_GOVER_NUM)
        {
            printf("WARNING!! please choose the number of your government from the above list of governments...\n");

            getchar();
            delete_exact_lines(3);

            check_mem_addre_gover = mem_addre_gover(ptr_n);
        }

        delete_exact_lines(28);
        printf("government name : ");
        show_gover_member(ptr_n);
        printf("\n");

        //2- district
        DMEMBER_COND check_mem_addre_distr = mem_addre_distr(ptr_n);
        while(check_mem_addre_distr == WRONG_DISTR_FORMAT)
        {
            printf("WARNING!! wrong district format, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_mem_addre_distr = mem_addre_distr(ptr_n);
        }

        //3- street name
        DMEMBER_COND check_mem_addre_stre = mem_addre_stre(ptr_n);
        while(check_mem_addre_stre == WRONG_STRE_FORMAT)
        {
            printf("WARNING!! wrong street format (stre_name.st), please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_mem_addre_stre = mem_addre_stre(ptr_n);
        }

        //4- home number
        DMEMBER_COND check_mem_addre_home_num = mem_addre_home_num(ptr_n);
        while(check_mem_addre_home_num == WRONG_HOME_NUM_FORMAT)
        {
            printf("WARNING!! home number must be integer value, please try again...\n");

            getchar();
            delete_exact_lines(3);

            check_mem_addre_home_num = mem_addre_home_num(ptr_n);
        }

        //=========================================================================================================================================================================================================

        member_node *temp_rep = ptrmember;
        while(temp_rep != NULL)
        {
            /*using (name - address - phone number) to identify if applicant have another account (membership) or not and if yes stop process of making another membership*/
            if( ( strcmp(temp_rep->bo.member_name , ptr_n->bo.member_name) == 0 ) && (temp_rep->bo.member_addre.gover == ptr_n->bo.member_addre.gover) && ( strcmp(temp_rep->bo.member_addre.distr , ptr_n->bo.member_addre.distr) == 0 ) && ( strcmp(temp_rep->bo.member_addre.street , ptr_n->bo.member_addre.street) == 0 ) && ( temp_rep->bo.member_addre.home_no == ptr_n->bo.member_addre.home_no ) && ( strcmp(temp_rep->bo.pho_num , ptr_n->bo.pho_num) == 0 ) )
            {
                printf("WARNING!! the applicant is already having a membership (account) and it's forbidden to have 2 accounts...\n");
                printf("NOTE THAT -> the current application of entering a new member have been erased \n");
                free(ptr_n);
                ptr_n = NULL;
                flag_repeated_account = 1;
                break;
            }
            temp_rep = temp_rep->next;
        }

        if(flag_repeated_account == 1)
        {
            printf("do you want to continue in add new member again in library membership list(y/n)?? ");
            check_decision =  check_des(&des);
            while(check_decision == WRONG_DES_FORMAT)
            {
                printf("WARNING!! you must type either y or n, please try again...\n");

                getchar();
                delete_exact_lines(3);

                printf("do you want to continue in add new member again in library membership list(y/n)?? ");
                check_decision =  check_des(&des);
            }

            getchar();
            if(des == 'y')
            {
                system("cls");
                continue;
            }
            else if(des == 'n')// break function and return back
                break;
        }

        //=========================================================================================================================================================================================================

        /*========================================================================================================================*/
        /*initially number of borrowing processes done by member, number of late returning, and times of exceeding expiration date
         equal to zero and state of member permission of borrowing is not_panded*/

        ptr_n->bo.num_bor = ptr_n->bo.num_late = ptr_n->bo.exceed_exp =  0;
        ptr_n->bo.member_perm = NOT_PANDED;
        /*========================================================================================================================*/

        ptr_n->next = NULL;
        ptr_n->prev = NULL;

        if(ll_member_is_empty(ptrmember) == 1)//first node in member list
        {
            ptrmember->head = ptr_n;
            ptrmember->tail = ptr_n;
        }

        else//just doing appending for doubly linked list of member
        {
            member_node *tempm = ptrmember->head;

            while(tempm != NULL)
                tempm = tempm->next;

            ptr_n->prev = ptrmember->tail;
            ptrmember->tail->next = ptr_n;
            ptrmember->tail = ptr_n;
        }

        printf("\n\t\tmember with name (%s) and code (%s) successfully added in library membership list\n\n", ptr_n->bo.member_name, ptr_n->bo.member_code);

        printf("do you want to add new member again in library membership list(y/n)?? ");
        des_state check_var_des =  check_des(&des);
        while(check_var_des == WRONG_DES_FORMAT)
        {
            printf("WARNING!! you must type either y or n, please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to add new member again in library membership list(y/n)?? ");
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

void modify_member(member *ptrmember)
{
    u16 choice;
    bool flag = 0 , key_same_mem = 0;
    u8 des;
    member_node *temp;

    if(ll_member_is_empty(ptrmember) == 1)
    {
        printf("\t\t==============================================\n");
        printf("\t\tlibrary has not listed members in the system!!\n");
        printf("\t\t==============================================\n");
        return;
    }

    member_node *ptr_n = (member_node *)malloc(sizeof(member_node));
    if(ptr_n == NULL)
    {
        printf("\t\t==================================================\n");
        printf("\t\theap is full, try to free some space in heap first\n");
        printf("\t\t==================================================\n");
        return;
    }

    while(1)
    {
        des = 'm';

        printf("\t\t=================================\n");
        printf("\t\t::member's modification section::\n");
        printf("\t\t=================================\n");

        if(key_same_mem == 0)//in case loop again to modify same member data
        {
            DMEMBER_COND check_member_code = member_code(ptrmember , ptr_n , MODIFY_MEMBER_FUNC);

            while(1)
            {
                if(check_member_code == WRONG_MEMBER_CODE)
                {
                    printf("WARNING!! wrong memeber code format, please try again...\n");

                    getchar();
                    delete_exact_lines(3);

                    check_member_code = member_code(ptrmember , ptr_n , MODIFY_MEMBER_FUNC);
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
                        check_member_code = member_code(ptrmember , ptr_n , MODIFY_MEMBER_FUNC);
                    }
                    else if(des == 'n')
                    {
                        free(ptr_n);
                        ptr_n = NULL;
                        system("cls");
                        return;
                    }
                }
                else if(check_member_code == EXSISTED_MEMBER_CODE)
                    break;
            }

            temp = ptrmember->head;
            while(temp != NULL)
            {
                if(strcmp(temp->bo.member_code , ptr_n->bo.member_code) == 0)
                    break;
                temp = temp->next;
            }

            getchar();
            delete_exact_lines(2);

        }

        printf("member's data\n");
        printf("=============\n\n");
        print_member_data(temp);

        printf("\n======================================================================\n");
        printf("which of the following information do you want to change about the member:\n");
        printf("======================================================================\n\n");
        printf("(1) member's name:\n");
        printf("(2) member's gender:\n");
        printf("(3) member's age:\n");
        printf("(4) member's phone number:\n");
        printf("(5) member's government:\n");
        printf("(6) member's district:\n");
        printf("(7) member's street name:\n");
        printf("(8) member's home number:\n");
        printf("(9) Exit:\n");
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
                    DMEMBER_COND check_member_name = member_name(ptr_n);
                    while(check_member_name == WRONG_MEMBER_NAME)
                    {
                        printf("WARNING!! unacceptable new name of member, please try again...\n");

                        getchar();
                        delete_exact_lines(2);

                        check_member_name = member_name(ptr_n);
                    }
                    strcpy(temp->bo.member_name, ptr_n->bo.member_name);
                    printf("\t\t========================================\n");
                    printf("\t\tchanging member name successfully done!!\n");
                    printf("\t\t========================================\n");
                    flag = 1;
                    break;
                }

            case 2:
                {
                    DMEMBER_COND check_mem_gender = mem_gender(ptr_n);
                    while(check_mem_gender == WRONG_GENDER)
                    {
                        printf("WARNING!! gender is either m or f, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_mem_gender = mem_gender(ptr_n);
                    }
                    temp->bo.gender = ptr_n->bo.gender;
                    printf("\t\t============================================\n");
                    printf("\t\tchanging member's gender successfully done!!\n");
                    printf("\t\t============================================\n");
                    flag = 1;
                    break;
                }

            case 3:
                {
                    DMEMBER_COND check_mem_age = mem_age(ptr_n);
                    while(check_mem_age == WRONG_AGE)
                    {
                    printf("WARNING!! wrong age format, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_mem_age = mem_age(ptr_n);
                    }
                    temp->bo.age = ptr_n->bo.age;
                    printf("\t\t=========================================\n");
                    printf("\t\tchanging member's age successfully done!!\n");
                    printf("\t\t=========================================\n");
                    flag = 1;
                    break;
                }

            case 4:
                {
                    DMEMBER_COND check_mem_phon_num = member_phonnum(ptr_n);
                    while(check_mem_phon_num == WRONG_MEMBER_PHONNUM)
                    {
                        printf("WARNING!! wrong phone number format, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_mem_phon_num = member_phonnum(ptr_n);
                    }
                    strcpy(temp->bo.pho_num , ptr_n->bo.pho_num);
                    printf("\t\t==================================================\n");
                    printf("\t\tchanging member's phone number successfully done!!\n");
                    printf("\t\t==================================================\n");
                    flag = 1;
                    break;
                }

            case 5:
                {
                    print_list_gover();

                    DMEMBER_COND check_mem_addre_gover = mem_addre_gover(ptr_n);
                    while(check_mem_addre_gover == WRONG_GOVER_NUM)
                    {
                        printf("WARNING!! please choose the number of your government from the above list of governments...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_mem_addre_gover = mem_addre_gover(ptr_n);
                    }

                    /*delete list of govers and also line of asking for choose from list,
                    only show just which gover. member is from*/
                    delete_exact_lines(28);
                    show_gover_member(ptr_n);

                    temp->bo.member_addre.gover = ptr_n->bo.member_addre.gover;
                    printf("\t\t================================================\n");
                    printf("\t\tchanging member's government successfully done!!\n");
                    printf("\t\t================================================\n");
                    flag = 1;
                    break;
                }

            case 6:
                {
                    DMEMBER_COND check_mem_addre_distr = mem_addre_distr(ptr_n);
                    while(check_mem_addre_distr == WRONG_DISTR_FORMAT)
                    {
                        printf("WARNING!! wrong district format, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_mem_addre_distr = mem_addre_distr(ptr_n);
                    }
                    strcpy(temp->bo.member_addre.distr , ptr_n->bo.member_addre.distr);
                    printf("\t\t===============================================\n");
                    printf("\t\tchanging member's distract successfully done!!\n");
                    printf("\t\t===============================================\n");
                    flag = 1;
                    break;
                }

            case 7:
                {
                    DMEMBER_COND check_mem_addre_stre = mem_addre_stre(ptr_n);
                    while(check_mem_addre_stre == WRONG_STRE_FORMAT)
                    {
                        printf("WARNING!! wrong street format (stre_name.str), please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_mem_addre_stre = mem_addre_stre(ptr_n);
                    }
                    strcpy(temp->bo.member_addre.street , ptr_n->bo.member_addre.street);
                    printf("\t\t==================================================\n");
                    printf("\t\tchanging member's street name successfully done!!\n");
                    printf("\t\t==================================================\n");
                    flag = 1;
                    break;
                }

            case 8:
                {
                    DMEMBER_COND check_mem_addre_home_num = mem_addre_home_num(ptr_n);
                    while(check_mem_addre_home_num == WRONG_HOME_NUM_FORMAT)
                    {
                        printf("WARNING!! home number must be integer value, please try again...\n");

                        getchar();
                        delete_exact_lines(3);

                        check_mem_addre_home_num = mem_addre_home_num(ptr_n);
                    }
                    temp->bo.member_addre.home_no = ptr_n->bo.member_addre.home_no;
                    printf("\t\t==================================================\n");
                    printf("\t\tchanging member's home number successfully done!!\n");
                    printf("\t\t==================================================\n");
                    flag = 1;
                    break;
                }

            case 9:
                des = 'e';
                break;

            default:
                printf("WARNING!! wrong choice not included in the list...\n");
                break;
        }// end bracket of switch on choice of user to modify member's data

        if(des == 'e')
        {
            getchar();
            free(ptr_n);
            ptr_n = NULL;
            return;
        }
        else if(flag == 1)
        {
            printf("**member's data after modification**\n");
            printf("====================================\n\n");

            print_member_data(temp);
        }

        printf("do you want to do another modification to the same member (y/n)? ");
        des_state check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do another modification to the same member (y/n)? ");
            check_decision = check_des(&des);
        }

        getchar();

        if(des == 'y')
        {
            system("cls");
            key_same_mem = 1;
            continue;
        }

        key_same_mem = 0;

        printf("do you want to do another modification to another member (y/n)? ");
        check_decision = check_des(&des);
        while(check_decision == WRONG_DES_FORMAT)
        {
            printf("WARNING!! wrong decision format (decision is either y or n), please try again...\n");

            getchar();
            delete_exact_lines(3);

            printf("do you want to do another modification to another member (y/n)? ");
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
    }//end_bracket of while(1) loop of modify_member function
}//end_bracket of function itself

/********************************************************************/

void print_member_data(member_node *ptr_node)
{
    printf("=====================================================================================================================================================================================================================================\n\n");
    printf("name\t\t\t\t   gender\tage\t\tphone number\t\tgovernment\t\tdistrict\t\t\t\tstreet\t\t\t\t\thome number\n");
    printf("%-35s" , ptr_node->bo.member_name);

    if(ptr_node->bo.gender == 'm')
        printf("male\t\t");
    else if(ptr_node->bo.gender == 'f')
        printf("female       ");

    printf("%d\t\t%-11s\t\t" , ptr_node->bo.age , ptr_node->bo.pho_num);
    show_gover_member(ptr_node);
    printf("\t\t%-35s\t%-35s\t%d\n" , ptr_node->bo.member_addre.distr , ptr_node->bo.member_addre.distr , ptr_node->bo.member_addre.home_no);

    printf("\n=====================================================================================================================================================================================================================================\n\n");

}

/********************************************************************/
