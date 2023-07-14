/********************************************************************/
/************** NAME : Eslam Osama Saad     *************************/
/************** DATE : 01 / 07 / 2023       *************************/
/************** VERSION : 1.0 			    *************************/
/************** SWC : console application 	*************************/
/********************************************************************/

#include<stdio.h>//for input output processes and getchar()
#include<string.h>//for strlen() and strcpy()
#include <stdlib.h>//for dynamic memory allocation

#include"LSTD_TYPES.h"
#include"utility_control.h"

/********************************************************************/

void erase_prev_lines(void)
{
    while(getchar() != '\n');//this line is usde to flush input buffer
    getchar();//to be able to see input message;
    printf("\x1b[1F");
    printf("\x1b[1F");
    printf("\x1b[1F");
    printf("\x1b[2K");
    printf("\n");
    printf("\x1b[2K");
    printf("\x1b[1F");
}

/********************************************************************/

void delete_exact_lines(u16 num_lines)
{
    for(u16 i = 0 ; i < num_lines ; i++)
        printf("\x1b[1F");

    for(u16 j = 0 ; j < num_lines ; j++)
    {
        printf("\x1b[2K");
        printf("\n");
    }

    for(u16 t = 0 ; t < num_lines ; t++)
        printf("\x1b[1F");
}

/********************************************************************/

des_state check_des(u8 *ptr_des)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_des = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return
    gets(local_des);

    x = strlen(local_des);
    if(x != 1)
    {
        free(local_des);
        local_des = NULL;
        return WRONG_DES_FORMAT;
    }
    else if( !( (local_des[0] == 'y') || (local_des[0] == 'n') ) )
    {
        free(local_des);
        local_des = NULL;
        return WRONG_DES_FORMAT;
    }
    *ptr_des = local_des[0];
    free(local_des);
    local_des = NULL;
    return ok_des;
}

/********************************************************************/

choice_state check_choice(u16 *ptr_choice)
{
    u16  x = 150;// it's going to be erased after function return
    u8 *local_choice = (u8 *)malloc(x * sizeof(u8));// using dynamic memory allocation inorder to be able to erase it at the function return
    u16 max_u16_val = 65535;

    printf("please enter your choice = ");
    gets(local_choice);

    x = strlen(local_choice);
    if( (x > 5) || (x == 0) )// in case user entered enter only or counts of characters higher than 5
    {
        free(local_choice);
        local_choice = NULL;
        return WRONG_CHOICE_FORMAT;
    }
    else// we need to make sure all the inputs are digits
    {
        for(u16 i = 0 ; i < x ; i++)
        {
            if( (local_choice[i] < '0') || (local_choice[i] > '9') )
            {
                free(local_choice);
                local_choice = NULL;
                return WRONG_CHOICE_FORMAT;
            }
        }

    }

    if(atoi(local_choice) > max_u16_val)//in case user entered value higher than 65535
    {
        free(local_choice);
        local_choice = NULL;
        return WRONG_CHOICE_FORMAT;
    }

    *ptr_choice = atoi(local_choice);
    free(local_choice);
    local_choice = NULL;
    return ok_choice;
}

/********************************************************************/
